#include "../include/Tester.h"
#include "../include/RBTree.h"

void initialize() {
    std::string tests_path = "../Python_TestsGenerator/Tests";
    std::filesystem::path results_path = "../Python_TestsGenerator/Results";
    std::filesystem::path filename = "times5.csv";

    std::ofstream fout(results_path / filename);
    if (!fout.is_open()) {
        std::cerr << "Failed to open the output file.\n";
        return;
    }

    fout << "Data Structure,";
    bool first = true;
    for (const auto& entry : fs::directory_iterator(tests_path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::string filename = entry.path().stem().string();
            if (!first) fout << ',';
            fout << filename;
            first = false;
        }
    }

    fout << std::endl;
    fout.close();
}

int main() {
    initialize();

    const Tester<SplayTree> ST; ST.run("Splay Tree");
    const Tester<SkipList> SL; SL.run("Skip List");
    const Tester<BinaryTree> BT; BT.run("Binary Tree");
    const Tester<RBTree> RBT; RBT.run("RBTreeResults.csv");
    return 0;
}
