#pragma once
#include "Element.h"
#include <vector>

class Row {
protected:
	char* rowId;
	std::vector<Element *> elements;
public:
	Row();
	Row(char _rowId);

	void setRowId(char _rowId);

	unsigned getSize() const;
	char getRowId() const;

	Element* operator[](unsigned idx);
	
	~Row();
};
