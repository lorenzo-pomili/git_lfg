type user = {
  id: string,
  token: string,
  name: string,
};

module Decoder = {
  open Json.Decode;
  let to_user = json => {
    id: json |> field("id", string),
    token: json |> field("token", string),
    name: json |> field("name", string),
  };
};

module Encoder = {
  open Json.Encode;
  let to_user = (user: user) =>
    object_([
      ("id", string(user.id)),
      ("token", string(user.token)),
      ("name", string(user.name)),
    ]);
};

let getUser = () =>
  switch (Dom.Storage.(localStorage |> getItem("user"))) {
  | None => None
  | Some(user) => Some(Decoder.to_user(Js.Json.parseExn(user)))
  };

let setUser = user =>
  Dom.Storage.(
    localStorage
    |> setItem("user", Js.Json.stringify(Encoder.to_user(user)))
  );
