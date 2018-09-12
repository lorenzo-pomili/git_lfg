let getAllEvents = (): Js.Promise.t(list(Event.event)) =>
  Js.Promise.(
    Fetch.fetch(ServicesTools.server_url ++ "/getAllEvents")
    |> then_(Fetch.Response.json)
    |> then_(json => resolve(Event.Decoder.to_eventList(json)))
  );
