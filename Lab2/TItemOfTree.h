//
// Created by shand on 15.04.2022.
//

#ifndef INC_2_TITEMOFTREE_H
#define INC_2_TITEMOFTREE_H

#include <string>

class TItemOfTree {
public:
    TItemOfTree(std::string &key,
               unsigned long long value,
               TItemOfTree* parent): parent(parent), left(nullptr), right(nullptr), balance(0),
                                          key(key), value(value) {}
    int GetBalance() {
        return this->balance;
    }

    void SetBalance(short balance) {
        this->balance = balance;
    }

    void IncrBalance() {
        balance ++;
    }

    void DecrBalance() {
        balance --;
    }

    TItemOfTree* GetParent() {
        return this->parent;
    }
    void SetParent(TItemOfTree* item) {
        this->parent = item;
    }
    TItemOfTree* GetLeft() {
        return this->left;
    }
    void SetLeft(TItemOfTree* item) {
        this->left = item;
    }
    TItemOfTree* GetRight() {
        return this->right;
    }
    void SetRight(TItemOfTree* item) {
        this->right = item;
    }
    std::string GetKey() {
        return this->key;
    }
    void SetKey(std::string key) {
        this->key = key;
    }
    int GetValue() {
        return this->value;
    }
    void SetValue(unsigned long long value) {
        this->value = value;
    }


    static void PrintItem(TItemOfTree* item) {
        if (item != nullptr) {
            std::cout << item->GetKey() << " -> " << item->GetValue() << std::endl;
        } else {
            std::cout << "Empty node" << std::endl;
        }
    }


    static void ChangeRoot(TItemOfTree* item) {
        std::string s = "a";
        TItemOfTree* new_item = new TItemOfTree(s, 456, nullptr);
        new_item->SetLeft(item->GetLeft());
        item->SetLeft(nullptr);
        new_item->SetRight(item->GetRight());
        item->SetRight(nullptr);
        new_item->SetParent(item->GetParent());
        item->SetParent(nullptr);
        item = new_item;
    }

private:
    std::string key;
    unsigned long long value;
    TItemOfTree* parent;
    TItemOfTree* left;
    TItemOfTree* right;
    short balance;
};


#endif //INC_2_TITEMOFTREE_H
