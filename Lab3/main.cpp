#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<long> history;

void min_heapify(vector<vector<long>> &heap, int node_i)
{
    int left = 2 * (node_i + 1) - 1;
    int right = 2 * (node_i + 1);
    int smallest_i = node_i;
    if (left < heap.size() && heap[left][0] < heap[smallest_i][0])
    {
        smallest_i = left;
    }
    if (right < heap.size() && heap[right][0] < heap[smallest_i][0])
    {
        smallest_i = right;
    }

    if (smallest_i != node_i)
    {
        swap(history[heap[node_i][1]], history[heap[smallest_i][1]]);
        swap(heap[node_i], heap[smallest_i]);
        min_heapify(heap, smallest_i);
    }
}

void heap_decrease_key(vector<vector<long>> &heap, long node_i, long key)
{
    if (key <= heap[node_i][0])
    {
        heap[node_i][0] = key;
        while (node_i > 0 && heap[(node_i + 1) / 2 - 1][0] > heap[node_i][0])
        {
            swap(history[heap[(node_i + 1) / 2 - 1][1]], history[heap[node_i][1]]);
            swap(heap[node_i], heap[(node_i + 1) / 2 - 1]);
            node_i = (node_i + 1) / 2 - 1;
        }
    }
}

void heap_extract_min(vector<vector<long>> &heap, ofstream &out)
{
    if (heap.size() == 0)
    {
        cout << "*\n";
        return;
    }
    long min = heap[0][0];
    heap[0] = heap.back();
    history[heap[0][1]] = 0;
    heap.pop_back();
    min_heapify(heap, 0);
    cout << min << "\n";
}

int main()
{
    ifstream in("priorityqueue.in");
    ofstream out("priorityqueue.out");

    vector<vector<long>> heap;

    string command = "";
    long x = 0, y = 0;
    while (!in.eof())
    {
        command.clear();
        in >> command;
        if (command == "extract-min")
        {
            heap_extract_min(heap, out);
            history.push_back(-1);
        }
        else if (command == "push")
        {
            in >> x;
            long position = heap.size();
            heap.push_back({LONG_MAX, (long) history.size()});
            history.push_back(position);
            heap_decrease_key(heap, position, x);
        }
        else if (command == "decrease-key")
        {
            in >> x >> y;
            heap_decrease_key(heap, history[x - 1], y);
            history.push_back(-1);
        }
    }
    return 0;
}
