type state = {event: option(Event.event)};

type action =
  | GetEvent(Event.event);

let component = ReasonReact.reducerComponent("EventDetailLoader");

let make = (_, ~eventId: string) => {
  ...component,
  didMount: self =>
    Js.Promise.(
      EventsService.getEventDetail(eventId)
      |> then_(res => resolve(self.send(GetEvent(res))))
      |> ignore
    ),
  initialState: () => {event: None},
  reducer: (action, _state) =>
    switch (action) {
    | GetEvent(e) => ReasonReact.Update({event: Some(e)})
    },
  render: self =>
    <div>
      {
        switch (self.state.event) {
        | None => <div> {ReasonReact.string("Lodaing...")} </div>
        | Some(e) => <EventDetail event=e />
        }
      }
    </div>,
};
