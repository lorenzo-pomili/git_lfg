type t =
  | Login
  | Home;

let getRoute = path =>
  switch (path) {
  | ["home"] => Home
  | _ => Login
  };

let getPageFromPath = path => {
  let route = getRoute(path);
  switch (route) {
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
