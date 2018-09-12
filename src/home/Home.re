type state = {events: list(Event.event)};

type action =
  | InitEvents(list(Event.event));

let component = ReasonReact.reducerComponent("Home");

let make = _ => {
  ...component,
  initialState: () => {events: []},
  didMount: self =>
    Js.Promise.(
      EventsService.getAllEvents()
      |> then_(res => resolve(self.send(InitEvents(res))))
      |> ignore
    ),
  reducer: (action, _state) =>
    switch (action) {
    | InitEvents(el) => ReasonReact.Update({events: el})
    },
  render: self => <div> <EventsRender events={self.state.events} /> </div>,
};
