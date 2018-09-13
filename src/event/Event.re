type event = {name: string};

type eventOfList = {
  id: string,
  eventName: string,
};

module Decoder = {
  open Json.Decode;
  let to_eventOfList = json: eventOfList => {
    id: json |> field("id", string),
    eventName: json |> field("eventName", string),
  };
  let to_eventList = json: list(eventOfList) =>
    Belt.List.fromArray(json |> array(to_eventOfList));
  let to_event = json: event => {name: json |> field("name", string)};
};
