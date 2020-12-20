#ifndef MANAGER_H
#define MANAGER_H
#include <utility>
#include <queue>
#include <vector>
#include <string>
#include "Process.h";
#include "Resource.h";

class Manager {
private:
	Process* currentRunning;
	Process* nullProcess;
	std::vector<Process* > PCB; //every process has an uniqueID
	std::vector<Resource* > RCB;
	std::vector<std::queue<int> > RL;
	std::string output;
	//int uniqueID;

public:
	Manager();
	~Manager();
	void init();

	std::string getOutput();
	void updateOutput(std::string);

	void create(int);	//priority
	void destroy(int); 

	void request(int, int); // resource index, number of units to be requested
	void release(int, int); // resource index, number of units to be requested

	void timeout();
	void scheduler();

	std::vector<Resource*> getRCB();
	
	void insertToRL(int);	// the ID of a process
	void removeFromRL(int);	// the ID of a process

	void addToPCB(Process*);		// the ID of a process
	void removeFromPCB(int);// the ID of a process

	//int getProcessIndex(int); // the ID of a process, return the PCB index

	void releaseAllResourceOfProcess(int); //index

	Process* getCurrentRunningProcess();
};

#endif // !MANAGER_H