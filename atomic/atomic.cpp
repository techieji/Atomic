#include "header.hpp"

Expr parse_str(LStream ls) {
	assert(ls.getNext() == '"');
	std::string str("");
	while (ls.next != '"')
		str.push_back(ls.getNext());
	assert(ls.getNext() == '"');
	Atom atom(AtomType::STRING);
	atom.str = str;
	Expr expr(ExprType::ATOM);
	expr.a = &atom;
	return expr;
}

Expr parse_expr(LStream ls) {
	switch (ls.next) {
		// case 'λ':
		// 	return parse_function(ls);
		case '(':
			ls.getNext();
			Expr ret = parse_expr(ls);
			assert(ls.getNext() == ')');
			return ret;
		case '"':
			return parse_str(ls);
		default:
			exit(100);
	}
}

int main() {
	return 0;
}
