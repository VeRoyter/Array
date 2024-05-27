#pragma once
#ifndef CONTEINER_FROM_VOV_H_INCLUDED
#define CONTEINER_FROM_VOV_H_INCLUDED

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next = nullptr;
};

class Container {
private:
    Node* head;
public:
    Container() : head(nullptr) {}

    Container(const Container& other) {
        head = nullptr;


        Node* current = other.head;
        while (current != nullptr) {
            Node* newNode = new Node;
            newNode->data = (current->data);
            if (head == nullptr) {
                head = newNode;
            }
            else {
                Node* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
            current = current->next;
        }
    }

    void Push(int n) {
        Node* newNode = new Node{ n };
        if (!head) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    int size() {
        int count = 0;
        Node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    int max_size()
    {
        int max_const = head->data;
        Node* current = head->next;

        while (current != nullptr) {
            if (current->data > max_const) {
                max_const = current->data;
            }
            current = current->next;
        }

        return max_const;
    }


    bool empty() const {
        return head == nullptr;
    }

    bool operator==(Container& other) {
        Node* current1 = head;
        Node* current2 = other.head;
        while (current1 && current2) {
            if (current1->data != current2->data) return false;
            current1 = current1->next;
            current2 = current2->next;
        }
        return !current1 && !current2;
    }

    bool operator!=(Container& other) {
        return !(*this == other);
    }

    void Print()
    {
        Node* current;
        current = this->head;
        if (current == nullptr) {
            cout << "Clear" << endl;
        }
        else {
            do {
                if (current != nullptr)
                    cout << current->data << "   ";
                current = current->next;
            } while (current != nullptr);
        }
    }

    void Find(int n) {
        Node* current;
        int b = 1;
        current = this->head;

        if (current == nullptr)
            cout << "end of list" << endl;
        else {
            do {
                if (current->data == n) {
                    cout << b << endl;
                }
                b++;
                current = current->next;
            } while (current != nullptr);

        }
        if (b == 1)
            cout << "No such number" << endl;
    }

    void Deletel() {
        Node* current;
        current = this->head;
        if (current != nullptr)
            while (current->next != nullptr) {
                if (current->next->next == nullptr) {
                    delete current->next;
                    current->next = nullptr;
                    current = this->head;
                }
                else {
                    current = current->next;
                }
            }
        delete current;
        this->head = nullptr;
    }

    void Swap(Container head2) {
        while (this->head != NULL && head2.head != NULL) {
            int temp = this->head->data;
            this->head->data = head2.head->data;
            head2.head->data = temp;
            this->head = this->head->next;
            head2.head = head2.head->next;
        }
    }

    Container& operator=(Container& other) {
        Node* current;
        this->~Container();
        head = nullptr;
        current = other.head;
        while (current != nullptr) {
            Node* newNode = new Node;
            newNode->data = (current->data);
            if (head == nullptr) {
                head = newNode;
            }
            else {
                Node* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
            current = current->next;
        }
        return *this;
    }

    ~Container() {
        Node* current;
        current = this->head;
        if (current != nullptr)
            while (current->next != nullptr) {
                if (current->next->next == nullptr) {
                    delete current->next;
                    current->next = nullptr;
                    current = this->head;
                }
                else {
                    current = current->next;
                }
            }
        delete current;
        this->head = nullptr;
    }

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Node;
        using pointer = Node*;
        using reference = Node&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        void Swap(Iterator& other) {
            pointer temp = this->m_ptr;
            this->m_ptr = other.m_ptr;
            other.m_ptr = temp;
        }

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        Iterator& operator++() {
            if (m_ptr) {
                do {
                    m_ptr = m_ptr->next;
                } while (m_ptr && (*m_ptr).data % 3 != 0);
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }

    private:
        pointer m_ptr;
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

void Swap(Container head1, Container head2) {
    head1.Swap(head2);
}

#endif // CONTEINER_FROM_VOV_H_INCLUDED
