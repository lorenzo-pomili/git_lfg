let getAllEvents = (): Js.Promise.t(list(Event.eventOfList)) =>
  Js.Promise.(
    Fetch.fetch(ServicesTools.server_url ++ "/getAllEvents")
    |> then_(Fetch.Response.json)
    |> then_(json => resolve(Event.Decoder.to_eventList(json)))
  );

let getEventDetail = (eventId: string): Js.Promise.t(Event.event) =>
  Js.Promise.(
    Fetch.fetch(ServicesTools.server_url ++ "/getEventDetail/" ++ eventId)
    |> then_(Fetch.Response.json)
    |> then_(json => resolve(Event.Decoder.to_event(json)))
  );
