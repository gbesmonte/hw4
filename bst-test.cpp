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

    testTree.insert(std::make_pair(-142, -142));
    testTree.insert(std::make_pair(-73, -73));
    testTree.insert(std::make_pair(-64, -64));
    testTree.insert(std::make_pair(-61, -61));
    testTree.insert(std::make_pair(-53, -53));
    testTree.insert(std::make_pair(2, 2));
    testTree.insert(std::make_pair(28, 28));
    testTree.insert(std::make_pair(50, 50));
    testTree.insert(std::make_pair(71, 71));
    testTree.insert(std::make_pair(75, 75));
    testTree.insert(std::make_pair(76, 76));
    testTree.insert(std::make_pair(106, 106));
    testTree.insert(std::make_pair(147, 147));

    /* cout << "\nAVLTree contents:" << endl;
    for(AVLTree<uint16_t, uint16_t>::iterator it = testTree.begin(); it != testTree.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    } */

 /* cout << "Erasing b" << endl;
    at.remove('b'); */

    testTree.remove(76);
    testTree.remove(147);
    testTree.remove(-142);
    testTree.remove(-64);
    testTree.remove(-73);

    return 0;
}
