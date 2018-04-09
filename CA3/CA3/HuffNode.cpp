// x00111602
// Conor Griffin
#include "HuffNode.h"
#include <iostream>

// default constructor used for creating new HuffNode()
HuffNode::HuffNode() {

}

// constructor
HuffNode::HuffNode(char cIn, int i) {
	frequency = i;
	letter = cIn;
	leftChild = NULL;
	rightChild = NULL;
}

// destructor
HuffNode::~HuffNode() {
	if (leftChild != NULL) delete leftChild;
	if (rightChild != NULL) delete rightChild;
}




