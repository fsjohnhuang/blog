# (Web Animation API](https://developer.mozilla.org/en-US/docs/Web/API/Animation)
Provides a imperative way to control much more complex animation.
```
data Map = StrMap String String | IntMap String Int | FloatMap String Float

type Keyframes = [Map]
type AnimationEffectTimingProperties = Map
type Duration = Int
data Options = AnimationEffectTimingProperties | Duration

// Defines animation and play right now.
js/Element.animate :: -> Keyframes -> Options -> js/Animation
```

Keyframes
`offset: 0.4` equals to `40% { }` in CSS.
```
[
 {opacity: 1},               // equals to `from` or 0% in CSS
 {opacity: 0.8, offset: 0.4} // equals to 40% in CSS
 {opacity: 0}                // equals to `to` or 100% in CSS
]
```

Options
default timing funciton is linear
```
{
  duration: 3000 ;; unit is ms
  delay: 0
  fill: "forward"
  easing: "steps(8, end)"
  iterations: Infinity
}
```

## js/Animation
### Methods
```
// clears all keyframe effects
cancel :: nil -> nil

// seeks either end of an animation, depending on whether the animation is playing or reversing
finish :: nil -> nil

// suspends playing of an animation
pause :: nil -> nil

// starts or resumes playing of an animation, or begins the animiation again if it previously finshied
play :: nil -> nil

// reverses playback direction, stopping at the start of the animation. If the animation is finished or unplayed, it will play from end to beginning
// and changes playbackRate to -1
reverse :: nil -> nil

// sets the speed of an animation after first synchronizing its playback position.
// default value is 1, greater than 1 means speed up, less than 1 and greater than 0 means slow down.
updatePlaybackRate :: Float -> nil
```
### Events
`oncancel`
`onfinish`

### Properties
```
/*
 pause - pause()
 running - animate(), play()
 idle - cancel() 
 finished - finish()
 pending - when call pause(), animate(), play() the animation task would be pending for a while, then trun into pause or running state after milliseconds.
 */
Animation#playState :: String

// Unit is ms
// max value is `delay + (duration * iterations)` not effected by `playbackRate`
// read,write properties, so could step to specific point of timeline.
Animation.currentTime :: Maybe Int

// Unit is ms
// get or set point of timeline to start to play
Animation.startTime :: Maybe Int
```

## Polyfill 
https://github.com/web-animations/web-animations-js

## Ref
http://danielcwilson.com/blog/2015/07/animations-intro/
