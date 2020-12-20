#ifndef RESOURCE_H
#define RESOURCE_H
#include <iostream>
#include "Process.h"
//#include "Manager.h"

class Resource {
private:
	int state, maxUnit;
	std::vector < std::pair <int, int> > waitlist;

public:
	Resource(int);
	~Resource();

	void insertProcessPair(int i, int k);//process's id and requested units
	void removeProcessPair(int i, int k);//process's id and requested units
	std::pair <int, int> getNext();//process's id and requested units
	std::vector < std::pair <int, int> > getWaitlist(); //process's id and requested units

	void allocate(int k); //requestd units
	void free(int k); // released units
	int getFreeUnit();
	int getMaxUnit();
};

#endif // !RESOURCE_H