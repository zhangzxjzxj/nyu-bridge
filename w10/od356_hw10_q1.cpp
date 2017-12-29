//
// Created by omar delarosa on 11/26/17.
//

#include <iostream>
#include <queue>
using namespace std;

// For configuring the print command
const int IN_ORDER = 1;
const int PRE_ORDER = 2;
const int POST_ORDER = 3;
const int LEVEL_ORDER = 4;
const int PRETTY = 5;

template <class T>
class BSTNode;

// An AVL tree class
template <class T>
class BST {
    // Pointers for root, left and right nodes
    BSTNode<T> *root_;
    int currentSize;
public:
    BST<T>(): root_(nullptr), currentSize(0) {};
    ~BST<T>() { clearAll(); };

    // Insertion methods
    void insert(T item);
    void insert(BSTNode<T>* parentNode, BSTNode<T>* newNode);

    // Removal methods
    void remove(T item);
    void remove(BSTNode<T>* node);
    BSTNode<T>* findNodeByValue(T value);

    // Rotation methods
    BSTNode<T>* rotateLeft(BSTNode<T>* node);
    BSTNode<T>* rotateRight(BSTNode<T>* node);
    BSTNode<T>* rotateLeftRight(BSTNode<T>* node);
    BSTNode<T>* rotateRightLeft(BSTNode<T>* node);

    // Traversal functions
    void printInOrder(BSTNode<T>* node);
    void printPreOrder(BSTNode<T>* node);
    void printPostOrder(BSTNode<T>* node);
    void printLevelOrder();
    void prettyPrint(BSTNode<T>* node);
    void print(int order);

    // AVL tree helper functions
    void checkBalance(BSTNode<T>* node);
    int height(BSTNode<T>* node);
    BSTNode<T>* rebalance(BSTNode<T>* node);
    void fixParentPointers(BSTNode<T>* node);
    int getSize() { return currentSize; }
    void indentByLevel(ostream& outs, int level);

    // Cleanup
    void clearAll();
    void clearAll(BSTNode<T>* node);
};

template <class T>
class BSTNode {
    // Pointers for the node's parent, data, left, and right links.
    T data_;
    BSTNode<T> *parent_;
    BSTNode<T> *left_;
    BSTNode<T> *right_;
public:
    // Constructor and destructor
    BSTNode(T newData = T(), BSTNode<T>* newParent = nullptr,
            BSTNode<T>* newLeft = nullptr, BSTNode<T>* newRight = nullptr):
        data_(newData), parent_(newParent), left_(newLeft), right_(newRight) {};
    ~BSTNode() =default;

    // Helper functions
    int getLevel();
    friend class BST<T>;
};

void testInsertionAndPrinting();

int main() {
    testInsertionAndPrinting();
    return 0;
}

// ---------------
// BST
// ---------------

template <class T>
void BST<T>::insert(T item) {
    BSTNode<T>* newNode = new BSTNode<T>(item);
    // Tree is empty
    if (root_ == nullptr) {
        root_ = newNode;
    } else {
        insert(root_, newNode);
    }
    currentSize++;
}

template <class T>
void BST<T>::insert(BSTNode<T> *parentNode, BSTNode<T> *newNode) {
    // Case 1: newNode data is more than target parent node data...
    if (newNode->data_ > parentNode->data_) {
        // insert node in empty right slot
        if (parentNode->right_ == nullptr) {
            parentNode->right_ = newNode;
            newNode->parent_ = parentNode;
        } else {
            // recurse right
            insert(parentNode->right_, newNode);
        }
    // Case 2: newNode data is less than
    } else {
        if (parentNode->left_ == nullptr) {
            parentNode->left_ = newNode;
            newNode->parent_ = parentNode;
        } else {
            insert(parentNode->left_, newNode);
        }
    }
    checkBalance(newNode);
}

template <class T>
void BST<T>::checkBalance(BSTNode<T> *node) {
    // Null case. (i.e. end of recursive calls.)
    if (node == nullptr) return;

    // Fix parent before any height calculations
    fixParentPointers(node);

    int hLeft = height(node->left_);
    int hRight = height(node->right_);

    if ((hLeft - hRight > 1) || (hRight - hLeft < -1)) {
        rebalance(node);
    }
    if (node->parent_ == nullptr)
        return;
    else
        checkBalance(node->parent_);
}

