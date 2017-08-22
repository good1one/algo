#include <utility>
#include <iostream>


struct Node {
    int * val;
    Node * prev;
    Node * next;

    // Constructors
    //.....................................
    Node()
            : prev(nullptr)
            , val(nullptr)
            , next(nullptr)
    {}

    Node(Node * p, int * v, Node * n)
            : prev(p)
            , val(v)
            , next(n)
    {}

    // Operator ++ --  *
    //.....................................
    Node& operator ++() {
        *this =  *(this->next);
        return *this;
    }

    Node& operator --() {
        *this = *(this->prev);
        return *this;
    }

    int& operator * () {
        return *(this->val);
    }

    // Compare
    //.....................................
    bool operator == (const Node& other) const {
        return (prev == other.prev && val == other.val && next == other.next);
    }

    bool operator != (const Node& other) const {
        return !(*this == other);
    }
};


class List {
private:
    size_t sz;
    Node * head;
    Node * back;

    void Insert(Node * p, int other, Node * n) {
        auto tmp = new Node(p, new int(other), n);
        p->next = tmp;
        n->prev = tmp;
        tmp = nullptr;
        ++sz;
    }

    void Delete(Node * prev, Node * cur, Node * next) {
        prev->next = next;
        next->prev = prev;

        delete cur->val;
        delete cur;
        --sz;
    }

public:
    // Constructors
    //.....................................
    List() {
        head = new Node();
        back = new Node();

        head->next = back;
        back->prev = head;
        sz = 0;
    }

    // Push/pop + front/end
    //.....................................
    void push_front(int other) {
        Insert(head, other, head->next);
    }

    void push_back(int other) {
        Insert(back->prev, other, back);
    }

    void pop_front() {
        Delete(head, head->next, head->next->next);
    }

    void pop_back() {
        Delete(back->prev->prev, back->prev, back);
    }

    // Iterators
    //.....................................
    Node& begin() {
        return *head->next;
    }

    Node& end() {
        return *back;
    }

    // Size
    //.....................................
    size_t size() const {
        return sz;
    }

    // Destructors
    //.....................................
    ~List() {
        size_t tmp = sz;
        for (size_t i = 0; i < tmp; ++i) {
            this->pop_back();
        }
        delete head;
        delete back;
    }
};


int main() {
    List l;
    l.push_back(1);
    std::cout << *l.begin();
}

