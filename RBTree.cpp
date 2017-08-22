#include <iostream>
#include <vector>
#include <memory>


template <typename T>
struct Node {
    T val;

    Node<T> * r = nullptr;   // Right
    Node<T> * l = nullptr;   // Left
    Node<T> * p = nullptr;   // Parent

    char color = 'R';     // Color | Red by default
};


template <typename T>
class RBTree {
private:
    // Grandparent/Uncle
    //.....................................
    Node<T> * grandparent(Node<T> * n) {
        if ((n != nullptr) && (n->p != nullptr))
            return n->p->p;
        else
            return nullptr;
    }

    Node<T> * uncle(Node<T> * n) {
        Node<T> * g = grandparent(n);
        if (g == nullptr)
            return nullptr;
        if (n->p == g->l)
            return g->r;
        else
            return g->l;
    }

    // Rotate right/left
    //.....................................
    void rotate_left(Node<T> * n) {
        Node<T> * pivot = n->r;

        pivot->p = n->p;
        if (n->p != nullptr) {
            if (n->p->l == n)
                n->p->l = pivot;
            else
                n->p->r = pivot;
        } else {
            head = pivot;
        }

        n->r = pivot->l;
        if (pivot->l != nullptr)
            pivot->l->p = n;

        n->p = pivot;
        pivot->l = n;
    }

    void rotate_right(Node<T> * n) {
        Node<T> * pivot = n->l;

        pivot->p = n->p;
        if (n->p != nullptr) {
            if (n->p->l == n)
                n->p->l = pivot;
            else
                n->p->r = pivot;
        } else {
            head = pivot;
        }

        n->l = pivot->r;
        if (pivot->r != nullptr)
            pivot->r->p = n;

        n->p = pivot;
        pivot->r = n;
    }

    // Insert cases
    //.....................................
    void insert_case5(Node<T> * n) {
        Node<T> * g = grandparent(n);

        n->p->color = 'B';
        g->color = 'R';
        if ((n == n->p->l) && (n->p == g->l)) {
            rotate_right(g);
        } else {
            rotate_left(g);
        }
    }

    void insert_case4(Node<T> * n) {
        Node<T> * g = grandparent(n);

        if ((n == n->p->r) && (n->p == g->l)) {
            rotate_left(n->p);
            n = n->l;
        } else if ((n == n->p->l) && (n->p == g->r)) {
            rotate_right(n->p);
            n = n->r;
        }
        insert_case5(n);
    }

    void insert_case3(Node<T> * n) {
        Node<T> * u = uncle(n);
        Node<T> * g;

        if ((u != nullptr) && (u->color == 'R') && (n->p->color == 'R')) {
            n->p->color = 'B';
            u->color = 'B';
            g = grandparent(n);
            g->color = 'R';
            insert_case1(g);
        } else {
            insert_case4(n);
        }
    }

    void insert_case2(Node<T> * n) {
        if (n->p->color == 'B')
            return;
        else
            insert_case3(n);
    }

    void insert_case1(Node<T> * n) {
        if (n->p == nullptr)
            n->color = 'B';
        else
            insert_case2(n);
    }

    // Print RBTree
    //.....................................
    void RecursiveOutNode(Node<T> * n) {
        if (n == nullptr) return;

        RecursiveOutNode(n->l);
        std::cout << n->val << ' ';
        if (n->l != nullptr) {
            std::cout << n->l->val << ' ';
        } else {
            std::cout << "null" << ' ';
        }

        if (n->r != nullptr) {
            std::cout << n->r->val << ' ';
        } else {
            std::cout << "null" << ' ';
        }
        std::cout << n->color << '\n';
        RecursiveOutNode(n->r);
    }
public:
    Node<T> * head = nullptr;
    size_t sz = 0;

    // Bin search
    //.....................................
    bool bin_search(T value, Node<T> * n) {
        if (n == nullptr) return 0;

        if (value < n->val) return bin_search(value, n->l);
        if (value > n->val) return bin_search(value, n->r);
        return 1;
    }

    // Insert Node
    //.....................................
    void insert_node(long long object) {
        ++sz;

        Node<T> * tmp = head;
        if (head == nullptr) {
            head = new Node<T>();
            head->val = object;
            head->color = 'B';
            return;
        }

        Node<T> * p;
        while (tmp != nullptr) {
            p = tmp;
            if (object < tmp->val) {
                tmp = tmp->l;
            } else if (object > tmp->val) {
                tmp = tmp->r;
            } else if (object == tmp->val) {
                return;
            }
        }

        tmp = new Node<T>();
        tmp->val = object;
        tmp->p = p;
        if (object < p->val) {
            p->l = tmp;
        } else if (object > p->val) {
            p->r = tmp;
        }

        insert_case1(tmp);
        return;
    }

    // Print RBTree
    //.....................................
    void out() {
        RecursiveOutNode(head);
    }
};


int main() {
    long long CommandAmount = 0;
    std::cin >> CommandAmount;

    RBTree<long long> g;

    long long cmd, val;
    for (long long i = 0; i != CommandAmount; ++i) {
        std::cin >> cmd >> val;

        if (cmd == 0) {
            g.insert_node(val);
        } else if (cmd == 1) {
            if (g.bin_search(val, g.head))
                std::cout << "Yes" << '\n';
            else
                std::cout << "No" << '\n';
        }
    }

    std::cout << g.sz << '\n';
    g.out();
}

