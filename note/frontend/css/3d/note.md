GPU是分层渲染，这样可以让GPU和CPU并行工作。
[gpu-accelerated-compositing-in-chrom](http://www.chromium.org/developers/design-documents/gpu-accelerated-compositing-in-chrome "gpu-accelerated-compositing-in-chrome")

ie9已经支持gpu加速，但却起到反效果。

```
/* 开启GPU加速 */
.cube{
  transform: transition3d(0,0,0);
  /* 或者 transform: translateZ(0); */
}
```

Q:在chrome下，当元素设置为`position: absolute/fixed`且开启gpu加速，则元素有可能凭空消失。
A:避免同时设置

Q:启动gpu加速后，浏览器可能会频繁抖动。
A:使用如下CSS属性
```
backface-visibility: hidden;
perspective: 1000;
```

## 监控fps
1. chrome devtool/performance/rendering/FPS meter
可查看的指标：
Frame Rate(fps)
GPU Raster(ization)，是否启用gpu光栅化，通过`chrome://flags`启用`GPU rasterization`。
GPU Memory，显示已用(used)和最大(max)的显存。

2. chrome devtool/more tools/layers
可查看当前页面有多少个layer
Size，复合层尺寸
Compositing Reasons，复合层生成的原因
Memory estimate，复合层所占内存
Paint count，repaint次数
Slow scroll region，
Sticky postion constraint


rendering tree 后会一次执行，reflow->repaint->composite
reflow，会计算每个元素的形状（宽、高）和位置。
repaint，绘制元素的颜色、背景等。
composite，浏览器将各层信息发送给gpu，由gpu合成显示到屏幕上。
composite的过程是：
1. 生成每个复合层的图像
2. 准备复合层的数据
3. 准备动画着色器
4. 向gpu发送数据
隐式composite：当位于包含复合层的兄弟元素的上方时，该元素会被隐式提升到一个新的复合层。
因此元素A和元素B分别包含在各自的复合层，若元素A发生动画，那么仅元素A需repaint，其他复合层可重用。

减少reflow和repaint的方式：
1. 不要一条一条修改dom样式，尽量使用className一次修改;
2. dom离线后修改
2.1. 使用domcumentFragment操作dom
2.2. 设置`display:none`（会触发一次reflow），然后作修改后在显示出来;
2.3. clone一个dom到内存，修改后再通过`replaceWith`或`replaceChild`替换。
3. 不要使用table布局，局部改动都会引发整个table的reflow
4. transform和opacity只会引发composition，不会引起relow和repaint

Q: 如何实现仅触发composite?
A: css property需要不影响normal flow，不依赖normal flow和不造成repaint。
只有transform和opacity满足上述三个要求，**所以动画中仅修改transform和opacity属性，即使不触发gpu加速，也会生成复合层**。

position为absolute作移动，虽然不会影响normal flow，但它会依赖normal flow。因为left值可以为相对offsetParent的百分数。
```
<style>
  @keyframes move-left {
	100% {
	  left: 70px;
	}
  }
  .move-left {
    position: absolute;
	animation: move-left 2s;
  }
</style>
<div class="move-left"></div>
```

gpu加速好处：动画工作在独立的线程，和js并行。
gpu加速的坏处：
1. 提升元素到复合层需要额外的repaint
2. 复合层传输到gpu有延时（当复合层多时，会出现界面抖动）
3. 复合层需要额外的内存
4. 耗电

以下情况会提升元素到独立的复合层
1. 设置`position: fixed`，当浏览器可视区出现滚动条时会生成复合层，滚动条消失时复合层就会销毁;
2. `<flash>`,`<canvas>`,`<iframe>`和`<video>`;
3. 通过CSS transition、animation和Web Animation API设置含transform和opacity的动画，动画开始时会生成复合层，结束后复合层会销毁;
4. 设置了`will-change`css属性的元素;
5. 设置了3D transform css属性的元素;
6. 设置CSS filter
7. 兄弟元素拥有复合层，且z-index比其他兄弟元素低，那么其他兄弟节点均会生成复合层

will-change，让开发者告知浏览器该元素有哪些属性将发生变化，让浏览器可以提前准备和优化。有可能会提升元素到新的复合层中。
```
will-change: auto | <animateable-feature>
<animateable-feature>的值：
scroll-position:将会改变滚动条的位置
contents:将会改变元素的内容
<custom-ident>:将改变元素的某css属性，如transform、left、top等

兼容性：chrome36+
```
最佳实践：
1. 最小范围使用（作用场景、作用属性最小范围）
2. 告知浏览器**即将**发生的变化，而不是**正在**发生的变化。
```
/* 当进入祖先元素时预先设置will-change，退出时自动卸载复合层 */
.ancestor:hover .target {
  will-change: transform, opacity;
}
.target {
  transition: transform;

  &:hover {
    transform: scale(1.5);
  }
}
```
```
const target = document.querySelector(".target")
target.addEventListener("mousedown", e => {
  e.target.style.whillChange = "transform"
})
target.addEventListener("click", e => {
  e.target.style.transform = "scale(1.5)"
})
target.addEventListener("animationEnd", e => {
  e.target.style.willChange = "auto"
})
```
反模式：
```
/* 告知正在发生的变化，不但没优化，反而会让浏览器多生成复合层，降低性能 */
.target {
  transition: transform;
  
  &:hover {
    will-change: transform;
    transform: scale(1.5);
  }
}

/* css属性过多，增加浏览器负担 */
.ancestor:hover .target {
  will-change: all;
}
```

技巧
1. 通过opacity实现改变背景色动画
```
.target {
  width: 100px;
  height: 100px;
  background: red;
  
  &::before {
    content: "";
	display: block;
	width: 100%;
	height: 100%;
	background: blue;
	opacity: 0;
	transition: opacity 20s;
  }
  
  &:hover::before {
    opacity: 1;
  }
}
```
2. 压缩元素所占的显存
一张宽高均为300px的图片，所占显存为`300*300*4=360000`。
```
/* .target的显示效果是100px*100px */
.target {
  width: 10px;
  height: 10px;
  transform: scale(10);
}
```

http://www.html5rocks.com/en/tutorials/speed/high-performance-animations/
https://segmentfault.com/a/1190000008015671
https://csstriggers.com/
