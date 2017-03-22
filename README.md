# cs480
compiler project


## C-Minus Grammar

1.   _program_              &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     _declaration-list_
2.   _declaration-list_    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     _declaration-list declaration_ | _declaration_
3.   _declaration_          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _var-declaration_ | _fun-declaration_
4.   _var-declaration_     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _type-specific_ **ID** **;** | _type-specific_ **ID** **[** **NUM** **]** **;**
5.   _type-specifier_       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **int** | **void**
6.   _fun-declaration_      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _type-specifier_ **ID** **(** params **)** _compound-stmt_
7.   _params_              &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _param-list_ | **void**
8.   _param-list_           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _param-list_ **,** _param_ | _param_
9.   _param_                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _type-specifier_ **ID** | _type-specifier_ **ID** **[** **]**
10.  _compound-stmt_        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **{** _local-declarations statement-list_ **}**
11.  _local-declarations_   &nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _local-declarations var-declarations_ | _empty_
12.  _statement-list_       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     _statement-lest statement_ | _empty_
13.  _statement_            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _expression-stmt_ | _compound-stmt_ | _selection-stmt_ | _iteration-stmt_ | _return-stmt_
14.  _expression-stmt_      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _expression_ **;** | **;**
15.  _selection-stmt_       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **if** **(** _expression_ **)** _statement_ | **if** **(** _expression_ **)** _statement_ **else** _statement_
16.  _iteration-stmt_       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **while** **(** _expression_ **)** _statement_
17.  _return-stmt_          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **return** **;** | **return** _expression_ **;**
18.  _expression_           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _var_ **=** _expression_ | _simple-expression_
19.  _var_                  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **ID** | **ID** **[** _expression_ **]**
20.  _simple-expression_    &nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _additive-expression relop additive-expression_ | _additive-expression_
21.  _relop_                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **<=** | **<** | **>** | **>=** | **==** | **!=**
22.  _additive-expression_  &nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _additive-expression addop term_ | _term_
23.  _addop_                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **+** | **-**
24.  _term_                 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _term mulop factor_ | _factor_
25.  _mulop_                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     * | **/**
26.  _factor_              &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **(** _expression_ **)** | _var_ | _call_ | **NUM**
27.  _call_                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      **ID** **(** args **)**
28.  _args_                 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _arg-list_ | _empty_
29.  _arg-list_             &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      _arg-list_ **,** _expression_ | _expression_
