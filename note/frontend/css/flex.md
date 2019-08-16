# Flex

flex container
main axis, main start, main end
cross axis, cross start, cross end

flex item
main size, cross size

## Browser Compatiable
IE10+

## Properties of Flex Container
`display: flex`, defines a block flex container.
`display: inline-flex`, defines an inline flex container.
The above two types flex containers enable a flex context for all their direct children.

`flex-direction: row | row-reverse | column | column-reverse`
Establishing the main axis and the direction flex items are placed in the flex container.

`flex-wrap: nowrap | wrap | wrap-reverse`

`flex-flow: <flex-direction> || <flex-wrap>`
A shorthand flex-driection and flex-wrap, which together define the flex container's main and cross axis.

`justify-content: flex-start | flex-end | center | space-between | space-around | space-evenly`
Defines the alignment along the main axis which helps distribute extra free space left over.

`align-items: flex-start | flex-end | center | stretch | baseline`
Defines the how the flex items are laid out along the cross axis on the current line.

`align-content: flex-start | flex-end | center | stretch | space-between | space-around`
Defines the alignment along the cross axis for flex container's lines.
no effect when there is only one line of flex items.

## Properties of Flex Item
`order: <integer>`, default 0
`flex-grow: <number>`, default 0
`flex-shrink: <number>`, default 1
set to 0, would not shrink when space is not enough.

`flex-basis: <length> | auto`, default auto
defines the default size of an element before the remaining space is distributed. set to 0, then flex-grow is no effect.
`flex: none | [<flex-grow> <flex-shrink>? || <flex-basis>]`
defualt `0 1 auto`
keyword `none` (0 0 auto) and `auto` (1 1 auto)

`align-self: auto | flex-start | flex-end | center | baseline | stretch`

float,clear,vertical-align have no effect on flex items.
