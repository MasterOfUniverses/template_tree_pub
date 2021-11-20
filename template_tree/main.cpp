#include"TreeSet.h"

using namespace std;

int main(){
	try{
	MyTree<int> int_tree;
	for(int i=0;i<1536;i++){
		int_tree.insert(i);
	}
	
	int i=-1;
	int_tree.erase(i);
	for(int i=0;i<3072;i++){
		
		int_tree.insert(i);
		
	}
	for(int i=int_tree.size()-1;i>-1;i--){
		if(i%3==0){
			int_tree.erase(i);
		}
	}
	for(int i=3071;i>-1;i--){
		if((i%4==0)){
			int_tree.erase(i);
		}
	}
	ofstream out;
	out.open("output.txt");
	
	out<<int_tree;
	return 0;
	}catch(MyException x){
	cout<<x<<endl;
	}
}
