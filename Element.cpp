#include "Element.h"
#include <exception>
#include <iostream>

using namespace std;
	
Element::Element() {
	row = nullptr;
	output = nullptr;
	column = "";
}
	
Element::Element(char _row, char _output, string _column) {
	row = new char;
	*row = _row;
	output = new char;
	*output = _output;
	column = _column;
}

void Element::setRow(char _row) {
	if ('A' <= _row && _row <= 'Z' || _row == '-') {
		row = new char;
		*row = _row;
	}
	else
		throw runtime_error("Incorrect state table format, the states should only be from the english alphabet (or neutral)!");
}

void Element::setOutput(char _output) {
	output = new char;
	*output = _output;
}

void Element::setColumn(string _column) {
	column = _column;
}

char Element::getRow() const { 
	return *row;
}
	
char Element::getOutput() const { 
	return *output;
}

string Element::getColumn() const {
	return column;
}
	
Element::~Element() {
	delete row;
	delete output;
}
