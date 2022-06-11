#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream in("height.in");
	ofstream out("height.out");

	long n, key, left_child, right_child;
	in >> n;

	long node_levels[n];
	// fill(node_levels, node_levels + n - 1, 0);
	long max_level = 0;
	for (long i = 0; i < n; ++i)
	{
		if (i == 0)
		{
			node_levels[i] = 1;
		}
		in >> key >> left_child >> right_child;
		if (left_child != 0)
		{
			node_levels[left_child - 1] = node_levels[i] + 1;
		}
		if (right_child != 0)
		{
			node_levels[right_child - 1] = node_levels[i] + 1;
		}

		if (max_level < node_levels[i])
		{
			max_level = node_levels[i];
		}
	}

	out << max_level;
	return 0;
}