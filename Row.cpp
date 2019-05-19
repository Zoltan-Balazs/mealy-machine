#include "Element.h"
#include "Row.h"
#include <exception>
#include <iostream>

Row::Row() {
	rowId = nullptr;
}

Row::Row(char _rowId) {
	rowId = new char;
	*rowId = _rowId; 
}

void Row::setRowId(char _rowId) {
	rowId = new char;
	*rowId = _rowId;
}

char Row::getRowId() const { 
	return *rowId;
}

unsigned Row::getSize() const { 
	return elements.size();
}


Element* Row::operator[](unsigned idx) {
	if (idx >= elements.size()) {
		for (unsigned i = elements.size(); i <= idx; i++) {
			elements.push_back(new Element());
		}
	}
	return elements[idx];
}

Row::~Row() {
	elements.erase(elements.begin(), elements.end());
}
