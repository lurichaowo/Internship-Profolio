// Jason Chen 23642753
#include <iostream>
#include <memory>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include "harddisk.h"
#include "cpu.h"
#include "ram.h"

//A program that stimulates some aspects of an OS.

//check if string contains only numbers
bool check_str_for_num(std::string s){
    if (!s.empty()){
        for (size_t i = 0; i < s.size(); i++){
            if (!isdigit(s[i])){
                //contains a char
                return false;
            }
        }
    }
    else{
        // if is empty
        return false;
    }
    // contains only numbers
    return true;
}

// check if string contains only non number chars
bool only_char(std::string s){
    if (!s.empty()){
        for (size_t i = 0; i < s.size(); i++){
            if (isdigit(s[i])){
                //contains dig
                return false;
            }
        }
    }
    else{
        // is empty
        return false;
    }
    // contains only char
    return true;
}

// creates new process based on inputted size, pid, and if it is Rt or not
std::shared_ptr<Process> create_new_Process(unsigned long size, unsigned long pCount, bool isRT){
    auto new_p = std::make_shared<Process>();
    new_p->set_pID(pCount); // set pID
    new_p->set_RT(isRT); // sets RT or not 
    new_p->set_size(size); // set process "size" - how much ram it will take up
    return new_p;
}

// ram size asking function
unsigned long ask_RAM(){
    // str and unsigned long var 
    std::string ram_input;
    unsigned long ram_mem;
    while (true){ // until correct input is given
        std::cout << "Enter the amount of RAM memory (max is 4bil)" << std::endl;
        getline(std::cin, ram_input);
        ram_input.erase(remove(ram_input.begin(), ram_input.end(), ' '), ram_input.end()); // remove white spaces
        bool input_check = check_str_for_num(ram_input);
        if (!input_check){
            // if contains non digit in input
            std::cout << "Please enter a valid RAM memory amount" << std::endl;
            ram_input = "";
        }
        else{
            // contains only digits
            ram_mem = std::stoul(ram_input); // turn str to unsigned long 
            if (ram_mem <= 0 || ram_mem > 4000000000){
                // invalid inputs 
                std::cout << "Please enter a valid RAM memory amount" << std::endl;
                ram_input = "";
            }
            else{
                // return ram size
                return ram_mem;
            }
        }
    }
    return 0;
}

// hd # asking function
unsigned long ask_HD(){
    // str and unsigned long var
    std::string hd_input;
    unsigned long hd_num;
    while (true){ // until correct input is given
        std::cout << "Enter the amount of Harddisk" << std::endl;
        getline(std::cin, hd_input);
        hd_input.erase(remove(hd_input.begin(), hd_input.end(), ' '), hd_input.end()); // remove whtie spaces
        bool input_check = check_str_for_num(hd_input);
        if (!input_check){
            // contains non digits 
            std::cout << "Please enter a valid harddisk amount" << std::endl;
            std::cout << "Remember: the theoretical limit is 24 harddisks" << std::endl;
            hd_input = "";
        }
        else{
            // contains only digits
            hd_num = std::stoul(hd_input); // str to unsigned long
            if (hd_num < 0 || hd_num > 24){
                // invalid input values
                std::cout << "Please enter a valid harddisk amount" << std::endl;
                std::cout << "Remember: the theoretical limit is 24 harddisks" << std::endl;
                hd_input = "";
            }
            else{
                // return num of HDs
                return hd_num;
            }
        }
    }
    return 0;

}

std::deque<std::shared_ptr<Harddisk>> create_HD_deque(unsigned long const hd_count){
    std::deque<std::shared_ptr<Harddisk>> deq;
    for (unsigned long i = 0; i < hd_count; i++){
        auto new_hd = std::make_shared<Harddisk>(); // creates new HD 
        new_hd->set_hd_num(i); // sets HD #
        deq.push_back(new_hd); // adds to deque
    }
    return deq;
}

int parse_b(std::string b){
    for (size_t i = 0; i < b.size(); i++){
        if (!isdigit(b[i])){
            return i;
        }
    }
    return 0;
}

int parse_a(std::string a){
    for (size_t i = 0; i < a.size(); i++){
        if (isdigit(a[i])){
            return i;
        }
        if (a[i] == 'm' || a[i] == 'r' || a[i] == 'i'){
            return i;
        }
    }
    return 0;
}

