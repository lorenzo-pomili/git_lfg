module IndexWrapper = {
  open ReasonReact;
  type state = {currentContent: reactElement};
  type action =
    | ContentChanged(reactElement);
  let component = ReasonReact.reducerComponent("Index");
  let make = _ => {
    ...component,
    didMount: self => {
      let watcherId = PageRouter.init(el => self.send(ContentChanged(el)));

      self.onUnmount(() => PageRouter.destroy(watcherId));
    },
    initialState: () => {
      currentContent:
        PageRouter.getPageFromPath(
          ReasonReact.Router.dangerouslyGetInitialUrl().path,
        ),
    },
    render: self =>
      <div className="app"> <div> {self.state.currentContent} </div> </div>,
    reducer: (action, _) =>
      switch (action) {
      | ContentChanged(el) => ReasonReact.Update({currentContent: el})
      },
  };
};

ReactDOMRe.renderToElementWithId(<IndexWrapper />, "mainContent");
