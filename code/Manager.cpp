#include "Manager.h"

Manager::Manager() {
	nullProcess = new Process();
	nullProcess->setID(-999);
	this->output = "";
}

Manager::~Manager(){
	delete nullProcess;
	this->output.clear();
}

void Manager::init() {
	this->PCB = std::vector<Process*>(16, this->nullProcess);
	this->RCB = {};
	this->RL = {};

	Process* newProcess = new Process();
	newProcess->setID(0);
	newProcess->setStateTo(true);
	newProcess->setPriority(0);
	this->PCB[0] = newProcess;
	//this->PCB.push_back(newProcess);

	for (int i = 0; i < 3; i++) {
		this->RL.push_back(std::queue <int>{});
	}
	this->RL[0].push(newProcess->getID());

	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			this->RCB.push_back(new Resource(1));
		}
		else {
			this->RCB.push_back(new Resource(i));
		}
	}
	this->currentRunning = newProcess;
	this->scheduler();
	return;
}

std::string Manager::getOutput() {
	return this->output;
}
void Manager::updateOutput(std::string incoming) {
	this->output += incoming;
}

void Manager::scheduler() {
	for (int i = 2; i >= 0; i--) {
		if (!this->RL[i].empty()) {
			//std::cout << "RL " << i << " not empty";
			int currentRunningID = this->RL[i].front();
			//int currentRunningIndex = this->getProcessIndex(currentRunningID);
			//this->currentRunning = this->PCB[currentRunningIndex];
			this->currentRunning = this->PCB[currentRunningID];
			//std::cout << " " << currentRunningID << std::endl;
			this->output += std::to_string(this->currentRunning->getID());
			this->output += " ";
			break;
		}
	}
	return;
}
void Manager::timeout() {
	for (int i = 2; i >= 0; i--) {
		if (!this->RL[i].empty()) {
			int frontID= this->RL[i].front();
			//std::cout << frontID << " ";
			this->RL[i].pop();
			this->RL[i].push(frontID);
			break;
		}
		//std::cout << std::endl;
	}
	this->scheduler();
	return;
}


void Manager::create(int priority) {
	if (priority == 0)
		throw Invalid();
	Process* newProcess = new Process();
	newProcess->setPriority(priority);
	newProcess->setStateTo(true);
	newProcess->setParent(this->currentRunning->getID());
	this->addToPCB(newProcess);
	this->currentRunning->addChildren(newProcess->getID());
	this->insertToRL(newProcess->getID());
	this->scheduler();
	return;
}
void Manager::destroy(int index) {
	if (PCB[index] != this->nullProcess) {
		if (this->currentRunning->containProcess(this->PCB[index]->getID()) or this->currentRunning->getID() == index) {
			std::queue <int> descendants = {};
			descendants.push(this->PCB[index]->getID());
			while (!descendants.empty()) {
				int frontID = descendants.front();
				//int index = this->getProcessIndex(frontID);
				if (frontID != -999) {
					for (int i = 0; i < this->PCB[frontID]->getChildren().size(); i++) {
						descendants.push(this->PCB[frontID]->getChildren()[i]);
					}
					int parentID = this->PCB[frontID]->getParent();
					//this->currentRunning->removeChildren(this->PCB[frontID]->getID());
					this->PCB[parentID]->removeChildren(this->PCB[frontID]->getID());
					//this->removeFromPCB(this->PCB[index]->getID());
					this->removeFromRL(this->PCB[frontID]->getID());
					this->releaseAllResourceOfProcess(frontID);
					this->removeFromPCB(frontID);
				}
				else
					break;
				descendants.pop();
			}
		}
		else
			throw Invalid();
	}
	else
		throw Invalid();//=================================================
	
	this->scheduler();
	return;
}


