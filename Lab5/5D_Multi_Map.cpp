#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

class Set
{
private:
    list<string> *hash_table;
    unsigned long width;

private:
    unsigned long hash(string key)
    {
        unsigned long pow = 1;
        unsigned long hash_value = 0;
        for (short i = 0; i < key.size(); ++i)
        {
            hash_value += (key[i] - 'A' + 1) * pow;
            pow *= 41;
            hash_value %= width;
        }

        return hash_value;
    }

public:
    Set(unsigned long capacity)
    {
        width = capacity;
        hash_table = new list<string>[width];
    }
    ~Set()
    {
        delete [] hash_table;
    }

    bool exists(string value_to_find)
    {
        unsigned long index = hash(value_to_find);
        for (string key: hash_table[index])
        {
            if (key == value_to_find)
            {
                return true;
            }
        }
        return false;
    }
    void insert(string value_to_insert)
    {
        unsigned long index = hash(value_to_insert);
        if (!exists(value_to_insert))
        {
            hash_table[index].push_back(value_to_insert);
        }
    }
    void remove(string value_to_remove)
    {
        unsigned long index = hash(value_to_remove);
        for (auto element = hash_table[index].begin(); element != hash_table[index].end(); ++element)
        {
            if (*element == value_to_remove)
            {
                hash_table[index].erase(element);
                break;
            }
        }
    }
    list<string> get_elements()
    {
        list<string> elements;
        for (unsigned long i = 0; i < width; ++i)
        {
            if (!hash_table[i].empty())
            {
                elements.insert(elements.end(), hash_table[i].begin(), hash_table[i].end());
            }
        }
        return elements;
    }
};

struct Multi_Pair
{
    Multi_Pair(string key, string value)
    {
        this->key = key;
        values = new Set(300);
        values->insert(value);
    }
    ~Multi_Pair()
    {
        delete values;
    }

    string key;
    Set *values;
};

class Multi_Map
{
private:
    list<Multi_Pair *> *hash_table;
    unsigned long width;

private:
    unsigned long hash(string key)
    {
        unsigned long pow = 1;
        unsigned long hash_value = 0;
        for (short i = 0; i < key.size(); ++i)
        {
            hash_value += (key[i] - 'A' + 1) * pow;
            pow *= 41;
            hash_value %= width;
        }

        return hash_value;
    }

    Set *get_element_values(string key)
    {
        unsigned long index = hash(key);
        for (Multi_Pair *pair: hash_table[index])
        {
            if (pair->key == key)
            {
                return pair->values;
            }
        }
        return nullptr;
    }
public:

    Multi_Map(unsigned long capacity = 100000)
    {
        width = capacity;
        hash_table = new list<Multi_Pair *>[width];
    }
    ~Multi_Map()
    {
        delete [] hash_table;
    }

    void insert(string key, string value)
    {
        unsigned long index = hash(key);
        Set *values = get_element_values(key);

        if (values == nullptr)
        {
            Multi_Pair *pair = new Multi_Pair(key, value);
            hash_table[index].push_back(pair);
        }
        else
        {
            values->insert(value);
        }
    }
    void remove(string key, string value)
    {
        Set *values = get_element_values(key);
        if (values != nullptr)
        {
            values->remove(value);
        }
    }
    void remove_all(string key)
    {
        unsigned long index = hash(key);
        for (auto pair = hash_table[index].begin(); pair != hash_table[index].end(); ++pair)
        {
            if ((*pair)->key == key)
            {
                hash_table[index].erase(pair);
                break;
            }
        }
    }
    list<string> get(string key)
    {
        Set *values = get_element_values(key);
        if (values == nullptr)
        {
            return list<string>(0);
        }
        else
        {
            return values->get_elements();
        }
    }

};

int main()
{
    ifstream in("multimap.in");
    ofstream out("multimap.out");

    string command, x, y;

    Multi_Map custom_multi_map(100001);

    while (!in.eof())
    {
        command.clear();
        in >> command >> x;

        if (command == "put")
        {
            in >> y;
            custom_multi_map.insert(x, y);
        }
        else if (command == "delete")
        {
            in >> y;
            custom_multi_map.remove(x, y);
        }
        else if (command == "get")
        {
            list<string> values = custom_multi_map.get(x);
            cout << values.size() << " ";
            for (string value: values)
            {
                cout << value << " ";
            }
            cout << endl;
        }
        else if (command == "deleteall")
        {
            custom_multi_map.remove_all(x);
        }
    }
    return 0;
}
