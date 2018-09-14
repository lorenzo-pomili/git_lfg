module EventsRenderLoaderSig: Loader.DataSig with type getParams = string = {
  type e = list(Event.eventOfList);
  type getParams = string;
  let getData = token => EventsService.getAllEvents(token);
  let render = events => <EventsRender events />;
};

module Aux = Loader.Make(EventsRenderLoaderSig);

module Render = {
  let make = (~token) => Aux.make(~getParams=token);
};
