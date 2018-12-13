open SharedTypes;

type state = {
  board,
  gameState,
};

type action =
  | Mark;

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
    gameState: Draw,
  },
  reducer: (action, state) =>
    switch (action) {
    | Mark => ReasonReact.Update({...state, gameState: Draw})
    },
  render: self =>
    <div> <Board state=self.state onMark=(_evt => self.send(Mark)) /> </div>,
};