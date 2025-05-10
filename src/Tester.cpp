#include "Tester.h"

#include "SplayTree.h"
#include "SkipList.h"
#include "BinaryTree.h"
#include "DataStructure.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::pair<std::string, int>> Tester::setup(const std::string& file_name) {
    std::vector<std::pair<std::string, int>> operations;
    std::ifstream f(file_name);
    if (!f.is_open()) {
        throw std::runtime_error("File does not exist: " + file_name);
    }

    std::string line;
    while (std::getline(f, line)) {
        std::istringstream iss(line);
        std::string operation;
        if (float value; iss >> operation >> value) {
            operations.emplace_back(operation, value);
        }
    }

    f.close();
    return operations;
}

void Tester::run() const{
    for (const auto& file : std::filesystem::directory_iterator(data_path)){
        if (file.is_regular_file()) {
            std::string file_name = current_tests_path + file.path().filename().string();
            std::cout << std::endl << "Reading data from: " << file_name << std::endl;

            std::vector<std::pair<std::string, int>> operations(Tester::setup(file_name));

            bool status(true);
            auto start = std::chrono::high_resolution_clock::now();
            for (auto op : operations){
                switch (op.first) {
                  case "insert": //ds.insert(itp.second); break;
                  case "search": //ds.search(itp.second); break;
                  case "delete": //ds.erase(itp.second); break;
                  default: status = false; break;
                }
            }

            auto end = std::chrono::high_resolution_clock::now();

            const std::chrono::duration<double, std::milli> current_runtime = end - start;

            if (status) {
                data_structure.addLastRuntime(current_runtime);
            } else {
                const std::chrono::duration<double, std::milli> no_value{0.0};
                data_structure.addLastRuntime(no_value);
            }

                Test::setResult(current_results_path, sort_name, file_name, order == 0 ? "ASC" : "DESC", algorithm);
            }
        }
    }
    const auto sort_times = data_structure.getSortTimes();
    //Test::setStats(current_results_path, sort_name, sort_times);
}