https://www.w3.org/TR/html/syntax.html#void-element
## Void Element
Void element must not have content, they are just kind of pointers to an element that is installed in the page.
So we can use self-closing tag to indicate void element.
```
<br> <hr> <img> <input> <link> <meta>
<area> <base> <col> <command> <embed> <keygen> <param> <source> <track> <wbr>
```
self-closing tag in xhtml1.0
```
<img src="john.png" />
```
self-closing tag in html4.01
```
<img src="john.png">
```
self-closing tag in html5
```
<img src="john.png" />
<img src="john.png">
```

## 5 kinds of space entity
1. No-break Space, `&nbsp;`
2. En Space, `&ensp;`. `en` is unit of typograph, is half of `em`. `en` is the width of half-width, `em` is the width of full-width.
3. Em Space, `&emsp;`. Full-width space.
4. Thin Space, `&thinsp;`, its width is about 1/6 of `em`.
5. Zero with Non Joiner, `&zwnj;`
6. Zero with Joiner, `&zwj;`
