from lark import Lark

code = r"""
_seperated{elem, sep}: [ elem (sep elem)* ]

start: assignment*
assignment: NAME "=" expr ";"
?expr: ("λ"|"l") _seperated{NAME, ","} "->" expr                   -> mk_func
    | expr "(" _seperated{expr, ","} ")"                       -> call_func
    | "(" expr ")"
    | NAME                                        -> get_var
    | NUMBER  -> number
    | STRING  -> string

%import common.SIGNED_NUMBER -> NUMBER
%import common.ESCAPED_STRING -> STRING
%import common.CNAME -> NAME
%import common.WS
%ignore WS
"""

sample = 'inc = λx,y -> add(sub(x, y), 10);\ndiscard = trace(inc(10, 20));'

print(Lark(code, parser='lalr').parse(sample).pretty())
