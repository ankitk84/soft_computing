#include <bits/stdc++.h>
using namespace std;

bool comp(vector<int> &a, vector<int> &b)
{
    if (a.size() != b.size())
        return false;
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return false;
    return true;
}

class state
{

public:
    // the current state
    vector<vector<int>> table;

    state()
    {
        for (int i = 0; i < 4; i++)
        {
            vector<int> v(4, -1);
            table.push_back(v);
        }
    }

    // returns the heuristic value for the current state
    // uses the manhattan distance between the position of each tile in the current state and the final state
    int heuristic(state &final)
    {

        map<int, vector<int>> _goal;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (final.table[i][j] != -1)
                {
                    for (int k = 0; k < j; k++)
                    {
                        _goal[final.table[i][j]].push_back(final.table[i][k]);
                    }
                }
            }
        }

        int cost = 0;

        for (int i = 0; i < 4; i++)
        {
            vector<int> temp;
            for (int j = 0; j < 4; j++)
            {

                if (table[i][j] == -1)
                    break;
                if (j)
                    temp.push_back(table[i][j - 1]);

                if (temp.size() == 0 or comp(temp, _goal[table[i][j]]))
                    cost += temp.size();
                else
                    cost -= temp.size();
            }
        }

        return cost;
    }

    // returns a vector containing all the nieghbours of the current state
    vector<state> generate_neighbours()
    {

        vector<state> neighbours;

        for (int i = 0; i < 4; i++)
        {
            int val, j;
            state curr, temp;
            curr.table = table;
            for (j = 0; j < 4; j++)
            {
                if (table[i][j] == -1)
                    break;
            }
            if (j == 0)
                continue;
            val = table[i][j - 1];
            curr.table[i][j - 1] = -1;
            temp = curr;
            for (j = 0; j < 4; j++)
            {
                curr = temp;
                if (i == j)
                    continue;
                int k;
                for (k = 0; k < 4; k++)
                {
                    if (curr.table[j][k] == -1)
                        break;
                }
                curr.table[j][k] = val;
                neighbours.push_back(curr);
            }
        }
        return neighbours;
    }

    // prints the current state
    void display()
    {
        cout << endl;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << table[i][j] << " ";
            }
            cout << endl;
        }
    }
};

void steepest_ascent_hill_climb(state &initial, state &final)
{
    initial.display();
    int best = initial.heuristic(final);
    if (best == 6)
    {
        cout << "\nThe final state has been reached.\n";
        return;
    }

    vector<state> neighbours = initial.generate_neighbours();
    state next;
    next.table = initial.table;

    for (auto &neighbour : neighbours)
    {
        int curr = neighbour.heuristic(final);
        if (curr > best)
        {
            best = curr;
            next = neighbour;
        }
    }

    if (next.table == initial.table)
    {
        cout << "Stuck at a local minimum! Could not find any further path.\n";
        return;
    }

    steepest_ascent_hill_climb(next, final);
}

int main()
{

    state initial;
    state final;

    // initial.table = {{1, -1, -1, -1}, {4, 3, -1, -1}, {-1, -1, -1, -1}, {2, -1, -1, -1}};
    initial.table = {{1, 4, 3, 2}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}};
    final.table = {{4, 3, 2, 1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}};

    // vector<state> neighbours = initial.generate_neighbours();

    // for (state st : neighbours)
    // {
    //     cout << st.heuristic(final) << endl;
    //     for (int i = 0; i < 4; i++)
    //     {
    //         for (int j = 0; j < 4; j++)
    //         {
    //             cout << st.table[i][j] << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    // cout << initial.heuristic(final) << endl;

    steepest_ascent_hill_climb(initial, final);
}