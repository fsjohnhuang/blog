1. 国际化不仅仅是语言、时间、货币、书写方向，还有使用习惯(例如：提示消息停留时长)
2. 不要使用中文或unicode字符作为多语言key，半角和全角符号会引发翻译异常
3. 不要采用动态生成多语言key的策略，应采用静态多语言key，从而可预见翻译范围
4. 要增加多语言裸装模式，从而检查多语言的问题
5. 外来数据如何做多语言呢？
6. 多语言key采用英语(ASCII单字节编码)，并尽量精炼简短，可减小语言包的大小．
