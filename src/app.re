[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");
let toString = ReasonReact.string;
let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className="app">
      <h1 className="app__title"> (ReasonReact.string("Tic Tac Toe")) </h1>
      <Game />
    </div>,
};