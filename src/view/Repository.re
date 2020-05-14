type dataFromText('a) = {
  text: string,
  data: RemoteData.t(Github.Api.error, 'a)
};

let component = ReasonReact.statelessComponent("ChooseRepository");

let make = (user, repo, ~onChangeUser, ~onChangeRepo, ~onSubmit, _children) => {
  ...component,

  render: self => {
    let userStr =
    <div className="changelog-set-repository">
      <h2 className="section-title is-active">{ReasonReact.string("1. Choose a Repository")}</h2>
      <span className="service">{ReasonReact.string("github.com")}</span>
      <span></span>
      <span></span>
      <span>{ReasonReact.string(url |> Url.toString)}</span>
      {
        (user != "" && repository != "") ?
        <button onClick={_ => onSubmit(state) }>{ReasonReact.string("Next")}</button> :
        ReasonReact.null
      }
    </div>
  }
};
