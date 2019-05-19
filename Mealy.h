#pragma once
#include "Row.h"
#include <string>
#include <vector>

class Mealy {
private:
	std::vector<Row *> rows;
	char output;
	char prevState;
public:
	Mealy();
	Mealy(std::string filename);

	void execute(std::string inFilename, std::string outFilename);

	~Mealy();
};
