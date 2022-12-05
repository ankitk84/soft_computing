//
//  main.cpp
//  RouletteWheel

#include <iostream>
#include <ctime>
#include<cstdlib>
using namespace std;

// define the struct for data
struct data{
	int location;
	int frequency;
};

// define forward declarations below
int random_number();
void fillMeUp(data arr[]);
void spinMeRound(data arr[], int spins, int offset);
void displayResults(data arr[], int spins);
void testingRoulette();
void theGambler();

int main() {
	// launch part 1
	testingRoulette();
	// launch part 2
	theGambler();
	// stop the program and wait
	cout << "Please press enter to continue..." << endl;
	getchar();

	return 0;
}

void testingRoulette(){
	// declare array of data points
	data spin36[5], spin360[5], spin3600[5], spin36000[5];
	// fill the arrays with default values
	fillMeUp(spin36);
	fillMeUp(spin360);
	fillMeUp(spin3600);
	fillMeUp(spin36000);
	// spin the roulette wheel
	spinMeRound(spin36, 36, 1);
	spinMeRound(spin360, 360, 7);
	spinMeRound(spin3600, 3600, 2);
	spinMeRound(spin36000, 36000, 3);
//	// output the results
	displayResults(spin36, 36);
	displayResults(spin360, 360);
	displayResults(spin3600, 3600);
	displayResults(spin36000, 36000);
}

void theGambler(){
	int tempspin = 0, bet = 0, bankroll = 1000;
	for (int i = 0; i < 1000; i++){
		tempspin = random_number();
		bet = random_number();
		if (tempspin == bet)
			bankroll += 34;
		else
			bankroll += -1;
			
	}
	cout << "End Bankroll = " << bankroll << endl;
	int a_tempspin = 0, a_bet = 0, total = 0, average = 0;
	for (int n = 0; n < 1000; n++){
		int a_bankroll = 1000;
		for (int i = 0; i < 1000; i++){
			a_tempspin = random_number();
			a_bet = random_number();
			if (a_tempspin == bet)
				a_bankroll += 34;
			else
				a_bankroll += -1;
			
		}
		total += a_bankroll;
	}
	average = total/1000;
	cout << "The average end Bankroll = " << average << endl;
}

int random_number(){
	// returns a random number between 0 and 34
	// only need up to 34 as data.location at 0 is 1
	return rand() % 35;
}

void fillMeUp(data arr[]){
	for (int i = 0; i < 35; i++){
		arr[i].frequency = 0;
		arr[i].location = (i + 1);
	}
}

void spinMeRound(data arr[], int spins, int offset){
	// set up a random seed
	srand(time(NULL)*offset);
	// spin
	for (int i = 0; i < spins; i++){
		int tmp = random_number();
		arr[tmp].frequency++;
	}
}

void displayResults(data arr[], int spins){
	// break a line
	cout << endl;
	// display the results
	for (int i = 0; i < 35; i++){
		cout << arr[i].location << " appeared " << arr[i].frequency << " times in the " << spins << " spin trial" << endl;
	}
}
