#include "Mealy.h"
#include <exception>
#include <iostream>	
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

int main(void) {
	//We set the console so it can handle western latin characters "pseudo-unicode"
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	//We initialize the variables containing the filenames
	string startFilename;
	string inputFilename;
	string outputFilename;

	cout << "Please provide the name of the file where you would like to read the state table from (without extension): ";
	getline(cin, startFilename);
	cout << "Please provide the name of the file where you would like to read the inputs from (without extension): ";
	getline(cin, inputFilename);
	cout << "Please provide the name of the file where you would like to write the solution to (without extension): ";
	getline(cin, outputFilename);

	try {
		Mealy system(startFilename + ".txt");
		system.execute(inputFilename + ".txt", outputFilename + ".txt");
	}
	catch (const exception& msg) {
		cout << msg.what() << endl;
	}

	return 0;
}
