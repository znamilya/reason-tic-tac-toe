open SharedTypes;

type action =
  | Mark(string)
  | Restart;

type winningRows = list(list(int));

let winningRows = [
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
              | (_, Marked(_)) => cell
              | (Playing(player), Empty) => Marked(player)
              | (_, Empty) => Empty
              } :
              cell;
          })
     );

let getWinner = (flattenBoard, coords) =>
  switch (
    List.nth(flattenBoard, List.nth(coords, 0)),
    List.nth(flattenBoard, List.nth(coords, 1)),
    List.nth(flattenBoard, List.nth(coords, 2)),
  ) {
  | (Marked(Cross), Marked(Cross), Marked(Cross)) => Cross
  | (Marked(Cyrcle), Marked(Cyrcle), Marked(Cyrcle)) => Cyrcle
  | (_, _, _) => NoOne
  };

let gameEnded = board =>
  List.for_all(
    field => field == Marked(Cyrcle) || field == Marked(Cross),
    board,
  );

let whosPlaying = (gameState: gameState) =>
  switch (gameState) {
  | Playing(Cross) => Playing(Cyrcle)
  | _ => Playing(Cross)
  };

let checkGameState =
    (
      winningRows: winningRows,
      updatedBoard: board,
      oldBoard: board,
      gameState: gameState,
    ) =>
  oldBoard == updatedBoard ?
    gameState :
    {
      let flattenBoard = List.flatten(updatedBoard);
      let rec check = (rest: winningRows) => {
        let head = List.hd(rest);
        let tail = List.tl(rest);
        switch (
          getWinner(flattenBoard, head),
          gameEnded(flattenBoard),
          tail,
        ) {
        | (Cross, _, _) => Winner(Cross)
        | (Cyrcle, _, _) => Winner(Cyrcle)
        | (_, true, []) => Draw
        | (_, false, []) => whosPlaying(gameState)
        | _ => check(tail)
        };
      };
      check(winningRows);
    };
let component = ReasonReact.reducerComponent("Game");
let toString = ReasonReact.string;

let initialState = {
  board: [
    [Empty, Empty, Empty],
    [Empty, Empty, Empty],
    [Empty, Empty, Empty],
  ],
  gameState: Playing(Cross),
};

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch (action) {
    | Mark(cellId) =>
      let nextBoard = updateBoard(state.board, state.gameState, cellId);

      ReasonReact.Update({
        board: nextBoard,
        gameState:
          checkGameState(
            winningRows,
            nextBoard,
            state.board,
            state.gameState,
          ),
      });
    | Restart => ReasonReact.Update(initialState)
    },
  render: self =>
    <div>
      {switch (self.state.gameState) {
       | Playing(_) =>
         <Board
           state={self.state}
           onMark={cellId => self.send(Mark(cellId))}
         />
       | Draw => <GameOver onRestart={_evt => self.send(Restart)} />
       | Winner(player) =>
         <Winnner player onRestart={_evt => self.send(Restart)} />
       }}
    </div>,
};