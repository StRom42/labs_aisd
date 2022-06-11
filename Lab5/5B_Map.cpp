#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>

using namespace std;

class Map
{
private:
    struct Pair
    {
        string key;
        string value;
    };
    list<Pair> *hash_table;
    unsigned long width;

private:
    unsigned long hash(string key)
    {
        unsigned long long hash_result = 0;
        for (short i = 0; i < key.size(); ++i)
        {
            hash_result += (key[i] - 'a' + 1) * pow(3.0, i);
        }
        hash_result %= width;
        return hash_result;
    }

public:
    Map(unsigned long capacity = 10000)
    {
        width = capacity;
        hash_table = new list<Pair>[width];
    }
    ~Map()
    {
        delete [] hash_table;
    }
    void insert(string key, string value)
    {
        unsigned long index = hash(key);
        for (auto pair = hash_table[index].begin(); pair != hash_table[index].end(); ++pair)
        {
            if (pair->key == key)
            {
                pair->value = value;
                return;
            }
        }
        hash_table[index].push_back({key, value});
    }
    void remove(string key)
    {
        unsigned long index = hash(key);
        auto pair_i = hash_table[index].begin();
        for (auto pair = hash_table[index].begin(); pair != hash_table[index].end(); ++pair)
        {
            if (pair->key == key)
            {
                hash_table[index].erase(pair_i);
                break;
            }
            ++pair_i;
        }
    }
    string get(string key)
    {
        unsigned long index = hash(key);
        string value;
        for (auto pair = hash_table[index].begin(); pair != hash_table[index].end(); ++pair)
        {
            if (pair->key == key)
            {
                value = pair->value;
                break;
            }
        }

        return ((value.empty()) ? "none" : value);
    }

};

int main()
{
    ifstream in("map.in");
    ofstream out("map.out");

    string command, x, y;

    Map custom_map(100001);

    while (!in.eof())
    {
        command.clear();
        in >> command >> x;

        if (command == "put")
        {
            in >> y;
            custom_map.insert(x, y);
        }
        else if (command == "delete")
        {
            custom_map.remove(x);
        }
        else if (command == "get")
        {
            out << custom_map.get(x) << endl;
        }
    }
    return 0;
}
