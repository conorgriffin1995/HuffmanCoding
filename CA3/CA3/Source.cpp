// x00111602
// Conor Griffin
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <queue>
#include "HuffTree.h"

using namespace std;

void calcFrequency(map <char, int> &frequency, ifstream& file);
void print(map<char, int> &frequency);

int main() {
	ifstream inFile;
	inFile.open("text.txt");
	map<char, int> frequency = map<char, int>();
	calcFrequency(frequency, inFile);		// 1
	print(frequency);
	HuffTree tree;
	tree.buildTree(frequency);				// 2, 3
	tree.Decode();							// 5				
	tree.Compress();						// 6

	inFile.close();

	system("pause");
	return 0;
}

/***************************************************************************************
*    Title: <Counting characters in the given string using C++ STL map >
*    Author: <Ravi Chandra Enaganti >
*    Date: <Tuesday, May 7, 2013>
*    Code version: <C++, Map, STL, String>
*    Availability: <http://comproguide.blogspot.ie/2013/05/counting-characters-in-given-string.html>
*
***************************************************************************************/
// Task 1
// determine the frequency of each character in the text
// use map of character and frequency
// pass in file (using ifstream)
void calcFrequency(map <char, int> &frequency, ifstream& file) {
	char c;
	while (file.get(c)) {					// loop to get characters
		if (!frequency.empty()) {			// if map not empty
											// auto is used as the type specifier
			auto item = frequency.find(c);	// find character in map
			if (item != frequency.end()) {	// if not present in map
				item->second++;				// increment int frequency
			}
			frequency.insert(pair<char, int >(c, 1));	// insert pair/ add entry
		}
		else {											// else map is empty
			frequency.insert(pair<char, int >(c, 1));	// insert pair
		}
	}
}

void print(map<char, int> &frequency) {
	for (auto elem : frequency) {							// loop through each map
		cout << elem.first << " " << elem.second << "\n";	// print out char, int
	}
}