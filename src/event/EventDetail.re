let renderPartecipant = (i, partecipant: Event.partecipant) =>
  <div key={"partecipant: " ++ string_of_int(i)}>
    {ReasonReact.string(partecipant.name)}
  </div>;

let component = ReasonReact.statelessComponent("EventDetail");

let make = (_, ~event: Event.event) => {
  ...component,
  render: _self =>
    <div>
      <div> {ReasonReact.string(event.name)} </div>
      <div>
        <div> {ReasonReact.string("Partecipants:")} </div>
        <div>
          {RenderHelpers.renderList(event.partecipants, renderPartecipant)}
        </div>
      </div>
      <div onClick={_e => ()}> {ReasonReact.string("Join Event")} </div>
    </div>,
};
