type event = {eventName: string};

module Decoder = {
  open Json.Decode;
  let to_event = json: event => {
    eventName: json |> field("eventName", string),
  };
  let to_eventList = json: list(event) =>
    Belt.List.fromArray(json |> array(to_event));
};
