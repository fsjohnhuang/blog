## ReactCSSTransitionGroup
provides an easy way to peform CSS transitions and animations when a React Component enters or leaves the DOM.
```
// version 1.x
import { injectGlobal } from "styled-components"
import ReactCSSTransitionGroup from "react-addons-css-transition-group"

injectGlobal`
  .sample-enter{
    opacity: 0.1;

    &.sample-enter-active{
      opacity: 1;
      transition: opacity 800ms ease-in;
    }
  }

  .sample-leave{
    opacity: 1;

    &.sample-leave-active{
      opacity: 0.1;
      transition: opacity 800ms ease-in;
    }
  }
`

class TodoList extends Component{
  constructor(props){
    super(props)
    this.state = {items: ["a", "b"]}

    this.handleRemove = this.handleRemove.bind(this)
    this.handleAdd = this.handleAdd.bind(this)
  }
  handleRemove(i){
    this.setState(({items}, _) => {items: (items.splice(i, 1), items.slice())})
  }
  handleAdd(){
    this.setState(({items}, _) => {items: items.concat([prompt("Inputs!")])})
  }
  render(){
    return(
      <div>
        <button onClick={ _ => this.handleAdd() }>Add</button>
        <ReactCSSTransitionGroup
          transitionName={{
            enter: "sample-enter",
            enterActive: "sample-enter-active",
            leave: "sample-leave",
            leaveActive: "sample-leave-active"
          }}
          transitionEnter={true}
          transitionEnterTimeout={500}
          transitionLeave={true}
          transitionLeaveTimeout={500} >
        { this.state.items.map((item, i) => (
              <div key={ item } onClick={ _ => this.handleRemove(i) }>
              { item }
              </div>
          ))
        }
        </ReactCSSTransitionGroup>
      </div>
    )
  }
}
```
the object value of `transitionName` above is the same as `transitionName="sample"`.
`transitionLeaveTimeout` is the timeout to remove element from DOM. If `transitionLeaveTimeout` is shorter than transition duration of `leave-active`, then could not play the animation completely.

### v2.0
https://reactcommunity.org/react-transition-group/css-transition
have been moved to [react-transition-group](https://github.com/reactjs/react-transition-group/tree/v1-stable) package.

## CSS3 Transition
```
transition: <transition-property> <transition-duration> <transition-timing-function> <transition-delay>;

<transition-property>: all | none | <property> [,<property>]\*
  only reflow and repaint properties could be animated. [CSS_animated_properties](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_animated_properties)
<transition-duration>: 0s | <time> [, <time>]\*
  the valid unit of <time> is `s` and `ms`
<transition-timing-function>: linear|ease|ease-in|ease-out|ease-in-out|cubic-bezier(n,n,n,n)
  the range of n in cubic-bezier is from 0 to 1.
  a very handy tool to tune cubic-bezier[cubic-bezier](http://cubic-bezier.com)
<transition-delay>: 0s | <time> [, <time>]
```

### multiple transitions
```
transition: width 2s ease
          , color 1s ease-out;
```

### How to trigger
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
el.style.background = "red" // no transition effect without reflow
```
3. update class by JS

```
// get or set below properties by JS would trigger reflow
offsetWidth, offsetHeight, offsetTop, offsetLeft
scrollWidth, scrollHeight, scrollTop, scrollLeft
clientWidth, clientHeight, clientTop, clientLeft
getComputeStyle(), currentStyle()
```

### [TransitionEnd Event](https://developer.mozilla.org/en-US/docs/Web/Events/transitionend)
One property transition fires a TransitionEnd event
```
document.querySelector(".sample")
  .addEventListener("transitionend"
    , e => {
      const pseudoElement = e.pseudoElement
          , propertyName = e.propertyName
          , elapsedTime = e.elapsedTime
    })
```

## [CSS3 Animation](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Animations/Using_CSS_animations)
```
/* Defines animation */
@keyframes <animation-name>{
  <keyframes-selector>{
    [<css-style>;]*
  }
}
```
`<animation-name>`, required
`<keyframes-selector>`, required, 0-100$ | from | to

```
/* Usage */
<css-selector>{
  animation: <animation-name> <animation-duration> <animation-timing-function> <animation-delay> <animation-iteration-count> <animation-direction> <animation-fill-mode> <animation-play-state>
}
```
`<animation-name>: none | <custom-ident> [, <custom-ident>]*`
  `<custom-ident>` should match
```
(defn valid? [custom-ident]
  (let [includes (partial re-find #"(?i)^[a-z][0-9a-z-_]*|-[a-z][0-9a-z-_]*$")
        excludes (comp not (partial re-find #"(?i)^none|unset|initial|inherit$"))]
    (->> custom-ident
      (every-pred includes excludes))))
```
  `/^[a-z][0-9a-z-_]*|-[a-z][0-9a-z-_]*$/i !/^none|unset|initial|inherit$/i`.
`<animation-duration>: 0s | <time>`
  the valid unit of <time> is `s` and `ms`
`<animation-timing-function>: [ease | ease-in | ease-out | ease-in-out | linear | step-start | step-end | steps(<integer>, <flag>) | frames(<integer>) | cubic-bezier(<number>,<number>,<number>,<number>)]+`
  `steps(<integer>, <flag>?)`, `<flag>: end | start`
  `step-start == steps(10, start)`
  `step-end == steps(10)`
`<animation-direction>: normal | reverse | alternate | alternate-reverse`
`<animation-fill-mode>: [none | forwards | backwards | both]+`
  specifies how a CSS animation should apply styles to its target before and after its execution.
  `forwards`, the target will retain the last keyframe style.
  `backwords`, the target will retain the first keyframe during the animation-delay period.
  `both`, follow the rules for both `forwards` and `backwards`.
`<animation-iteration-count>: [1 | <number> | infinite]+`
`<animation-play-state>: running | pause`

the order of keyframes is determined by `<animation-direction>` and `<animation-iteration-count>`

GIF provides animation but not support Alpha channel. PNG supports Alpha channel but no animaton.

[http://lea.verou.me/2011/09/pure-css3-typing-animation-with-steps/](http://lea.verou.me/2011/09/pure-css3-typing-animation-with-steps/)
### Events
`animationstart`
`animationiteration`, not be fired when `animation-iteration-count` is 1.
`animationend`
