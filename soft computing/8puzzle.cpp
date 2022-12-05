/*////////////////////////////////////////////////////////////////////////////

    This program solves the 8-puzzle problem using the Iterative Deepening
        Search (IDS)and the A* Search in C++ Language.

    Llave, Arvy
    Lumawag, Aira
    Ermino, Alliana
    Banzuela, Romelyn
    BSCS-3A

    //////////////////////////////////////////////////////////////////////////*/

#include<iostream>
#include<string>
#include<cmath>
#include<time.h>
#define SIZE 3

using namespace std;

/*
represents a single state of a puzzle.
        -tile configuarations
        -variable for storing move (up, down, left, right)
        -variable level for storing the depth of that state fro the initial state(root)

*/
struct singlestate{
        int blankTileX; //blanktile index row
        int blankTileY; //blanktile index column
        int tiles[SIZE][SIZE];
        string chosenmove;
        int level;
        singlestate * parentState;
        singlestate * up;
        singlestate * down;
        singlestate * right;
        singlestate * left;
};

/*
used to create list of states.
for creating fringe
*/
struct listofstates{
        singlestate * state;
        listofstates * fringeNext;
};

//variable declarations and initialization for goal state
int goalState[][SIZE]={{1,2,3},{8,0,4},{7,6,5}};

//function declarations
singlestate* createInitialState(int arr[][SIZE]);
singlestate* transformArrayToState(int state[][SIZE]);

bool validatemove(singlestate* state, char direction);
bool checkGoal(singlestate* state1);
int moveSequence(singlestate* state);
int calculateHeuristic(singlestate* state);

//function declarations for 2 algorithm
void astarsearch(singlestate* initialState);
void iterativeDeepening(singlestate* initialState);

//functions for accessing & inserting into list
void insertintothelist(listofstates** list, singlestate* state);
singlestate* pickfirststate(listofstates** list);
bool notYetExpanded(listofstates* list, singlestate* state);
singlestate* pickStateWithLowestHeuristic(listofstates** list);


//////////// MAIN PROGRAM ////////////////

int main(){
        //2d array that will hold the values of the initial configuration
        int inputArray[SIZE][SIZE] = {0};

        singlestate* root = NULL;
        cout << "\n---------------------------------------\n";
    cout << "\tTHE 8 PUZZLE GAME";
    cout << "\n---------------------------------------\n";
    cout << "\nIf this is your initial state:\n\n";

        //a for loop that displays the example tile configuration
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            if(j == 0)
                cout << "\t";

            cout << goalState[i][j] << " ";
        }
        cout << "\n";
    }
        //Instructions when code is run
    cout << "\nYour input should be: 1 2 3 8 0 4 7 6 5\n";
    cout << "\nRepresent the tiles from 0 to 8.\n";
    cout << "Start inputting from left to right of each row.\n";
        cout << "Starting from the top most.";
    cout << "\n---------------------------------------\n\n";


    //getting input from the user
    cout << "Enter the Initial State: ";

    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            cin >> inputArray[i][j];

        //inputing the initial state as root node
        //and create the initial state
        root = createInitialState(inputArray);


        //Variable that will hold the value of the Running time of the A* and IDS Algorithm
        double cpuTimeUsed;

        clock_t aStarStart, aStarEnd;
        cout << "\nA* search";
        aStarStart = clock();
        astarsearch(root);
        aStarEnd = clock();
        cpuTimeUsed = ((double)(aStarEnd-aStarStart))/ CLOCKS_PER_SEC;
        cout << "Running Time: "<<cpuTimeUsed<<endl;



        clock_t idsStart, idsEnd;
        cout << "\n\n\nIterative Deepening search";
        idsStart = clock();
        iterativeDeepening(root);
        idsEnd = clock();
        cpuTimeUsed = ((double)(idsEnd-idsStart))/ CLOCKS_PER_SEC;
        cout << "Running time: "<<cpuTimeUsed<<endl;

        return 0;
}

/*
setting up and creating initial state.
*/
singlestate* createInitialState(int array2d[][SIZE])
{
        singlestate* state = new(singlestate);
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        //locating the blank tile and at the same time copying array to array in struct
                        if(array2d[i][j] == 0)
                        {
                                state->blankTileX = i;
                                state->blankTileY = j;
                        }
                        //copying array to array in singlestate struct
                        state->tiles[i][j] = array2d[i][j];
                }
        }
        state->level = 0;
        state->chosenmove = "START";
        //the root node has no parent node
        state->parentState = NULL;
        return state;
}

