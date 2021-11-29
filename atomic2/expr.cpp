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

void pprint(std::string indent = "") {
	switch (tag) {
		case ExprType::PARSE_FAILED:
			std::cout << indent << "PARSE_FAILED" << 
