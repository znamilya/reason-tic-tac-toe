open SharedTypes;

let component = ReasonReact.statelessComponent("Board");
let toString = ReasonReact.string;

let make = (~state: state, ~onMark, _children) => {
  ...component,
  render: _self =>
    <div className="game-board">
      {state.board
       |> List.mapi((index: int, row: row) =>
            <Row rowIndex=index row onMark key={string_of_int(index)} />
          )
       |> Array.of_list
       |> ReasonReact.array}
    </div>,
};