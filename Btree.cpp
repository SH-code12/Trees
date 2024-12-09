#include <iostream>
using namespace std;

template <typename T, int order>
class Node {
public:
    T keys[order - 1];       // Keys in the node (order - 1 keys)
    Node* children[order];   // Pointers to child nodes (order children)
    int degree;              // Current number of keys
    bool isLeaf;             // True if leaf node

    // Constructor
    Node(bool isLeaf = true) {
        this->isLeaf = isLeaf;
        degree = 0;
        for (int i = 0; i < order; ++i) {  // Initialize children array to nullptr
            children[i] = nullptr;
        }
    }
};

template <typename T, int order>
class BTree {
private:
    Node<T, order>* root;

    // Split the child of a node
    void split(Node<T, order>* parent, int index) {
        Node<T, order>* fullChild = parent->children[index];
        Node<T, order>* newNode = new Node<T, order>(fullChild->isLeaf);

        int mid = (order - 1) / 2;

        // Copy second half of keys from fullChild to newNode
        newNode->degree = fullChild->degree - mid - 1;
        for (int i = 0; i < newNode->degree; ++i) {
            newNode->keys[i] = fullChild->keys[mid + 1 + i];
        }

        // If not a leaf, copy second half of children
        if (!fullChild->isLeaf) {
            for (int i = 0; i <= newNode->degree; ++i) {
                newNode->children[i] = fullChild->children[mid + 1 + i];
            }
        }

        // Reduce the degree of fullChild
        fullChild->degree = mid;

        // Shift parent's children and insert newNode
        for (int i = parent->degree; i > index; --i) {
            parent->children[i + 1] = parent->children[i];
        }
        parent->children[index + 1] = newNode;

        // Shift parent's keys and insert middle key
        for (int i = parent->degree - 1; i >= index; --i) {
            parent->keys[i + 1] = parent->keys[i];
        }
        parent->keys[index] = fullChild->keys[mid];

        parent->degree++;
    }

// Insert into a node that is not full
void insertNonFull(Node<T, order>* node, T key) {
    int index = node->degree - 1;

    if (node->isLeaf) {
        // Insert key into the correct position in the leaf node in sorted order
        while (index >= 0 && key < node->keys[index]) {
            node->keys[index + 1] = node->keys[index];
            index--;
        }
        node->keys[index + 1] = key;  // Insert the key at the correct position
        node->degree++;
    } else {
        // Find the child to descend into
        while (index >= 0 && key < node->keys[index]) {
            index--;
        }
        index++;

        // Split the child if full
        if (node->children[index]->degree == order) { // Check if the child is full
            split(node, index);
            // After splitting, check which child the new key should go into
            if (key > node->keys[index]) {
                index++;
            }
        }
        // Recursively insert the key into the appropriate child
        insertNonFull(node->children[index], key);
    }
}


    // Traverse and print the tree
    void traverse(Node<T, order>* node, int level = 0) {
        if (node == nullptr) return;

        // Print current level
        for (int i = 0; i < level; ++i) cout << "  ";
        for (int i = 0; i < node->degree ; ++i) {
            cout << node->keys[i];
            if (i < node->degree - 1) cout << ",";
        }
        cout << endl;

        // Recursively print child nodes
        if (!node->isLeaf) {
            for (int i = 0; i <= node->degree; ++i) {
                traverse(node->children[i], level + 1);
            }
        }
    }

public:
    BTree() {
        root = nullptr;
    }

    // Insert a key into the BTree
    void Insert(T key) {
        if (root == nullptr) {
            root = new Node<T, order>(true);
            root->keys[0] = key;
            root->degree = 1;
        } else {
            if (root->degree == order ) {
                Node<T, order>* newRoot = new Node<T, order>(false);
                newRoot->children[0] = root;
                split(newRoot, 0);
                root = newRoot;
            }
            insertNonFull(root, key);
        }
    }

    // Print the BTree
    void Print() {
        traverse(root);
    }
};

int main() {
    BTree<int, 3> t1;
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    t1.Print();

    BTree <char, 5> t; // Construct a BTree of order 5, which stores char data
    t.Insert('G');

    t.Insert('I');

    t.Insert('B');

    t.Insert('J');

    t.Insert('C');

    t.Insert('A');

    t.Insert('K');

    t.Insert('E');

    t.Insert('D');

    t.Insert('S');
    // t.Print();

    t.Insert('T');
    // t.Print();

    t.Insert('R');
    // t.Print();

    t.Insert('L');
    

    t.Insert('F');

    t.Insert('H');
    // t.Print();

    t.Insert('M');
    // t.Print();

    t.Insert('N');
    // t.Print();

    t.Insert('P');
    // t.Print();

    t.Insert('Q');
    t.Print(); // Should output the tree in the correct structure

    return 0;
}
