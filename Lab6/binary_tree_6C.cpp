#include <iostream>
#include <fstream>

using namespace std;

class BSTree
{
private:
    struct Node
    {
        Node(long value = 0, Node * parent = nullptr, Node * left = nullptr, Node * right = nullptr)
            : value(value), left(left), right(right), parent(parent) {};

        ~Node()
        {
            delete left;
            delete right;
        }

        long value;
        Node * left;
        Node * right;
        Node * parent;
    };

    Node * make_node(long value = 0)
    {
        Node *new_node = new Node(value);
        return new_node;
    }
    Node * insert_algo(Node * current, long value_to_insert)
    {
        if (current == nullptr)
        {
            return make_node(value_to_insert);
        }
        if (value_to_insert < current->value)
        {
            current->left = insert_algo(current->left, value_to_insert);
            current->left->parent = current;
        }
        else if (value_to_insert > current->value)
        {
            current->right = insert_algo(current->right, value_to_insert);
            current->right->parent = current;
        }
        return current;
    }
    Node * find_minimum(Node * subtree_root)
    {
        Node * current = subtree_root;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }
    Node * find_maximum(Node * subtree_root)
    {
        Node * current = subtree_root;
        while (current->right != nullptr)
        {
            current = current->right;
        }
        return current;
    }

    Node * find_successor(Node * current)
    {
        if (current->right != nullptr)
        {
            return find_minimum(current->right);
        }
        Node * parent_node = current->parent;
        while (parent_node != nullptr && current == parent_node->right)
        {
            current = parent_node;
            parent_node = current->parent;
        }
        return parent_node;
    }
    Node * delete_algo(Node * current, long value_to_delete)
    {
        if (current == nullptr)
        {
            return nullptr;
        }
        if (current->value == value_to_delete)
        {
            if (current->left == nullptr && current->right == nullptr)
            {
                delete current;
                return nullptr;
            }
            else if (current->right == nullptr)
            {
                Node * tmp = current->left;
                tmp->parent = current->parent;
                current->left = nullptr;
                delete current;
                return tmp;
            }
            else
            {
                Node * successor = find_successor(current);
                current->value = successor->value;
                current->right = delete_algo(current->right, current->value);
            }
        }
        if (current->value > value_to_delete)
        {
            current->left = delete_algo(current->left, value_to_delete);
        }
        if (current->value < value_to_delete)
        {
            current->right = delete_algo(current->right, value_to_delete);
        }

        return current;
    }

    Node * find_algo(Node * current, long value_to_find)
    {
        if (current == nullptr)
        {
            return nullptr;
        }
        if (current->value == value_to_find)
        {
            return current;
        }
        else if (current->value < value_to_find)
        {
            return find_algo(current->right, value_to_find);
        }
        else
        {
            return find_algo(current->left, value_to_find);
        }
    }

    long find_next_value_algo(Node * current, long value)
    {
        if (current == nullptr)
        {
            return LONG_MAX;
        }
        if (current->value > value)
        {
            if (current->left == nullptr)
            {
                return current->value;
            }
            long next = find_next_value_algo(current->left, value);

            return ((next != LONG_MAX) ? next : current->value);
        }
        return find_next_value_algo(current->right, value);
    }
    long find_prev_value_algo(Node * current, long value)
    {
        if (current == nullptr)
        {
            return LONG_MIN;
        }
        if (current->value < value)
        {
            if (current->right == nullptr)
            {
                return current->value;
            }
            long prev = find_prev_value_algo(current->right, value);

            return ((prev != LONG_MIN) ? prev : current->value);
        }
        return find_prev_value_algo(current->left, value);
    }

public:
    BSTree()
    {
        root = nullptr;
    }
    ~BSTree()
    {
        delete root;
    }
    void insert(long value)
    {
        root = insert_algo(root, value);
    }
    void del_value(long value)
    {
        root = delete_algo(root, value);
    }
    bool exists(long value)
    {
        Node * current = find_algo(root, value);
        return (current != nullptr);
    }
    long next_value(long value)
    {
        return find_next_value_algo(root, value);
    }
    long prev_value(long value)
    {
        return find_prev_value_algo(root, value);
    }

private:
    Node *root;
};





int main()
{
    ifstream in("bstsimple.in");
    ofstream out("bstsimple.out");

    BSTree tree;

    string command = "";
    long operand = 0;

    while (!in.eof())
    {
        command.clear();
        in >> command >> operand;

        if (command == "insert")
        {
            tree.insert(operand);
        }
        else if (command == "delete")
        {
            tree.del_value(operand);
        }
        else if (command == "exists")
        {
            out << ((tree.exists(operand)) ? "true" : "false") << endl;
        }
        else if (command == "next")
        {
            long result = tree.next_value(operand);
            if (result != LONG_MAX)
            {
                out << result << endl;
            }
            else
            {
                out << "none" << endl;
            }
        }
        else if (command == "prev")
        {
            long result = tree.prev_value(operand);
            if (result != LONG_MIN)
            {
                out << result << endl;
            }
            else
            {
                out << "none" << endl;
            }
        }

    }

    return 0;
}
