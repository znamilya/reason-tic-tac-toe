open SharedTypes;

let component = ReasonReact.statelessComponent("GameOver");

let renderPlayer = (player: player) =>
  switch (player) {
  | Cross => "Cross"
  | Cyrcle => "Cyrcle"
  };

let make = (~player: player, ~onRestart, _children) => {
  ...component,
  render: _self => {
    <div>
      <h2>
        {ReasonReact.string("Winner is: ")}
        {player |> renderPlayer |> ReasonReact.string}
      </h2>
      <button onClick=onRestart> {ReasonReact.string("Restart")} </button>
    </div>;
  },
};