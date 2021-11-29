import string

class Lookahead:
    def __init__(self, i): 
        self.i = i
        self.next = next(self.i)
    def __next__(self):
        ret = self.next
        self.next = next(self.i)
        return ret
    def __iter__(self):
        return self


def parse_assignment(i):
    name = parse_name(i)
    assert next(i) == '='
    expr = parse(name)
    return ('assignment', name, expr)

def parse(i):
    pass

def parse_func(i):
    assert next(i) == 'λ'
    args = []
    name = ''
    for x in i:
        if x == ',':
            args.append(name)
            name = ''
        elif x == '-' and i.next == '>':
            args.append(name)
            break
        else:
            name += x
    expr = parse(i)
    return ('fn', args, expr)

def parse_fncall(i):
    fn = parse(i)      # doesn't consume `(`
    assert i.next == '('
    args = []
    while i.next != ')':
        args.append(parse(i))
    return ('call', fn, args)

def parse_name(i):
    name = next(i)
    assert name in string.alphabet
    while i.next in string.alphanumeric:
        name += next(i)
    return name

def parse_num(i):
    num = next(i)
    assert name in string.digits
    while i.next in string.digits:
        num += next(i)
    return int(num)

def parse_string(i):
    string = ''
    assert next(i) == '"'
    while i.next != '"':
        string += next(i)
    return string
