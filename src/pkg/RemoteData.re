let maybe = (v, f) => BsAbstract.Option.maybe(~f, ~default=v);

type t('e, 'a) =
  | NotAsked
  | Loading
  | Failure('e)
  | Success('a);

let isNotAsked = v => switch v {
| NotAsked => true
| _ => false
};

let isLoading = v => switch v {
| Loading => true
| _ => false
};

let getFailure = v => switch v {
| Failure(err) => Some(err)
| _ => None
};

let getSuccess = v => switch v {
| Success(x) => Some(x)
| _ => None
};

let eq = (eqErr, eqVal, a, b) => switch a {
| NotAsked => isNotAsked(b)
| Loading => isLoading(b)
| Failure(err) => getFailure(b) |> maybe(false, eqErr(err))
| Success(v) => getSuccess(b) |> maybe(false, eqVal(v))
};
