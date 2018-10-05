type partecipant = {name: string};
type event = {
  id: option(string),
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
    id: Some(json |> field("id", string)),
    name: json |> field("name", string),
    partecipants: json |> field("partecipants", to_partecipants),
  };
};

module Encoder = {
  open Json.Encode;
  let to_partecipant = (partecipant: partecipant) =>
    object_([("name", string(partecipant.name))]);
  let to_partecipants_list = (partecipants: list(partecipant)) =>
    array(to_partecipant, Belt.List.toArray(partecipants));
  let to_event = (event: event) =>
    object_([
      ("id", string(Belt.Option.getWithDefault(event.id, ""))),
      ("name", string(event.name)),
      ("partecipants", to_partecipants_list(event.partecipants)),
    ]);
};
