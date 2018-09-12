let component = ReasonReact.statelessComponent("Home");

let make = _ => {
  ...component,
  render: _self => <div> {ReasonReact.string("Home")} </div>,
};
