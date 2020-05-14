let baseClass = "loading-input";
let component = ReasonReact.statelessComponent("LoadingInput");

let make = (text, loading, renderLoaded, _children) => {
  ...component,

  render: _ => {
    let containerClass = baseClass ++ "-container" ++ switch loading {
    | RemoteData.NotAsked | Loading => ""
    | Failure(_) => " is-error"
    | Success(_) => " is-success"
    };

    let prefix = switch loading {
    | NotAsked => ReasonReact.null
    | _ => ReasonReact.null /* TODO */
    };

    let inpt = <input className=baseClass value=text />;

    switch loading {
    | NotAsked =>
      <div className=containerClass>
        <input value=text />
      </div>

    | Failure(_)
    | Loading => <div className=containerClass />

    | Success(_v) =>
      <div>
        inpt
      </div>
    };
  }

};
