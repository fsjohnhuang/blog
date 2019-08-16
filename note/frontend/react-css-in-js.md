## [classnames](https://www.npmjs.com/package/classnames)
Installs
```
npm i classnames --save
```
### Basic Usage
```
import classnames from "classnames"

classnames("foo", {bar: false}, 0, false, null, 1) //=> "foo 1"

// dynamic class name with ES2015 computed keys
let btnType = "primary"
classnames({
  ['btn-${btnType}']: true
}) //=> “btn-primary”
```

### Sub Module `dedupe`
```
import classnames from "classnames/dedupe"

classnames("foo", "foo", "bar") //=> "foo bar"
classnames("foo", {foo: false}, "bar") //=> "bar"
```

### Sub Module `bind`
```
import classnames from "classnames/bind"

const classNames = {
  foo: "btn-primary",
  bar: "btn-error"
}
const cx = classnames(classNames)
cx({
  foo: true,
  bar: false
})//=> "btn-primary"
```

## [css-modules](https://github.com/css-modules/css-modules)
The cons of CSS
1. Global Namespace
2. Complicate Dependencies Management
3. Dead Code Elimination is Hard
4. Minfication(long class name is hard to minficate)
5. Can't Sharing Constants with JS
6. Non-deterministic Resolution(because of cascade)
7. Isolation(weak of couple)

###  CSS in JS
Features:
1. Generates random className, avoiding name conllisions.
2. Accepts css class name + css-in-js.
```
const Title = styled.h2`
  color: red;
`
<Title className="title">Hello World</Title> //=> <h2 class="title sc-aaxs xao">Hello World</h2>
```
3. supports pseudo selector
4. supports media query
5. supports css animation

pros:
1. adapts React and React-Native
2. CSS must be attached to React Component, eliminates redundant CSS rules.
3. supports autoprefix.
4. compress the classnames.
5. dynamic style(generate style on runtime)

cons:
1. hard to debug
2. can't utilize css preprocessor, so migration from old project is hard.

[css-in-js tech stack comparison](https://github.com/MicheleBertoli/css-in-js)

#### [styled-components](styled-components)
```
# Installs
$ npm i styled-components --save
```

**Basic Usage**
```
import styled, { css } from "styled-components"

const Title = styled.h1`
  font-size: 1.5em;
  text-align: center;
  color: ${props => props.color || "palevioletred"};

  ${props => props.error && css`
    background: red;
    color: white;
  `}
`

<Title>
  Hello World
</Title>
<Title error>
  Error
</Title>
```
**Neating**
```
import styled from "styled-components"

const Title = styled.h1`
  font-size: 20px;

  &:hover {
    text-shadow: 0 0 10px #888;
  }

  > .icon{
    font-size: 14px;
  }

  @media all and (max-width:600px){
    font-size: 18px;
  }
`
```

**Additional Props**
```
import styled from "styled-components"

const Title = styled.input.attrs({
  placeholder: "Enter Name!",             // speicifies the native attributes of input element, so `active: false` would throw error
  margin: props => props.margin || "1em"
})`
  color: ${ props => props.color };
  /* use dynamically computed props */
  margin: ${ props => props.margin };
`
```
**Sharing Style**
1. `styled(ReactComponent)`
```
import styled from "styled-components"

function Link ({className, children}){
  return (
    <a className={ className }>
      { children }
    </a>
  )
}
const StyledLink = styled(Link)`
  font-weight: bold;
`
```
2. `StyledComponent.extend`
```
import styled from "styled-components"

const StyledLink = styled("a")`
  font-weight: bold;
`

const BigLink = StyledLink.extend`
  font-size: 30px;
`
```
**CSS Animation**
```
import styled, { keyframes } from "styled-components"

const rotate360 = keyframes`
  from {
    transform: rotate(0deg);
  }
  to{
    transform: rotate(360deg);
  }
`

const Rotate = styled.div`
  display: inline-block;
  animation: ${rotate360} 2s linear infinite;
  padding: 2rem 1rem;
  font-size: 1.2rem;
`
```
**Theme**
Sets `<ThemeProvider>` as root of app.
```
import React, { Component } from "react"
import styled, { ThemeProvider } from "styled-components"

const THEMES = {
  dark: {fg: "#fff", bg: "#333"},
  light: {fg: "#333", bg: "#fff"}
}

const ListItem = styled.li.attrs({tabIndex:0})`
  color: ${props => props.theme.fg};
  border: solid 1px ${props => props.theme.fg};
  background: ${props => props.theme.bg};
`

class ThemeList extends Component{
  constructor(props){
    super(props)

    this.state = {
      theme: "dark",
      themes: Object.keys(THEMES)
    }

    this.changeTheme = this.changeTheme.bind(this)
  }
  changeTheme({target}){
    this.setState({ theme: target.value })
  }
  render(){
    return (
      <ThemeProvider theme={ THEMES[this.state.theme] }>
        <ul>
        {
          this.themes.map(theme => (
            <ListItem innerRef={ x => { this[this.state.theme + "Ref"] = x } }
                      key={ this.state.theme }
                      value={ this.state.theme }
                      onClick={ this.changeTheme }>
              { this.state.theme }
            </ListItem>
          ))
        }
        </ul>
      </ThemeProvider>
    )
  }
}
```

theme 1-\* variants
variants across multiple dimension:
1. cosy and compact
2. accessibility modes
......
tool/pattern: [styled-theming](http://thejameskyle.com/styled-theming.html)

**Global Style**
```
import { injectGlobal } from "styled-components"

injectGlobal`
  @font-face{
    font-family: "Operator Mono";
    src: url("../fonts/Operator-Mono.ttf");
  }

  body{
    margin: 0;
  }
`
```

### CSS Modules
1. compresses the classnames.
2. utilizes preprocessor.

#### Features
1. Generates random className, avoiding name conllisions.
2. Provides a way to access CSS classname and binding(not variable) by JS.
3. Provides import and extend by `compose`

#### Enables CSS Modules in css-loader
webpack.config.js
```
{
  loader: require.resolve('css-loader'),
  options: {
    modules: true,
  },
},
```

#### Usage
```
/* __variable.scss */
$primary_fg: #fff;
$error_fg: red;

/* There is no variable in CSS Modules, but we could utilize variable of SCSS/SASS */
:export{
  primary_fg: $primary_fg;
  error_fg: $error_fg;
}

/* reset.scss */
/* `:global(<classname>)` indicates to preserve the classname*/
body{
  margin: 0;
}
:global(.main){
  padding: 10px;
}

/* common.scss */
.primary_background{
  background: blue;
}

/* list.scss */
@import 'reset.scss'
@import '__variable.scss'

.primary_border{
  border: solid 1px $primary_fg;
}
.list__item{
  composes: primary_border;
  composes: primary_background from "./common.scss";
  display: block;
  animation: rotate 5s linear infinite;
}

/* the keyframes name `rotate` would be transform to random code */
@keyframes rotate{
  from{
    transform: rotate(0deg);
  }
  to{
    transform: rotate(360deg);
  }
}
```
#### [react-css-modules](https://github.com/gajus/react-css-modules)
```
import CSSModules from "react-css-modules"
import styles from "./styles.css"

function List(props){
  return (
    <a styleName="list__item">{ props.children }</a>
  )
}
export default CSSModules(List, styles)
```