template <class T>
BSTNode<T>* BST<T>::rebalance(BSTNode<T> *node) {
    BSTNode<T>* newNode = node;
    int hLeft = height(newNode->left_);
    int hRight = height(newNode->right_);
    if ((hLeft - hRight) > 1) {
        if (height(node->left_->left_) > height(newNode->left_->right_)) {
            newNode = rotateRight(newNode);
        } else {
            newNode = rotateLeftRight(newNode);
        }
    } else {
        if (height(node->right_->left_) > height(newNode->right_->right_)) {
            // TODO: should this be flipped?
            newNode = rotateLeft(newNode);
        } else {
            // TODO: should this be flipped?
            newNode = rotateRightLeft(newNode);
        }
    }
    if (node->parent_ == nullptr) {
        root_ = newNode;
        newNode->parent_ = nullptr;
    } else {
        //Update parent's child pointers
        if (node->parent_->left_ == node) {
           node->parent_->left_ = newNode;
        } else {
            node->parent_->right_ = newNode;
        }
    }
    return newNode;
}

template <class T>
void BST<T>::fixParentPointers(BSTNode<T> *node) {
    if (node == nullptr) return;
    if (node->left_)
        node->left_->parent_ = node;
    if (node->right_)
        node->right_->parent_ = node;
}

// Rotations

/*
 *   Rotate left:
 *
 *   pivot node = a
 *
 *   ex1 R:            ex2 RL:
 *
 *       a               a               b
 *      /               /              /   \
 *     b               b         ->   a     c
 *    /                 \
 *   c                   c
 *
 */
template <class T>
BSTNode<T>* BST<T>::rotateLeft(BSTNode<T>* node) {
    BSTNode<T>* temp = node->right_;
    node->right_ = temp->left_;
    temp->left_ = node;
    return temp;
};
/*
 *  Rotate right:
 *
 *   pivot node = c
 *
 *   ex1 R:            ex2 RL:
 *
 *    a                   a              b
 *     \                   \           /   \
 *      b                   b    ->   a     c
 *       \                 /
 *        c               c
 */

template <class T>
BSTNode<T>* BST<T>::rotateRight(BSTNode<T>* node) {
    BSTNode<T>* temp = node->left_;
    node->left_ = temp->right_;
    temp->right_ = node;
    return temp;
};

template <class T>
BSTNode<T>* BST<T>::rotateLeftRight(BSTNode<T> *node) {
    node->left_ = rotateLeft(node->left_);
    return rotateRight(node);
}

template <class T>
BSTNode<T>* BST<T>::rotateRightLeft(BSTNode<T> *node) {
    node->right_ = rotateRight(node->right_);
    return rotateLeft(node);
}

template <class T>
int BSTNode<T>::getLevel() {
    int counter = 0;
    BSTNode<T>* temp = parent_;
    while (temp != nullptr) {
        temp = temp->parent_;
        counter++;
    }
    return counter;
}

template <class T>
void BST<T>::print(int order) {
    switch (order) {
        case IN_ORDER:
            printInOrder(root_);
            break;
        case PRE_ORDER:
            printPreOrder(root_);
            break;
        case POST_ORDER:
            printPostOrder(root_);
            break;
        case LEVEL_ORDER:
            printLevelOrder();
            break;
        case PRETTY:
        default:
            prettyPrint(root_);
            break;
    }
}

template <class T>
void BST<T>::printInOrder(BSTNode<T> *node) {
    if (node != nullptr) {
        printInOrder(node->left_);
        cout << node->data_ << ", ";
        printInOrder(node->right_);
    }
}

template <class T>
void BST<T>::printPreOrder(BSTNode<T> *node) {
    if (node != nullptr) {
        cout << node->data_ << ", ";
        printPreOrder(node->left_);
        printPreOrder(node->right_);
    }
}

template <class T>
void BST<T>::printPostOrder(BSTNode<T> *node) {
    if (node != nullptr) {
        printPostOrder(node->left_);
        printPostOrder(node->right_);
        cout << node->data_ << ", ";
    }
}

template <class T>
void BST<T>::printLevelOrder() {
    queue<BSTNode<T>*> q;
    q.push(this->root_);
    while (!q.empty()) {
        BSTNode<T>* temp = q.front();
        q.pop();
        cout << temp->data_ << ", ";
        if (temp->left_ != nullptr)
            q.push(temp->left_);
        if (temp->right_ != nullptr)
            q.push(temp->right_);
    }
}

template <class T>
void BST<T>::prettyPrint(BSTNode<T> *node) {
    if (node != nullptr) {
        prettyPrint(node->right_);
        indentByLevel(cout, node->getLevel());
        cout << node->data_;
        cout << endl;
        prettyPrint(node->left_);
    }
}

template <class T>
void BST<T>::indentByLevel(ostream& outs, int level) {
 for (int i = 0; i < level; i++) {
     outs << "\t";
 }
}

template <class T>
int BST<T>::height(BSTNode<T>* node) {
    // TODO: save these values to avoid repeated computations/traversals
    int leftH, rightH;
    if (node == nullptr) {
        return 0;
    }
    leftH = height(node->left_);
    rightH = height(node->right_);
    if (leftH > rightH) {
        return 1 + leftH;
    } else {
        return 1 + rightH;
    }
}

