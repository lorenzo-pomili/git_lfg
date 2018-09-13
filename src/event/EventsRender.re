let renderList = l => ReasonReact.array(Array.of_list(l));

let renderEvent = (i, event: Event.event) =>
  <div key={"Event" ++ string_of_int(i)}>
    {ReasonReact.string(event.eventName)}
  </div>;

let component = ReasonReact.statelessComponent("EventsRender");

let make = (~events=[], _) => {
  ...component,
  render: _self =>
    <div> {renderList(Belt.List.mapWithIndex(events, renderEvent))} </div>,
};