void Manager::request(int r, int k) {
	if (r < 0 or r > 3) {
		throw Invalid();
	}
	if (this->currentRunning->getID() == 0 and this->RL[2].empty() and this->RL[1].empty()) {
		throw Invalid();
	}
	if (this->RCB[r]->getMaxUnit() < k)
		throw Invalid();

	if (this->RCB[r]->getFreeUnit() >= k) {
		this->RCB[r]->allocate(k);
		this->currentRunning->insertResourcePair(r, k);
	}
	else {
		this->currentRunning->setStateTo(false);
		this->removeFromRL(this->currentRunning->getID());
		this->RCB[r]->insertProcessPair(this->currentRunning->getID(), k);
		for (int i = 0; i < this->currentRunning->getResources().size(); i++) {
			if (this->currentRunning->getResources()[i].first == r and this->currentRunning->getResources()[i].second + k > this->RCB[r]->getMaxUnit())
				throw Invalid();
		}
	}
	this->scheduler();
}
void Manager::release(int r, int k) { 
	this->currentRunning->removeResourcePair(r, k);
	this->RCB[r]->free(k);

	while ( !this->RCB[r]->getWaitlist().empty() and this->RCB[r]->getFreeUnit() > 0) {
		std::pair <int, int> nextPair = this->RCB[r]->getNext();
		if (this->RCB[r]->getFreeUnit() >= nextPair.second) {
			this->RCB[r]->allocate(nextPair.second);
			//int indexOfJ = this->getProcessIndex(nextPair.first);
			int indexOfJ = nextPair.first;
			this->PCB[indexOfJ]->insertResourcePair(r, nextPair.second);
			this->PCB[indexOfJ]->setStateTo(true);
			this->RCB[r]->removeProcessPair(nextPair.first, nextPair.second);
			this->insertToRL(nextPair.first);
		}
		else {
			break;
		}
	}
	this->scheduler();
	return;
}


std::vector<Resource*> Manager::getRCB() {
	return this->RCB;
}


void Manager::insertToRL(int id) {
	int priority = this->PCB[id]->getPriority();
	this->RL[priority].push(id);
}
void Manager::removeFromRL(int id) {
	//int index = this->getProcessIndex(id);
	int priority = this->PCB[id]->getPriority();
	std::queue <int> newRLForI = {};

	bool found = false;
	while (!this->RL[priority].empty()) {
		int current = this->RL[priority].front();
		if (current != id) {
			newRLForI.push(current);
		}
		else {
			found = true;
		}
		this->RL[priority].pop();
	}
	this->RL[priority] = newRLForI;
}


void Manager::addToPCB(Process* p) {
	bool added = false;
	for (int i = 0; i < this->PCB.size(); i++) {
		if(this->PCB[i] == this->nullProcess){
			this->PCB[i] = p;
			p->setID(i);
			added = true;
			break;
		}
	}
	if (!added) {
		throw Invalid();
	}
	return;
}

void Manager::removeFromPCB(int id) {
	if (this->PCB[id] != this->nullProcess) {
		this->PCB[id] = this->nullProcess;
	}
	else {
		throw Invalid();
	}
	return;
}
//void Manager::removeFromPCB(int id) {
//	for (int i = 0; i < this->PCB.size(); ++i) {
//		if (this->PCB[i]->getID() == id) {
//			this->PCB.erase(this->PCB.begin() + i);
//		}
//	}
//	return;
//}


//int Manager::getProcessIndex(int id) {
//	//std::cout << "Id " << id << std::endl;
//	for (int i = 0; i < this->PCB.size(); i++) {
//		//std::cout << "Here" << std::endl;
//		if (this->PCB[i]->getID() == id) {
//			//std::cout << "256" << std::endl;
//			return i;
//		}
//			
//	}
//	return -1;
//}


Process* Manager::getCurrentRunningProcess() {
	return this->currentRunning;
}

void Manager::releaseAllResourceOfProcess(int index) {
	for (int i = 0; i < this->PCB[index]->getResources().size(); i++) {
		int first = this->PCB[index]->getResources()[i].first;
		int second = this->PCB[index]->getResources()[i].second;
		//this->getRCB()[first]->free(second);
		//this->release(first, second);
		this->PCB[index]->removeResourcePair(first, second);
		this->RCB[first]->free(second);

		while (!this->RCB[first]->getWaitlist().empty() and this->RCB[first]->getFreeUnit() > 0) {
			std::pair <int, int> nextPair = this->RCB[first]->getNext();
			if (this->RCB[first]->getFreeUnit() >= nextPair.second) {
				this->RCB[first]->allocate(nextPair.second);
				//int indexOfJ = this->getProcessIndex(nextPair.first);
				int indexOfJ = nextPair.first;
				this->PCB[indexOfJ]->insertResourcePair(first, nextPair.second);
				this->PCB[indexOfJ]->setStateTo(true);
				this->RCB[first]->removeProcessPair(nextPair.first, nextPair.second);
				this->insertToRL(nextPair.first);
			}
			else {
				break;
			}
		}

	}
	return;
}