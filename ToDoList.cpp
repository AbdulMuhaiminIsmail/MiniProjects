#include <iostream>
#include <vector>

using namespace std;

int main() {
	bool isrun=true;
	string task;
	int choice, index;
	vector<string> tasks;
	cout<<"Menu:\n";
	cout<<"1)Add Task\n";
	cout<<"2)Remove Task\n";
	cout<<"3)Display Tasks\n";
	cout<<"4)Exit\n";
	cout<<"Please enter the number of option to proceed: ";
	cin>>choice;
	while (isrun==true)
	{
		if(choice==1){
		cout<<"What task would you like to add? ";
		cin>>task;
		tasks.push_back(task);
		cout<<"List Updated!";}
	else if(choice==2){
		cout<<"Which task would you like to remove? ";
		cin>>index;
		bool indexinrange=(index>=0 && index<tasks.size()); //checks if index is valid
		if(indexinrange==true)
			{tasks.erase(tasks.begin()+index); //statement to remove any member of vector
			cout<<"Task removed!";}
	    if(indexinrange==false)
			cout<<"Invalid index.";}
	else if(choice==3){
		cout<<"Here are the tasks in the list right now:";
		for(int k=0; k<tasks.size(); k++){ //tasks.size() returns number of elements in vector
			cout<<k+")"+tasks[k];}
	}		
	else if(choice==4)
		cout<<"Exited Successfully!";
		isrun=false;
	}
	return 0;
}

