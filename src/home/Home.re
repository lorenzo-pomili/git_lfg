type state = {user: option(User.user)};

type action =
  | GetUser(User.user);

let component = ReasonReact.reducerComponent("Home");

let make = _ => {
  ...component,
  initialState: () => {user: None},
  didMount: self =>
    switch (User.getUser()) {
    | None => ReasonReact.Router.push("/")
    | Some(user) => self.send(GetUser(user))
    },
  reducer: (action, _state) =>
    switch (action) {
    | GetUser(user) => ReasonReact.Update({user: Some(user)})
    },
  render: self =>
    <div>
      {
        switch (self.state.user) {
        | None => <div> {ReasonReact.string("login required")} </div>
        | Some(user) => <EventsRenderLoader.Render token={user.token} />
        }
      }
    </div>,
};
