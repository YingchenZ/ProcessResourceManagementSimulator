#ifndef PROCESS_H
#define PROCESS_H
#include <vector>
#include <utility>
#include "Resource.h"
#include "Exception.cpp"
//#include "Manager.h"

class Process {
private:
	bool stateReady;
	std::vector < std::pair <int, int> > resources;
	std::vector <int> children;
	int parentID;
	int id;
	int priority;

public:
	Process();
	~Process();

	void setStateTo(bool newState);
	bool getState();

	void setParent(int);
	int getParent(); //return parent's uniqueID

	void setID(int); //assign uniqueID to this process
	int getID();

	void setPriority(int);
	int getPriority();

	void insertResourcePair(int, int);
	void removeResourcePair(int, int);
	void clearResourcePair();
	//void releaseAllResource(Manager*);
	std::vector< std::pair <int, int> > getResources();

	void addChildren(int); //the corresponding process's uniqueID
	void removeChildren(int);
	std::vector <int> getChildren();

	bool containProcess(int); // the id of a process
	bool containResource(int);
};

#endif // !PROCESS_H