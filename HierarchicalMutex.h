//
// Created by joe on 16/12/2019.
//

#ifndef CONCURRENCY_HIERARCHICALMUTEX_H
#define CONCURRENCY_HIERARCHICALMUTEX_H


#include <mutex>
#include <climits>

class HierarchicalMutex {

    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;

    void check_for_hierarchy_violation() {
        if(this_thread_hierarchy_value <= hierarchy_value) {
            throw std::logic_error("mutex hierarchy violated");
        }
    }

    void update_hierarchy_value() {
        previous_hierarchy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }

public:
    explicit HierarchicalMutex(unsigned long value) :
            hierarchy_value(value),
            previous_hierarchy_value(0)
    {}

    void lock();

    void unlock();

    bool try_lock();
};

//set the first thread value
thread_local unsigned long HierarchicalMutex::this_thread_hierarchy_value(ULONG_MAX);


#endif //CONCURRENCY_HIERARCHICALMUTEX_H
