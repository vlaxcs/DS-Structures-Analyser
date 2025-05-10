#pragma once

#include <vector>
#include <chrono>

class DataStructure {
private:
    std::vector<std::chrono::duration<double, std::milli>> runtimes;

public:
    DataStructure() = default;

    template<typename T>
    void addLastRuntime(const T& current_runtime) {
        runtimes.push_back(current_runtime);
    }

    std::vector<std::chrono::duration<double, std::milli>> getRuntimes();

    virtual ~DataStructure() = default;

};