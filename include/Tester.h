#pragma once

#include "SplayTree.h"
#include "SkipList.h"
#include "BinaryTree.h"
#include "RBTree.h"

#include <string>
#include <chrono>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;

template<typename data_structure>
class Tester{
private:
  std::string tests_path;
  std::string results_path;
  std::vector<std::chrono::duration<double, std::milli>> runtimes;

public:
    Tester() : tests_path("../Python_TestsGenerator/Tests"), results_path("../Python_TestsGenerator/Results/times.csv"){};

    static std::vector<std::pair<std::string, int>> setup(const std::string& file_name) {
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

    void run(std::string ds_name) const {
        std::ofstream fout(results_path, std::ios::app);
        std::stringstream sstream;

        fout << std::format("{},", ds_name);
        for (const auto& file : std::filesystem::directory_iterator(tests_path)){
            data_structure ds;
            if (file.is_regular_file()) {
                std::string file_name = tests_path + "/" + file.path().filename().string();
                std::cout << std::endl << "Reading data from: " << file_name << std::endl;

                std::vector<std::pair<std::string, int>> operations(Tester::setup(file_name));

                bool status(true);
                auto start = std::chrono::high_resolution_clock::now();

                for (const auto& op : operations){
                    switch (op.first[0]) {
                      case 'i': ds.insert(op.second); break;
                      case 's': ds.search(op.second); break;
                      case 'd': ds.erase(op.second); break;
                      default: status = false; break;
                    }
                }

                auto end = std::chrono::high_resolution_clock::now();

                const std::chrono::duration<double, std::milli> current_runtime = end - start;
                std::cout << current_runtime;
                sstream << current_runtime << ", ";


                if (status) {
                    ds.addLastRuntime(current_runtime);
                } else {
                    const std::chrono::duration<double, std::milli> no_value{0.0};
                    ds.addLastRuntime(no_value);
                }
            }
        }
       // auto sort_times = ds.getRuntimes();
        //Test::setStats(current_results_path, sort_name, sort_times);

        auto res = sstream.str();
        res.erase(res.size() - 2);
        fout << res << std::endl;
    }


};