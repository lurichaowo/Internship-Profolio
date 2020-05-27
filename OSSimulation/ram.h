// Jason Chen 23642753
#ifndef RAM_H
#define RAM_H
#include <iostream>
#include <memory>
#include <deque>
#include <algorithm>
#include "process.h"

class RAM{
    private:
        unsigned long size; // ram size
        std::deque<std::shared_ptr<Process>> alloc_proc; // ram deque of proc alloc
        bool const find_space(unsigned long s); // internal function for if there is enough space for proc creation

    public:
        // sets ram with inputted size
        void set_RAM_size(unsigned long s);
        
        // returns size of ram
        unsigned long const get_RAM_size();

        // basically like find_space but returns current range available for new proc
        unsigned long const find_pos(unsigned long s);

        // inital ram check before proc creation
        bool const check_proc_size(unsigned long s);

        // adds proc to ram deque
        void add_proc(std::shared_ptr<Process>);

        // print S m command
        void const print_Sm();

        // when proc gets terminated 
        void terminate(unsigned long pid);

        // sorting ram for S m
        void sort_ram();
};

#endif