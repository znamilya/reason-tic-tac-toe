let component = ReasonReact.statelessComponent("Board");
let toString = ReasonReact.string;

let make = (~state, ~onMark, _children) => {
  ...component,
  render: _self =>
    <div onClick=(_evt => onMark())> (toString("Board")) </div>,
};