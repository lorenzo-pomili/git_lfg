let component = ReasonReact.statelessComponent("EventDetail");

let make = (_, ~event: Event.event) => {
  ...component,
  render: _self => <div> {ReasonReact.string(event.name)} </div>,
};
