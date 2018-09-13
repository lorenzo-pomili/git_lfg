module EventDetailLoaderSig: Loader.DataSig with type getParams = string = {
  type e = Event.event;
  type getParams = string;
  let getData = eventId => EventsService.getEventDetail(eventId);
  let render = event => <EventDetail event />;
};

module Aux = Loader.Make(EventDetailLoaderSig);

module Render = {
  let make = (~eventId) => Aux.make(~getParams=eventId);
};
