#pragma once

#include "SplayTree.h"
#include "SkipList.h"
#include "BinaryTree.h"
#include "DataStructure.h"

#include <string>
#include <chrono>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

template<typename data_structure>
class Tester{
private:
  std::string tests_path;
  std::string results_path;
  std::vector<std::chrono::duration<double, std::milli>> runtimes;

public:

  Tester() : tests_path("./Python_TestsGenerator"), results_path("./Results"){}

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

    void run() const{
        data_structure ds;

        for (const auto& file : std::filesystem::directory_iterator(tests_path)){
            if (file.is_regular_file()) {
                std::string file_name = tests_path + "/" + file.path().filename().string();
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
                    ds.addLastRuntime(current_runtime);
                } else {
                    const std::chrono::duration<double, std::milli> no_value{0.0};
                    ds.addLastRuntime(no_value);
                }

            }
        }
        const auto sort_times = ds.getSortTimes();
        //Test::setStats(current_results_path, sort_name, sort_times);
    }

};