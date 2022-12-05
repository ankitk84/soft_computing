#include<bits/stdc++.h>
#include<queue>
using namespace std;
//
//void q(int n){
//	queue<int>que;
//	for(int i=1;i<=n;i++){
//		que.push(i);
//	}
//	while(!que.empty()){
//		cout<<que.front()<<" ";
//		que.pop();
//	}
//	cout<<"\n";
//}

void deq(){
	deque<int>d;
	d.push_front(1);
	d.push_back(2);
	d.push_front(4);
	d.push_back(3);
	d.push_front(6);
	d.push_back(5);
	d.push_front(8);
	deque<int>::iterator it;
    for (it = d.begin(); it != d.end(); ++it){
        cout << *it<<" ";
	}
	cout<<endl;
	d.pop_front();
	d.pop_back();
	d.pop_front();
	d.pop_back();
	for (it = d.begin(); it != d.end(); ++it){
        cout << *it<<" ";
	}
	cout<<endl;
}

int main(){
	int n;
	cin>>n;
	clock_t start, end;
    start = clock(); 
	deq();
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5);
    cout << " sec " << endl;
	
}
