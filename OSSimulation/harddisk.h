// Jason Chen 23642753
#ifndef HARDDISK_H
#define HARDDISK_H
#include <iostream>
#include <memory>
#include <deque>
#include "process.h"

class Harddisk{
    private:
        unsigned long hd_num; // HD #
        std::shared_ptr<Process> currentProc = NULL; // current proc running on this HD
        std::deque<std::shared_ptr<Process>> ioqueue; // this hd's io queue

    public:
        // sets harddisk num
        void set_hd_num(unsigned long num);

        // get HD num
        unsigned long const get_hd_num();

        // get current running proc on HD #
        std::shared_ptr<Process> const get_current();
        
        // current running proc has finished work
        void work_done();

        // checks ioqueue for correct course of action
        void ioqueue_check();

        // adds processes to io queues
        void add_to_ioqueue(std::shared_ptr<Process> p);

        // add correct process to be the running proc (no logic)
        void run_process(std::shared_ptr<Process> p); 

        // print S i command
        void const print_Si();

};

#endif