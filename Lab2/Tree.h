//
// Created by shand on 16.04.2022.
//

#ifndef INC_2_TREE_H
#define INC_2_TREE_H
#include "TItemOfTree.h"
#include <iostream>
#include <cmath>

const short STOP = 0;
const short POS_MOVE = 1;
const short NEG_MOVE = -1;
const short POS_ROTATE = 2;
const short NEG_ROTATE = -2;

class Tree {
public:
    Tree (): root(nullptr) {};
    bool IsEmpty() {
        if (GetRoot() == nullptr) {
            return true;
        } else {
            return false;
        }
    }

    TItemOfTree* GetRoot() {
        return root;
    }

    void SetRoot (TItemOfTree* item) {
        if (item == nullptr) {
            return;
        }
        root = item;
    }

    void Print(TItemOfTree* item) {
        if (IsEmpty()) {
            std::cout << "Empty tree!" << std::endl;
        } else if (item != nullptr) {
            Print(item->GetLeft());
            std::cout << item->GetKey();
            Print(item->GetRight());
        } else {
            return;
        }
    }



    static TItemOfTree* GetMaxLeft (TItemOfTree* item) {
        item = item->GetLeft();
        while (item->GetRight() != nullptr) {
            item = item->GetRight();
        }
        return item;
    }

    static TItemOfTree* GetMinRight (TItemOfTree* item) {
        item = item->GetRight();
        while (item->GetLeft() != nullptr) {
            item = item->GetLeft();
        }
        return item;
    }

    unsigned long long Search(TItemOfTree* item, std::string &key) {

        if (key == item->GetKey()) {
            return item->GetValue();
        } else if (key > item->GetKey()) {
            if (item->GetRight() != nullptr) {
                Search(item->GetRight(), key);
            } else {
                return -1;
            }

        } else if (key < item->GetKey()) {
            if (item->GetLeft() != nullptr) {
                Search(item->GetLeft(), key);
            } else {
                return -1;
            }
        }

    }


    void InsertElement(std::string &key, unsigned long long value) {
        if (GetRoot() == nullptr) {
            auto* item = new TItemOfTree(key, value, nullptr);
            SetRoot(item);
        } else {
            Insert(key, value,GetRoot());
        }
    }

    void Insert(std::string &key, unsigned long long value, TItemOfTree* item) {

        if (key < item->GetKey()) {
            if (item->GetLeft() == nullptr) {
                auto* new_item = new TItemOfTree(key, value, item);
                item->SetLeft(new_item);
                new_item->SetParent(item);
                new_item->GetParent()->IncrBalance();
                BalanceInsert(new_item->GetParent());
            } else {
                Insert(key, value, item->GetLeft());
            }
        } else if (key > item->GetKey()) {
            if (item->GetRight() == nullptr) {
                auto* new_item = new TItemOfTree(key, value, item);
                item->SetRight(new_item);
                new_item->SetParent(item);
                item->DecrBalance();
                BalanceInsert(item);
            } else {
                Insert(key, value, item->GetRight());
            }
        } else {
            item->SetValue(value);
        }
    }



