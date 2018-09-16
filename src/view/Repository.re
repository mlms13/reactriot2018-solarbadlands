type state = {
  service: RepoSource.t,
  user: string,
  repository: string
};

type action =
  | SetService(RepoSource.t)
  | SetUser(string)
  | SetRepository(string);

let component = ReasonReact.reducerComponent("SetRepository");

let make = (~onSubmit, _children) => {
  ...component,

  initialState: () => { service: Github, user: "atom", repository: "atom" },

  reducer: (action, state) => switch action {
  | SetService(s) => Update({ ...state, service: s })
  | SetUser(s) when s != state.user => Update({ ...state, user: s, repository: "" })
  | SetUser(_) => NoUpdate
  | SetRepository(s) => Update({ ...state, repository: s })
  },

  render: self => {
    let { service, user, repository } as state = self.state;
    let (/) = Url.(//);
    let baseUrl = RepoSource.url(service);
    let url = baseUrl / user / repository;

    <div className="changelog-set-repository">
      <h2 className="section-title is-active">{ReasonReact.string("1. Choose a Repository")}</h2>
      <span>{ReasonReact.string(url |> Url.toString)}</span>
      {
        (user != "" && repository != "") ?
        <button onClick={_ => onSubmit(state) }>{ReasonReact.string("Next")}</button> :
        ReasonReact.null
      }
    </div>
  }
};
