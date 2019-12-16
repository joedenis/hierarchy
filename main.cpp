//simple hierarchy mutex

#include <iostream>
#include "HierarchicalMutex.h"


int main() {
    std::cout << "hierarchy mutex coming!" << std::endl;

    HierarchicalMutex high_level(1000);
    HierarchicalMutex low_level(100);
    HierarchicalMutex ultra_low_level(10);

    high_level.lock();
    low_level.lock();
    ultra_low_level.lock();

    return 0;
}
