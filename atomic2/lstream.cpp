#include "header.hpp"

LStream::LStream(std::string filename) : file(filename) {
	if (!file.is_open()) {
		std::cerr << "Could not open " << filename << std::endl;
		exit(1);
	}
	file.get(next);
}

char LStream::get_next() {
	current = next;
	file.get(next);
	return current;
}
