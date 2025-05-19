#include "Tester.h"

// 2. BinaryTree vezi dc pica pe 100k numere
// 3. de dat erase() la inceput de fiecare for() din tester::run()
// 4. De adaugat runtimes in csv

int main() {
    const Tester<SplayTree> ST; ST.run();
    //const Tester<SkipList> SL; SL.run();
    //const Tester<BinaryTree> BT; BT.run();
    return 0;
}