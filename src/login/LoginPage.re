type state = {logged: bool};
type action =
  | Login;

let tryLoginWithGithub = token =>
  LoginService.loginWithGithub(token)
  |> Js.Promise.then_(result => Js.Promise.resolve(result));

let loginWithGithub = (user, send) => {
  User.setUser(user);
  Js.Promise.(
    tryLoginWithGithub(user.token)
    |> then_((res: LoginService.Login.response) =>
         resolve(
           if (res.isValid) {
             send(Login);
             ReasonReact.Router.push("/home");
           } else {
             ();
           },
         )
       )
    |> ignore
  );
};
let component = ReasonReact.reducerComponent("LoginPage");

let make = _ => {
  ...component,
  initialState: () => {logged: false},
  didMount: self => {
    let user = User.getUser();
    switch (user) {
    | None => ()
    | Some(u) => loginWithGithub(u, self.send)
    };
  },
  reducer: (action, _state) =>
    switch (action) {
    | Login => ReasonReact.Update({logged: true})
    },
  render: self =>
    <div>
      <div
        className="loginButton"
        onClick={
          _e =>
            loginWithGithub(
              {id: "id", token: "test_token", name: "Test User"},
              self.send,
            )
        }>
        {ReasonReact.string("Login with Github")}
      </div>
    </div>,
};
