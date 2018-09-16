type t = {
  login: string,
  id: int,
  avatarUrl: string,
};

let make = (login, id, avatarUrl) =>
  { login, id, avatarUrl };

let decode = json => {
  let ((<$>), (<*>)) = ResultOfDecodeFailure.InfixApply.((<$>), (<*>));
  let (field, int, string) = DecodeAsResult.(decodeField, decodeInt, decodeString);

  make
    <$> field("login", string, json)
    <*> field("id", int, json)
    <*> field("avatar_url", string, json);
};
