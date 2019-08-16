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
`<keyframes-selector>`, required, 0-100% | from | to

```
/* Usage */
<css-selector>{
  animation: <animation-name> <animation-duration> <animation-timing-function> <animation-delay> <animation-iteration-count> <animation-direction> <animation-fill-mode> <animation-play-state>
}
```
`<animation-name>: none | <custom-ident> [, <custom-ident>]*`
  `<custom-ident>` 
should match
```
(defn valid? [custom-ident]
  (let [includes (partial re-find #"(?i)^[a-z][0-9a-z-_]*|-[a-z][0-9a-z-_]*$")
        excludes (comp not (partial re-find #"(?i)^none|unset|initial|inherit$"))]
    (->> custom-ident
      (every-pred includes excludes))))
```
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
`<animation-play-state>: running | paused`

the order of keyframes is determined by `<animation-direction>` and `<animation-iteration-count>`

GIF provides animation but not support Alpha channel. PNG supports Alpha channel but no animaton.

[http://lea.verou.me/2011/09/pure-css3-typing-animation-with-steps/](http://lea.verou.me/2011/09/pure-css3-typing-animation-with-steps/)
### Events
`animationstart`
`animationiteration`, not be fired when `animation-iteration-count` is 1.
`animationend`

### Replay
```css
@keyframes colorchange{
  from { background: red; }
  to { background: green; }
}
.box{
  width: 100px;
  height: 100px;
}
.changing{
  animation: colorchange 2s;
}
```
```html
<div class="box"></div>
<input value="play"/>
```
```cljs
(defn play []
  (let [host (js/document.querySelector "div")]
    (set! (.-className host) "box")
    (js/window.requestAnimationFrame
      #(js/window.requestAnimationFrame #(set! (.-className host) "box changing"))))

(-> (js/document.querySelector "input")
    (.addEventListener "click" play))
```
