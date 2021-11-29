#include "header.hpp"

using std::cout, std::endl;

Expr::Expr(ExprType _type, std::list<Expr*> _expr_list) {
	tag = _type;
	expr_list = _expr_list;
}

Expr::Expr(int num) {
	tag = ExprType::NUMBER;
	i = num;
}

Expr::Expr(float fl) {
	tag = ExprType::FLOAT;
	f = fl;
}

Expr::Expr(std::string s) {
	tag = ExprType::STRING;
	str = s;
}

Expr::Expr(ExprType t) {
	tag = t;
}

void Expr::pprint(std::string indent = "") {
	std::cout << indent;
	switch (tag) {
		case ExprType::PARSE_FAILED:
			std::cout << "PARSE_FAILED" << endl;
			break;
		case ExprType::NONE:
			std::cout << "None" << endl;
			break;
		case ExprType::NAME:
			std::cout << str << endl;
			break;
		case ExprType::STRING:
			std::cout << '"' << str << '"' << endl;
			break;
		case ExprType::FLOAT:
			std::cout << f << endl;
			break;
		case ExprType::NUMBER:
			std::cout << i << endl;
			break;
		case ExprType::GET_VAR:
			std::cout << "get_var" << endl;
			for (x : expr_list)
				x->pprint(indent + "  "); // fix later
		// finish
	}
}
