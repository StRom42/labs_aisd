#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    long key;
    long height;
    Node *left_child;
    Node *right_child;

    Node(long key,
         Node *left_child = nullptr, Node *right_child = nullptr)
        : key(key), height(0),
          left_child(left_child), right_child(right_child) {}
};

class AVL_tree
{
private:
    Node *root = nullptr;
    long node_amount = 0;

private:
    long left_height(Node *node)
    {
        return ((node->left_child == nullptr) ? 0 : node->left_child->height);
    }
    long right_height(Node *node)
    {
        return ((node->right_child == nullptr) ? 0 : node->right_child->height);
    }
    long calc_height(Node *current)
    {
        return max(left_height(current), right_height(current)) + 1;
    }
    void init_heights(Node *current)
    {
        if (current == nullptr)
        {
            return;
        }
        if (current->left_child == nullptr &&
                current->right_child == nullptr)
        {
            current->height = 1;
            return;
        }

        init_heights(current->left_child);
        init_heights(current->right_child);

        current->height = calc_height(current);
    }
    long get_balance(Node *current)
    {
        long left_h = 0, right_h = 0;
        if (current == nullptr)
        {
            return 0;
        }
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

    void clear_tree(Node *current)
    {
        if (current == nullptr)
        {
            return;
        }
        clear_tree(current->left_child);
        clear_tree(current->right_child);

        delete current;
    }


    Node *rotation(Node *old_root, bool type_is_left)
    {
        Node *new_root = nullptr;

        if (type_is_left)
        {
            new_root = old_root->right_child;

            old_root->right_child = new_root->left_child;

            new_root->left_child = old_root;
        }
        else
        {
            new_root = old_root->left_child;

            old_root->left_child = new_root->right_child;

            new_root->right_child = old_root;
        }

        calc_height(old_root);
        calc_height(new_root);

        return new_root;
    }

    Node *balance(Node *current)
    {
        if (get_balance(current->right_child) < 0)
        {
            current->right_child = rotation(current->right_child, false);
        }

        return rotation(current, true);
    }

public:
    AVL_tree();
    AVL_tree(ifstream &in)
    {
        long N, key, left_i, right_i;
        in >> N;

        node_amount = N;

        vector<Node *> input_tree(N);

        for (long i = 0; i < N; ++i)
        {
            in >> key >> left_i >> right_i;
            if (i == 0)
            {
                input_tree[i] = new Node(key);
            }
            else
            {
                input_tree[i]->key = key;
            }
            if (left_i != 0)
            {
                input_tree[left_i - 1] = new Node(0);
                input_tree[i]->left_child = input_tree[left_i - 1];
            }
            if (right_i != 0)
            {
                input_tree[right_i - 1] = new Node(0);
                input_tree[i]->right_child = input_tree[right_i - 1];
            }
        }
        init_heights(input_tree[0]);
        root = input_tree[0];

        root = balance(root);
    }
    ~AVL_tree()
    {
        clear_tree(root);
    }

    void print_tree(ofstream &out)
    {
        queue<Node *> node_queue;
        node_queue.push(root);
        long num = 1, left_i = 0, right_i = 0;
        Node *current = nullptr;

        out << node_amount << endl;

        while (!node_queue.empty())
        {
            left_i = 0; right_i = 0;

            current = node_queue.front();
            node_queue.pop();

            if (current->left_child != nullptr)
            {
                node_queue.push(current->left_child);
                left_i = ++num;
            }
            if (current->right_child != nullptr)
            {
                node_queue.push(current->right_child);
                right_i = ++num;
            }

            out << current->key << " " << left_i << " " << right_i << endl;
        }
    }

};

int main()
{
    ifstream in("rotation.in");
    ofstream out("rotation.out");

    AVL_tree tree(in);

    tree.print_tree(out);


    return 0;
}
