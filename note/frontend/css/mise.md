## currentColor
CSS3 feature which applies the color as same as current color of element
```
.target{
  color: red;
  border-top: solid 1px blue;
  border-bottom: solid 1px currentColor;
}
.target:hover{
  color: yellow;
}
```

## :root
Refers `<html>` element.
Supported from IE9.

## Pseudo element started with `::`
Starts with `::` when refers pseudo element is preference from IE9.
```
.target :before { content: "..."; } /*for IE8*/
.target ::before { content: ""; } /*for IE9*/
```
