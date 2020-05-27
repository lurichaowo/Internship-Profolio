// Jason Chen 23642753
#include "harddisk.h"

// sets harddisk num
void Harddisk::set_hd_num(unsigned long num){
    hd_num = num;
}

// get HD num
unsigned long const Harddisk::get_hd_num(){
    return hd_num;
}

// get current running proc on HD #
std::shared_ptr<Process> const Harddisk::get_current(){
    return currentProc;
}

// current running proc has finished work
void Harddisk::work_done(){
    currentProc = NULL;
    ioqueue_check();
}

// checks ioqueue for correct course of action
void Harddisk::ioqueue_check(){
    if (currentProc == NULL){
        if (ioqueue.size() > 0){
            run_process(ioqueue[0]);
            ioqueue.erase(ioqueue.begin());
        }
    }
}

// adds processes to io queues
void Harddisk::add_to_ioqueue(std::shared_ptr<Process> p){
    ioqueue.push_back(p);
    ioqueue_check();
}

// add correct process to be the running proc (no logic)
void Harddisk::run_process(std::shared_ptr<Process> p){
    currentProc = p;
}

// print S i command
void const Harddisk::print_Si(){
    std::cout << "HDD #" << get_hd_num() << ": " ;
    if (currentProc != NULL){
        std::cout << "P" << currentProc->read_pID();
    }
    std::cout << "\nI/O queue #" << get_hd_num() << ": ";
    if (ioqueue.size() > 0){
        for (size_t i = 0; i < ioqueue.size(); i++){
            std::cout << "P" << ioqueue[i]->read_pID();
            if (i != ioqueue.size()-1){
                std::cout << " <- ";
            }
        }
    }
    std::cout << "\n";
}