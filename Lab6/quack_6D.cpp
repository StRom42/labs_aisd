#include <iostream>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

class Quack
{
private:
    queue<uint16_t> quack_queue;
    vector<uint16_t> registers;
    map<string, long> labels;
    long current_position;

public:
    Quack()
    {
        registers = vector<uint16_t>(26);
        current_position = 0;
    }
    void put(uint16_t x)
    {
        quack_queue.push(x);
    }
    void arithmetic_operation(const char operation)
    {
        uint16_t x = quack_queue.front(); quack_queue.pop();
        uint16_t y = quack_queue.front(); quack_queue.pop();
        uint16_t result = 0;
        switch (operation)
        {
            case '+':
                result = x + y;
            break;
            case '-':
                result = x - y;
            break;
            case '*':
                result = x * y;
            break;
            case '/':
                result = (y == 0) ? 0 : x / y;
            break;
            case '%':
                result = (y == 0) ? 0 : x % y;
            break;
        }
        quack_queue.push(result);
    }
    void put_into_register(const char reg)
    {
        uint16_t x = quack_queue.front(); quack_queue.pop();
        registers[reg - 'a'] = x;
    }
    void get_from_register(const char reg)
    {
        quack_queue.push(registers[reg - 'a']);
    }
    void quack_print(ostream &out, const char reg = 0, bool as_char = false)
    {
        uint16_t x = 0;
        if (reg == 0)
        {
            x = quack_queue.front(); quack_queue.pop();
        }
        else
        {
            x = registers[reg - 'a'];
        }
        if (as_char)
        {
            out << (char) (x % 256);
        }
        else
        {
            out << x << endl;
        }
    }
    void set_label(string label)
    {
        labels[label] = current_position;
    }
    void transfer(string label, char reg1 = 0, char reg2 = 0, bool equals_condition = true)
    {
        long position = labels[label];
        if (reg1 == 0)
        {
            current_position = position;
        }
        else if (reg2 == 0)
        {
            if (registers[reg1 - 'a'] == 0)
            {
                current_position = position;
            }
        }
        else if (equals_condition)
        {
            if (registers[reg1 - 'a'] == registers[reg2 - 'a'])
            {
                current_position = position;
            }
        }
        else if (!equals_condition)
        {
            if (registers[reg1 - 'a'] > registers[reg2 - 'a'])
            {
                current_position = position;
            }
        }
    }
    void quit()
    {
        current_position = -2;
    }

    void update_labels(vector<string> &code)
    {
        labels.clear();

        for (long i = 0; i < code.size(); ++i)
        {
            if (code[i][0] == ':')
            {
                labels[code[i].substr(1)] = i;
            }
        }
    }

    void run(vector<string> &code, ostream &out)
    {
        current_position = 0;
        string command = "";
        string arithmetic_operators = "+-*/%";
        update_labels(code);

        while (current_position >= 0 && current_position < code.size())
        {
            command = code[current_position];
            if (arithmetic_operators.find(command[0]) != string::npos)
            {
                arithmetic_operation(command[0]);
            }
            else if (command[0] == '>')
            {
                put_into_register(command[1]);
            }
            else if (command[0] == '<')
            {
                get_from_register(command[1]);
            }
            else if (command[0] == 'P')
            {
                if (command.size() == 1)
                {
                    quack_print(out);
                }
                else
                {
                    quack_print(out, command[1]);
                }
            }
            else if (command[0] == 'C')
            {
                if (command.size() == 1)
                {
                    quack_print(out, 0, true);
                }
                else
                {
                    quack_print(out, command[1], true);
                }
            }
            else if (command[0] == 'J')
            {
                transfer(command.substr(1));
            }
            else if (command[0] == 'Z')
            {
                transfer(command.substr(2), command[1]);
            }
            else if (command[0] == 'E')
            {
                transfer(command.substr(3), command[1], command[2], true);
            }
            else if (command[0] == 'G')
            {
                transfer(command.substr(3), command[1], command[2], false);
            }
            else if (command[0] == ':')
            {
                set_label(command.substr(1));
            }
            else
            {
                uint32_t x = stoi(command) % 65536;
                put(x);
            }

            ++current_position;
        }
    }

};

int main()
{
    ifstream in("quack.in");
    ofstream out("quack.out");

    Quack interpreter;
    vector<string> code;

    string command = "";
    while (!in.eof())
    {
        command.clear();
        in >> command;
        if (command.size() > 0)
        {
            code.push_back(command);
        }
    }

    interpreter.run(code, cout);
    return 0;
}
