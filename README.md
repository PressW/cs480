# cs480
compiler project


## C-Minus Grammar

1.   program              &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     declaration-list
2.   declaration          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     declaration-list declaration | declaration
3.   declaration          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      var-declaration | fun-declaration
4.   var-declaration      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      type-specific **ID** **;** | type-specific ID **[** **NUM** **]** **;**
5.   type-specifier       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      int | void
6.   fun-declaration      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      type-specifier **ID** **(** params **)** compound-stmt
7.   params               &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      param-list | **void**
8.   param-list           &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      param-list **,** param | param
9.   param                &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      type-specifier **ID** | type-specifier **ID** **[** **]**
10.  compound-stmt        &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **{** local-declarations statement-list **}**
11.  local-declarations   &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      local-declarations var-declarations | empty
12.  statement-list       &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     statement-lest statement | empty
13.  statement            &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      expression-stmt | compound-stmt | selection-stmt | iteration-stmt | return-stmt
14.  expression-stmt      &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      expression **;** | **;**
15.  selection-stmt       &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **if** **(** expression **)** statement | **if** **(** expression **)** statement **else** statement
16.  iteration-stmt       &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **while** **(** expression **)** statement
17.  return-stmt          &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **return** **;** | **return** expression **;**
18.  expression           &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      var **=** expression | simple-expression
19.  var                  &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **ID** | **ID** **[** expression **]**
20.  simple-expression    &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      additive-expression relop additive-expression | additive-expression
21.  relop                &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **<=** | **<** | **>** | **>=** | **==** | **!=**
22.  additive-expression  &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      additive-expression addop term | term
23.  addop                &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **+** | **-**
24.  term                 &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      term mulop factor | factor
25.  mulop                &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      ***** | **/**
26.  factor               &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **(** expression **)** | var | call | **NUM**
27.  call                 &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **ID** **(** args **)**
28.  args                 &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      arg-list | empty
29.  arg-list             &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      arg-list **,** expression | expression
