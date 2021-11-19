#include<iostream>
#include<fstream>
using namespace std;

int main(){
	ifstream in;
	in.open("output.txt");
	int x,count1=0,count2=0;
	while(!in.eof()){
		in>>x;
		if(x%3==0){
			count1++;
		}
		if(x%4==0){
			count2++;
		}
	}
	cout<<count1<<endl<<count2<<endl;
	return 0;
}
