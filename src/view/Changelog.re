type state =
  | ChooseRepository
  | ConfigParser(RepoData.t)
  | ConfigRange(RepoData.t, /* TODO: Parser.t */)
  /* Possibly TODO, intermediate state after receiving commits, while parsing */
  | ShowChangelog(RepoData.t /* TODO: Parser, Range, RemoteData of Commits */)
  ;

type action =
  | SetRepository(RepoData.t)
  | SetParseRules
  | SetCommitRange
  | SetCommits /* TODO: RemoteData of commits */
  ;

let component = ReasonReact.reducerComponent("Changelog");

let make = _children => {
  ...component,

  initialState: () => ChooseRepository,

  reducer: (action, state) => switch (action, state) {
  | (SetRepository(repo), _) => Update(ConfigParser(repo))
  | (SetParseRules, ConfigParser(repo)) => Update(ConfigRange(repo))
  | (SetCommitRange, ConfigRange(repo)) => UpdateWithSideEffects(
      ShowChangelog(repo /*, TODO: Loading */),
      _self => () /* TODO: API call */
    )
  | (SetCommits, ShowChangelog(repo)) => Update(ShowChangelog(repo))
  | _ => NoUpdate
  },

  render: ({ state }) => {
    <div>
      <AppHeader />
      {
        switch state {
        | ChooseRepository =>
          <Repository />

        | _ => ReasonReact.string("Unfinished State")
        }
      }
    </div>
  }
};
