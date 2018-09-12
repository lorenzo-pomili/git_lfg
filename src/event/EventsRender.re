let renderList = l => ReasonReact.array(Array.of_list(l));

let renderEvent = (event: Event.event) =>
  <div> {ReasonReact.string(event.eventName)} </div>;

let component = ReasonReact.statelessComponent("EventsRender");

let make = (~events=[], _) => {
  ...component,
  render: _self =>
    <div> {renderList(Belt.List.map(events, renderEvent))} </div>,
};
