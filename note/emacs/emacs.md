## 默认打开Emacs terminal ##
```
# 在~/.bashrc中添加
alias emacs='emacs -nw'
```

## 将CapsLook改为Ctrl
```
# /etc/default/keyboard
XKBOPTIONS=“ctrl:nocaps”
```
然后执行`sudo dpkg-reconfigure keyboard-configuration`

## 配置color-theme.el
下载资源
```bash
mkdir ~/.emacs.d/color-theme-6.5.5/
curl -o ~/.emacs.d/color-theme-6.5.5/color-theme.el http://lifegoo.pluskid.org/wiki/lisp/color-theme.el
```
在~/.emacs.d/init.el
```
;; -*- lexical-binding: t -*-
(add-to-list 'load-path "~/.emacs.d/color-theme-6.5.5")
;; 由于2.4开始Emacs对配色主题作了重大修订，因此引入旧的主题时，需打上plist-to-alist的补丁。
(defun plist-to-alist (the-plist)
  (defun get-tuple-from-plist (the-plist)
      (when the-plist
            (cons (car the-plist) (cadr the-plist))))
  (let ((alist '()))
      (while the-plist
            (add-to-list 'alist (get-tuple-from-plist the-plist))
	          (setq the-plist (cddr the-plist)))
		    alist))
(require 'color-theme)    ;; 引入依赖
(color-theme-subtle-green) ;; 启用配色主题
```
预览颜色-`M-x color-theme-select`，然后光标移动到对应的配色主题上回车即可预览，再按`d`即可获取如`(color-theme-dark-blue)`等启用主题的表达式。

包管理(MELPA)
-------------
`M-x package-install [ret] tide`，安装包

前缀
----
`C-c`，当前模式特有的命令
`C-x`，文件和缓冲区的命令
`C-h`，帮助命令
`M-x`，调用函数

## 帮助 ##
`C-h b`(describe-bindings)，显示当前major mode的所有绑定信息
`C-h f`(describe-function)，显示函数用途
`C-h v`(describe-variable)，显示变量用途
`C-h w`(where-is)，显示指定函数绑定到哪个快捷键
`C-h t`(help-with-tutorial)，调出emacs tutorial
`C-h r`(info-emacs-manual)，调出emacs manual

## 光标移动
`C-f`(forward-char), 前移1个字符
`C-b`(backward-char), 后退1个字符
`M-f`(forward-word), 前移1个单词
`M-b`(backward-word), 后退1个单词
`C-a`(beginning-of-line), 移至行首
`C-e`(end-of-line), 移至行尾
`beginning-of-line-text`，移至行第一字符前
`M-a`(backward-sentence), 移至句首
`M-e`(forward-sentence),移至句尾
`C-n`(next-line), 移至下一行
`C-p`(previous-line), 移至上一行
`M-{`(backward-paragraph), 向上移一段
`M-}`(forward-paragraph), 向下移一段
`M-<`(beginning-of-buffer), 移至当前Buffer第一个字符
`M->`(end-of-buffer), 移至当前Buffer最后一个字符
`C-v`(scroll-down), 向前翻页
`M-v`(scroll-up), 向后翻页
`M-x goto-line` 或 `M-g M-g`, 跳转到指定行
`M-x goto-char`,光标移至文件的第n
`C-l`(recenter), 光标所在行位于窗口中央
`M-r`, 将光标移至窗口中央那行
`C-u <命令重复执行次数> <命令>`或`M-<命令重复执行次数> <命令>`, 重复执行n次命令。如`C-u 10 C-p`就是向上移动10行。

`(modify-syntax-entry ?_ "w")`，单词不再以下划线作为划分。

