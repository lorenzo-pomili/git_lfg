module type DataSig = {
  type e;
  type getParams;
  let getData: getParams => Js.Promise.t(e);
  let render: e => ReasonReact.reactElement;
};

module Make = (Data: DataSig) => {
  type state = {data: option(Data.e)};

  type action =
    | GetData(Data.e);

  let component = ReasonReact.reducerComponent("Loader");

  let make = (_, ~getParams: Data.getParams) => {
    ...component,
    didMount: self =>
      Js.Promise.(
        Data.getData(getParams)
        |> then_(res => resolve(self.send(GetData(res))))
        |> ignore
      ),
    initialState: () => {data: None},
    reducer: (action, _state) =>
      switch (action) {
      | GetData(data) => ReasonReact.Update({data: Some(data)})
      },
    render: self =>
      <div>
        {
          switch (self.state.data) {
          | None => <div> {ReasonReact.string("Lodaing...")} </div>
          | Some(e) => Data.render(e)
          }
        }
      </div>,
  };
};
