#include "Process.h"

Process::Process() {
	this->stateReady = false;
	this->resources = std::vector < std::pair <int, int> >{};
	this->children = std::vector <int>{};
	this->parentID = -1;
	this->id = -1;
	this->priority = -1;
}

Process::~Process() {
	this->stateReady = false;
	this->resources.clear();
	this->children.clear();
	this->parentID = -1;
	this->id = -1;
	this->priority = -1;
}


void Process::setID(int newID) {
	this->id = newID;
	return;
}
int Process::getID() {
	return this->id;
}


void Process::setParent(int parentID) {
	this->parentID = parentID;
	return;
}
int Process::getParent() {
	return this->parentID;
}


void Process::setPriority(int priority) {
	this->priority = priority;
	return;
}
int Process::getPriority() {
	return this->priority;
}


void Process::setStateTo(bool newState) {
	this->stateReady = newState;
	return;
}
bool Process::getState() {
	return this->stateReady;
}


void Process::insertResourcePair(int r, int k) {
	//if (std::find(resources.begin(), resources.end(), std::make_pair(r, k)) != resources.end())
	//	throw Invalid();

	for (int i = 0; i < this->resources.size(); i++) {
		if (this->resources[i].first == r) {
			this->resources[i].second += k;
			return;
		}
	}
	this->resources.push_back(std::make_pair(r, k));
	return;
}
void Process::removeResourcePair(int r, int k) {
	//if (std::find(resources.begin(), resources.end(), std::make_pair(r, k)) == resources.end())
	//	throw Invalid();
	//if (containResource(r))
	//	throw Invalid();
	bool found = false;
	for (int i = 0; i < this->resources.size(); ++i) {
		if (this->resources[i].first == r and this->resources[i].second >=k) {
			if (this->resources[i].second > k) {
				this->resources[i].second -= k;
			}
			else {
				this->resources.erase(this->resources.begin() + i);
			}
			found = true;
			break;
		}
		//if (this->resources[i].first == r and this->resources[i].second == k) {
		//	this->resources.erase(this->resources.begin() + i);
		//	break;
		//}
	}

	if (!found)
		throw Invalid();
	return;
}
void Process::clearResourcePair() {
	this->resources = {};
	return;
}
//void Process::releaseAllResource(Manager* m) {
//	for (int i = 0; i < this->resources.size(); i++) {
//		int first = this->resources[i].first;
//		int second = this->resources[i].second;
//		m->getRCB()[first]->free(second);
//	}
//	this->resources = {};
//}
std::vector< std::pair <int, int> > Process::getResources() {
	return this->resources;
}


void Process::addChildren(int i) {
	this->children.push_back(i);
}
void Process::removeChildren(int i) {
	//for (std::vector< int >::iterator iter = this->children.begin(); iter != this->children.end(); ++iter){
	//	if (*iter == i){
	//		this->children.erase(iter);
	//		break;
	//	}
	//}
	for (int index = 0; i < this->children.size(); ++i) {
		if (this->resources[index].first == i) {
			this->resources.erase(this->resources.begin() + index);
		}
	}
	return;
}
std::vector<int> Process::getChildren() {
	return this->children;
}


bool Process::containProcess(int id) {
	for (int i = 0; i < this->children.size(); i++) {
		if (this->children[i] == id)
			return true;
	}
	return false;
}

bool Process::containResource(int r) {
	bool contain = false;
	for (int i = 0; i < this->resources.size(); i++) {
		if (this->resources[i].first == i) {
			contain = true;
			break;
		}
	}
	return contain;
}