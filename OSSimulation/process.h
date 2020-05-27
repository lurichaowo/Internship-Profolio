// Jason Chen 23642753
#ifndef PROCESS_H
#define PROCESS_H
#include <deque>

class Process{
    private: 
        bool isRT; // if this proc is rt or not 
        std::deque<unsigned long> memAlloc; // mem range alloc in ram
        unsigned long pID; // pid 
        unsigned long p_size; // proc size

        // internal functions
        void create_common(); // sets process to be common process
        void create_RT(); // sets process to be a RT process

    public:  
        // sets the interval of memory to be taken up
        void set_mem_alloc(unsigned long loc1, unsigned long loc2);

        // sets proc size
        void set_size(unsigned long s);

        // get proc size
        unsigned long const get_size();

        // returns alloc mem range in ram
        std::deque<unsigned long> const get_alloc_range();

        // sets pid 
        void set_pID(unsigned long num);

        // returns pID of process
        unsigned long const read_pID();

        // proc to be common or rt based on input
        void set_RT(bool rt_status);

        // return if is real time or not 
        bool const read_RT();
};

#endif