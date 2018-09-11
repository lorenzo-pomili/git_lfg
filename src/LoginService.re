let server_url = "http://localhost:8008";

module Login = {
  type response = {
    isValid: bool,
    token: string,
  };
  module Decoder = {
    open Json.Decode;
    let to_response = json: response => {
      isValid: json |> field("isValid", bool),
      token: json |> field("token", string),
    };
  };
  module Encode = {
    open Json.Encode;
    let from_token = token => object_([("token", string(token))]);
  };
};

let loginWithGithub = token =>
  Js.Promise.(
    Fetch.fetchWithInit(
      server_url ++ "/loginWithGithub",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(
            Json.stringify(Login.Encode.from_token(token)),
          ),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(res => resolve(Login.Decoder.to_response(res)))
  );

/* let login = (): Js.Promise.t(Login.response) =>
   Js.Promise.(
     Fetch.fetch(server_url ++ "/login")
     |> then_(Fetch.Response.json)
     |> then_(json => resolve(Login.Decoder.to_response(json)))
   ); */
