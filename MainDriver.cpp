// Emily Gorman
// Project 2: Tracking Trees
// 12/15/2018
// MainDriver.cpp

#include <iostream> 
#include <string>
#include "Tree.h"
using namespace std;
void
getRequest(string & request)
{
	cout << "Enter request: ";
	cin >> request;
}
int main()
{
	Tree TheTree;
	string request;
	string ID;
	cout << "Available commands: display, build, search, update, quit" << endl;
	getRequest(request);
	while (request != "quit")
	{
		if (request == "build")
		{
			TheTree.build();
		}
		else if (request == "display")
		{
			TheTree.display(cout);
		}
		else if (request == "search")
		{
			cout << "Enter the ID of the node you wish to search for: ";
			cin >> ID;
			TheTree.search(ID);
		}
		else if (request == "update")
		{
			cout << "Enter the ID of the node you wish to update: ";
			cin >> ID;
			TheTree.update(ID);
		}
		else
		{
			cout << "Available commands: display, build, search, update, quit" << endl;
		}
		getRequest(request);
	}
	return 0;
}