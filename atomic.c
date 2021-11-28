#include <stdio.h>

enum AtomType {
	INTEGER,
	FLOAT,
	STRING,
	FUNCTION_TYPE
};

enum ExprType {
	MK_FUNC,
	CALL_FUNC,
	GET_VAR,
	ATOMIC
};

struct Atom {
	enum AtomType type;
	int intValue;
	float floatValue;
	char* stringValue;
	struct Function* functionValue;
};

struct Atom mkAtom(AtomType type) {
	struct Atom ret = {type, 0, 0, NULL};
	return ret;
}

struct ArgsLL {
	char* name;
	struct ArgsLL* next;
};

struct Function {
	struct ArgsLL* args;
};

int main() {
	return 0;
}