//copying values of 2d array to a new created state
singlestate* transformArrayToState(int array2d[][SIZE])
{
        singlestate* currentList = new(singlestate);
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        //locating the blank tile and at the same time copying array to array in struct
                        if(array2d[i][j] == 0)
                        {
                                currentList->blankTileX = i;
                                currentList->blankTileY = j;
                        }

                        //copying array to array in singlestate struct
                        currentList->tiles[i][j] = array2d[i][j];
                }
        }
        return currentList;
}
//////// A* Search Function ///////////
void astarsearch(singlestate* initialState){

        listofstates* openlist = NULL;  //Node declaration that willl store the list of open nodes
        listofstates* closelist = NULL; //Node declaration that willl store the list of close nodes
        insertintothelist(&openlist, initialState);
        int aStarExpansion = 0;

        while(openlist != NULL)
        {
                singlestate* currentState = pickStateWithLowestHeuristic(&openlist);
                insertintothelist(&closelist, currentState);
                //checks if the goal is found. if yes, display appropriate result and terminate using return keyword
                if(checkGoal(currentState))
                {
                        cout<<endl<<endl<<"Move Sequence: ";
                        int aStarDepth = moveSequence(currentState);  //the depth is the solution cost
                        cout << "\nSolution Cost: "<<aStarDepth-1<<endl;
                        cout << "Expansion: "<<aStarExpansion<<endl;
                        return;
                }
                aStarExpansion++;
                /*if the upward direction of the blanktile is a valid move,
                 create a new state applying that move and insert into the fringe
                */
                if(validatemove(currentState, 'U'))
                {

                        singlestate* currentList = transformArrayToState(currentState->tiles);
                        currentList->parentState = currentState;
                        currentList->level = currentState->level+1;
                        currentList->chosenmove = "Up";
                        currentList->tiles[currentList->blankTileX][currentList->blankTileY] = currentList->tiles[currentList->blankTileX-1][currentList->blankTileY];
                        currentList->blankTileX--;
                        currentList->tiles[currentList->blankTileX][currentList->blankTileY] = 0;

                        if(notYetExpanded(closelist, currentList))
                        {
                                insertintothelist(&openlist, currentList);
                        }
                }
                /*if the right move direction of the blanktile is a valid move,
                 create a new state applying that move and insert into the fringe
                */
                if(validatemove(currentState, 'R'))
                {

                        singlestate* currentList = transformArrayToState(currentState->tiles);
                        currentList->parentState = currentState;
                        currentList->level = currentState->level+1;
                        currentList->chosenmove = "Right";
                        currentList->tiles[currentList->blankTileX][currentList->blankTileY] = currentList->tiles[currentList->blankTileX][currentList->blankTileY+1];
                        currentList->blankTileY++;
                        currentList->tiles[currentList->blankTileX][currentList->blankTileY] = 0;

                        if(notYetExpanded(closelist, currentList))
                        {
                                insertintothelist(&openlist, currentList);
                        }
                }

                /*if the downward direction of the blanktile is a valid move,
                 create a new state applying that move and insert into the fringe
                */
                if(validatemove(currentState, 'D'))
                {

                        singlestate* currentList = transformArrayToState(currentState->tiles);
                        currentList->parentState = currentState;
                        currentList->level = currentState->level+1;
                        currentList->chosenmove = "Down";
                        currentList->tiles[currentList->blankTileX][currentList->blankTileY] = currentList->tiles[currentList->blankTileX+1][currentList->blankTileY];
                        currentList->blankTileX++;
                        currentList->tiles[currentList->blankTileX][currentList->blankTileY] = 0;

                        if(notYetExpanded(closelist, currentList))
                        {
                                insertintothelist(&openlist, currentList);
                        }
                }

                /*if the left move direction of the blanktile is a valid move,
                 create a new state applying that move and insert into the fringe
                */
                if(validatemove(currentState, 'L'))
                {

                        singlestate* currentList = transformArrayToState(currentState->tiles);
                        currentList->parentState = currentState;
                        currentList->level = currentState->level+1;
                        currentList->chosenmove = "Left";
                        currentList->tiles[currentList->blankTileX][currentList->blankTileY] = currentList->tiles[currentList->blankTileX][currentList->blankTileY-1];
                        currentList->blankTileY--;
                        currentList->tiles[currentList->blankTileX][currentList->blankTileY] = 0;

                        if(notYetExpanded(closelist, currentList))
                        {
                                insertintothelist(&openlist, currentList);
                        }
                }
        }
}
///////// IDS Function ///////////////
void iterativeDeepening(singlestate* initialState)
{
        int limit = 0;
        int idsExpansion = 0;

        while(true)
        {
                listofstates* visitedlist = NULL;
                listofstates* idsFringe = NULL;
                insertintothelist(&idsFringe, initialState);
                //when fringe is not NULL
                //perform Depth first search and explore the depth down until the level defined by the limit variable
                while(idsFringe != NULL)
                {
                        singlestate* currentState = pickfirststate(&idsFringe);
                        if(currentState->level > limit) continue;
                        insertintothelist(&visitedlist, currentState);
                        //callls for checkgoal function
                        if(checkGoal(currentState))
                        {
                                cout<<endl<<endl<<"Move Sequence: ";
                                int idsDepth = moveSequence(currentState);
                                cout << "\nSolution Cost: "<<idsDepth-1<<endl;
                                cout << "Expansion: "<<idsExpansion<<endl;
                                return;
                        }
                        //variable tracks th e expanded nodes
                        idsExpansion++;

                        /*
                        8 puzzle posible moves / directions
                        upward move
                        */
                        if(validatemove(currentState, 'U')){
                                singlestate* currentList = transformArrayToState(currentState->tiles);
                                currentList->parentState = currentState;
                                currentList->level = currentState->level+1;
                                currentList->chosenmove = "Up";
                                currentList->tiles[currentList->blankTileX][currentList->blankTileY] = currentList->tiles[currentList->blankTileX-1][currentList->blankTileY];
                                currentList->blankTileX--;
                                currentList->tiles[currentList->blankTileX][currentList->blankTileY] = 0;
                                if(notYetExpanded(visitedlist, currentList))
                                {
                                        insertintothelist(&idsFringe, currentList);
                                }
                        }
                        //right move
                        if(validatemove(currentState, 'R')){
                                singlestate* currentList = transformArrayToState(currentState->tiles);
                                currentList->parentState = currentState;
                                currentList->level = currentState->level+1;
                                currentList->chosenmove = "Right";
                                currentList->tiles[currentList->blankTileX][currentList->blankTileY] = currentList->tiles[currentList->blankTileX][currentList->blankTileY+1];
                                currentList->blankTileY++;
                                currentList->tiles[currentList->blankTileX][currentList->blankTileY] = 0;
                                if(notYetExpanded(visitedlist, currentList))
                                {
                                        insertintothelist(&idsFringe, currentList);
                                }
                        }
                        //move downward
                        if(validatemove(currentState, 'D'))
                        {
                                singlestate* currentList = transformArrayToState(currentState->tiles);
                                currentList->parentState = currentState;
                                currentList->level = currentState->level+1;
                                currentList->chosenmove = "Down";
                                currentList->tiles[currentList->blankTileX][currentList->blankTileY] = currentList->tiles[currentList->blankTileX+1][currentList->blankTileY];
                                currentList->blankTileX++;
                                currentList->tiles[currentList->blankTileX][currentList->blankTileY] = 0;
                                if(notYetExpanded(visitedlist, currentList))
                                {
                                        insertintothelist(&idsFringe, currentList);
                                }
                        }
                        //move left
                        if(validatemove(currentState, 'L'))
                        {
                                singlestate* currentList = transformArrayToState(currentState->tiles);
                                currentList->parentState = currentState;
                                currentList->level = currentState->level+1;
                                currentList->chosenmove = "Left";
                                currentList->tiles[currentList->blankTileX][currentList->blankTileY] = currentList->tiles[currentList->blankTileX][currentList->blankTileY-1];
                                currentList->blankTileY--;
                                currentList->tiles[currentList->blankTileX][currentList->blankTileY] = 0;
                                if(notYetExpanded(visitedlist, currentList))
                                {
                                        insertintothelist(&idsFringe, currentList);
                                }
                        }
                }
                limit++;        //increase depth limit
        }
}

