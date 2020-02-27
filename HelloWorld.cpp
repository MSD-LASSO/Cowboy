#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

int main()
{
	std::ofstream myFile;

	myFile.open("TestFile.txt");
	myFile << "Hello I am writing to the file as a test\n";

	return 0;
}
