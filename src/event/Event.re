type partecipant = {name: string};
type event = {
  name: string,
  partecipants: list(partecipant),
};

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

  let to_partecipant = json: partecipant => {
    name: json |> field("name", string),
  };
  let to_partecipants = json: list(partecipant) =>
    Belt.List.fromArray(json |> array(to_partecipant));

  let to_event = json: event => {
    name: json |> field("name", string),
    partecipants: json |> field("partecipants", to_partecipants),
  };
};
