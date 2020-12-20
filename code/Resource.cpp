#include "Resource.h"

Resource::Resource(int maxUnit) {
	this->state = maxUnit;
    this->maxUnit = maxUnit;
	this->waitlist = std::vector < std::pair <int, int> >{};
}


Resource:: ~Resource() {
	this->state = NULL;
    this->maxUnit = NULL;
	this->waitlist.clear();
}


void Resource::insertProcessPair(int i, int k) {
    //for (int i = 0; i < this->waitlist.size(); i++) {
    //    if (this->waitlist[i].first == i) {
    //        this->waitlist[i].second += k;
    //        if (this->waitlist[i].second > maxUnit)
    //            throw Invalid();
    //    }
    //}
	this->waitlist.push_back(std::make_pair(i, k));
}
void Resource::removeProcessPair(int i, int k){
    //for (std::vector< std::pair <int, int> >::iterator iter = this->waitlist.begin(); iter != this->waitlist.end(); ++iter){
    //    if (*iter == std::make_pair(i, k)){
    //        this->waitlist.erase(iter);
    //        break;
    //    }
    //}
    //==========================================
    for (int j = 0; j < this->waitlist.size(); ++j) {
        //if (this->waitlist[i].first == i and this->waitlist[i].second == k) {
        if(this->waitlist[j] == std::make_pair(i,k)){
            this->waitlist.erase(this->waitlist.begin() + j);
        }
    }
    return;
}


std::pair <int, int> Resource::getNext() {
    std::pair <int, int> next = this->waitlist[0];
    return next;
}


std::vector < std::pair <int, int> > Resource::getWaitlist() {
    return this->waitlist;
}

void Resource::allocate(int k) {
    this->state -= k;
}
void Resource::free(int k) {
    this->state += k;
}
int Resource::getFreeUnit() {
    return this->state;
}
int Resource::getMaxUnit() {
    return this->maxUnit;
}