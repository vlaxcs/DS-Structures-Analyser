#include "DataStructure.h"

void DataStructure::addLastRuntime(const auto &current_runtime) {
    this->runtimes.push_back(current_runtime);
}

const auto& DataStructure::getRuntimes() {
    return runtimes;
}