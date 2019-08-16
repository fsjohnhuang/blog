# CSS魔法堂：稍稍深入伪类选择器

## 前言
&emsp;过去零零星星地了解和使用`:link`、`::after`和`content`等伪类、伪元素选择器，最近看书时发现这方面有所欠缺，于是决定稍微深入学习一下，以下为伪类部分的整理。

## 伪类
&emsp;伪类选择器实质上是让设计师可以根据元素特定的状态，设置不同的视觉效果。具体有`:link`、`:visited`、`:hover`、`:active`、`:focus`、`:focus-within`、`:target`、`:root`和`:checked`。
### `HTMLAnchorElement`的4大经典伪类
1. `:link`，用于设置链接初始状态时的样式;
2. `:visited`，用于设置链接被点击过后的样式;
3. `:hover`，用于设置鼠标悬停在链接上方时，链接的样式;
4. `:active`，用于设置鼠标按键按下，但未释放时，链接的样式。

&emsp;想必各位都和我一样，最初接触到的就是上述4个伪类了吧？！而且还死机硬背它们的设置顺序(`LVAH`)吧，哈哈。

### 设置当前目标元素样式
&emsp;还记得URL中的井号吗？从井号(`#`)开始到URL的末尾称为URL的hash或fragment，用于定位页面内某项资源。假设现在页面存在`<h3 id="title">Target</h3>`的元素，那么只要地址栏输入`#title`浏览器就会不断滚动(滚动不一定存在补间动效)直到元素`h3#title`位于可视区的特定位置。（注意：请不要和UI Routing混为一谈）
&emsp;而上述这个被定位的页面资源，被称为**目标元素**或**当前活动元素**！可通过`:target`设置其样式。
&emsp;兼容性：IE9开始支持。

示例：
```
// 当前URL为http://foo.com#1
:target {
    color: red;
}
.title{
    color: blue;
    
    &:target{
        border: solid 1px red;
    }
}

.title{I'm not target element.}
.title#1{Yes, I'm.}
```

### 设置元素获得焦点时的样式
`:focus`用于设置元素处于focus状态下的样式。
兼容性：IE8开始支持。
那么哪些元素支持focus状态呢？那要先弄清楚通过哪些操作可能实现focus。
它们分别是：
1. 鼠标点击;
2. Tab键;
3. 通过JavaScript的`HTMLElement.prototype.focus()`方法。

那么传统上支持focus状态的元素必定是`a`、`button`、`input`、`select`和`textareas`.
而HTML5中增加当元素设置了`contenteditable`或`tabindex`属性时，该元素支持focus状态。
也就是符合以下选择器的元素均支持focus状态。
```
a,button,input,select,textarea,[contenteditable],[tabindex]
```
注意：若`tabindex`属性值小于0，则无法通过Tab键获得焦点。但可以通过鼠标点击 或 脚本时元素获得焦点。

#### JS获取当前得到焦点的元素
```
/* 
 * 加载完成时默认返回body
 * 若某元素获得焦点时，则返回该元素
 */
document.activeElement :: HTMLElement
```
另外还有一个让人误会的属性
```
// 用于检测文档是否得到焦点，即用户是否正在与页面交互
// 页面仅仅位于屏幕可视区域，而用户没有与之交互时返回false。
document.hasFocus :: Void -> Boolean
```

### 设置子元素获得焦点时，该元素的样式
`:focus-within`，用于设置当子元素处于focus状态时，该元素的样式。
兼容性:Chrome63开始支持。

示例：二次确认密码时，密码框高亮
```
.form-control{
  &:focus-within > input{
    &:focus {
      border: solid 1px skyblue;
    }
    
    &:not(:focus){
      border: solid 1px orange;
    }
  }
}

.form-control>input.pwd[type=password]+input.confirm-pwd[type=password]
```

### 其他
1. `:root`，用于设置`<html>`元素的样式，从IE9开始支持。
2. `:checked`，用于设置单选和复选控件被选中的样式，从IE9开始支持。结合伪元素`::before`和`content`属性可以实现灵活高效的自定义单选和复选控件。
3. `:empty`，用于设置没有子节点的元素的样式。`div{ }`为存在TEXT_NODE子节点的元素，而`div{}`则为没有子节点的元素。
4. `:not`，作为谓语表达取反的语义。
5. `:placeholder-shown`，用于设置元素placeholder显示时的样式。

## 总结
尊重原创，转载请注明来自： ^_^肥仔John


## 参考
https://css-tricks.com/almanac/selectors/f/focus/
https://www.zhangxinxu.com/wordpress/2018/01/css-focus-within-pseudo-class-selector
