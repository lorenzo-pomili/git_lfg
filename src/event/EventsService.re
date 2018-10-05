let getAllEvents = (token: string): Js.Promise.t(list(Event.eventOfList)) =>
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

let addEvent = (event: Event.event) =>
  Js.Promise.(
    Fetch.fetchWithInit(
      ServicesTools.server_url ++ "/newEvent",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(
            Json.stringify(Event.Encoder.to_event(event)),
          ),
        (),
      ),
    )
    |> resolve
  );

let joinEvent = (event: Event.event, user: User.user) =>
  Js.Promise.(
    Fetch.fetchWithInit(
      ServicesTools.server_url ++ "/joinEvent",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(
            Json.stringify(
              Json.Encode.object_([
                ("user", User.Encoder.to_user(user)),
                ("event", Event.Encoder.to_event(event)),
              ]),
            ),
          ),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(newEvent => resolve(Event.Decoder.to_event(newEvent)))
  );
