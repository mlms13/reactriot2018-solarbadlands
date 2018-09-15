type protocol =
  | HTTP
  | HTTPS
  ;

type t = {
  protocol: protocol,
  host: string,
  port: option(int),
  path: array(string),
  /* search: Map.Make(string), */
  hash: option(string)
};

let protocolToString = a => switch a {
| HTTP => "http:"
| HTTPS => "https:"
}

let toString = ({ protocol, host, port, path, hash }) => {
  let maybe = (default, f) => BsAbstract.Option.maybe(~f, ~default);
  let portStr = maybe("", v => ":" ++ string_of_int(v), port);
  let pathStr = "/" ++ Js.Array.joinWith("/", path);
  let hashStr = maybe("", v => "#" ++ v, hash) ;

  protocolToString(protocol) ++ "//" ++ host ++ portStr ++ pathStr ++ hashStr;
};

let make = (~protocol, ~host, ~port=?, ~path=[||], ~hash=?, ()) =>
  { protocol, host, port, path, hash };

let makeBase = (protocol, host) => make(~protocol, ~host, ());
let makeHttpBase = host => makeBase(HTTP, host);
let makeHttpsBase = host => makeBase(HTTPS, host);

let addPath = (path, url) =>
  { ...url, path: Array.append(url.path, [|path|]) };

let (//) = (url, path) => addPath(path, url);
