let renderPartecipant = (i, partecipant: Event.partecipant) =>
  <div
    className="partecipantInList" key={"partecipant: " ++ string_of_int(i)}>
    {ReasonReact.string(partecipant.name)}
  </div>;

let component = ReasonReact.statelessComponent("EventDetail");

let make = (_, ~event: Event.event) => {
  ...component,
  render: _self =>
    <div className="eventDetailContainer">
      <div className="eventDetailName">
        {ReasonReact.string(event.name)}
      </div>
      <div className="partecipantsList">
        <div className="header"> {ReasonReact.string("Partecipants:")} </div>
        <div>
          {RenderHelpers.renderList(event.partecipants, renderPartecipant)}
        </div>
      </div>
      <div className="joinButton" onClick={_e => ()}>
        {ReasonReact.string("Join Event")}
      </div>
    </div>,
};
