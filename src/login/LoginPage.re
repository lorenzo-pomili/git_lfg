type state = {logged: bool};
type action =
  | Login;

let getToken = () => Dom.Storage.(localStorage |> getItem("token"));
let setToken = token => Dom.Storage.(localStorage |> setItem("token", token));

let tryLoginWithGithub = token =>
  LoginService.loginWithGithub(token)
  |> Js.Promise.then_(result => Js.Promise.resolve(result));

let loginWithGithub = (token, send) => {
  setToken(token);
  Js.Promise.(
    tryLoginWithGithub(token)
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
    let token = getToken();
    switch (token) {
    | None => ()
    | Some(token) => loginWithGithub(token, self.send)
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
        onClick={_e => loginWithGithub("test_token", self.send)}>
        {ReasonReact.string("Login with Github")}
      </div>
    </div>,
};