int main(){
    // Start of Program:
    CPU cpu; // the CPU, there is only 1 of them!!!

    // How much RAM memory is there?
    // is unsigned long so it can handle 4 bil pos ints (since it doesnt need to care abut neg)
    unsigned long const ram_mem_size = ask_RAM();
    RAM ram;
    ram.set_RAM_size(ram_mem_size);
    std::cout << "RAM size: " << ram.get_RAM_size() << std::endl;

    // How many HDs are there?
    unsigned long const hd_count = ask_HD();
    std::cout << "HDD number: " << hd_count << std::endl;

    // create a deque with the correct # of HDs
    std::deque<std::shared_ptr<Harddisk>> const hd_deq = create_HD_deque(hd_count);

    unsigned long pCount = 1; // process count for pID
    cpu.set_hdd(hd_deq); // gives cpu info about HD deque

    while (true){
        // user inputs processing shanigens
        std::string a;
        std::string b;
        std::cin >> a;        // takes the first part
        getline(std::cin, b); // takes 2nd part
        if (b.empty()){       // can be empty
            b = "";
        }

        // remove white spaces
        a.erase(remove(a.begin(), a.end(), ' '), a.end()); 
        b.erase(remove(b.begin(), b.end(), ' '), b.end());

        // parse b for stray letters and add to a 
        while (!check_str_for_num(b) && !only_char(b) && !b.empty()){ // if contains both non digits and numbers
            int pos = parse_b(b); // find where the non digits are 
            a = a + b[pos]; // add to end of a
            b.erase(b.begin()+pos); // remove from original b input
        }

        // parse a for stray numbers and add to b
        while (!only_char(a) && !check_str_for_num(a)){ // if contains both non digits and numbers
            int pos = parse_a(a); // find where digits are 
            std::cout << b << std::endl;
            b = a[pos] + b; // add to beginning of b
            a.erase(a.begin()+pos); // remove from original a input
        }

        // last check for misplaces space
        if (a[0] == 'S' && a.size() > 1){
            b = a[1] + b; 
            a.erase(a.begin()+1); 
        }

        // checking the user inputs for correct action to be taken
        if (check_str_for_num(b)){ // A # or AR # options
            if (a == "A"){
                // creates a common process with a b size
                    // check if ram has enough space first 
                if (ram.check_proc_size(std::stoul(b))){ // std::stoul = string to unsigned long
                    auto new_cP = std::make_shared<Process>();
                    new_cP = create_new_Process(std::stoul(b), pCount, false); // Com_proc creation
                    ram.add_proc(new_cP); // add to ram
                    cpu.queue_process(new_cP); // add to correct queue
                    ram.sort_ram(); // sorts ram for S m
                    pCount++; // increase pid
                }
                else{
                    std::cout << "Error: RAM doesn't have enough space to alloc the process" << std::endl;
                }
            }
            else if (a == "AR"){
                // creates a common process with a b size
                    // check if ram has enough space first
                if (ram.check_proc_size(std::stoul(b))){
                    auto new_cP = std::make_shared<Process>();
                    new_cP = create_new_Process(std::stoul(b), pCount, true); // RT_proc creation
                    ram.add_proc(new_cP); // add to ram
                    cpu.queue_process(new_cP); // add to correct queue
                    ram.sort_ram(); // sorts ram for S m
                    pCount++; // increase pid
                }
                else{
                    std::cout << "Error: RAM doesn't have enough space to alloc the process" << std::endl;
                }
            }
            else if (a == "d"){ // d # input
                if (hd_count == 0){
                    std::cout << "Error: there are no HD in this simulation" << std::endl;
                }
                else if (std::stoul(b) > hd_count - 1){
                    std::cout << "That is an invalid HD #" << std::endl;
                }
                else{
                    cpu.use_hd(std::stoul(b));
                }
            }
            else if (a == "D"){
                if (hd_count == 0){ // tries to use a hd when there isnt 
                    std::cout << "Error: there are no HD in this simulation" << std::endl;
                }
                else if (std::stoul(b) > hd_count - 1 || std::stoul(b) < 0){ // out of bound hd #s 
                    std::cout << "That is an invalid HD #" << std::endl;
                }
                else{ // correct input
                    cpu.hd_done(std::stoul(b));
                }
            }
            else{
                std::cout << "Invalid Input, please try again" << std::endl; 
            }
        }
        else if (only_char(b)){ // snapshot commands
            if (a == "S"){
                if (b == "r"){ // views cpu and ready queues
                    cpu.print_Sr();
                }
                else if (b == "i"){ // views hd and io queues
                    for (size_t i = 0; i < hd_deq.size(); i++){
                        hd_deq[i]->print_Si();
                    }
                }
                else if (b == "m"){ // views ram memory
                    ram.print_Sm();
                }
            }
            else{
                std::cout << "Invalid Input, please try again" << std::endl; 
            }
        }
        else if (b.empty()){ // other commands
            if (a == "Q"){ // ending time slice 
                cpu.end_TS();
            }
            else if (a == "t"){ // terminating process
                if (cpu.read_currentP() != NULL){ // if running proc exists
                    unsigned long pid = cpu.terminate(); // get pid while term running proc
                    ram.terminate(pid); // dealloc proc from ram with pid
                    ram.sort_ram(); // sort ram for S m
                }
            }
            else{
                std::cout << "Invalid Input, please try again" << std::endl; 
            }
        }
    }
}

// User Inputs:
// A size: A = new common process has been created
// PCB is created and place process into the RQ
// size = amount of memory needed for allocation
// new PID for each new process (starting at 1)

// AR size: AR = new RT process
//everything is the same as A size

// Q: time slice has ended for the currently running process

// t = currently running process terminates

// d number: the disk# that currently running process requests

// D number: the disk# has finished work for a certain process

// S r: shows the currently running process
// also shows the process waiting on both levels of the RQ

// S i: Shows what processes are using the HD and the queues for the HDs
// starting at harddisk 0
// for each busy HD, show the running process and show its I/O queue

// S m: shows state of memory
// range of memory addresses used by each process
