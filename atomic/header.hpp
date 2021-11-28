#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <cassert>

#define FILE_OPEN_ERROR 10
#define UNDEFINED_VARIABLE_ERROR 11

class LStream {
	FILE* ptr;
public:
	char next, current;
	LStream(std::string filename) {
		if (!(ptr = fopen(filename.c_str(), "r"))) exit(FILE_OPEN_ERROR);
		next = fgetc(ptr);
	}
	char getNext() {
		if (!((current = next) == EOF)) if ((next = fgetc(ptr)) == EOF) fclose(ptr);
		return current;
	}
};
enum class AtomType { INTEGER, FLOAT, STRING, NAME };
class Atom {
public:
	AtomType tag;
	union {
		int i;
		float f;
		std::string str;
	};
	Atom(AtomType _tag) : tag(_tag) {}
	~Atom() {}
};
enum class ExprType { ASSIGNMENT, MK_FUNC, CALL_FUNC, GET_VAR, ATOM } tag;
struct _Expr {
	enum { EXPR, ATOM } tag;
	union {
		Expr* e;
		Atom* a;
	};
};
class Expr {
public:
	ExprType tag;
		std::list<_Expr> l;
	Expr(ExprType _tag) : tag(_tag) {}
};
typedef std::map<std::string, Expr> scopeType;
class Env {
	scopeType scope; Env* outer = nullptr;
public:
	Env(scopeType _scope, Env* _outer = nullptr) : scope(_scope), outer(_outer) {}
	Expr findSymbol(std::string symbol) {
		if (scope.count(symbol))
			return scope[symbol];
		else if (outer != nullptr)
			return outer->findSymbol(symbol);
		else
			exit(UNDEFINED_VARIABLE_ERROR);
	}
	Env newChild(scopeType _scope) {
		return Env(_scope, this);
	}
};
