#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

struct Linked_Pair
{
    Linked_Pair(string key, string value,
                Linked_Pair *previous = nullptr,
                Linked_Pair *next = nullptr)
        : key(key), value(value), previous(previous), next(next) {}

    ~Linked_Pair()
    {
        if (previous != nullptr)
        {
            previous->next = next;
        }
        if (next != nullptr)
        {
            next->previous = previous;
        }
    }

    string key;
    string value;
    Linked_Pair *previous;
    Linked_Pair *next;
};

class Linked_Map
{
private:

    list<Linked_Pair *> *hash_table;
    Linked_Pair *last_pair;
    unsigned long width;

private:
    unsigned long hash(string key)
    {
        unsigned long long hash_result = 0;
        unsigned long pow = 1;
        for (short i = 0; i < key.size(); ++i)
        {
            hash_result += (key[i] - 'A' + 1) * pow;
            pow *= 3;
        }
        hash_result %= width;
        return hash_result;
    }

public:
    Linked_Map(unsigned long capacity = 10000)
    {
        width = capacity;
        hash_table = new list<Linked_Pair *>[width];
        last_pair = nullptr;
    }

    ~Linked_Map()
    {
        Linked_Pair *current_pair = last_pair, *tmp = nullptr;
        while (current_pair != nullptr)
        {
            tmp = current_pair->previous;
            delete current_pair;
            current_pair = tmp;
        }
        delete [] hash_table;
    }

    void insert(string key, string value)
    {
        unsigned long index = hash(key);
        for (auto pair = hash_table[index].begin(); pair != hash_table[index].end(); ++pair)
        {
            if ((*pair)->key == key)
            {
                (*pair)->value = value;
                return;
            }
        }
        Linked_Pair *pair = new Linked_Pair(key, value, last_pair);
        if (last_pair != nullptr)
        {
            last_pair->next = pair;
        }
        last_pair = pair;
        hash_table[index].push_back(pair);
    }

    string get(string key)
    {
        unsigned long index = hash(key);
        for (Linked_Pair * pair: hash_table[index])
        {
            if (pair->key == key)
            {
                return pair->value;
            }
        }
        return "none";
    }

    void remove(string key)
    {
        unsigned long index = hash(key);
        for (auto pair = hash_table[index].begin(); pair != hash_table[index].end(); ++pair)
        {
            if ((*pair)->key == key)
            {
                if (last_pair == (*pair))
                {
                    last_pair = (*pair)->previous;
                }
                delete (*pair);
                hash_table[index].erase(pair);
                break;
            }
        }
    }

    string predecessor(string key)
    {
        unsigned long index = hash(key);
        for (Linked_Pair * pair: hash_table[index])
        {
            if (pair->key == key)
            {
                if (pair->previous != nullptr)
                {
                    return pair->previous->value;
                }
                else
                {
                    return "none";
                }
            }
        }
        return "none";
    }

    string successor(string key)
    {
        unsigned long index = hash(key);
        for (Linked_Pair * pair: hash_table[index])
        {
            if (pair->key == key)
            {
                if (pair->next != nullptr)
                {
                    return pair->next->value;
                }
                else
                {
                    return "none";
                }
            }
        }
        return "none";
    }

};

int main()
{
    ifstream in("linkedmap.in");
    ofstream out("linkedmap.out");

    string command, x, y;

    Linked_Map custom_linked_map(100001);

    while (!in.eof())
    {
        command.clear();
        in >> command >> x;

        if (command == "put")
        {
            in >> y;
            custom_linked_map.insert(x, y);
        }
        else if (command == "delete")
        {
            custom_linked_map.remove(x);
        }
        else if (command == "get")
        {
            cout << custom_linked_map.get(x) << endl;
        }
        else if (command == "prev")
        {
            cout << custom_linked_map.predecessor(x) << endl;
        }
        else if (command == "next")
        {
            cout << custom_linked_map.successor(x) << endl;
        }
    }
    return 0;
}
