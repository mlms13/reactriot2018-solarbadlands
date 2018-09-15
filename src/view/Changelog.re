module Repository = Changelog_Repository;

type state =
  | ConfigRepository
  | ConfigParser(Repository.t)
  | ConfigRange(Repository.t, /* TODO: Parser.t */)
  /* Possibly TODO, intermediate state after receiving commits, while parsing */
  | ShowChangelog(Repository.t /* TODO: Parser, Range, RemoteData of Commits */)
  ;

type action =
  | SetRepository(Repository.t)
  | SetParseRules
  | SetCommitRange
  | SetCommits /* TODO: RemoteData of commits */
  ;

let component = ReasonReact.reducerComponent("Changelog");

let make = _children => {
  ...component,

  initialState: () => ConfigRepository,

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

  render: _self => {
    <div>
      <AppHeader />
      <div>
        {ReasonReact.string("Content goes here...")}
      </div>
    </div>
  }
};
