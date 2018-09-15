type t =
  | Github
  ;

let show = t => switch t {
| Github => "github.com"
};

let icon = t => switch t {
| Github => ""
};

let url = t => switch t {
| Github => Url.makeHttpsBase("github.com")
};
