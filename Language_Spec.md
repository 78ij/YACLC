#  Yet Another C-like language 

## 词法(正则表达式)
```
id      := [a-zA-Z]([a-zA-Z]|[0-9]|_)*
intcon  := [1-9][0-9]*
charcon := '([a-zA-Z]|[0-9]|\\n|\\0)'
floatcon:= [-+]?[0-9]*\.?[0-9]?([eE][-+]?[0-9]+)?
```
## 关键字

char,int,float,void,if,while,for,return,break,continue

## 语法(EBNF)
```
prog	    :	{ dcl ';'  |  func }
dcl	        :	type var_decl { ',' var_decl }
            |	[ extern ] type id '(' parm_types ')' { ',' id '(' parm_types ')' }
            |	[ extern ] void id '(' parm_types ')' { ',' id '(' parm_types ')' }
var_decl	:	id { '[' intcon ']' }
type	    :	char
 	        |	int
            |   float
parm_types	:	void
 	        |	type id { '[' ']' } { ',' type id { '[' ']' } }
func	    :	type id '(' parm_types ')' '{' { type var_decl { ',' var_decl } ';' } { stmt } '}'
 	        |	void id '(' parm_types ')' '{' { type var_decl { ',' var_decl } ';' } { stmt } '}'
stmt	    :	if '(' expr ')' stmt [ else stmt ]
            |	while '(' expr ')' stmt
            |	for '(' [ assg ] ';' [ expr ] ';' [ assg ] ')' stmt
            |	return [ expr ] ';'
            |	assg ';'
            |	id '(' [expr { ',' expr } ] ')' ';'
            |	'{' { stmt } '}'
            |	';'
            |   break
            |   continue
assg	    :	id [ '[' expr ']' ] assgop expr
expr_left   ：	id {'[' expr ']'}
expr	    :	'–' expr
            |	'!' expr
            |	expr binop expr
            |	expr relop expr
            |	expr logical_op expr
            |   expr_left
            |   id  '(' [expr { ',' expr } ] ')' 
            |	'(' expr ')'
            |	intcon
            |	charcon
            |	floatcon
            |   expr_left self_op
binop	    :	+
            |	–
            |	*
            |	/
assgop      :   =
            |   +=
            |   -=
            |   /=
            |   *=
relop	    :	==
            |	!=
            |	<=
            |	<
            |	>=
            |	>
logical_op	:	&&
 	        |	||
self_op     :   ++
            |   --
```
## 语义规则

### 声明的规则
1. 数组的每一维必须具有正整数。（这在语法分析中可以得出，因为本语法中不存在负的int字面值类型）。
2. 一个标识符在全局作用域只能被声明一次，在每个局部作用域只能被声明一次。
3. 一个函数只能拥有最多一个原型且被定义最多一次。
4. 若一个函数拥有原型，它的定义和原型的函数签名必须一致。
5. 在函数定义中，其形参的每个标识符最多出现一次。
6. 函数的形参作用域为此函数的定义。
7. 若函数没有参数，它的定义和原型必须使用void表明这一点。

### 类型规则

变量在使用前必须定义。函数的参数类型和返回值类型在调用前必须指明。若一个标识符的作用域为某个函数，则在次作用域内所有对这个标识符的使用均指代这个实体。若一个标识符作用域为全局，则在函数中对此标识符的使用指代这个全局实体。重定义问题的行为是未定义的。
下面的规则是有关类型兼容性的：

1. int和int兼容，char和char兼容，float和float兼容。
2. int和char相兼容。
3. int、float、char组成的数组本身之间互相兼容。
4. int，float, char类型以及它们组成的数组元素之间互相可以隐式转换（可视为兼容）。
4. 任何不符合以上规则的都不互相兼容。

### 函数定义
1. 对于表达式内的函数调用，该函数的返回类型不能为void。单独构成语句（statement）的函数调用，该函数必须返回void。
2. 返回类型为void的函数，其定义内部不能存在形如return expr;的语句；返回类型不为void的语句，其内部不能存在形如return;的语句。（注意，本实现不做执行路径检查，故本条规则不一定保证程序不存在问题）

### 表达式

1. 若e为字面值常量（floatcon，intcon，charcon），则其类型为对应的类型。
2. 若e为标识符，则e的类型为标识符的类型。若e为一个数组的元素，则它的类型是数组元素的类型。
3. 若e为函数调用，则其类型为函数返回值类型。
4. 若e为形如e1+e2,e1-e2,e1*e2,e1/e2,-e1,e1++,e1--的表达式，则e的类型按以下规则确定：
    * e1和e2为相同类型，则e为此类型；
    * e1和e2为不同类型，则e为按float、int、char的优先级确定，类型为其中排名最高的。
5. 若e为形如e1>=e2,e1==e2,e1<=e2,e1 < e2,e1 > e2,e1 != e2，e1&&e2，e1||e2,!e1的表达式，则e的类型为int。
6. 数组的索引必须具有int类型。
7. 函数调用的每一个实参类型必须和形参类型兼容。
8. +，-，*，/，<,>,<=,>=,==,!=中，将先把char转换为int，然后若有float，转换为float，并进行运算。
9. &&,||,!的子表达式类型和值会被转换为int。

### 语句

1. 只有char，int，float或它们组成的数组的元素才能作为赋值的对象。赋值语句的右边表达式的类型必须和左边的类型兼容。（复合赋值语句中，等价于一个表达式的类型和左边的类型兼容）
2. return语句中表达式的类型必须和函数的返回值兼容。
3. if,for和while的条件表达式必须和int类型兼容。