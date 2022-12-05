#include <bits/stdc++.h>
using namespace std;

float my_random_fun(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

int main()
{
    int x1, x2, CS, L, D, employee_bees, on_the_bees, food_source;
    float a, b;
    cout << "Enter the range for variable x1 and x2" << endl;
    cin >> a >> b;
    cout << "Enter the colony size(CS)" << endl;
    cin >> CS;
    cout << "Enter the limit for scout(L)" << endl;
    cin >> L;
    cout << "Enter the dimension of the probablem(D)" << endl;
    cin >> D;

    employee_bees = on_the_bees = CS / 2;
    int count[employee_bees] = {0};
    food_source = employee_bees;
    float pos_food[food_source][2] = {0.0};

    for (int i = 0; i < food_source; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            pos_food[i][j] = my_random_fun(a, b);
        }
    }

    cout << "Positions of food source are :" << endl;
    for (int i = 0; i < food_source; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << pos_food[i][j] << "  ";
        }
        cout << endl;
    }

    cout << "Values of function F(x) are: " << endl;
    float F[food_source], fit[food_source];
    for (int i = 0; i < food_source; i++)
    {
        float x = pos_food[i][0];
        float y = pos_food[i][1];
        F[i] = pow(x, 2) + pow(y, 2);
        cout << F[i] << endl;
    }

    float max_fitnss = 0;

    cout << "Initial Fitness values are: " << endl;
    for (int i = 0; i < food_source; i++)
    {
        if (F[i] >= 0)
        {
            fit[i] = (1 / (1 + F[i]));
        }
        if (F[i] < 0)
        {
            fit[i] = 1 - F[i];
        }

        if (fit[i] > max_fitnss)
            max_fitnss = fit[i];

        cout << fit[i] << endl;
    }

    cout << "Maximum fitness value is: " << max_fitnss << endl;

    int flag1in = 0;
    do
    {
        // Employed Bee Phase
        for (int i = 0; i < employee_bees; i++)
        {
            cout << "(" << i + 1 << ")"
                 << " Employed bee:" << endl;
            float phila = my_random_fun(-1.0, 1.0);
            int k = (rand() > RAND_MAX / 2) ? 0 : 1;
            cout << "phila : " << phila << endl;
            cout << "k : " << k << endl;
            float m[2];
            for (int j = 0; j < 2; j++)
            {
                m[j] = pos_food[i][j] + (phila * (pos_food[i][j] - pos_food[k][j]));
                if (m[j] > pos_food[i][j])
                {
                    cout << endl
                         << "Value changed" << endl;
                }
                else
                {
                    m[j] = pos_food[i][j];
                }
                cout << m[j] << endl;
            }

            float new_Fx, new_fit;

            float x = m[0];
            float y = m[1];
            new_Fx = pow(x, 2) + pow(y, 2);
            cout << "New F(x) is: " << new_Fx << endl;
            if (new_Fx >= 0)
            {
                new_fit = (1 / (1 + new_Fx));
            }
            if (new_Fx < 0)
            {
                new_fit = 1 - new_Fx;
            }
            cout << "New fitness is: " << new_fit << endl;

            if (new_fit > F[i])
            {
                cout << "New fitness is greater than previous fitness so vector changes" << endl;
                fit[i] = new_fit;
                F[i] = new_Fx;
                pos_food[i][0] = m[0];
                pos_food[i][1] = m[1];
                count[i] = 0;
            }
            else
            {
                cout << "New fitness is not more than previous fitness so require more trials" << endl;
                count[i]++;
            }

            cout << endl;
        }

        cout << "New Positions of food source are :" << endl;
        for (int i = 0; i < food_source; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << pos_food[i][j] << "  ";
            }
            cout << endl;
        }

        for (int i = 0; i < employee_bees; i++)
            cout << count[i];

        float probab[employee_bees];
        float sum = 0;
        for (int i = 0; i < employee_bees; i++)
            sum += fit[i];

        for (int i = 0; i < employee_bees; i++)
        {
            probab[i] = (fit[i] / sum);
        }

        cout << "probabability are: " << endl;
        for (int i = 0; i < employee_bees; i++)
            cout << probab[i] << endl;

        // Onlooker Bees Phase
        for (int i = 0; i < on_the_bees; i++)
        {
            cout << "(" << i + 1 << ")"
                 << " Onlooker Bee:" << endl;
            double rndNumber = rand() / (double)RAND_MAX;
            double offset = 0.0;
            int ii = 0;

            for (int r = 0; r < on_the_bees; r++)
            {
                offset += probab[r];
                if (rndNumber < offset)
                {
                    ii = r;
                    break;
                }
            }

            int j = (rand() > RAND_MAX / 2) ? 0 : 1;
            int k = (rand() > RAND_MAX / 3) ? 0 : 1;
            float phila = my_random_fun(-1.0, 1.0);
            cout << "ii : " << ii << endl;
            cout << "j : " << j << endl;
            cout << "phila : " << phila << endl;
            cout << "k : " << k << endl;

            float m = pos_food[ii][j] + (phila * (pos_food[ii][j] - pos_food[k][j]));
            float temp = pos_food[ii][j];
            cout << m << endl;
            if (m > pos_food[ii][j])
            {
                cout << endl
                     << "Value changed" << endl;
                pos_food[ii][j] = m;
            }

            float new_Fx, new_fit;

            float x = pos_food[ii][0];
            float y = pos_food[ii][1];
            new_Fx = pow(x, 2) + pow(y, 2);
            cout << "New F(x) is: " << new_Fx << endl;
            if (new_Fx >= 0)
            {
                new_fit = (1 / (1 + new_Fx));
            }
            if (new_Fx < 0)
            {
                new_fit = 1 - new_Fx;
            }
            cout << "New fitness is: " << new_fit << endl;

            if (new_fit > F[ii])
            {
                cout << "New fitness is greater than previous fitness so vector changes" << endl;
                F[ii] = new_Fx;
                fit[ii] = new_fit;
                count[ii] = 0;
            }
            else
            {
                cout << "New fitness is not more than previous fitness so require more trials" << endl;
                count[ii]++;
                pos_food[ii][j] = temp;
            }

            cout << endl;
        }
        cout << "Final Values of function F(x) are: " << endl;
        for (int i = 0; i < food_source; i++)
            cout << F[i] << endl;

        float maxi_fit = 0;
        int max;

        cout << "Final Fitness values are: " << endl;
        for (int i = 0; i < food_source; i++)
        {
            if (fit[i] > maxi_fit)
            {
                maxi_fit = fit[i];
                max = i;
            }

            cout << fit[i] << endl;
        }

        // Memorize Best
        cout << "Best solution is: " << endl;
        cout << pos_food[max][0] << "  " << pos_food[max][1] << endl;

        // Scout Bees Phase
        cout << "Trial Counter vector is: " << endl;
        for (int i = 0; i < employee_bees; i++)
            cout << count[i] << endl;

        int abd_sol;
        for (int i = 0; i < employee_bees; i++)
        {
            if (count[i] > L)
            {
                abd_sol = i;
                flag1in = 1;
            }
        }

        if (flag1in == 1)
        {
            cout << "Repeat the process as the limit of the probablem (L) is exceeded by :" << abd_sol << endl;
        }

    } while (flag1in == 1);

    cout << "Reached the end of the program";

    return 0;
}