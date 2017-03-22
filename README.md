# cs480
compiler project


## C-Minus Grammar

1.   program              &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;     declaration-list
2.   declaration          &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;     declaration-list declaration | declaration
3.   declaration          &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;      var-declaration | fun-declaration
4.   var-declaration      &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;      type-specific **ID** **;** | type-specific ID **[** **NUM** **]** **;**
5.   type-specifier       &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;      int | void
6.   fun-declaration       ->      type-specifier **ID** **(** params **)** compound-stmt
7.   params                ->      param-list | **void**
8.   param-list            ->      param-list **,** param | param
9.   param                 ->      type-specifier **ID** | type-specifier **ID** **[** **]**
10.  compound-stmt         ->      **{** local-declarations statement-list **}**
11.  local-declarations    ->      local-declarations var-declarations | empty
12.  statement-list        ->      statement-lest statement | empty
13.  statement             ->      expression-stmt | compound-stmt | selection-stmt | iteration-stmt | return-stmt
14.  expression-stmt       ->      expression **;** | **;**
15.  selection-stmt        ->      **if** **(** expression **)** statement | **if** **(** expression **)** statement **else** statement
16.  iteration-stmt        ->      **while** **(** expression **)** statement
17.  return-stmt           ->      **return** **;** | **return** expression **;**
18.  expression            ->      var **=** expression | simple-expression
19.  var                   ->      **ID** | **ID** **[** expression **]**
20.  simple-expression     ->      additive-expression relop additive-expression | additive-expression
21.  relop                 ->      **<=** | **<** | **>** | **>=** | **==** | **!=**
22.  additive-expression   ->      additive-expression addop term | term
23.  addop                 ->      **+** | **-**
24.  term                  ->      term mulop factor | factor
25.  mulop                 ->      ***** | **/**
26.  factor                ->      **(** expression **)** | var | call | **NUM**
27.  call                  ->      **ID** **(** args **)**
28.  args                  ->      arg-list | empty
29.  arg-list              ->      arg-list **,** expression | expression
