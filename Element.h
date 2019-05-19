#pragma once
#include <iostream>
#include <string>

class Element{
protected:
	char* row;
	char* output;
	std::string column;
public:
	Element();
	Element(char _row, char _output, std::string _column);
	
	void setRow(char _row);
	void setOutput(char _output);
	void setColumn(std::string _column);

	char getRow() const;
	char getOutput() const;
	std::string getColumn() const;

	~Element();
};
