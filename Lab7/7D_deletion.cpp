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

    Node(long key, long height = 0,
         Node *left_child = nullptr, Node *right_child = nullptr)
        : key(key), height(height),
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
        if (current == nullptr) return 0;
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
        if (current == nullptr)
        {
            return 0;
        }
        return right_height(current) - left_height(current);
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


    Node *rotate(Node *old_root, bool type_is_left)
    {
        Node *new_root = (type_is_left) ? old_root->right_child : old_root->left_child;

        if (type_is_left)
        {
            old_root->right_child = new_root->left_child;

            new_root->left_child = old_root;
        }
        else
        {
            old_root->left_child = new_root->right_child;

            new_root->right_child = old_root;
        }

        old_root->height = calc_height(old_root);
        new_root->height = calc_height(new_root);

        return new_root;
    }

    Node *balance(Node *current)
    {
        current->height = calc_height(current);

        if (get_balance(current) < -1)
        {
            if (get_balance(current->left_child) > 0)
            {
                current->left_child = rotate(current->left_child, true);
            }
            return rotate(current, false);
        }
        if (get_balance(current) > 1)
        {
            if (get_balance(current->right_child) < 0)
            {
                current->right_child = rotate(current->right_child, false);
            }
            return rotate(current, true);
        }
        return current;
    }

    Node *insert(Node *current, long value)
    {
        if (current == nullptr)
        {
            ++node_amount;
            return new Node(value, 1);
        }

        if (current->key < value)
        {
            current->right_child = insert(current->right_child, value);
        }
        else if (current->key > value)
        {
            current->left_child = insert(current->left_child, value);
        }

        return balance(current);
    }

    Node *remove(Node *current, long value)
    {
        if (current == nullptr)
        {
            return nullptr;
        }

        if (current->key < value)
        {
            current->right_child = remove(current->right_child, value);
        }
        else if (current->key > value)
        {
            current->left_child = remove(current->left_child, value);
        }
        else
        {
            if (calc_height(current) == 1)
            {
                --node_amount;
                delete current;
                return nullptr;
            }
            else if (current->left_child == nullptr)
            {
                --node_amount;
                Node *tmp = current->right_child;
                delete current;
                current = tmp;
            }
            else
            {
                Node *predecessor = current->left_child;
                while (predecessor->right_child != nullptr)
                {
                    predecessor = predecessor->right_child;
                }

                current->key = predecessor->key;
                current->left_child = remove(current->left_child, predecessor->key);
            }

        }
        return balance(current);
    }

public:
    AVL_tree();
    AVL_tree(ifstream &in)
    {
        long N, key, left_i, right_i;
        in >> N;

        node_amount = N;

        if (node_amount < 1)
        {
            return;
        }

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
        init_heights(input_tree.front());
        root = balance(input_tree.front());
    }
    ~AVL_tree()
    {
        clear_tree(root);
    }

    void insert(long value)
    {
        root = insert(root, value);
    }

    void remove(long value)
    {
        root = remove(root, value);
    }

    void print_tree(ofstream &out)
    {
        queue<Node *> node_queue;
        if (root != nullptr) node_queue.push(root);
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
    ifstream in("deletion.in");
    ofstream out("deletion.out");

    AVL_tree tree(in);

    long value_to_insert;
    in >> value_to_insert;

    tree.remove(value_to_insert);

    tree.print_tree(out);


    return 0;
}