//Function that insert nodes into the list
void insertintothelist(listofstates** list, singlestate* state)
{
        listofstates* currentList = new(listofstates);
        currentList->state = state;
        currentList->fringeNext = NULL;
        if(*list != NULL)
        {
                currentList->fringeNext = *list;
        }
        *list = currentList;
}
//picks the state with lower heuristic out of the openlist
singlestate* pickStateWithLowestHeuristic(listofstates** list)
{

        //temporary pointer used to travel the list
        listofstates* traversal = *list;
        //used to hold the previous node to reconnect 2 sides of deleted node incase the bestNode is found at the middle
        listofstates* previousNode;
        //holds the currentBest node
        listofstates* currentBestNode;
        //will hold the finalbest node/state
        singlestate* bestNode = NULL;

        //case1: if the list has only one node, return that node
        if((*list)->fringeNext == NULL)
        {
                bestNode = (*list)->state;
                //after getting the node, deletes from the list
                delete *list;
                *list = NULL;
                return bestNode;
        }
        //sets the first item's heuristic value as the current lowest
        int currentMin = calculateHeuristic(traversal->state);
        //sets the first item in the list as the current best state
        currentBestNode = traversal;
        //while the list is not yet in the end
        while(traversal->fringeNext != NULL)
        {
                //continue comparing in which will be the bestState with the lowest heuristic value
                int heuristic = calculateHeuristic(traversal->fringeNext->state);
                //if found something better than the currentMin
                if(heuristic < currentMin)
                {
                    //sets that new state as the current state
                        previousNode = traversal;
                        currentBestNode = traversal->fringeNext;
                        currentMin = heuristic;
                }
                //increment into the list
                traversal = traversal->fringeNext;
        }
        bestNode = currentBestNode->state;
        //properly deleting the chosen state
        if(*list != NULL)
        {
                if(currentBestNode == *list)
                {
                        return pickfirststate(list);
                }else if(currentBestNode->fringeNext == NULL)
                {
                        //delete the last state by setting the previousNode state to NULL
                        previousNode->fringeNext = NULL;
                }else
                {
                        previousNode->fringeNext = currentBestNode->fringeNext;
                }
        }
        delete currentBestNode;
        return bestNode;
}

