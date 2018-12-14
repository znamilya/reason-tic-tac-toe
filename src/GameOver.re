let component = ReasonReact.statelessComponent("GameOver");

let make = (~onRestart, _children) => {
  ...component,
  render: _self =>
    <div>
      <h2> {ReasonReact.string("Game over")} </h2>
      <button onClick=onRestart> {ReasonReact.string("Restart")} </button>
    </div>,
};