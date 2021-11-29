#include "header.hpp"

using namespace std;

int main() {
	LStream test("test.at");
	cout << "'a' == " << test.next << endl;
	cout << "'a' == " << test.get_next() << endl;
	cout << "'d' == " << test.next << endl;
	cout << "'d' == " << test.get_next() << endl;
}
