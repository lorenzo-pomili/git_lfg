type state = {currentEvent: Event.event};

type action =
  | UpdateEvent(Event.event);

let renderPartecipant = (i, partecipant: Event.partecipant) =>
  <div
    className="partecipantInList" key={"partecipant: " ++ string_of_int(i)}>
    {ReasonReact.string(partecipant.name)}
  </div>;

let joinEvent = (event, send) =>
  switch (User.getUser()) {
  | None => ()
  | Some(user) =>
    Js.Promise.(
      EventsService.joinEvent(event, user)
      |> then_(newEvent => resolve(send(UpdateEvent(newEvent))))
      |> ignore
    )
  };
let component = ReasonReact.reducerComponent("EventDetail");

let make = (~event: Event.event, _) => {
  ...component,
  initialState: () => {currentEvent: event},

  reducer: (action, _state) =>
    switch (action) {
    | UpdateEvent(newEvent) => ReasonReact.Update({currentEvent: newEvent})
    },
  render: ({state, send}) =>
    <div className="eventDetailContainer">
      <div className="eventDetailName">
        {ReasonReact.string(state.currentEvent.name)}
      </div>
      <div className="partecipantsList">
        <div className="header"> {ReasonReact.string("Partecipants:")} </div>
        <div>
          {
            RenderHelpers.renderList(
              state.currentEvent.partecipants,
              renderPartecipant,
            )
          }
        </div>
      </div>
      <div
        className="joinButton"
        onClick={_e => joinEvent(state.currentEvent, send)}>
        {ReasonReact.string("Join Event")}
      </div>
    </div>,
};
