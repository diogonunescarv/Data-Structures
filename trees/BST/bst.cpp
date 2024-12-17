#include <iostream>
using namespace std;

struct Node {
    int data;
    int level;
    Node* left;
    Node* right;
    Node(int val) : data(val), level(0), left(NULL), right(NULL) {}
};

class bst {
    private:
        Node* root;

        Node* insert(Node* current, int val);
        Node* remove(Node* current, int val);
        Node* findMin(Node* current);
        void inOrder(Node* current);
        void preOrder(Node* current);
        void destroyTree(Node* current);
        void setLevelsPreOrder(Node* current, int level);
        void setLevelsInOrder(Node* current, int level);
        void adjustLevels();
        bool exists(Node* current, int val);

    public:
        bst();
        ~bst();
        void insert(int val);
        void remove(int val);
        void displayInOrder();
        void displayPreOrder();
};

bst::bst() {
    root = NULL;
}

bst::~bst() {
    destroyTree(root);
}

void bst::destroyTree(Node* current) {
    if (current) {
        destroyTree(current->left);
        destroyTree(current->right);
        delete current;
    }
}

void bst::setLevelsPreOrder(Node* current, int level) {
    if (!current) return;

    current->level = level; 
    setLevelsPreOrder(current->left, level + 1); 
    setLevelsPreOrder(current->right, level + 1); 
}

void bst::setLevelsInOrder(Node* current, int level) {
    if (!current) return;

    setLevelsInOrder(current->left, level + 1);
    current->level = level; 
    setLevelsInOrder(current->right, level + 1);
}

void bst::adjustLevels() {
    setLevelsPreOrder(root, 0);
    setLevelsInOrder(root, 0);
}

Node* bst::insert(Node* current, int val) {
    if (!current) return new Node(val);

    if (val < current->data)
        current->left = insert(current->left, val);
    else if (val > current->data)
        current->right = insert(current->right, val);

    return current;
}

void bst::insert(int val) {
    root = insert(root, val);
    adjustLevels(); 
}

bool bst::exists(Node* current, int val) {
    if (!current) return false;

    if (val == current->data) return true;
    else if (val < current->data) return exists(current->left, val);
    else return exists(current->right, val);
}

Node* bst::remove(Node* current, int val) {
    if (!current) return NULL; 

    if (val < current->data) {
        current->left = remove(current->left, val);
    } else if (val > current->data) {
        current->right = remove(current->right, val);
    } else {
        if (!current->left) {
            Node* temp = current->right;
            delete current;
            return temp;
        }
        if (!current->right) {
            Node* temp = current->left;
            delete current;
            return temp;
        }

        Node* temp = findMin(current->right);
        current->data = temp->data;
        current->right = remove(current->right, temp->data);
    }
    return current;
}

void bst::remove(int val) {
    if (!exists(root, val)) { 
        cout << "ERROR" << endl;
    } else {
        root = remove(root, val); 
        adjustLevels(); 
    }
}

Node* bst::findMin(Node* current) {
    while (current && current->left)
        current = current->left;
    return current;
}

void bst::inOrder(Node* current) {
    if (current) {
        inOrder(current->left);
        cout << current->data << "/" << current->level << " ";
        inOrder(current->right);
    }
}

void bst::displayInOrder() {
    inOrder(root);
    cout << endl;
}

void bst::preOrder(Node* current) {
    if (current) {
        cout << current->data << "/" << current->level << " ";
        preOrder(current->left);
        preOrder(current->right);
    }
}

void bst::displayPreOrder() {
    preOrder(root);
    cout << endl;
}

int main() {
    bst mytree;
    char command;
    int key;

    do {
        try {
            cin >> command;
            switch (command) {
                case 'i': // Insert
                    cin >> key;
                    mytree.insert(key);
                    break;

                case 'r': // Remove
                    cin >> key;
                    mytree.remove(key);
                    break;

                case 'o': // In order exibition
                    mytree.displayInOrder();
                    break;

                case 'p': // Pre-order exibition
                    mytree.displayPreOrder();
                    break;

                case 'f': 
                    break;

                default:
                    cerr << "Invalid comand!" << endl;
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (command != 'f');

    return 0;
}
