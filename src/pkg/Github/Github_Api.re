let (//) = Url.(//);

type error =
  | NetworkError
  | ResponseError
  | ParseError(DecodeFailure.t);

let mapErr = (fn, r) => switch r {
| Belt.Result.Ok(a) => Belt.Result.Ok(a)
| Belt.Result.Error(x) => Belt.Result.Error(fn(x))
};

let mapDecode = (decode, v) =>
  decode(v) |> mapErr(x => ParseError(x));

let decodeInner = (fut, decoder) =>
  fut |. Future.map(a => Belt.Result.flatMap(a, mapDecode(decoder)));

type response('a) = Future.t(Belt.Result.t('a, error));

let baseUrl = Url.makeHttpsBase("api.github.com");

let make = (~method=Fetch.Get, url: Url.t) => {
  let req = Fetch.RequestInit.make(
    ~method_ = method,
    ~headers = Fetch.HeadersInit.make({
      "Accept": "application/vnd.github.v3+json"
    }),
    ()
  );

  Fetch.fetchWithInit(Url.toString(url), req)
    |. FutureJs.fromPromise(_ => NetworkError);
};

let getJSON = url =>
  make(url) |. Future.flatMapOk(res =>
    Fetch.Response.json(res) |. FutureJs.fromPromise(_ => ResponseError)
  );

let getRepository = (user, repo) =>
  getJSON(baseUrl // "repos" // user // repo)
    |. decodeInner(Github_Repository.decode);
