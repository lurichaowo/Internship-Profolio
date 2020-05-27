// Jason Chen 23642753
#include <iostream>
#include <memory>
#include <deque>
#include "process.h"
#include "harddisk.h"
#include "ram.h"

class CPU{
    private:
        std::deque<std::shared_ptr<Process>> rtQueue; // the RT RQ
        std::deque<std::shared_ptr<Process>> cQueue; // the common RQ
        std::shared_ptr<Process> runningProc = NULL; // currently running proc on cpu
        std::deque<std::shared_ptr<Harddisk>> hddDeque; // deque of HDs

    public: 
        // returns common process deque
        std::deque<std::shared_ptr<Process>> const read_queue();

        //returns rt deque queue
        std::deque<std::shared_ptr<Process>> const read_rqueue();

        // return current running process
        std::shared_ptr<Process> const read_currentP();

        // time slice of current running process ended
        void end_TS();

        // terminate currently running process
        unsigned long terminate();

        // checks queues for correct course of action with processes
        // will run after everytime a process when events calls for it 
        void queue_check();

        //preempt the runningP
        void preempt();

        // adds processes to respective ready queues
        void queue_process(std::shared_ptr<Process> p);

        // add correct process to be the running (no logic)
        void run_process(std::shared_ptr<Process> p); 
        
        // sets deque of harddisk
        void set_hdd(std::deque<std::shared_ptr<Harddisk>> hdd);

        // currentP will start using hd #
        void use_hd(int num); 

        // proc using hd is done and returning to proper ready queue
        void hd_done(int num);

        // do Sr prints
        void const print_Sr();
};