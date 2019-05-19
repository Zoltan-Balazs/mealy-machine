#include "Mealy.h"	
#include <cmath>
#include <exception>
#include <fstream>	
#include <iostream>	
#include <sstream>	
#include <vector>
#include <iomanip>	

using namespace std;

Mealy::Mealy() {
	rows = vector<Row*>();
	output = '2';
	prevState = 'A';
}

Mealy::Mealy(string filename) {
	output = '2';
	prevState = 'A';
	
	string temp;
	
	ifstream startFile;
	startFile.open(filename);
	if (startFile.fail())
		throw runtime_error("The directory doesn't contain a file named " + filename);

	unsigned numOfCols = 0;
	while (startFile.peek() != '\n' && startFile >> temp)
		numOfCols++;

	startFile.seekg(0, startFile.beg);

	char currentChar;
	startFile.get(currentChar);
	
	if (currentChar != '-')	
		throw runtime_error("The state table format in " + filename + " doesn't match the documentation (top left should be a '-')!");
	
	rows.push_back(new Row(currentChar));
	Row* currentRow = rows[rows.size() - 1];

	startFile.get(currentChar);
	if (currentChar != '\t' && currentChar != ' ')
		throw runtime_error("The state table header in " + filename + " contains characters that shouldn't be there!");

	string binaryNum;

	while (currentChar != '\n') {
		startFile.get(currentChar);

		if (currentChar == '0' || currentChar == '1') {
			binaryNum += currentChar;
			if (startFile.peek() != '\t' && startFile.peek() != '\n' && startFile.peek() != ' ') {
				while (pow(2, static_cast<int>(binaryNum.size())) != numOfCols - 1) {
					startFile.get(currentChar);
					if (currentChar != '0' && currentChar != '1')
						throw runtime_error("The state table header in " + filename + " contains charachters that aren't 0 or 1!");
					binaryNum += currentChar;
				}
			}
		}
		else
			throw runtime_error("The state table header in " + filename + " contains charachters that aren't 0 or 1!");

		startFile.get(currentChar);
		if (currentChar == '\t' || currentChar == '\n' || currentChar == ' ') {
			(*currentRow)[(currentRow->getSize())]->setColumn(binaryNum);
			binaryNum.clear();
		}
		else
			throw runtime_error("The state table format in " + filename + " is incorrect!");

	}

	startFile.get(currentChar);

	rows.push_back(new Row(currentChar));
	currentRow = rows[rows.size() - 1];

	while (!startFile.eof()) {
		startFile.get(currentChar);
		
		if ('A' <= currentChar && currentChar <= 'Z') {
			char tmp;
			tmp = currentChar;
			startFile.get(currentChar);
			startFile.get(currentChar);
			(*currentRow)[(currentRow->getSize())]->setRow(tmp);
			(*currentRow)[(currentRow->getSize()) - 1]->setOutput(currentChar);
		}
		else if ('-' == currentChar && !startFile.eof()) {
			char tmp;
			tmp = currentChar;
			(*currentRow)[(currentRow->getSize())]->setRow(tmp);
			(*currentRow)[(currentRow->getSize()) - 1]->setOutput(currentChar);
		}
		else if (currentChar == '\n') {
			startFile.get(currentChar);
			if ('A' <= currentChar && currentChar <= 'Z') {
				rows.push_back(new Row(currentChar));
				currentRow = rows[rows.size() - 1];
			}
			else {
				throw runtime_error("The state table format in " + filename + " is incorrect (the first column must only contain a single letter of the english alphabet)!");
			}
			
		}
		else if (currentChar != ' ' && currentChar != '\t' && !startFile.eof()) {
			throw runtime_error("The state table in " + filename + " contains characters that shouldn't be there!");
		}
	}

	for (unsigned i = 1; i < rows.size(); i++) {
		if (rows[i]->getSize() != numOfCols - 1) {
			throw runtime_error("The state table in " + filename + " has varying column lengths!");
		}
		for (unsigned j = 0; j < (*rows[i]).getSize(); j++) {
			(*rows[i])[j]->setColumn((*rows[0])[j]->getColumn());
		}
	}

	startFile.close();
}

void Mealy::execute(string inFilename, string outFilename) {
	string temp;

	ifstream inputFile;
	inputFile.open(inFilename);
	if (inputFile.fail())
		throw runtime_error("The directory doesn't contain a file named " + inFilename);

	ofstream outputFile;
	outputFile.open(outFilename);
	if (outputFile.fail())
		throw runtime_error("Error creating " + outFilename);

	inputFile.seekg(0, inputFile.end);
	int size = inputFile.tellg();
	inputFile.clear();
	inputFile.seekg(0, inputFile.beg);

	outputFile << "Solution: " << endl;
	cout << "Solution: " << endl;

	char currentInput;
	string binaryNum;
	bool success = false;

	while (!inputFile.eof()) {
		inputFile.get(currentInput);

		if (currentInput == '0' || currentInput == '1') {
			binaryNum += currentInput;
		}

		if (currentInput != '0' && currentInput != '1' && currentInput != '\t' && currentInput != '\n' && currentInput != ' ') {
			outputFile << "Incorrect character in " << inFilename << " it should only contain 0s and 1s";
			throw runtime_error("Incorrect character in " + inFilename + " it should only contain 0s and 1s";);
		}

		if (currentInput == ' ' || currentInput == '\t' || currentInput == '\n' || size == static_cast<int>(inputFile.tellg())) {

			if (prevState == '-') {
				outputFile << "The previous state was neutral, we can't go anywhere!";
				throw runtime_error("The previous state was neutral, we can't go anywhere!");
			}

			for (unsigned i = 1; i < rows.size(); i++) {
				if (rows[i]->getRowId() == prevState) {
					for (unsigned j = 0; j < (*rows[i]).getSize(); j++) {
						if (binaryNum == (*rows[i])[j]->getColumn()) {
							prevState = (*rows[i])[j]->getRow();
							output = (*rows[i])[j]->getOutput();
							cout << binaryNum << " ";
							outputFile << binaryNum << " ";
							j = (*rows[i]).getSize();
							success = true;
						}
					}
					i = rows.size();
				}
			}
	
			if (!success) {
				outputFile << "Incorrect input in " << inFilename << " it contains inputs that aren't in the header of the state table";
				throw runtime_error("Incorrect input in " + inFilename + " it contains inputs that aren't in the header of the state table");
			}
			binaryNum.clear();
		}

		if (currentInput == '\n') {
			
			outputFile << right << setw(10) << prevState << "/" << output << endl;
			cout << right << setw(10) << prevState << "/" << output << endl;
		}
	}

	outputFile << right << setw(10) << prevState << "/" << output << " ";
	cout << right << setw(10) << prevState << "/" << output << " ";

	outputFile.close();
	inputFile.close();
}

Mealy::~Mealy() {
	rows.erase(rows.begin(), rows.end());
}
