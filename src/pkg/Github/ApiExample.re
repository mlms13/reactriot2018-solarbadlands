type error('err) =
  | NetworkError
  | ExpectedJson
  | ParseError('err);

/**
 * Map one kind of Belt.Result.Error into another kind of Belt.Result.Error
 * e.g. (('err => 'otherError), Belt.Result.t('a, 'err)) => Belt.Result.t('a, 'otherError)
 */
let mapErr = (fn, r) => switch r {
| Belt.Result.Ok(a) => Belt.Result.Ok(a)
| Belt.Result.Error(x) => Belt.Result.Error(fn(x))
};

/**
 * Given a Future of Result where the Ok contains JSON and the Error contains an `error`
 * as defined above, and a `decode` function that can convert JSON into some type ('a)
 * or a parse error ('err), this function will decode the inner JSON, and return it as
 * a Future of Result of either Ok(parsedData) or Error(error('err))
 */
let decodeInner = (fut, decode) =>
  fut |. Future.map(jsonResult => {
    Belt.Result.flatMap(jsonResult, json => decode(json) |> mapErr(x => ParseError(x)))
  });

/**
 * Make a Get request to Github using the provided URL path. The "promise" is returned
 * as a Future of Result, where the Error would hold a NetworkError (defined above).
 */
let get = (relativeUrl: string) => {
  let fullUrl = "https://api.github.com" ++ relativeUrl;
  let req = Fetch.RequestInit.make(
    ~method_ = Fetch.Get,
    ~headers = Fetch.HeadersInit.make({
      "Accept": "application/vnd.github.v3+json"
    }),
    ()
  );

  Fetch.fetchWithInit(fullUrl, req)
    |. FutureJs.fromPromise(_ => NetworkError);
};

/**
 * Make a Get request to Github, parsing the response as JSON. The Error will hold
 * either a `NetworkError` if the request failed, or an `ExpectedJson` if the
 * response couldn't be parsed as JSON.
 */
let getJSON = url =>
  get(url) |. Future.flatMapOk(res =>
    Fetch.Response.json(res) |. FutureJs.fromPromise(_ => ExpectedJson)
  );

let getUser = (username) =>
  getJSON("/users/" ++ username)
    |. decodeInner(Github_User.decode);

let getRepository = (user, repo) =>
  getJSON("/repos/" ++ user ++ "/" ++ repo)
    |. decodeInner(Github_Repository.decode);
