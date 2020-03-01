parser combinatore

一般编译器会将依赖CPU生成的机器码的部分单独归为一个名为Backend的模块，然后根据不同的CPU更换相应的Backend。

解释型语言经过编译后分别生成以下两种形式的代码，用于后期运行。
1. 分析树
2. 字节码（更底层）

JIT(Just-In-Time)编译：在运行的同时将字节码转换为机器码的功能，这个功能不属于解释器的。

辅助工具
yacc/bison：用于根据语法规则自动生成解析器。
lex/flex：用于根据词法规则自动生成词法分析器。
#+begin_src
# 安装
> sudo apt install bison flex

# 编译
> bison -d calc.y
> flex calc.l
> gcc -o calc lex.yy.c calc.tab.c -lm

# 生成解析器包含定义的终结符、非终结符、冲突和解析对照表(parse table)信息的calc.output文件
> bison -dv calc.y
#+end_src
calc.output内容解读：
1. $accpet代表输入开始，$end代表输入结束。
2. 状态段落中，BNF符号间的“句号“代表当前匹配的规则下，解析到哪个token。下方空行后的内容为下一个token的转换规则。
3. 在状态a中执行归约，执行后还在状态a中。

词法分析->语法分析->语义分析->生成代码
词法分析：将源码分割为若干个记号(token)；
  词法分析器(lexical analyzer)
语法分析：将记号构建分析树/语法树/抽象语法树；
  解析器(parser)
语义分析：检查语法正确和是否存在逻辑问题；
生成代码：根据分析树，生成机器码或字节码等最终可执行代码。

将分析树/语法树中一些无用记号剔除后才能叫抽象语法树。

特征符：用于区别Token种类的代号。
Token包含3个属性：种类，原始字符和值。不同种类的Token，传送给解析器的属性不同。

BNF(巴科斯范式，Backus Normal Form)，用于定义语法规则。
示例：整数加减
#+begin_src
1 line: expr CR
      ;
2 expr: term
      | expr ADD term
      | expr SUB term
      ;
3 term: INTEGER
      ;
#+end_src
1. 其中line,expr,term为非终结符(nonterminal), CR,ADD,SUB和INTEGER为终结符(terminal)。
2. 每条语法规则称为Production。
3. Production左侧的为Left Hand Side，右侧为Right Hand Side。
4. 第一条Production的的Left Hand Side称为Start Symbol。

Top-Down(自顶向下)：
就是从Start Symbol开始出发。

现在解析1+2-3的过程如下：
1. 词法分析得到Token序列：INTEGER(1),ADD,INTEGER(2),SUB,INTEGER(3)
2. 将INTEGER(1)移进栈中，且其符合规则3，因此可对其进行归约转换为term。此时栈数据为[term]，符合规则2，继续归约转换为expr，栈数据最终变为[expr]。
3. 移进下一个Token，栈数据变为[expr ADD]，没有符合的规则，继续移进下一个TokenINTEGER(2)，该Token匹配规则3归约为term，此时栈数据为[expr ADD term]，整体匹配规则2，归约为expr，栈数据由回到[expr]了。
4. 移进下一个Token，栈数据变为[expr SUB]，继续移进下一个Token INTEGER(3)，最后得到栈数据为[line]


shift(移进)：将Token放进栈的过程。
reduce(归约)：Token或栈数据匹配某个语法规则，触发置换的过程。

冲突(conflict)：语法模糊不清的地方。2种冲突
1. 归约/归约(reduce/reduce)：同时存在多个可归约的规则;
  解决方法：以第一个匹配的优先。
2. 移进/归约(shift/reduce)：既满足移进又满足归约规则。
  解决方法：优先匹配移进规则。

关键字分上下文无关关键字(就是一般的关键字) 和 上下文关键字(context keyword)，上下文关键字是在特殊的区域中才对编译器有特殊意义的，如C#的get仅在属性中作为关键字使用，其他区域均作为普通的标识符使用。

** 语法分析器
*** 递归下降分析(recursive descent)
当命中非终结符时，会递归调用其下级函数。采用此方式实现的解析器称为递归下降解析器。
做法：
将BNF转换为语法图(syntax diagram)
1. 一个非终结符对应一个处理函数
2. 语法图里出现非终结符代表对应处理函数被调用

环形缓冲区(Ring Buffer)，预读一个Token，一旦发现预读的Token不需要时，则其暂存到环形缓冲区。

左递归BNF语法
#+begin_src
expression
         : term
         | expression ADD term
         | expression SUB term
         ;
term
         : primary_expression
         | term MUL primary_expression
         | term DIV primary_expression
         ;
primary_expression
         : DOUBLE_LITERAL;
