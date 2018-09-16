type workflow =
  | ChooseRepository
  | ConfigRange
  | ConfigParser
  /* Possibly TODO, intermediate state after receiving commits, while parsing */
  | ShowChangelog /* TODO: Parser, Range, RemoteData of Commits */
  ;

type state = {
  workflow: workflow,
  repo: RemoteData.t(Github.Api.error, Github.Repository.t)
};

type action =
  | PickRepo(Repository.state)
  | UpdateRepo(RemoteData.t(Github.Api.error, Github.Repository.t))
  | SetCommitRange
  | SetParseRules
  | SetCommits /* TODO: RemoteData of commits */
  ;

let component = ReasonReact.reducerComponent("Changelog");

let make = _children => {
  ...component,

  initialState: () => {
    workflow: ChooseRepository,
    repo: NotAsked
  },

  reducer: (action, state) => switch (action, state) {

  | (PickRepo({ user, repository }), _) => UpdateWithSideEffects(
    { repo: Loading, workflow: ConfigRange },
    self => Github.Api.getRepository(user, repository)
      |. Future.tapOk(v => self.send(UpdateRepo(Success(v))))
      |. Future.tapError(x => self.send(UpdateRepo(Failure(x))))
      |> ignore
  )

  | (UpdateRepo(data), _) => Update({ ...state, repo: data })

  | _ => NoUpdate

  /* | (SetParseRules, ConfigParser(repo)) => Update(ConfigRange(repo)) */
  /* | (SetCommitRange, ConfigRange(repo)) => UpdateWithSideEffects( */
      /* ShowChangelog(repo /*, TODO: Loading */), */
      /* _self => () TODO: API call */
    /* ) */
  /* | (SetCommits, ShowChangelog(repo)) => Update(ShowChangelog(repo)) */
  /* | _ => NoUpdate */
  },

  render: ({ state, send }) => {
    <div>
      <AppHeader />
      {
        switch (state.workflow, state.repo) {
        /* Step 1 */

        | (ChooseRepository, _) =>
          <Repository onSubmit={v => send(PickRepo(v))} />


        /* Step 2 */
        | (ConfigRange, NotAsked) | (ConfigRange, Loading) =>
          ReasonReact.string("LOADING")

        | (ConfigRange, Failure(_)) =>
          ReasonReact.string("FAILED")

        | (ConfigRange, Success(v)) =>
          ReasonReact.string("CONFIG RANGE, success!")

        | _ => ReasonReact.string("Unfinished State")
        }
      }
    </div>
  }
};
