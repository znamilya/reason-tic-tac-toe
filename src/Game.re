open SharedTypes;

type action =
  | Mark(string);

type winningRows = list(list(int));

let winningCombs = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6],
];

let updateBoard = (board: board, gameState: gameState, cellId: string): board =>
  board
  |> List.mapi((rIndex, row) =>
       row
       |> List.mapi((cIndex, cell) => {
            let isMatch =
              string_of_int(rIndex) ++ string_of_int(cIndex) === cellId;

            isMatch ?
              switch (gameState, cell) {
              | (Playing(player), Empty) => Marked(player)
              | _ => cell
              } :
              cell;
          })
     );

let component = ReasonReact.reducerComponent("Game");
let toString = ReasonReact.string;

let make = _children => {
  ...component,
  initialState: () => {
    board: [
      [Empty, Empty, Empty],
      [Empty, Empty, Empty],
      [Empty, Empty, Empty],
    ],
    gameState: Playing(Cross),
  },
  reducer: (action, state) =>
    switch (action) {
    | Mark(cellId) =>
      let nextBoard = updateBoard(state.board, state.gameState, cellId);

      ReasonReact.Update({
        board: nextBoard,
        gameState:
          switch (state.gameState) {
          | Playing(Cross) => Playing(Cyrcle)
          | Playing(Cyrcle) => Playing(Cross)
          | _ => state.gameState
          },
      });
    },
  render: self =>
    <div>
      <Board state={self.state} onMark={cellId => self.send(Mark(cellId))} />
    </div>,
};