    void BalanceInsert(TItemOfTree* item) {
        if (item->GetBalance() == 0) {
            return;
        } else if (item->GetParent() == nullptr) {
            if (abs(item->GetBalance()) != 2) {
                return;
            }
        } else {

            if (abs(item->GetBalance()) == 1) {
                TItemOfTree* parent = item->GetParent();
                if (parent->GetLeft() == item) {
                    parent->IncrBalance();
                } else {
                    parent->DecrBalance();
                }
                TItemOfTree* new_item = item->GetParent();
                BalanceInsert(new_item);
            } else if (item->GetBalance() == 2) {
                if (item->GetLeft()->GetBalance() == 1) {
                    item->SetBalance(0);
                    item->GetLeft()->SetBalance(0);
                    RotateRight(item);
                } else if (item->GetLeft()->GetBalance() == -1) {
                    if (item->GetLeft()->GetRight() != nullptr) {
                        if (item->GetLeft()->GetRight()->GetBalance() == 0) {
                            item->SetBalance(0);
                            item->GetLeft()->SetBalance(0);
                            item->GetLeft()->GetRight()->SetBalance(0);
                        } else if (item->GetLeft()->GetRight()->GetBalance() == 1) {
                            item->SetBalance(-1);
                            item->GetLeft()->SetBalance(0);
                            item->GetLeft()->GetRight()->SetBalance(0);
                        } else if (item->GetLeft()->GetRight()->GetBalance() == -1) {
                            item->SetBalance(0);
                            item->GetLeft()->SetBalance(1);
                            item->GetLeft()->GetRight()->SetBalance(0);
                        }
                    }
                    RotateLeft(item->GetLeft());
                    RotateRight(item);
                }
                item = item->GetParent();
                BalanceInsert(item);
            } else if (item->GetBalance() == -2) {
                if (item->GetRight()->GetBalance() == 1) {
                    if (item->GetRight()->GetLeft() != nullptr) {
                        if (item->GetRight()->GetLeft()->GetBalance() == 0) {
                            item->SetBalance(0);
                            item->GetRight()->SetBalance(0);
                            item->GetRight()->GetLeft()->SetBalance(0);
                        } else if (item->GetRight()->GetLeft()->GetBalance() == 1) {
                            item->SetBalance(0);
                            item->GetRight()->SetBalance(-1);
                            item->GetRight()->GetLeft()->SetBalance(0);
                        } else if (item->GetRight()->GetLeft()->GetBalance() == -1) {
                            item->SetBalance(-1);
                            item->GetRight()->SetBalance(0);
                            item->GetRight()->GetLeft()->SetBalance(0);
                        }
                    }
                    RotateRight(item->GetRight());
                    RotateLeft(item);
                } else if (item->GetRight()->GetBalance() == -1) {
                    item->SetBalance(0);
                    item->GetRight()->SetBalance(0);
                    RotateLeft(item);
                }
                item = item->GetParent();
                BalanceInsert(item);
            }
        }
    }

    void RotateLeft(TItemOfTree* item) {
        if (item->GetRight() == nullptr) {
            return;
        }
        TItemOfTree* right = item->GetRight();
        TItemOfTree* child = right->GetLeft();
        TItemOfTree* parent = item->GetParent();
        if (parent == nullptr) {
            root = right;
        }
        right->SetParent(parent);
        if (parent != nullptr) {
            if (parent->GetLeft() == item) {
                parent->SetLeft(right);
            } else {
                parent->SetRight(right);
            }
        }
        if (child != nullptr) {
            child->SetParent(item);
        }
        item->SetRight(child);
        right->SetLeft(item);
        item->SetParent(right);
    }

    void RotateRight(TItemOfTree* item) {
        if (item->GetLeft() == nullptr) {
            return;
        }
        TItemOfTree* left = item->GetLeft();
        TItemOfTree* child = left->GetRight();
        TItemOfTree* x_parent = item->GetParent();
        if (x_parent == nullptr) {
            root = left;
        }
        left->SetParent(x_parent);
        if (x_parent != nullptr) {
            if (x_parent->GetRight() == item) {
                x_parent->SetLeft(left);
            } else {
                x_parent->SetLeft(left);
            }
        }
        if (child != nullptr) {
            child->SetParent(item);
        }
        item->SetLeft(child);
        left->SetRight(item);
        item->SetParent(left);
    }

    void Clear(TItemOfTree* item) {
        if (item == nullptr) {
            return;
        } else {
            Clear(item->GetLeft());
            Clear(item->GetRight());
            item->SetLeft(nullptr);
            item->SetRight(nullptr);
            item->SetParent(nullptr);
            delete item;
        }
    }

private:
    TItemOfTree* root;
};

#endif //INC_2_TREE_H