template <class T>
void BST<T>::remove(T item) {
    BSTNode<T>* temp = nullptr;
    temp = findNodeByValue(item);
    // If the node is present, remove it.
    if (temp != nullptr) {
        remove(temp);
    }
    currentSize--;
    // Otherwise, item is not in tree
    // and there is no work to be done.
}

template <class T>
void BST<T>::remove(BSTNode<T> *node) {

    // Case 1: no children
    if (node->left_ == nullptr && node->right_ == nullptr) {
        // check if this is root or left/right of
        // parent last node on the tree
        if (node->parent_ == nullptr) {
            root_ = nullptr;
        } else if (node->parent_->left_ == node) {
            node->parent_->left_ = nullptr;
        } else {
            node->parent_->right_ = nullptr;
        }
        delete node;
    // Case 2a: one child (right, no left)
    } else if (node->left_ == nullptr) {
        // Promote node->right_
        BSTNode<T>* toDelete = node->right_;
        node->data_ = toDelete->data_;
        node->left_ = toDelete->left_;
        if (node->left_ != nullptr)
            node->left_->parent_ = node;
        node->right_ = toDelete->right_;
        if (node->right_ != nullptr)
            node->right_->parent_ = node;
        delete toDelete;
    // Case 2b: one child (left, no right)
    } else if (node->right_ == nullptr) {
        // Promote node->left
        BSTNode<T>* toDelete = node->left_;
        node->data_ = toDelete->data_;
        node->left_ = toDelete->left_;
        if (node->left_ != nullptr)
            node->left_->parent_ = node;
        node->right_ = toDelete->right_;
        if (node->right_ != nullptr)
            node->right_->parent_ = node;
        delete toDelete;
    // Case 3: two children
    } else {
        // Choose someone else to delete.
        //
        // Can either be max of left subtree
        // or min of right subtree.
        //
        // Min of right subtree...
        BSTNode<T>* minOfRight = node->right_;
        while (minOfRight->left_ != nullptr) {
            minOfRight = minOfRight->left_;
        }
        node->data_ = minOfRight->data_;

        // Recurse
        remove(minOfRight);
    }

    // Rebalance after removals
    checkBalance(node->parent_);
}

template <class T>
BSTNode<T>* BST<T>::findNodeByValue(T value) {
    // Empty tree
    if (root_ == nullptr) return nullptr;

    BSTNode<T>* temp = root_;
    while (temp != nullptr) {
        if (value == temp->data_) return temp;
        if (value < temp->data_) {
            temp = temp->left_;
        } else {
            temp = temp->right_;
        }
    }

    return temp;
}

template <class T>
void BST<T>::clearAll() {
    clearAll(root_);
}

template <class T>
void BST<T>::clearAll(BSTNode<T>* node) {
    BSTNode<T>* temp = node;

    if (temp != nullptr) {
        if (temp->left_ != nullptr)
            clearAll(temp->left_);
        if (temp->right_ != nullptr)
            clearAll(temp->right_);
        delete node;
        currentSize--;
    }
}

// ---------------
// BST Node
// --------------

// Utility functions
void testInsertionAndPrinting() {
    int numbers[10] = {7,4,1,10,6,2,8,5,9,3};
    cout << "Using arr [ ";
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << ", ";
    }
    cout << "]" << endl;

    BST<int>* tree = nullptr;
    tree = new BST<int>();

    cout << endl;
    cout << "Testing removal:" << endl;
    cout << "Starting size: ";
    for (int i = 0; i < 10; i++) {
        tree->insert(numbers[i]);
    }

    cout << tree->getSize() << endl;

    // Testing clear
    delete tree;

    cout << "Size after removals: ";
    cout << tree->getSize() << endl << endl;
    cout << "Testing insertions:" << endl;
    tree = new BST<int>();
    for (int i = 0; i < 10; i++) {
        tree->insert(numbers[i]);
    }
    cout << "print: in order: ";
    tree->print(IN_ORDER);
    cout << endl;

    cout << "print: pre order: ";
    tree->print(PRE_ORDER);
    cout << endl;

    cout << "print: post order: ";
    tree->print(POST_ORDER);
    cout << endl;

    cout << "print: level order: ";
    tree->print(LEVEL_ORDER);
    cout << endl;

    cout << "print: pretty print: ";
    cout << endl;
    tree->print(PRETTY);
    cout << endl;

    cout << "removals:" << endl;
    cout << "starting size: " << tree->getSize() << endl;
    int currentRemoval;
    for (int i = 0; i < 10; i++) {
        currentRemoval = numbers[i];
        tree->remove(currentRemoval);
    }
    cout << "ending size: " << tree->getSize() << endl;
    delete tree;
}
