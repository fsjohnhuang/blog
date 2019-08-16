使用伪元素的好处：
1. html代码量减少，对SEO有帮助
2. 提高JS查询元素的效率

```
div::after{
    content: "普通字符串";
    /* 自增计数器，用于插入数字/字母/罗马数字编号
     * counter-reset: [<identifier> <integer>?]+，必选，用于标识自增计数器的作用范围，<identifier>为自定义名称，<integer>为起始编号默认为0。
     * counter-increment: [<identifier> <integer>?]+，用于标识计数器与实际关联的范围，<identifier>为counter-reset中的自定义名称，<integer>为步长默认为1。
     * <list-style-type>: disc | circle | square | decimal | decimal-leading-zero | lower-roman | upper-roman | lower-greek | lower-latin | upper-latin | armenian | georgian | lower-alpha | upper-alpha
     */
    content: counter(<identifier>, <list-style-type>);
    content: attr(父元素的html属性名称);
    content: url(图片、音频、视频等资源的url);
    /* 使用unicode字符集，采用4位16进制编码
     * 但不同的浏览器显示存在差异，而且移动端识别度更差
     */
    content: "\21e0";
    /* content的多个值可以任意组合，各部分通过空格分隔 */
    content: "'" attr(title) "'";
}
```
换行符：HTML实体为`&#010`，CSS为`\A`，JS为`\uA`。

## counter
```html
.dl
 .dt{chapter1}
 .dd{text11}
 .dd{text12}
 .dt{chapter2}
 .dd{text21}
```
```css
.dl {
  counter-reset: dt 0; /* 表示解析到.dl时，重置dt计数器为0 */
  
  & .dt {
    counter-reset: dd 0; /* 表示解析到.dt时，重置dd计数器为0 */
    
    &::before{
        counter-increment: dt 1; /* 表示解析到.dt时，dt计数器自增1 */
        content: counter(dt, lower-roman) " ";
    }
  }
  
  & .dd::before {
    counter-increment: dd 1; /* 表示解析到.dd时，dd计数器自增1 */
    content: counter(dd) " ";
  }
}
```

## counters
嵌套计数器
`counters(<identifier>, <separator>, <list-style-type>?)`
示例：
```html
.ol
  .li
    .ol
      .li{a}
      .li{b}
  .li
    .ol
      .li{c}
```
```css
.ol {
    counter-reset: ol;
    & .li::before {
        counter-increment: ol;
        content: counters(ol, ".");
    }
}
```

## open-quote,close-quote,no-open-quote和no-close-quote
`<q>`会根据父元素的`lang`属性自动创建`::before`和`::after`来实现插入quotation marks。
```html
p[lang=en]>q{英语}
p[lang=no]>q{挪威语}
p[lang=zh]>q{汉语}
```
1. 自定义quotation mark
```css
p[lang=en] > q {
    quotes: "<!--" "-->";
}
```
2. 取消quotation mark
```css
p[lang=en] > q {
  &::before {
      content: no-open-quote;
  }
  &::after{
      content: no-close-quote;
  }
}
```
或
```
p[lang=en] > q {
  &::before {
      content: none;
  }
}
```
3. 为其他元素定义quotation mark
```html
div[lang=no]>.quote{挪威语}
```
```css
div[lang=no] > .quote {
  quotes: "<<-" "->>";
  &::before {
      content: open-quote;
  }
  &::after{
      content: close-quote;
  }
}
```


## 限制
css2.1中引入
除Opera9.5+中所有元素均支持外，其他浏览器仅能用于`:before`,`:after`,`::before`和`::after`内。
无法通过JS获取content的运算结果，只能获取原始值
```cljs
(comment "
  .target::before {
    content: counter(mycounter) " ";
  }
")

(defn get-computed-style [prop]
  (fn [el pseudo-element]
    (-> (js/window.getComputedStyle el pseudo-element)
        (.getPropertyValue prop))))
(def get-content (get-computed-style "content"))

(-> (js/document.querySelector ".target")
    (get-content "::before")
    print)
# Echo is: "counter(mycounter) \“ \""
```


## 浏览器兼容性
IE8



## 参考
http://www.wozhuye.com/compatible/297.html
https://dev.opera.com/articles/css-generated-content-techniques/


## Pseudo Element
默认`display:inline`

### :first-line
只能用于块级元素。
可用的CSS属性：font,color,bacground,word-spacing,letter-spacing,text-decoration,vertical-align,text-transform,line-height,clear.
### :first-letter
只能用于块级元素。
可用的CSS属性：font,color,bacground,margin,padding,border,text-decoration,vertical-align,text-transform,line-height,float,clear.
### ::selection
匹配选中部分的内容。
可用的CSS属性：background, color.
### :before,:after
默认`user-select:none`．因此content的内容无法被用户选中．

```
.target:hover::after
```

### 操作样式的JS API
```
data PseudoElement = ":before" | ":after“ | ”:first-line" | ":first-letter" | "::selection" | ":backdrop" | Null
window.getComputedStyle :: HTMLElement -> PseudoElement -> CSSStyleDeclaration

{- 获取CSS属性值 -}
data CSSPropertyName = "float" | "bacground-color" | ......
data DOMPropertyname = "cssFloat" | "styleFloat" | "backgroundColor" | ......
-- IE9+
CSSStyleDeclaration#getPropertyValue :: CSSPropertyName -> *
-- IE6~8
CSSStyleDeclaration#getAttribute :: CSSPropertyName -> *
-- 键值对方式
CSSStyleDeclaration#[DOMPropertyName] -> *
```

## 示例
### 分割线
```html
p.sep{or}
```
```css
.sep {
  position: relative;
  text-align: center;
  
  &::before,
  &::after {
    content: "";
    box-sizing: border-box;
    height: 1px;
    width: 50%;
    border-left: 3em solid transparent;
    border-right: 3em solid transparent;
    position: absolute;
    top: 50%;
  }
  
  &::before {
    left: 0;
  }
  
  &::after {
    right: 0;
  }
}
```
### 只读效果(通过遮罩原来的元素实现)
```html
.input-group {
  position: relative;
  
  &.readonly::before {
    content: "";
    position: absolute;
    width: 100%;
    height: 100%;
    top: 0;
    left: 0;
  }
}
```
### 计数器
```html
.selections>input[type=checkbox]{option1}+input[type=checkbox]{option2}
.selection-count
```
```css
.selections{
  counter-reset: selection-count;
  
  & input:checked {
    counter-increment: selection-count;
  }
}
.selection-count::before {
  content: counter(selection-count);
}
```

# 伪类
按设置顺序列出：
`:link`，表示链接初始状态
`:visited`，表示链接点击过的状态
`:hover`，表示元素处于悬停的状态
`:focus`，表示元素获取光标焦点的状态
`:active`，表示链接处于激活状态（鼠标按键按下，但未释放）

`:target`
描述：设置目标元素的样式．目标元素就是URL锚对应的元素(目标元素也称为当前活动元素)
兼容性：IE9+
示例：
```
// 当前url为http://foo.com#1
:target {
  border: 1px solid blue;
}
.title {
  color: red;
}
.title:target {
  color: yellow;
}

.not-target[id=1]{target element}
```

`:root`
描述：选择`<html>`元素
兼容性：IE9+

`:checked`
描述：选中`input[type=radio]`和`input[type=checkbox]`的选中的元素
兼容性：IE9+
