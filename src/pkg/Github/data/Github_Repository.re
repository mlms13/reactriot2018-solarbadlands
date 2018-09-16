type t = {
  id: int,
  name: string,
  description: string,
  owner: Github_User.t,
  htmlUrl: string
};

let make = (id, name, description, owner, htmlUrl) =>
  { id, name, description, owner, htmlUrl };

let decode = json => {
  let ((<$>), (<*>)) = ResultOfDecodeFailure.InfixApply.((<$>), (<*>));
  let (field, int, string) = DecodeAsResult.(decodeField, decodeInt, decodeString);

  make
    <$> field("id", int, json)
    <*> field("name", string, json)
    <*> field("description", string, json)
    <*> field("owner", Github_User.decode, json)
    <*> field("html_url", string, json);
};
