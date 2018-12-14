open SharedTypes;

let component = ReasonReact.statelessComponent("Row");

let make = (~rowIndex: int, ~row: row, ~onMark, _children) => {
  ...component,
  render: _self => {
    <div className="row">
      {row
       |> List.mapi((index: int, cell: field) =>
            <Cell
              cell
              onMark={_evt =>
                onMark(string_of_int(rowIndex) ++ string_of_int(index))
              }
              key={string_of_int(index)}
            />
          )
       |> Array.of_list
       |> ReasonReact.array}
    </div>;
  },
};