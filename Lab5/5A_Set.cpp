#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class Set
{
private:
    vector<vector<long>> hash_table;
    long width;
    long p, a, b;

private:
    long hash(long key)
    {
        long hash_value = abs((a * key + b) % p) % width;

        return hash_value;
    }

public:
    Set(long capacity)
    {
        width = capacity;

        hash_table.resize(width);
        
        srand(42);

        p = (long) pow(2, ceil(log2(width)));
        a = rand() % p;
        b = rand() % (p - 1) + 1;
    }

    bool exists(long value_to_find)
    {
        long index = hash(value_to_find);
        for (long key: hash_table[index])
        {
            if (key == value_to_find)
            {
                return true;
            }
        }
        return false;
    }
    void insert(long value_to_insert)
    {
        long index = hash(value_to_insert);
        if (!exists(value_to_insert))
        {
            hash_table[index].push_back(value_to_insert);
        }
    }
    void remove(long value_to_remove)
    {
        long index = hash(value_to_remove);
        for (long i = 0; i < hash_table[index].size(); ++i)
        {
            if (hash_table[index][i] == value_to_remove)
            {
                hash_table[index].erase(hash_table[index].begin() + i);
            }
        }
    }


};

int main()
{
    ifstream in("set.in");
    ofstream out("set.out");

    string command;
    long operand = 0;

    Set custom_set(1000000);

    while (!in.eof())
    {
        command.clear();
        in >> command;
        in >> operand;

        if (command == "insert")
        {
            custom_set.insert(operand);
        }
        else if (command == "delete")
        {
            custom_set.remove(operand);
        }
        else if (command == "exists")
        {
            out << ((custom_set.exists(operand)) ? "true" : "false") << endl;
        }
    }
    return 0;
}
