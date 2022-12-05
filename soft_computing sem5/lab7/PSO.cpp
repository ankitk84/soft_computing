// Maximization Problem for the function : -(x * x) + 5 * x + 20

#include <bits/stdc++.h>
using namespace std;

int gene, numberOfParticles;
double W, C1, C2, gbest, fgbest;
double upprbound, lbound;

struct swarme
{
    double position;
    double velocty;
    double pbest;
    double fbest;
};

struct swarme *population;

double ranmd(double l, double u)
{
    double r = ((double)rand() / (RAND_MAX));
    return (u - l) * r + l;
}

double ranmd()
{
    return ((double)rand() / (RAND_MAX));
}

double func(double x)
{
    return -(x * x) + 5.0 * x + 20.0;
}

void initialize()
{
    population = new struct swarme[numberOfParticles];
    cout << "Enter lower and upper bound for the variable: ";
    cin >> lbound >> upprbound;
    for (int i = 0; i < numberOfParticles; i++)
    {
        cout << "Enter initial position of " << i + 1 << "th particle: ";
        cin >> population[i].position;
        population[i].velocty = 0;
        population[i].pbest = population[i].position;
        population[i].fbest = func(population[i].pbest);
        if (gbest < population[i].pbest)
        {
            gbest = population[i].pbest;
        }
    }
}

void update()
{
    double R1 = ranmd();
    double R2 = ranmd();
    for (int i = 0; i < numberOfParticles; i++)
    {
        population[i].velocty = W * population[i].velocty + C1 * R1 * (population[i].pbest - population[i].position) + C2 * R2 * (gbest - population[i].position);
        if ((population[i].position + population[i].velocty) <= upprbound && (population[i].position + population[i].velocty) >= lbound)
        {
            population[i].position = population[i].position + population[i].velocty;
        }
    }
}

void evaluate()
{
    for (int i = 0; i < numberOfParticles; i++)
    {
        if (population[i].fbest < func(population[i].position))
        {
            population[i].pbest = population[i].position;
            population[i].fbest = func(population[i].position);
        }
        if (fgbest < func(population[i].position))
        {
            gbest = population[i].position;
            fgbest = func(population[i].position);
        }
    }
}

void report()
{
    cout << "Final position and velocity of the particles is:\n\n";
    cout << "S.no\t\tposition\t\tvelocity\t\tP.Best\t\tF.Best\n";
    for (int i = 0; i < numberOfParticles; i++)
    {
        printf(" %d\t\t  %.2f  \t\t  %.2f  \t\t %.2f \t\t %.2f \n", i + 1, population[i].position, population[i].velocty, population[i].pbest, population[i].fbest);
    }
    cout << endl;
    cout << "Global Best Value is:" << endl;
    cout << "x = " << fixed << setprecision(2) << gbest << endl;
    cout << "f(" << gbest << ") = " << fgbest << endl;
}

int main()
{
    cout << "Enter No of geneerations: ";
    cin >> gene;
    cout << "Enter Maximum No of Particles: ";
    cin >> numberOfParticles;
    cout << "Enter value of Inertia Factor: ";
    cin >> W;
    cout << "Enter value of C1: ";
    cin >> C1;
    cout << "Enter value of C2: ";
    cin >> C2;
    srand(time(NULL));
    initialize();
    for (int i = 0; i < gene; i++)
    {
        update();
        evaluate();
    }
    report();
    return 0;
}

/*
Input:

5
9
0.9
1.5
1.5
-10 10
-9.6
-6
-2.6
-1.1
0.6
2.3
2.8
8.3
10


*/