// Jason Chen 23642753
#include "ram.h"

// sets ram with inputted size
void RAM::set_RAM_size(unsigned long s){
    size = s;
}    

// returns size of ram
unsigned long const RAM::get_RAM_size(){
    return size;
}

// checks if there is enough space in ram for process to alloc for new proc creation
bool const RAM::find_space(unsigned long s){
    // from start of deque/vec of process in ram
    for (size_t i = 0; i < alloc_proc.size(); i++){
        if (i == alloc_proc.size()-1){
            // if reach end of deque of proc 
            // and didnt find spaces big enough btwn processes
            // check if diff of end of last proc mem alloc and max ram mem size
            if (((size-1) - alloc_proc[i]->get_alloc_range()[1]) >= s){
                // fits the new proc size 
                    // if fits, insert proc at end of deque with proper mem locs
                return true;
            }
            else{
                // if not, cout error code 
                return false;
            }
        }
        else if (alloc_proc[0]->get_alloc_range()[0] > s){ // if space in front before 1st proc in deque is big enough
            return true;
        }
        else{
            // if 
            // check the size between the end mem loc of a proc 
            // and the begin of proc mem alloc of next 
            std::deque<unsigned long> const proc1 = alloc_proc[i]->get_alloc_range();
            std::deque<unsigned long> const proc2 = alloc_proc[i+1]->get_alloc_range();
            if (proc2[0] - proc1[1] > s){
                // to see if there is enough space in the difference 
                    // ie - p1 = [0, x] and p2 = [y, z]
                    // if y-x = new proc size 
                    // insert new proc between p1 and p2
                return true;
            }
        }
    }
    return false;       
}

// basically like find_space but returns current range available for new proc
unsigned long const RAM::find_pos(unsigned long s){
    for (size_t i = 0; i < alloc_proc.size(); i++){
        if (alloc_proc[0]->get_alloc_range()[0] >= s){
            // the case where there is a big enoug gap in the beginning
            return 0;
        }
        else if (i == alloc_proc.size()-1){ // case where space after last proc in deque is enough
            if (alloc_proc[i]->get_alloc_range()[1] - size > s){
                return alloc_proc[i]->get_alloc_range()[1] + 1;
            }
        }
        else{ // checks between proc in deque
            std::deque<unsigned long> const proc1 = alloc_proc[i]->get_alloc_range();
            std::deque<unsigned long> const proc2 = alloc_proc[i+1]->get_alloc_range();
            if (proc2[0] - proc1[1] > s){
                return proc1[1]+1;
            }
        }
    }    
    return 0;
}

// inital ram check before proc creation
bool const RAM::check_proc_size(unsigned long s){
    // when process gets created
        // check if needed size > ram_size 
            // instant rejection - dont even need to scan RAM 
    if (s <= size){
        if (alloc_proc.size() == 0){
            // scenario 1: 
            // if there is no process at all in deque
            // p1 will be [0, x]
            return true;
        }
        else{
            if (find_space(s)){
                // scenario 2: 
                // there are process(es) in the deque
                return true;
            }
        }  
    }
    return false;
}

// adds proc to ram deque
void RAM::add_proc(std::shared_ptr<Process> p){
    unsigned long new_Pro_s = p->get_size(); // size of proc
    if (new_Pro_s <= size){
        if (alloc_proc.size() == 0){ // if no proc exists in ram
            p->set_mem_alloc(0, new_Pro_s-1); // start from beginning
            alloc_proc.push_back(p);
        }
        else{ // proc already exist 
            unsigned long const insert_addr = find_pos(new_Pro_s); // find correct mem loc to let proc alloc 
            p->set_mem_alloc(insert_addr, insert_addr + new_Pro_s-1); // alloc mem 
            alloc_proc.push_back(p); // add to ram deque
        }
    }
}

// print S m command
void const RAM::print_Sm(){
    if (alloc_proc.size() > 0){
        for (size_t i = 0; i < alloc_proc.size(); i++){ // parsing 
            std::deque<unsigned long> const proc = alloc_proc[i]->get_alloc_range();
            std::cout << proc[0] << " - " << proc[1] << " P" << alloc_proc[i]->read_pID() << std::endl;
        }
    }
}

// when proc gets terminated 
void RAM::terminate(unsigned long pid){
    if (alloc_proc.size() > 0){
        for (size_t i = 0; i < alloc_proc.size(); i++){ // parse to find correct proc
            if (alloc_proc[i]->read_pID() == pid){ 
                alloc_proc.erase(alloc_proc.begin()+ i); // remove
            }
        }
    }
}

// sorting ram for S m
void RAM::sort_ram(){
    if (alloc_proc.size() > 0){
        std::deque<unsigned long> unsorted; // temp deque for pids
        for (size_t i = 0; i < alloc_proc.size(); i++){
            unsorted.push_back(alloc_proc[i]->get_alloc_range()[0]);
        }
        std::sort(unsorted.begin(), unsorted.end()); // sort temp pid deque
        
        std::deque<std::shared_ptr<Process>> sorted_deque; // temp deque of proc pointers
        for (size_t i = 0; i < unsorted.size(); i++){ // sort proc pointer deque based on sorted pid deque
            for (size_t j = 0; j < alloc_proc.size(); j++){
                if (alloc_proc[j]->get_alloc_range()[0] == unsorted[i]){
                    sorted_deque.push_back(alloc_proc[j]);
                }
            }
        }
        alloc_proc = sorted_deque; // ram deque correctly sorted
    }
}
