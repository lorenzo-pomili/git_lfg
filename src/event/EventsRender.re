type state = {addingNewEvent: bool};

type action =
  | AddingNewEvent(bool);

let changeAddingStatus = (send, adding) => send(AddingNewEvent(adding));

let goToDetail = id => ReasonReact.Router.push("/eventDetail/" ++ id);

let renderEvent = (i, event: Event.eventOfList) =>
  <div
    key={"Event" ++ string_of_int(i)} onClick={_e => goToDetail(event.id)}>
    {ReasonReact.string(event.eventName)}
  </div>;

let addEvent = event =>
  switch (event) {
  | None => ()
  | Some(e) => EventsService.addEvent(e) |> ignore
  };

let component = ReasonReact.reducerComponent("EventsRender");

let make = (~events=[], _) => {
  ...component,
  initialState: () => {addingNewEvent: false},
  reducer: (action, _state) =>
    switch (action) {
    | AddingNewEvent(adding) => ReasonReact.Update({addingNewEvent: adding})
    },
  render: self =>
    <div>
      <div>
        {
          if (self.state.addingNewEvent) {
            <div>
              <NewEventForm
                onAdd={event => addEvent(event)}
                onCancel={_e => changeAddingStatus(self.send, false)}
              />
            </div>;
          } else {
            <div onClick={_e => changeAddingStatus(self.send, true)}>
              {ReasonReact.string("Create New Event")}
            </div>;
          }
        }
      </div>
      <div> {RenderHelpers.renderList(events, renderEvent)} </div>
    </div>,
};