### 插件
[ace-jump-mode](https://github.com/winterTTr/ace-jump-mode "ace-jump-mode")
跨windows标记字符、单词，快速移动光标
```
# 安装
curl -o ~/.emacs/pkgs/ace-jump-mode.el https://raw.githubusercontent.com/winterTTr/ace-jump-mode/master/ace-jump-mode.el
```
```
;; 配置
(add-to-list 'load-path "~/.emacs/pkgs")

(autoload
  'ace-jump-mode
  "ace-jump-mode" t)
(eval-after-load "ace-jump-mode" '(ace-jump-mode-enable-mark-sync))
	  
(define-key global-map (kbd "C-c SPC") 'ace-jump-mode)
(define-key global-map (kbd "C-x SPC") 'ace-jump-mode-pop-mark) ;; 光标移动到执行ace-jump前的位置
```
```
;; 使用
"C-c SPC" ==> ace-jump-word-mode
enter first character of a word, select the highlighted key to move to it.

"C-u C-c SPC" ==> ace-jump-char-mode
enter a character for query, select the highlighted key to move to it.

"C-u C-u C-c SPC" ==> ace-jump-line-mode
each non-empty line will be marked, select the highlighted key to move to it.
```

## 编辑
`M-BackSpace`(backward-kill-word), 删除光标前的单词
`M-d`(forward-kill-word), 删除光标后的单词
`BackSpace`(delete-backward-char), 删除光标前的字符
`C-d`(delete-char), 删除光标后的字符
`C-/`(undo), 撤销操作
`C-/ C-/`, 重做操作
`C-@`(set-mark-command), 对内容进行选中处理，称为标记(Mark)。选中的内容称为区域(Region)
`M-@`(mark-word),选中光标后的单词
`M-h`(mark-paragraph), 选中段落
`C-x C-x`(exchange-point-and-mark), 交换区域的开始和结束位置
`C-x C-p`, 选中当前页
`C-x h`, 选中整个Buffer
`C-x C-f`, 打开/创建目标文件，直接回车则打开空的buffer
`C-x C-c`, 关闭Emacs
`C-g`, 中断当前执行的命令
`M-x indent-region`, 缩进选中的region。
`M-z`(zap-to-char), 删除光标到指定字符（包含指定字符）的内容
`C-o`(open-line)，插入空行
`C-x C-o`(delete-blank-line)，删除空行
`C-x z`(repeat)，重复前一个命令

`M-c`(capitalize-word)，光标后单词首字母大写
`M-u`(upcase-word)，光标后单词大写
`M-l`(downcase-word)，光标后单词小写
downcase-region，选定区域小写
upcase-region，选定区域大写

`M--`(negtive-argument)，方向操作，后面叠加其他需要反向操作的命令
`M-;`(comment-dwim)，在所在行最后添加注释，或选中region则注释整个region



删除(delete), 移除(kill), 召回(yank) 和 移除环(kill-ring)

### kill
`C-k`(kill-line) ，移除到行尾
`M-k`(kill-sentence)，移除到句尾
`M-x kill-whole-line`，移除整行
`M-w`(kill-ring-save), 将内容保存到kill-ring但不从buffer中删除
`C-w`(kill-region)，移除Region
`C-y`(yank)，召回kill-ring当前指针的内容
`M-y`(yank-pop)，移动指针，并召回指针的内容
`C-u n M-y`，召回kill-ring中指定槽位的内容

mark-ring

	
## 搜索
`C-s <搜索字符串>`, 向前增量搜索
`C-r <搜索字符串>`, 向后增量搜索
`C-s C-w`, 将光标所在单词作为<搜索字符串>
`C-s C-y`, 将光标所在到行尾作为<搜索字符串>
`C-s M-y`, 把kill-ring的内容作为<搜索字符串>
`M-s w <搜索字符串>`(isearch-forward-word), 向前词组查询
`M-s w C-r <搜索字符串>`(isearch-backward-word), 向后词组查询
`M-x isearch-forward-regexp`, 向前正则查询
`M-x isearch-backward-regexp`, 向后正则查询

search-ring, 队列，每次搜索的<搜索字符串>都会入队列。
`C-s M-n`, 从search-ring中获取上一个记录
`C-s M-p`, 从search-ring中获取下一个记录
`C-s M-c`, 切换当前搜索是否大小写敏感

`M-x replace-string`, 向前一次性替换所有匹配的字符串
`M-x replace-regexp`, 向前一次性替换所有匹配的字符串
`M-x query-replace`, 和`M-x replace-string`一样，但每项替换前均会咨询。y表示执行，n表示跳过，q表示退出替换，`C-r`表示进入递归编辑状态
在替换过程中，临时需要编辑其他内容，然后继续回到替换过程时，可以先按`C-r`进入递归编辑状态，然后编辑完后，按`C-M-c`回到替换过程。

## Buffer
`C-x C-b`, 列出当前所有缓冲区
`C-x k`, 关闭当前缓存区
`C-x b`, 切换缓存区
`C-x C-k s`, 保存当前Buffer
`C-x s`, 保存所有未保存过的Buffer
`C-x C-w`, 文件另
## 窗口
`C-x 0`(delete-window), 关闭当前窗口
`C-x 1`(delete-other-windows), 最大化当前窗口
`C-x winner-mode`进入winner-mode，然后`winner-undo`或`C-c <left>`，恢复原窗口的布局
`C-x 2`(split-window-vertically), 垂直分割当前窗口
`C-x 3`(split-window-horizontally), 水平分割当前窗口
`C-x o`(other-window),选择下一个窗口
windmove-left/up/right/down, 切换到对应方向的窗口上
`C-M-v`(scroll-other-window),滚动下一个窗口
`C-x 4 f`(find-file-other-window), 在另一个窗口打开文件
`C-x 4 r`(find-file-read-only-other-window)，在另一个窗口以只读方式打开文件
`C-x 4 d`(dired-other-window), 在另一个窗口打开目录
`C-x 4 m`(mail-other-window), 在另一个窗口写邮件
`C-x 4 b`(switch-to-buffer-other-window), 在另一个窗口打开缓存，并且光标移到新窗口
`C-x 4 C-o`(display-buffer)，在另一个窗口打开缓存，并且光标保持在当前窗口
`C-x ^`(enlarge-window)，增加窗口1行高度
`C-x }`(shrink-window-horizontally)，收窄窗口1列的宽度
`C-x {`(enlarge-window-horizontally)，增加窗口1列的宽度
`C-x +`(balance-windows)，使所有窗口大小一样
`C-x -`(shrink-window-if-larger-than-buffer)，将窗口缩小到恰好适配buffer

`M-x compare-windows`，两个窗口的buffer做diff
`M-x scroll-all`，启动scroll-all的minor mode，打开相同buffer的windows，一直保持滚动同步
`M-x follow-mode`，启动follow的minor mode，将打开相同buffer的windows连接为一个整体的window。

### 插件
[window-numbering](https://raw.githubusercontent.com/nschum/window-numbering.el/master/window-numbering.el)
将子窗口自动编号(`M-0`到`M-9`)

## 书签 ##
`bookmark-set`，`C-x r m`设置书签
`bookmark-bmenu-list`，列出所有已保存的书签，选中书签后回车就会跳转到该书签，按q则退出。
`bookmark-delete`，删除一个书签
`bookmark-jump`，`C-x r b`跳转到书签所在行
`bookmark-save`，保存书签到~/.emacs.bmk中

## 执行elisp
`M-x load-file <RET> <RET>`, 运行当前文件
`M-x load-file 文件路径 <RET> <RET>`, 运行指定文件
`M-x eval-buffer`, 运行当前Buffer
`C-x C-e`, 运行当前行的elisp代码

## shell
`M-x ansi-term`

## Minor配置
```
(tool-bar-mode -1)    ;; 关闭工具栏
(menu-bar-mode -1)    ;; 关闭菜单栏
scroll-bar-mode -1)  ;; 关闭文件滑动控件
(global-linum-mode 1) ;; 启动行号
(setq linum-format "%d ") ;; 设置行号的显示格式
(delete-selection-mode 1) ;; 启用选中某段内容时，输入则会先删除该段内容
(setq make-backup-files nil) ;; 关闭自动生成备份文件(~为后缀的文件)
(setq backup-directory-alist '(("." . "~/.backups"))) ;; 或者将备份文件全部保存到~/.backups目录下
;; #yourfile#就是上次未保存的文件内容，emacs会提示你可以恢复文件
;; M-x recover-file <ret> 文件名 <ret>
;; yes <ret>
;; C-x C-s

(global-hl-line-mode 1) ;; 光标所在行高亮
(global-auto-revert-mode 1) ;; Emacs自动加载外部修改过的文件
(setq auto-save-default nil) ;; 关闭自动保存文件
(show-paren-mode 1) ;; 当光标位于括号上时，会高亮其匹配的另一个括号
(electric-pair-mode 1) ;; 自动补全括号、引号等
(winner-mode 1) ;; 启用winner-mode，然后就可以执行窗口的redo和undo了
```

缩写，输入缩写然后空格自动展开
```
(setq-default abbrev-mode 1)
(define-abbrev-table 'global-abbrev-table '(
  ("jabbrev" "abbrevation")
))
```

Hippie-expand，Emacs自带的自动完成框架。所有缓存中的内容均可作为自动完成的素材
```
(setq hippie-expand-try-function-list '(try-expand-debbrev
					try-expand-debbrev-all-buffers
					try-expand-debbrev-from-kill
					try-complete-file-name-partially
					try-complete-file-name
					try-expand-all-abbrevs
					try-expand-list
					try-expand-line
					try-complete-lisp-symbol-partially
					try-complete-lisp-symbol))
(global-set-key (kbd "M-/") 'hippie-expand)
```

## Dired Mode, 目录管理
`C-x d`进入Dired Mode。
在Dired Mode下可执行如下操作
`+`，创建目录
`g`，刷新目录
`C`，拷贝
`D`，删除
`R`，重命名
`d`，标记删除
`u`，取消标记
`x`，执行所有标记

```
(setq dired-recursive-deletes 'always) ;; 默认递归删除
(setq dired-recursive-copies 'always) ;; 默认递归拷贝
(put 'dired-find-alternate-file 'disabled nil) ;; 重用唯一的缓冲区作为Dired Mode显示专用
```

### 插件
[find-file-in-project](https://github.com/technomancy/find-file-in-project "find-file-in-project")

## Minibuffer
`M-x set-variable`，设置变量。例子：`M-x set-variable <ret> insert-default-directory <ret> nil`关闭`find-file`的默认路径。
Minibuffer和buffer操作基本相同，除了`C-o`输入回车、`C-q <tab>`输入tab键和`C-q <spc>`输入space键。
光标位于Minibuffer，滚动邻近buffer区采用`M-<pgup>/<pgdown>`。
自动补全：
`<tab>`，尽可能补全，当失败时执行`?`
`<spc>`，最多补全一个单词，当失败时执行`?`
`?`，罗列所有可能的命令，然后光标移动到命令列表的buffer，选中命令后按`<ret>`即可以。
例如：
`g-l`，命令列表中就含有`goto-line`了。

`M-p`，上一个历史命令
`M-n`，下一个历史命令
`M-r <ret>`，向前正则查询历史命令
`M-s <ret>`，向后正则查询历史命令

### 插件
[smex](https://github.com/nonsequitur/smex/ "smex")



## Major配置
```
;; 根据文件名匹配Major Mode
(setq auto-mode-alist
  (append
    '(("\\.js\\'" . js2-mode)
	  ("\\.html\\'" . web-mode)
	  ("\\.md\\'" . markdown-mode))
    auto-mode-alist))
```
命名方式
`modename-mode`,模式命名规则
`modename-hook`,模式的钩子
`modename-variable`,模式的变量

## 插件
### 自动完成
#### Company
```
(global-company-mode 1) ;; 启用
```

### Markdown ###
![Homepage](https://jblevins.org/projects/markdown-mode/ "Homepage")
`S-TAB`，视图模式切换（大纲、目录、正常）
`C-c C-t n`，插入hash样式标题，n从1到5。
`C-c C-t t`，插入underline样式一级标题。
`C-c C-t s`，插入underline样式二级标题。
`C-c C-a l`，插入链接。
`C-c C-i`，插入图片。
`C-c C-s b`，插入引用内容。
`C-c C-s c`，插入inline代码
`C-c C-p b`，插入粗体
`C-c C-p i`，插入斜体
`C-c -`，插入水平线

### js2-refactor ###
[JavaScript重构工具](https://github.com/magnars/js2-refactor.el)

### ag ###
helm-ag可以在emacs中调用ag
`(global-set-key (kbd "C-c p s") 'helm-do-ag-project-root)`

### JS语法检查 ###
![Flycheck](https://github.com/flycheck/flycheck "Flycheck")

### CSS辅助 ###
rainbow-mode,css颜色代码作为背景色

### 代码片段 ###
[auto-yasnippet](https://github.com/abo-abo/auto-yasnippet "auto-yasneppit")
[emmet-mode](https://github.com/smihica/emmet-mode "emmet-mode")
[web-mode](http://web-mode.org/ "web-mode")
### Evil, VIM快捷键 ###
Normal Mode -> Normal State


### Org Mode
`C-c C-e h o`,导出html文件.