#+end_src
Syntax Graph
#+begin_src
expression
         : term (ADD/SUB term)*
         ;
term
         : primary_expression (MUL/DIV primary_expression)*
         ;
primary_expression : DOUBLE_LITERAL;
#+end_src
代码实现
#+begin_src
double parse_expression(){
  double term1 = parse_term();
  Token token;

  for (;;){
    get_token(&token);
    if (token.kind == OPERATOR_ADD_TOKEN || token.kind == OPERATOR_SUB_TOKEN){
      double term2 = parse_term();
      if (token.kind == OPERATOR_ADD_TOKEN){
        term1 += term2;
      }
      else {
        term1 -= term2;
      }
    }
    else {
      unget_token(token);
      break;
    }
  }

  return term1;
}
#+end_src

LL表示从程序源代码的最左边开始读入，并且发生归约时Token从左边开始归约(即采用最左推导-Leftmost derivation），置换为分析树。采用递归下降的LL解析器，是按照自上而下的顺序解析，无法处理"左递归"的语法。
LR表示从程序源代码的最左边开始读入，但发生归约时Token从右边开始归约(也称为最右推导-Rightmost derivation)，置换为分析树。LR解析器是按照自下而上的顺序解析，所以也称为”自底向上“解析器。

LL(1)后的1表示预读1个Token(lookahead symbol)，即预读1个Token做LL分析。
LALR(1)的LA就是Look Ahead，即预读1个Token作LR分析。
LL(n)，前瞻N个Token。

能够被LL(1)解析的语法称为LL(1)语法。

** 无类型语言

顶层结构：执行语句可写在函数和类的外面。


## 波兰表达式(Polish Notation, 前缀表达式)
中缀表达式 5 + ( 6 - 4 / 2) * 3 的波兰表达式为 + 5 * - 6 / 4 2 3

### 中缀表达式转换为波兰表达式的方法
准备一个波兰表达式栈，和一个操作符(Operator)栈
1. 从右到左顺序扫描中缀表达式；
2. 若为操作数(Operand)则将操作数压入波兰表达式栈；
3. 若为右括号则压入操作符栈；
4. 若为左括号则对操作符栈执行连续多次弹栈，直至将操作符栈中最近一个右括号都弹栈为止，过程中被弹出的非括号类符号均依次压入波兰表达式栈中；
5. 若为非括号操作符
   5.1. 若当前操作符优先级低于操作符栈顶操作符，则操作符栈弹栈，并压入波兰表达式栈中
   5.1. 若当前操作符优先级高于操作符栈顶操作符，则压入操作符栈
6. 扫描完毕后将操作符栈弹栈至清空，过程中被弹出的符号均依次压入波兰表达式栈中
7. 对波兰表达式栈弹栈至清空，过程中被弹出的栈帧依次进入FIFO队列即可。

### 波兰表达式的运算方式
准备一个操作数(Operand)栈
1. 从右到左顺序扫描波兰表达式；
2. 若为操作数则压栈；
3. 若为操作符则对操作数栈连续执行2次弹栈，并作为操作符号的操作数进行运行，并将运算结果再次亚栈；
4. 直至扫描完毕。

## 逆波兰表达式(Reverse Polish Notation, 后缀表达式)
中缀表达式 5 + ( 6 - 4 / 2) * 3 的逆波兰表达式为 5 6 4 2 / - 3 * +

### 中缀表达式转换为波兰表达式的方法
准备一个逆波兰表达式栈，和一个操作符(Operator)栈
1. 从左到右顺序扫描中缀表达式；
2. 若为操作数(Operand)则将操作数压入逆波兰表达式栈；
3. 若为左括号则压入操作符栈；
4. 若为右括号则对操作符栈执行连续多次弹栈，直至将操作符栈中最近一个左括号都弹栈为止，过程中被弹出的非括号类符号均依次压入逆波兰表达式栈中；
5. 若为非括号操作符
   5.1. 若当前操作符优先级低于操作符栈顶操作符，则操作符栈弹栈，并压入逆波兰表达式栈中
   5.1. 若当前操作符优先级高于操作符栈顶操作符，则压入操作符栈
6. 扫描完毕后将操作符栈弹栈至清空，过程中被弹出的符号均依次压入逆波兰表达式栈中
7. 此时逆波兰表达式栈顶就是逆波兰表达式的末尾。

### 逆波兰表达式的运算方式
准备一个操作数(Operand)栈
1. 从左到右顺序扫描逆波兰表达式；
2. 若为操作数则压栈；
3. 若为操作符则对操作数栈连续执行2次弹栈，并作为操作符号的操作数进行运行，并将运算结果再次亚栈；
4. 直至扫描完毕。
