#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    // Add your code below
	if (root == nullptr){
		return true;
	}

	int _lHeight = treeHeight(root->left);
	int _rHeight = treeHeight(root->right);

	if (root->left != nullptr && root->right != nullptr && _lHeight - _rHeight != 0){
		return false;
	}

	bool _lEqual = 1;
	if (root->left){
		_lEqual = equalPaths(root->left);
	}
	bool _rEqual = 1;
	if (root->right){
		_rEqual = equalPaths(root->right);
	}

	if (_lEqual && _rEqual){
		return true;
	}

	return false;
}

int treeHeight(Node* root){
	if (root == nullptr){
		return 0;
	}

	if (root->left == nullptr && root->right == nullptr){
		return 1;
	}

	int _left = treeHeight(root->left);
	int _right = treeHeight(root->right);
	
	if (_left >= _right){
		return _left + 1;
	}
	else{
		return _right + 1;
	}
}
