#pragma once

#include <vector>
#include <chrono>

class DataStructure {
private:
    std::vector<std::chrono::duration<double, std::milli>> runtimes;

public:
    DataStructure();

    void addLastRuntime(const auto &current_runtime);
    const auto& getRuntimes();

    ~DataStructure();

};