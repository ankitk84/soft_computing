// Maximization Problem for the function : -(x * x) + 5 * x + 20

#include <bits/stdc++.h>

typedef struct Chrom
{
    short int bit[6]; // ith bit represent the ith gene of that chromosome
    int fit;
} chrom;

void *evpop(chrom popcurrent[4]); // defining the functions that we will use
int x(chrom popcurrent);
int y(int x);
void *pickchroms(chrom popcurrent[4]);
void *crossover(chrom popnext[4]);
void *mutation(chrom popnext[4]);

int main() // the main function
{

    srand(time(0));

    int num; // num is the no. of iterations
    int i, j;

enter:
    printf("\nPlease enter the no. of iterations:  ");
    scanf("%d", &num); // enter the no. of iterations in num

    chrom popcurrent[4]; // we make 4 chromes of popcurrent
    chrom popnext[4];    // we make 4 chromes of popnext

    if (num < 1) // if a -ve number is inserted .. enter num again
        goto enter;

    evpop(popcurrent); // initialise pop current

    for (i = 0; i < num; i++) // loop num times
    {

        printf("\ni = %d\n", i); // print the iteration number

        for (j = 0; j < 4; j++)
            popnext[j] = popcurrent[j]; // copy popcurrent to popnext in order to adjust it

        pickchroms(popnext); // pick best chromes
        crossover(popnext);  // cross over to get children chromes
        mutation(popnext);   // mutate with a low probability

        for (j = 0; j < 4; j++)
            popcurrent[j] = popnext[j]; // copy the chromes of popnext to popcurrent

    } // loop back until no. of iterations is exceeded

    return 0;
}

void *evpop(chrom popcurrent[4]) // takes a pointer to a chrom of 4 elements
{
    int i, j, value;
    int random;
    for (j = 0; j < 4; j++) // loop of j to choose chromes from [0] to [3]
    {
        for (i = 0; i < 6; i++) // loop of i to choose the gene of the chrom from  [0] to [5]

        {
            random = rand();               // creating random value
            random = (random % 2);         // make the random value o or 1 only
            popcurrent[j].bit[i] = random; // initialising the bit[i] of chrom[j] with random
        }

        value = x(popcurrent[j]);                // get the value of the chrom as integer
        popcurrent[j].fit = y(x(popcurrent[j])); // calcualte the fitness of chrom[j]
        printf("\n popcurrent[%d]=%d%d%d%d%d%d    value=%d    fitness = %d", j,
               popcurrent[j].bit[5], popcurrent[j].bit[4], popcurrent[j].bit[3], popcurrent[j].bit[2],
               popcurrent[j].bit[1], popcurrent[j].bit[0], value, popcurrent[j].fit);
    }

    return (0);
}

// chromosome is associated with an integer value
int x(chrom popcurrent)
{
    int z;
    z = (popcurrent.bit[0] * 1) + (popcurrent.bit[1] * 2) + (popcurrent.bit[2] * 4) + (popcurrent.bit[3] * 8) + (popcurrent.bit[4] * 16);
    if (popcurrent.bit[5] == 1)
        z = z * (-1);
    return (z);
}

// calculating the fitness of integer x
int y(int x)
{
    int y;
    y = -(x * x) + 5 * x + 20;
    return (y);
}

void *pickchroms(chrom popcurrent[4])
{

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (popcurrent[j + 1].fit > popcurrent[j].fit)
            {
                chrom temp = popcurrent[j + 1];
                popcurrent[j + 1] = popcurrent[j];
                popcurrent[j] = temp;
            }
        }

    for (int i = 0; i < 4; i++)
        printf("\nSorting : popnext[%d] fitness=%d", i, popcurrent[i].fit); // printing the result
    printf("\n");                                                           // print new line

    return (0);
}

void *crossover(chrom popnext[4])
{
    int random;
    int i;
    random = rand();
    random = ((random % 5) + 1);
    for (i = 0; i < random; i++)
    {
        popnext[2].bit[i] = popnext[0].bit[i];
        popnext[3].bit[i] = popnext[1].bit[i];
    }

    for (i = random; i < 6; i++) // crossing the bits beyond the cross point index
    {
        popnext[2].bit[i] = popnext[1].bit[i]; // child 1 cross over
        popnext[3].bit[i] = popnext[0].bit[i]; // chlid 2 cross over
    }                                          // end of for

    for (i = 0; i < 4; i++)
        popnext[i].fit = y(x(popnext[i])); // calculating the fitness values for the new set

    for (i = 0; i < 4; i++)
        printf("\nCrossOver popnext[%d]=%d%d%d%d%d%d    value=%d    fitness = %d", i,
               popnext[i].bit[5], popnext[i].bit[4], popnext[i].bit[3], popnext[i].bit[2],
               popnext[i].bit[1], popnext[i].bit[0], x(popnext[i]), popnext[i].fit);

    return (0);
}

void *mutation(chrom popnext[4])
{

    int random;
    int row, col, value;
    random = rand() % 50;

    if (random == 25)
    {
        col = rand() % 6;
        row = rand() % 4;

        if (popnext[row].bit[col] == 0) // invert the bit to 1 if it was 0
            popnext[row].bit[col] = 1;

        else if (popnext[row].bit[col] == 1) // invert the bit to 0 if it was 1
            popnext[row].bit[col] = 0;

        popnext[row].fit = y(x(popnext[row])); // calculate the fitness for the mutated chrome
        value = x(popnext[row]);
        printf("\nMutation occured in popnext[%d] bit[%d]:=%d%d%d%d%d%d    value=%d   fitness=%d",
               row, col, popnext[row].bit[5], popnext[row].bit[4], popnext[row].bit[3], popnext[row].bit[2],
               popnext[row].bit[1], popnext[row].bit[0], value, popnext[row].fit);
    }

    return (0);
}