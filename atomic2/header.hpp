#pragma once
#include <list>
#include <string>
#include <fstream>
#include <iostream>

class LStream {
	std::ifstream file;
public:
	char next, current;
	LStream(std::string filename);
	char get_next();
};

enum class ExprType {
	START,
	ASSIGNMENT,
	FUNC,
	CALL_FUNC,
	GET_VAR,
	NUMBER,
	FLOAT,
	STRING,
	NAME,
	NONE,
	PARSE_FAILED
};

class Expr {
	ExprType tag;
	union {
		std::list<Expr*> expr_list;
		int i;
		float f;
		std::string str;
	};
public:
	Expr(ExprType, std::list<Expr*>);
	Expr(int);
	Expr(float);
	Expr(std::string);
	Expr(ExprType);
	void pprint(std::string indent);
};

Expr* parse(LStream);
Expr* parse_assign(LStream);
Expr* parse_fn(LStream);
Expr* parse_call(LStream);
Expr* parse_var(LStream);
Expr* parse_num(LStream);
Expr* parse_str(LStream);
Expr* parse_name(LStream);
