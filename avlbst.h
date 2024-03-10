#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void removeFix(AVLNode<Key,Value>* p, int8_t diff);
    void rotateRight(AVLNode<Key,Value>* n);
    void rotateLeft(AVLNode<Key,Value>* n);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // constructor: AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    AVLNode<Key,Value>* n = nullptr;

    //if tree is empty
    if (this->root_ == nullptr){
        n = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        n->setBalance(0);
        this->root_ = n;
        return;
    }
    //if not empty
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->root_);
    while (curr != nullptr) {
        if (curr->getKey() == new_item.first) {
            curr->setValue(new_item.second);
            break;
        }

        if (curr->getLeft() == nullptr && new_item.first < curr->getKey()) {
            n = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
            n->setBalance(0);
            curr->setLeft(n);
            if (curr->getBalance() == 1){
                curr->setBalance(0);
            }
            else if (curr->getBalance() == 0){
                curr->setBalance(-1);
                insertFix(curr, n);
            }
            break;
        }
        if (curr->getRight() == nullptr && new_item.first > curr->getKey()) {
            n = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
            n->setBalance(0);
            curr->setRight(n);
            if (curr->getBalance() == -1){
                curr->setBalance(0);
            }
            else if (curr->getBalance() == 0){
                curr->setBalance(1);
                insertFix(curr, n);
            }
            break;
        }

        if (new_item.first < curr->getKey()) {
            curr = curr->getLeft();
        }
        else if (new_item.first > curr->getKey()){
            curr = curr->getRight();
        }
    }
    //this->printRoot(this->root_);
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n){
    if (p == nullptr || p->getParent() == nullptr){
        return;
    }
    AVLNode<Key,Value>* g = p->getParent();
    //if p is the left child of g
    if (g->getLeft() == p){
        g->updateBalance(-1);
        if (g->getBalance() == 0){
            return;
        }
        else if (g->getBalance() == -1){
            insertFix(g, p);
        }
        else if (g->getBalance() == -2){
            //if zig zig
            if (p->getLeft() == n){
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            //if zig zag
            else if (p->getRight() == n){
                int8_t nBal = n->getBalance();
                rotateLeft(p);
                rotateRight(g);
                if (nBal == -1){
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                }
                else if (nBal == 0){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if (nBal == 1){
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }
    //if p is the right child of g
    else if (g->getRight() == p){
        g->updateBalance(1);
        if (g->getBalance() == 0){
            return;
        }
        else if (g->getBalance() == 1){
            insertFix(g, p);
        }
        else if (g->getBalance() == 2){
            //if zig zig
            if (p->getRight() == n){
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            //if zig zag
            else if (p->getLeft() == n){
                int8_t nBal = n->getBalance();
                rotateRight(p);
                rotateLeft(g);
                if (nBal == 1){
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                }
                else if (nBal == 0){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if (nBal == -1){
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* n){
    //taking a left child, making it the parent, and making the og parent the new right child
    //AVLNode<Key,Value>* p = n->getParent();
    AVLNode<Key,Value>* x = n;
    AVLNode<Key,Value>* y = n->getLeft();
    AVLNode<Key,Value>* a = y->getLeft();
    AVLNode<Key,Value>* b = y->getRight();
    AVLNode<Key,Value>* c = x->getRight();
    nodeSwap(x, y);
    y->setLeft(a);
    y->setRight(x);
    x->setLeft(b);
    x->setRight(c);
    if (c != nullptr){
        c->setParent(x);
    }
    if (a != nullptr){
        a->setParent(y);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n){
    //AVLNode<Key,Value>* p = n->getParent();
    AVLNode<Key,Value>* x = n;
    AVLNode<Key,Value>* y = n->getRight();
    AVLNode<Key,Value>* a = y->getRight();
    AVLNode<Key,Value>* b = y->getLeft();
    AVLNode<Key,Value>* c = x->getLeft();
    nodeSwap(x, y);
    y->setLeft(x);
    y->setRight(a);
    x->setLeft(c);
    x->setRight(b);
    if (c != nullptr){
        c->setParent(x);
    }
    if (a != nullptr){
        a->setParent(y);
    }
}
/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key,Value>* n = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if (n == nullptr){
        return;
    }
    int8_t diff = 0;
    while (true) {
        //Case 1
        if (n->getLeft() == nullptr && n->getRight() == nullptr) {
            AVLNode<Key,Value>* p = n->getParent();
            if (p != nullptr) {
                if (p->getLeft() == n) {
                    p->setLeft(nullptr);
                    diff = 1;
                }
                else if (p->getRight() == n){
                    p->setRight(nullptr);
                    diff = -1;
                }
            }
            if (n == this->root_){
                this->root_ = nullptr;
            }
            delete n;
            removeFix(p, diff);
            break;
        }
        //Case 2
        if (n->getLeft() != nullptr && n->getRight() == nullptr) {
            AVLNode<Key, Value>* p = n->getLeft();
            nodeSwap(p, n);
            if (n == this->root_){
                this->root_ = p;
            }
            p->setRight(n->getRight());
            p->setLeft(n->getLeft());
            if (n->getRight() != nullptr){
                n->getRight()->setParent(p);
            }
            if (n->getLeft() != nullptr){
                n->getLeft()->setParent(p);
            }
            diff = 1;
            delete n;
            removeFix(p, diff);
            break;
        }
        if (n->getLeft() == nullptr && n->getRight() != nullptr) {
            AVLNode<Key, Value>* p = n->getRight();
            nodeSwap(p, n);
            if (n == this->root_){
                this->root_ = p;
            }
            p->setRight(n->getRight());
            p->setLeft(n->getLeft());
            if (n->getRight() != nullptr){
                n->getRight()->setParent(p);
            }
            if (n->getLeft() != nullptr){
                n->getLeft()->setParent(p);
            }
            diff = -1;
            delete n;
            removeFix(p, diff);
            break;
        }
        //Case 3
        if (n->getLeft() != nullptr && n->getRight() != nullptr) {
            AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(n));
            nodeSwap(pred, n);
            continue;
        }
    }
    //this->printRoot(this->root_);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, int8_t diff){
    if (n == nullptr){
        return;
    }

    AVLNode<Key,Value>* p = n->getParent();
    int8_t ndiff = 0;
    if (p != nullptr){
        if (p->getLeft() == n){
            ndiff = 1;
        }
        else if (p->getRight() == n){
            ndiff = -1;
        }
    }

    if (diff == -1){
        if (n->getBalance() + diff == -2){
            AVLNode<Key,Value>* c = n->getLeft();
            if (c->getBalance() == -1){
                rotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if (c->getBalance() == 0){
                rotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
            }
            else if (c->getBalance() == 1){
                AVLNode<Key,Value>* g = c->getRight();
                int8_t gBal = g->getBalance();
                rotateLeft(c);
                rotateRight(n);
                if (gBal == 1){
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                }
                else if (gBal == 0){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                else if (gBal == -1){
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        }
        else if(n->getBalance() + diff == -1){
            n->setBalance(-1);
            return;
        }
        else if (n->getBalance() + diff == 0){
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
    else if (diff == 1){
        if (n->getBalance() + diff == 2){
            AVLNode<Key,Value>* c = n->getRight();
            if (c->getBalance() == 1){
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if (c->getBalance() == 0){
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
            }
            else if (c->getBalance() == -1){
                AVLNode<Key,Value>* g = c->getLeft();
                int8_t gBal = g->getBalance();
                rotateRight(c);
                rotateLeft(n);
                if (gBal == -1){
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                }
                else if (gBal == 0){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                else if (gBal == 1){
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        }
        else if(n->getBalance() + diff == 1){
            n->setBalance(1);
            return;
        }
        else if (n->getBalance() + diff == 0){
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
