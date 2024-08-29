#include <iostream>
#include <vector>

#define MAX_KEYS 3 //Maximum number of keys in a node. For 2-3-4 tree, max is 3

using namespace std;
class TwoThreeFourTree;

struct Node {
    vector<int> keys;
    bool isLeaf;
    vector<Node*> children;

    Node() : isLeaf(true), children(4, nullptr) {};
};

void printTree(const Node* node)//pre-order
{
    if (node == nullptr)
        return;
    printTree(node->children[0]);

    if (node->keys.size() >= 1)
        cout << node->keys[0] << " ";

    printTree(node->children[1]);

    if (node->keys.size() >= 2)
        cout << node->keys[1] << " ";

    printTree(node->children[2]);

    if (node->keys.size() >= 3)
        cout << node->keys[2] << " ";

    printTree(node->children[3]);
}

class TwoThreeFourTree {
private:
    Node* root;
    int t; //degree
public:
    TwoThreeFourTree() : root{ nullptr }, t(2) {};

    Node* getRoot() const
    {
        return root;
    }

    void insert(int key)
    {
        if (root == nullptr)
        {
            createTree(key);
        }
        else if (root->keys.size() == MAX_KEYS)
        {
            splitRoot();
            insertNonFilled(root, key);
        }
        else 
        {
            insertNonFilled(root, key);
        }
    }

    void createTree(int key)
    {
        if (root == nullptr)
        {
            root = new Node();
            root->keys.push_back(key);
            root->isLeaf = true;
        }
    }

    void splitRoot()
    {
        Node* temp = new Node();
        temp->isLeaf = false;
        temp->children[0] = root;
        root = temp;
        splitChild(root, 0);
    }

    void splitChild(Node* x, int i){
        Node* z = new Node();
        Node* y = x->children[i];
        z->isLeaf = y->isLeaf;

        for (int j = 0; j < (t - 1); j++){
            z->keys.insert(z->keys.begin() + j, y->keys[j + t]);
        }

        if (!y->isLeaf){
            for (int j = 0; j < t; j++)
            {
                z->children[j] = y->children[j + t];
            }
        }
        x->keys.insert(x->keys.begin() + i, y->keys[t - 1]);
        x->children.insert(x->children.begin() + i + 1, z);
        x->children.resize(4);
        y->keys.resize(t - 1);
    }

    void insertNonFilled(Node* node, int key){
        int i = node->keys.size();
        if (node->isLeaf){
            while (i > 0 && key < node->keys[i - 1]){
                i--;
            }
            node->keys.insert(node->keys.begin() + i, key);
        }
        else{
            while (i > 0 && key < node->keys[i - 1]){
                i--;
            }
            if (node->children[i]->keys.size() == MAX_KEYS){
                splitChild(node, i);
                if (key > node->keys[i]){
                    i++;
                }
            }
            insertNonFilled(node->children[i], key);
        }
    }
};

int main()
{
    TwoThreeFourTree mTree;
    mTree.insert(15);
    mTree.insert(10);
    mTree.insert(20);
    mTree.insert(5);
    mTree.insert(4);
    mTree.insert(3);
    mTree.insert(2);
    mTree.insert(1);
    Node* node = mTree.getRoot();
    printTree(node);
    return 0;
}