#include <iostream>
#include <fstream>

using namespace std;

void calc_heights(double bulb_heights[], long garland_length, double h1, double h2)
{
    fill(bulb_heights, bulb_heights + garland_length - 1, 0);

    bulb_heights[0] = h1;
    bulb_heights[1] = h2;

    for (long i = 2; i < garland_length; ++i)
    {
        bulb_heights[i] = 2 * bulb_heights[i - 1] - bulb_heights[i - 2] + 2;
    }
}

bool garland_is_valid(double bulb_heights[], long garland_length)
{
    for (long i = 0; i < garland_length; ++i)
    {
        if (bulb_heights[i] < 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    long n;
    double A;
    cin >> n >> A;

    double bottom = 0, top = A, middle;
    double bulb_heights[n];

    while (top - bottom > 1e-8)
    {
        middle = (top + bottom) / 2;

        calc_heights(bulb_heights, n, A, middle);

        if (garland_is_valid(bulb_heights, n))
        {
            top = middle;
        }
        else
        {
            bottom = middle;
        }
    }

    cout << fixed;
    cout.precision(2);
    cout << bulb_heights[n - 1];

    return 0;
}
