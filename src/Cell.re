open SharedTypes;

let toValue = (cell: field) =>
  switch (cell) {
  | Marked(Cross) => "X"
  | Marked(Cyrcle) => "O"
  | Empty => ""
  };

let component = ReasonReact.statelessComponent("Cell");

let make = (~cell: field, ~onMark, _children) => {
  ...component,
  render: _self => {
    <div className="cell" onClick={_evt => onMark()}>
      {cell |> toValue |> ReasonReact.string}
    </div>;
  },
};