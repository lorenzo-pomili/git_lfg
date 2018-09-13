type t =
  | Login
  | Home
  | EventDetail(string);

let getRoute = path =>
  switch (path) {
  | ["home"] => Home
  | ["eventDetail", id] => EventDetail(id)
  | _ => Login
  };

let getPageFromPath = path => {
  let route = getRoute(path);
  switch (route) {
  | EventDetail(id) => <EventDetailLoder eventId=id />
  | Login => <LoginPage />
  | Home => <Home />
  };
};

let init = pageChanged => {
  let watchId =
    ReasonReact.Router.watchUrl(url => {
      let page = getPageFromPath(url.path);
      pageChanged(page);
    });
  watchId;
};

let destroy = ReasonReact.Router.unwatchUrl;
