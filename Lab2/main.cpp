#include <iostream>

#include "Tree.h"

int main() {
    Tree* MyTree = new Tree();

    unsigned long long value = 123;
    std::string str_a, str_b, str_c;

//    while (std::cin >> str >> value) {
//        MyTree->InsertElement(str, value);
//        TItemOfTree::PrintItem(MyTree->GetRoot());
//        std::cout << MyTree->GetRoot()->GetBalance() << std::endl;
//    }
//
//    TItemOfTree::PrintItem(MyTree->GetRoot());

    str_a = "a";
    str_b = "b";
    str_c = "c";
    MyTree->InsertElement(str_a, value);
    std::cout << MyTree->GetRoot()->GetBalance() << std::endl;
    MyTree->InsertElement(str_b, value);
    std::cout << MyTree->GetRoot()->GetBalance() << std::endl;
    MyTree->InsertElement(str_c, value);
    std::cout << MyTree->GetRoot()->GetBalance() << std::endl;

    TItemOfTree::PrintItem(MyTree->GetRoot());

    MyTree->Print(MyTree->GetRoot());
    std::cout << std::endl;

    MyTree->Clear(MyTree->GetRoot());
    delete MyTree;
    return 0;
}
