let component = ReasonReact.statelessComponent("AppHeader");

let make = _children => {
  ...component,

  render: _ =>
    <header className="app-header">
      <h1>{ReasonReact.string("Friendly Changelog")}</h1>
    </header>
};
