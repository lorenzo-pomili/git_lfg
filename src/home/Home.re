let getToken = () => Dom.Storage.(localStorage |> getItem("token"));

type state = {token: option(string)};

type action =
  | GetToken(string);

let component = ReasonReact.reducerComponent("Home");

let make = _ => {
  ...component,
  initialState: () => {token: None},
  didMount: self =>
    switch (getToken()) {
    | None => ReasonReact.Router.push("/")
    | Some(token) => self.send(GetToken(token))
    },
  reducer: (action, _state) =>
    switch (action) {
    | GetToken(token) => ReasonReact.Update({token: Some(token)})
    },
  render: self =>
    <div>
      {
        switch (self.state.token) {
        | None => <div> {ReasonReact.string("login required")} </div>
        | Some(token) => <EventsRenderLoader.Render token />
        }
      }
    </div>,
};
