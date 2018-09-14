let renderList = (l, render) => {
  let renderedList = Belt.List.mapWithIndex(l, render);
  ReasonReact.array(Array.of_list(renderedList));
};
