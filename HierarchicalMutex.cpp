//
// Created by joe on 16/12/2019.
//

#include "HierarchicalMutex.h"

void HierarchicalMutex::lock() {
    check_for_hierarchy_violation();
    internal_mutex.lock();
    update_hierarchy_value();
}

void HierarchicalMutex::unlock() {
    this_thread_hierarchy_value = previous_hierarchy_value;
    internal_mutex.unlock();
}

bool HierarchicalMutex::try_lock() {
    check_for_hierarchy_violation();
    if(!internal_mutex.try_lock()) return false;
    update_hierarchy_value();
    return true;
}
