#include <bits/stdc++.h>

using namespace std;

// Heuristic function --> number of inversions in the array
// We try to minimize the value of heuristic function
int heuristic_value(vector<int> &v)
{
    int val = 0, n = v.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (v[j] < v[i])
                val++;
        }
    }
    return val;
}

int main()
{

    int n;
    cout << "Enter the size of the array : ";
    cin >> n;

    vector<int> v(n);
    cout << "Enter " << n << " elements of the array : ";
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    // Evaluating the initial state
    int bestValue = heuristic_value(v);
    int swaps = 0;

    while (bestValue > 0)
    {
        for (int i = 0; i < n - 1; i++)
        {
            // Applying operations on the current state to generate new state
            swap(v[i], v[i + 1]);
            int curValue = heuristic_value(v);
            // if the new state is better than the current state
            if (curValue < bestValue)
            {
                cout << "After swap " << ++swaps << endl;
                for (int i : v)
                    cout << i << " ";
                cout << endl;
                bestValue = curValue;
            }
            else
            {
                // if the new state didn't give better heuristic value
                swap(v[i], v[i + 1]);
            }
        }
    }

    cout << "Final ans : " << endl;
    for (int i : v)
        cout << i << " ";

    return 0;
}
