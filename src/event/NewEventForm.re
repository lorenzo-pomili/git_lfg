type state = {event: option(Event.event)};

type action =
  | EventNameChange(Event.event);

let changeEventName = (e, send) => {
  let name = ReactEvent.Form.target(e)##value;
  send(EventNameChange({name, partecipants: []}));
};

let component = ReasonReact.reducerComponent("NewEventForm");

let make = (~onCancel, ~onAdd, _) => {
  ...component,
  initialState: () => {event: None},
  reducer: (action, _state) =>
    switch (action) {
    | EventNameChange(event) => ReasonReact.Update({event: Some(event)})
    },
  render: self =>
    <div>
      <div>
        <span> {ReasonReact.string("Name: ")} </span>
        <input onChange={e => changeEventName(e, self.send)} />
      </div>
      <div onClick={_e => onAdd(self.state.event)}>
        {ReasonReact.string("Send")}
      </div>
      <div onClick=onCancel> {ReasonReact.string("Cancel")} </div>
    </div>,
};
