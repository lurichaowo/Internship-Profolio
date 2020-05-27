// Jason Chen 23642753
#include "cpu.h"

// returns common process deque
std::deque<std::shared_ptr<Process>> const CPU::read_queue(){
    return cQueue;
}

//returns rt deque queue
std::deque<std::shared_ptr<Process>> const CPU::read_rqueue(){
    return rtQueue;
}

// return current running process
std::shared_ptr<Process> const CPU::read_currentP(){
    return runningProc;
}

// time slice of current running process ended
void CPU::end_TS(){
    if (runningProc->read_RT()){
        // if runningP is rt 
        rtQueue.push_back(runningProc);
        terminate();
    }
    else if (!runningProc->read_RT()){
        // if runningP is common
        cQueue.push_back(runningProc);
        terminate();
    }
}

// terminate currently running process
unsigned long CPU::terminate(){
    unsigned long const pid = runningProc->read_pID();
    runningProc = NULL;
    queue_check(); // check ready queue for runnable proc 
    return pid;
}


// checks queues for correct course of action with processes
// will run after everytime a process when events calls for it 
void CPU::queue_check(){
    // case 1: if rP is empty but rt isnt run head of rtQ
    if (runningProc == NULL && rtQueue.size() > 0){
        run_process(rtQueue[0]);
        rtQueue.erase(rtQueue.begin());
    }
    // case 2: preempt if rt needs to use cpu 
    else if (runningProc != NULL && rtQueue.size() > 0){
        if (!runningProc->read_RT()){
            preempt();
            rtQueue.erase(rtQueue.begin());
        }
    }
    // case 3: if nothing is running, and only has common proc
    else if (runningProc == NULL && rtQueue.size() == 0 && cQueue.size() > 0){
        run_process(cQueue[0]);
        cQueue.erase(cQueue.begin());
    }
}

//preempt the runningP - logic done already
void CPU::preempt(){
    cQueue.push_front(runningProc); // put runningP to head of CQ
    run_process(rtQueue[0]); // put head of Rt to runnningP
}

// adds processes to respective ready queues
void CPU::queue_process(std::shared_ptr<Process> p){
    if (p->read_RT()){
        // if process is real time, add to RT queue
        rtQueue.push_back(p);
        
        // after process gets added to queue, run the queue checkers
        queue_check();
    }
    else{
        // if process is common, add to common queue
        cQueue.push_back(p);
        // run the queue checkers
        queue_check();
    }
}

// make process to be the running (no logic)
void CPU::run_process(std::shared_ptr<Process> p){
    runningProc = p;
}

// sets deque of harddisk
void CPU::set_hdd(std::deque<std::shared_ptr<Harddisk>> hdd){
    hddDeque = hdd;
}

// currentP will start using hd #
void CPU::use_hd(int num){
    if (runningProc != NULL){
        hddDeque[num]->add_to_ioqueue(runningProc); // adds to io queue
    }
    runningProc = NULL; // empty running proc
    queue_check(); // run queue checker
}

// proc using hd is done and returning to proper ready queue
void CPU::hd_done(int num){
    if (hddDeque[num]->get_current() != NULL){ // there is a running proc on HD #
        queue_process(hddDeque[num]->get_current()); // add to correct ready queue
        hddDeque[num]->work_done(); // tell HD to clear its running proc 
    }
}

// do Sr prints
void const CPU::print_Sr(){
    // prints state of CPU and both levels of queues
    if (runningProc == NULL){ // CPU snapshot
        std:: cout << "CPU:" << std::endl;
    }
    else{
        std::cout << "CPU: P" << read_currentP()->read_pID() << std::endl;
    }
    std::cout << "RT Queue: "; // rtQueue prints
    if (rtQueue.size() > 0){
        for (size_t i = 0; i < rtQueue.size(); i++){
            std::cout << "P" << rtQueue[i]->read_pID();
            if (i != rtQueue.size()-1){
                std::cout << " <- ";
            }
        }
    }
    std::cout << "\nCommon Queue: "; // cQueue prints
    if (cQueue.size() > 0){
        for (size_t i = 0; i < cQueue.size(); i++){
            std::cout << "P" << cQueue[i]->read_pID();
            if (i != cQueue.size()-1){
                std::cout << " <- ";
            }
        }
    }
    std::cout << "\n";
}