bool checkGoal(singlestate* state1)
{
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        if(state1->tiles[i][j] != goalState[i][j])
                                return false;
                }
        }
        return true;
}
//prints the path took from the initial to the goal state
int moveSequence(singlestate* state)
{
        if(state != NULL)
        {
                int i;
                i = moveSequence(state->parentState) + 1;
                cout << " "<<state->chosenmove<<" >";
                return i;
        }else{
                return 0;
        }
}

//checks if a move in certain direction is valid, will return true 
bool validatemove(singlestate* state, char direction)
{
        //valid if the column of the blank tile is greater than 0 or not on the leftmost part of the puzzle
        if(direction == 'U'){
                if(state->blankTileX>0)
                        return true;
        }
        else if(direction == 'R'){
                if(state->blankTileY<SIZE-1)
                        return true;
        }
        else if(direction == 'D'){
                if(state->blankTileX<SIZE-1)
                        return true;
        }
        else if(direction == 'L'){
                if(state->blankTileY>0)
                        return true;
        }
        return false;
}

// O(n^4) 4 for loops
int calculateHeuristic(singlestate* state)
{
        //will hold the total manhattan distance
        int dist = 0;
        int goalTileX;
        int goalTileY;

		//loops through all the tiles of the goal state
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                		//if the position of the tile is equal to the position of that tile in goal state, the we don't need to do anything
                		//because in computing manhattan distance, we will just need to sum all the difference in distance to their respective position in goalstate
						//so if the that tile is already in the right position, the distance is 0.
                        if(state->tiles[i][j] == goalState[i][j])
                                continue;
                        else
                        {		//flag for determining if the the distance variable is already assigned with value greater than 0
                                //-1 means that the distance is not yet computed
								int distance = -1;
								//loops throught all the tiles of the state we are comparing with the goalstate
                                for(int y=0; y<SIZE; y++)
                                {
                                        for(int x=0; x<SIZE; x++)
                                        {		//if the value of state's tile and goalstate's tile are equal, the find their distance
                                                if(state->tiles[y][x] == goalState[i][j]){
                                                        if(distance == -1)
                                                        {
                                                        	//distance is difference in their column and plus difference in rows
                                                                distance = abs(i-y) + abs(j-x);
                                                        }
                                                }
                                        }
                                }
                                //summation of distances
                                dist += distance;
                        }
                }
        }
        //return the heuristic value
        return dist + state->level;
}

//return the first node in the list
singlestate* pickfirststate(listofstates** list)
{
        singlestate* currentList = NULL;
        if(*list != NULL)
        {
                currentList = (*list)->state;
                listofstates* temp = *list;
                *list = (*list)->fringeNext;
                delete temp;
        }
        return currentList;
}


//checks if the node is not yet expanded
bool notYetExpanded(listofstates* list, singlestate* state)
{
        listofstates* traversal = list;
        while(traversal != NULL)
        {
                int flag = 1;
                for (int i = 0; i < SIZE; i++)
                {
                        for (int j = 0; j < SIZE; j++)
                        {
                                if(state->tiles[i][j] != traversal->state->tiles[i][j])
                                {
                                        flag = 0;
                                }
                        }
                }
                if(flag)
                {
                        return false;
                }
                traversal = traversal->fringeNext;
        }
        return true;
}
