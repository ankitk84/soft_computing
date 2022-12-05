#include<bits/stdc++.h>

using namespace std;

int main(){

	int individuals;
	cout<<"enter the number of individuals";
	cin>>individuals;
	int fit[individuals];
	cout<<"enter fitness values";
	
	for(int i=0;i<individuals;i++){
		cin>>fit[i];
	}
	float sum = 0;
	for (int i = 0; i < individuals; i++) {
		sum += fit[i];
	}
	cout<<sum<<endl;
	int count[individuals] ={0};

	// float accum =0.0;
	// for (int i = 0; i < individuals; i++) {
	// 	accum += (fit[i]/sum);
	// }


	 for (int i = 0; i < 10000; i++) {
		//generate random float number between 0 and initial sum
		float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / sum));

		//sum up all individuals' fitness
		float newSum = 0;
		for (int j = 0; j < individuals; j++) {
			newSum += fit[j];
			//stop when the new sum is higher than the random number
			if (newSum > r){
				count[j]++;		//increase count for the chosen individual
				break;
			}
		}
		
	}

	for (int i = 0; i < individuals;i++) {
		cout << i+1 << " was chosen " << count[i] << " times." << endl;
			}
	return 0;

}

