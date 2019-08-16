# CSS3 Transition
```
transition: <transition-property> <transition-duration> <transition-timing-function> <transition-delay>;

<transition-property>: all | none | <property> [,<property>]*
  only reflow and repaint properties could be animated. [CSS_animated_properties](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_animated_properties)
<transition-duration>: 0s | <time> [, <time>]*
  the valid unit of <time> is `s` and `ms`
<transition-timing-function>: linear|ease|ease-in|ease-out|ease-in-out|cubic-bezier(n,n,n,n)
  the range of n in cubic-bezier is from 0 to 1.
  a very handy tool to tune cubic-bezier[cubic-bezier](http://cubic-bezier.com)
<transition-delay>: 0s | <time> [, <time>]
```

## multiple transitions
```
transition: width 2s ease
          , color 1s ease-out;
```

## How to trigger
1. pseudo class
`:link`, effective to link
`:visited`, effective to link
`:hover`, effective to all elements, when mouse hover
`:active`, effective to all elements, when mouse click
`:focus`, effective to focusable elements
2. update css properties by JS
```
el.style.display = "block"  // original display value is `none`
el.offsetTop                // force reflow
el.style.background = "red"
```
3. update class by JS
```
// get or set below properties by JS would trigger reflow
offsetWidth, offsetHeight, offsetTop, offsetLeft
scrollWidth, scrollHeight, scrollTop, scrollLeft
clientWidth, clientHeight, clientTop, clientLeft
getComputeStyle(), currentStyle()
```

## [TransitionEnd Event](https://developer.mozilla.org/en-US/docs/Web/Events/transitionend)
One property transition fires one TransitionEnd event
```
document.querySelector(".sample")
  .addEventListener("transitionend"
    , e => {
      const pseudoElement = e.pseudoElement
          , propertyName = e.propertyName
          , elapsedTime = e.elapsedTime
    })
```
So
```
transition: visibility .9s,
            opacity 1s;
```
would fires two transitionend event.

## visibility
`visibility` is valid property to be applied transition effection.
The value `hidden` equals to 0, and value `visible` equals to 1. so the transition between `hidden` and `visible` equals to 0 to 1.And 0 means hidden totally, non-zero means display.

The **important feature** of `visibility: hidden` is 
1. still occupy the position.
2. would not intercept the mouse events anymore.

so we would implement Tips component with `opacity` and `visibility` properties.

## `display:none` disables transition
`display:none` would disable transition effection.

```
<style>
.box{
  display: none;
  background: red;
  height: 20px;
}
</style>
<div class="box"></div>
<button id="btn1">Transition has no effect</button>
<button id="btn2">Transition takes effect</button>
<script>
const box = document.querySelector(".box")
    , btn1 = document.querySelector("#btn1")
    , btn2 = document.querySelector("#btn2")
btn1.addEventListener("click", e => {
  box.style.display = "block"
  box.style.background = "blue"
})
btn2.addEventListener("click", e => {
  box.style.display = "block"
  box.offsetWidth              // force reflow
  box.style.background = "blue"
})
</script>
```
 
## Ref
[小tip: transition与visibility](http://www.zhangxinxu.com/wordpress/2013/05/transition-visibility-show-hide/)
