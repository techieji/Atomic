import string

class Lookahead:
    def __init__(self, i):
        self.i = iter(i)
        self.next = next(self.i)
    def __next__(self):
        ret = self.next
        try:
            self.next = next(self.i)
        except StopIteration:
            self.next = None
        if ret is None:
            raise StopIteration
        return ret
    def __iter__(self):
        return self
    def select_until(self, c):
        s = ''
        while self.next != c:
            s += next(self)
        return s
    @propert

def parse(i):
    if i.next == '(':
        e = parse(Lookahead(i.select_until(')')))
        next(i)
        return e
    elif i.next == 'λ':
        return parse_func(i)
    elif i.next in string.digits:
        return parse_num_or_float(i)
    elif i.next == '"':
        return parse_string(i)
    elif i.next in [')', ';', ',']:
        return
    else:
        return parse_fncall_or_name(i)

def parse_func(s):
    assert next(i) == 'λ'
    args = []
    name = ''
    for x in i:
        if x == ',':
            args.append(name)
            next(i)
            name = ''
        elif x == '-' and i.next == '>':
            next(i)
            args.append(name)
            break
        else:
            name += x
    expr = parse(i)
    return ('fn', args, expr)

def parse_fncall_or_name(i):
    if i.next == '(':
        fn = parse(i)      # doesn't consume `(`
    else:
        fn = parse_name(i)
    if i.next != '(':
        return ('var', fn)
    args = []
    while i.next != ')':
        args.append(parse(i))
        next(i)   # get rid of comma
    return ('call', fn, args)

def parse_name(i):
    name = next(i)
    print(name)
    assert name in string.ascii_letters
    while i.next in (string.ascii_letters + string.digits + '_'):
        name += next(i)
    return name

def parse_num_or_float(i):
    num = next(i)
    assert num in string.digits
    while i.next in string.digits:
        num += next(i)
    if i.next == '.':
        num += next(i)
        while i.next in string.digits:
            num += next(i)
        return float(num)
    return int(num)

def parse_string(i):
    string = ''
    assert next(i) == '"'
    while i.next != '"':
        string += next(i)
    return string

if __name__ == '__main__':
    s = 'add_ten_to_sum = λx,y -> sum(x, y, 10);'.replace(' ', '')
    s = 'λx,y -> sum(x, y, 10)'.replace(' ', '')
    # print(''.join(Lookahead(s)))
    print(parse_func(Lookahead(s)))
