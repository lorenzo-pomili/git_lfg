let renderList = l => ReasonReact.array(Array.of_list(l));

let goToDetail = id => ReasonReact.Router.push("/eventDetail/" ++ id);

let renderEvent = (i, event: Event.eventOfList) =>
  <div
    key={"Event" ++ string_of_int(i)} onClick={_e => goToDetail(event.id)}>
    {ReasonReact.string(event.eventName)}
  </div>;

let component = ReasonReact.statelessComponent("EventsRender");

let make = (~events=[], _) => {
  ...component,
  render: _self =>
    <div> {renderList(Belt.List.mapWithIndex(events, renderEvent))} </div>,
};
