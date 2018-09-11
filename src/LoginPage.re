type state = {logged: bool};
type action =
  | Login;

let tryLoginWithGithub = token =>
  LoginService.loginWithGithub(token)
  |> Js.Promise.then_(result => Js.Promise.resolve(result));

let loginWithGithub = (token, send) =>
  Js.Promise.(
    tryLoginWithGithub(token)
    |> then_((res: LoginService.Login.response) =>
         resolve(
           if (res.isValid) {
             send(Login);
           } else {
             ();
           },
         )
       )
    |> ignore
  );

let component = ReasonReact.reducerComponent("LoginPage");

let make = _ => {
  ...component,
  initialState: () => {logged: false},
  reducer: (action, _state) =>
    switch (action) {
    | Login => ReasonReact.Update({logged: true})
    },
  render: self =>
    <div>
      <div>
        {
          !self.state.logged ?
            ReasonReact.string("not logged") : ReasonReact.string("logged")
        }
      </div>
      <div onClick={_e => loginWithGithub("test_token", self.send)}>
        {ReasonReact.string("Login with Github")}
      </div>
    </div>,
};
