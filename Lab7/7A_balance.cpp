#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Node
{
    long key;
    long height;
    Node *parent;
    Node *left_child;
    Node *right_child;

    Node(long key, Node *parent = nullptr,
         Node *left_child = nullptr, Node *right_child = nullptr)
        : key(key), parent(parent), height(0),
          left_child(left_child), right_child(right_child) {}
};

class AVL_tree
{
private:
    Node *root = nullptr;
    vector<Node *> tree;

private:
    Node *calc_heights(Node *current)
    {
        if (current->left_child == nullptr &&
                current->right_child == nullptr)
        {
            current->height = 1;
            return current;
        }
        long left_h = 0, right_h = 0;
        if (current->left_child != nullptr)
        {
            Node *left = calc_heights(current->left_child);
            left_h = left->height;
        }
        if (current->right_child != nullptr)
        {
            Node *right = calc_heights(current->right_child);
            right_h = right->height;
        }
        current->height = max(left_h, right_h) + 1;
        return current;
    }
    long get_balance(Node *current)
    {
        long left_h = 0, right_h = 0;
        if (current->left_child != nullptr)
        {
            left_h = current->left_child->height;
        }
        if (current->right_child != nullptr)
        {
            right_h = current->right_child->height;
        }
        return right_h - left_h;
    }

public:
    AVL_tree();
    AVL_tree(ifstream &in)
    {
        long N, key, left_i, right_i;
        in >> N;

        tree.resize(N);

        for (long i = 0; i < N; ++i)
        {
            in >> key >> left_i >> right_i;
            if (i == 0)
            {
                tree[i] = new Node(key);
            }
            else
            {
                tree[i]->key = key;
            }
            if (left_i != 0)
            {
                tree[left_i - 1] = new Node(0, tree[i]);
                tree[i]->left_child = tree[left_i - 1];
            }
            if (right_i != 0)
            {
                tree[right_i - 1] = new Node(0, tree[i]);
                tree[i]->right_child = tree[right_i - 1];
            }
        }
        root = calc_heights(tree[0]);
    }
    ~AVL_tree()
    {
        for (long i = 0; i < tree.size(); ++i)
        {
            delete tree[i];
        }
    }

    void print_tree(ofstream &out)
    {
        for (long i = 0; i < tree.size(); ++i)
        {
            out << get_balance(tree[i]) << endl;
        }
    }


};

int main()
{
    ifstream in("balance.in");
    ofstream out("balance.out");

    AVL_tree tree(in);
    tree.print_tree(out);


    return 0;
}
