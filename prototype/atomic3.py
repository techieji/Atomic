import string

def parse(s):
    if s[0] == '(':
        return parse(s[:s.index(')')])
    elif s[0] == 'λ':
        return parse_fn(s)
    elif s[0] in string.ascii_letters:
        if '(' in s:
            return parse_call(s)
        else:
            return ('name', s)
    else:
        return eval(s)     # parse_atomic

def parse_fn(s):
    args = s[s.index('λ')+1:s.index('->')].split(',')
    rest = parse(s[s.index('->')+2:])
    return ('fn', args, rest)

def parse_call(s):
    name, _args = s.split('(')
    _args = _args[:-2]   # Remove `)` and something else??
    return ('call', name, [parse(x) for x in _args.split(',')])

def parse_assignment(s):
    name, expr = s.split('=')
    return ('set', name, parse(expr))

if __name__ == '__main__':
    s = 'add_ten_to_sum = λx,y -> sum(x, y, 10);'.replace(' ', '')
    # s = 'λx,y -> sum(x, y, 10)'.replace(' ', '')
    # print(''.join(Lookahead(s)))
    print(parse_assignment(s))
