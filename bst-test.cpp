#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    /*BinarySearchTree<int,int> bt;
    bt.insert(std::make_pair(2, 8));
    bt.insert(std::make_pair(1, -50));
    bt.insert(std::make_pair(3, 0));
    bt.insert(std::make_pair(10, 0));
    bt.insert(std::make_pair(15, 0));


    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<int,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    for(BinarySearchTree<int,int>::iterator it2 = bt.begin(); it2 != bt.end(); ++it2) {
        cout << it2->first << " " << it2->second << endl;
    }
*/
    // AVL Tree Tests
    AVLTree<uint16_t, uint16_t> testTree;

    testTree.insert(std::make_pair(10, 8));
    testTree.insert(std::make_pair(20, 159));
    testTree.insert(std::make_pair(30, 9));
    testTree.insert(std::make_pair(15, 0x5a));
    testTree.insert(std::make_pair(25, 0xb));
    testTree.insert(std::make_pair(12, 4));
    testTree.insert(std::make_pair(5, 159));
    testTree.insert(std::make_pair(3, 159));
    testTree.insert(std::make_pair(8, 159));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<uint16_t, uint16_t>::iterator it = testTree.begin(); it != testTree.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
/*    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b'); */

    return 0;
}
