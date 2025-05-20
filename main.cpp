#include "Tester.h"

// TODO
// 1. erase() pentru SplayTree
// 2. BinaryTree vezi dc pica pe 100k numere
// 3. de dat erase() la inceput de fiecare for() din tester::run()
// 4. De adaugat runtimes in csv

int main() {
    const Tester<SplayTree> ST; ST.run("SplayResults.csv");
    const Tester<SkipList> SL; SL.run("SkipResults.csv");
    const Tester<BinaryTree> BT; BT.run("BTreeResults.csv");
    return 0;
}