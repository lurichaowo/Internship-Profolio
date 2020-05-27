// Jason Chen 23642753
#include "process.h"

// sets the interval of memory to be taken up
void Process::set_mem_alloc(unsigned long loc1, unsigned long loc2){
    memAlloc.push_back(loc1);
    memAlloc.push_back(loc2);
}

// sets proc size
void Process::set_size(unsigned long s){
    p_size = s;
}

// get proc size
unsigned long const Process::get_size(){
    return p_size;
}

// returns alloc mem range in ram
std::deque<unsigned long> const Process::get_alloc_range(){
    return memAlloc;
}

// sets pid 
void Process::set_pID(unsigned long num){
    pID = num;
}

// returns pid 
unsigned long const Process::read_pID(){
    return pID;
}

void Process::set_RT(bool rt_status){
    if (rt_status){
        create_RT();
    }
    else {
        create_common();
    }
}

// sets proc to common 
void Process::create_common(){
    isRT = false;
}

// sets proc to rt 
void Process::create_RT(){
    isRT = true;
}

// return whether proc is rt or not 
bool const Process::read_RT(){
    return isRT;
}