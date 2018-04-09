// x00111602
// Conor Griffin
#pragma once
#include "HuffNode.h"
#include <vector>
#include <queue>
#include <map>
using namespace std;

/***************************************************************************************
*    Title: <Greedy Algorithms | Set 3 (Huffman Coding)>
*    Author: <Aashish Barnwal>
*    Date: <NA>
*    Code version: <1.0 (C++ Using STL)>
*    Availability: <https://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/>
*
***************************************************************************************/
// For comparison of
// two heap nodes (needed in min heap)
struct compare {
	bool operator()(HuffNode* l, HuffNode* r)
	{
		return (l->getFrequency() > r->getFrequency());
	}
};

class HuffTree
{
public:
	HuffTree();
	void buildTree(map<char, int> &freq);						// 2	
	map<char, string> Codes(HuffNode *subtreeRoot, string str);	// 3
	void Encode(map<char, string> &mappings);					// 4
	void Decode();												// 5
	void Compress();											// 6
	void Decompress();											// 7
private:
	HuffNode * root;
	map<char, string> mappings = map<char, string>();
	// queue of nodes 
	priority_queue <HuffNode*, vector<HuffNode*>, compare> minHeap;
	void Decode(HuffNode *root, ifstream &inFile, ofstream &fileDec);

};
