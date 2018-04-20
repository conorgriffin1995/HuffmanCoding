// x00111602
// Conor Griffin
#include "HuffTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

HuffTree::HuffTree() {
	root = NULL;
}

/***************************************************************************************
*    Title: <Greedy Algorithms | Set 3 (Huffman Coding)>
*    Author: <Aashish Barnwal>
*    Date: <NA>
*    Code version: <1.0 (C++ Using STL)>
*    Availability: <https://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/>
*
***************************************************************************************/
// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
// Part 2
void HuffTree::buildTree(map<char, int> &freq) {
	map<char, string> mappings = map<char, string>();

	// left right and top node pointers
	HuffNode *left, *right, *top;

	// loop through maps
	for (auto elem : freq) {
		// create new node
		HuffNode *node = new HuffNode();
		// node letter = first element in map
		node->letter = elem.first;
		// node frequency = second element in map
		node->frequency = elem.second;
		// push node onto heap
		minHeap.push(node);
	}

	// set eof marker
	HuffNode *n = new HuffNode();
	n->letter = '¿';
	n->frequency = 1;
	minHeap.push(n);

	// Iterate while size of heap doesn't become 1
	while (minHeap.size() != 1) {
		// Extract the two minimum
		// freq items from min heap
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();

		// Create a new internal node with
		// frequency equal to the sum of the
		// two nodes frequencies. Make the
		// two extracted node as left and right children
		// of this new node. Add this node
		// to the min heap 
		// '$' is a special value for internal nodes, not used
		top = new HuffNode('$', left->frequency + right->frequency);
		top->leftChild = left;
		top->rightChild = right;

		// Add this node to the min heap
		minHeap.push(top);
	}
	// set root to final tree
	root = minHeap.top();
	// print codes of heap
	mappings = Codes(minHeap.top(), "");
	// Encode mappings
	Encode(mappings);
}

// Prints huffman codes from
// the root of Huffman Tree.
// Part 3
map<char, string> HuffTree::Codes(HuffNode *subtreeRoot, string str) {

	if (!subtreeRoot) {
		return mappings;
	}
	else {
		Codes(subtreeRoot->leftChild, str + "0");		// recursively call method to print left nodes
		Codes(subtreeRoot->rightChild, str + "1");		// recursively call method to print right nodes
														// '$' is a special value for internal nodes, not used
		if (subtreeRoot->letter != '$') {
			subtreeRoot->code = str;
			cout << "Code for: " << subtreeRoot->letter << " " << subtreeRoot->code << endl;

			mappings.insert(pair<char, string>(subtreeRoot->letter, subtreeRoot->code));
		}
		return mappings;
	}
}

// Part 4
void HuffTree::Encode(map<char, string> &mappings) {
	char c;
	ifstream inFile("text.txt");
	ofstream outFile("encoded.txt");
	while (inFile.get(c)) {
		for (auto elem : mappings) {
			if (c == elem.first) {
				outFile << elem.second;
			}
		}
	}
}

// Part 5
void HuffTree::Decode() {
	ifstream inFile("encoded.txt");
	ofstream fileDec("decoded.txt");
	Decode(root, inFile, fileDec);
}
void HuffTree::Decode(HuffNode *root, ifstream &inFile, ofstream &fileDec) {
	char c;
	HuffNode *curr = root;

	while (inFile.get(c)) {
		if (c == '0') {
			curr = curr->leftChild;
		}
		else {
			curr = curr->rightChild;
		}
		if (curr->leftChild == NULL && curr->rightChild == NULL) {
			fileDec << curr->letter;
			curr = root;
		}
	}

	inFile.close();
	fileDec.close();
}

// Part 6
/***************************************************************************************
*    Title: <Simple text-to-binary converter written in C++>
*    Author: <Dale Wilson>
*    Date: <Apr 28 '14 at 15:19>
*    Code version: <C++11:>
*    Availability: <https://stackoverflow.com/questions/23344257/convert-a-string-of-binary-into-an-ascii-string-c>
*
***************************************************************************************/

void HuffTree::Compress() {
	ifstream inFile("encoded.txt");
	ofstream compFile("compressed.txt");

	while (inFile.good()) {
		bitset<8> bits;
		inFile >> bits;
		char c = char(bits.to_ulong());
		compFile << c;
	}

	compFile << 'š'; // end of file marker

	inFile.close();
	compFile.close();
}

// Part 7
/***************************************************************************************
*    Title: <Convert a string of binary into an ASCII string (C++)>
*    Author: <Jamal>
*    Date: <Feb 5 '14 at 5:56>
*    Code version: <NA>
*    Availability: <https://codereview.stackexchange.com/questions/2661/simple-text-to-binary-converter-written-in-c>
*
***************************************************************************************/
void HuffTree::Decompress() {
	ifstream inFile("compressed.txt");
	ofstream compFile("decompressed.txt");
	char c;
	while (inFile.get(c)) {
		bitset<8> binary(c);
		compFile << binary;
	}

	inFile.close();
	compFile.close();

	ifstream decFile("decompressed.txt");
	ofstream file("decompressedText.txt");

	Decode(root, decFile, file);

	decFile.close();
	file.close();


}



