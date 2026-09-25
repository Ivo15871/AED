#include <iostream>
template <typename T> struct node {
  T valor;
  node *siguiente;
  node(T v) : valor(v), siguiente(nullptr) {}
};
template <typename T> class cList {
private:
  node<T> *head;
  int num_elementos;

public:
  cList() : head(nullptr), num_elementos(0) {}
  void push_back(T v) {
    node<T> **p = &head;
    while (*p) {
      p = &(*p)->siguiente;
    }
    node<T> *q = new node<T>(v);
    *p = q;
    num_elementos++;
  }
  void print() {
    node<T> **p = &head;
    while (*p) {
      std::cout << (*p)->valor << "-->";
      p = &(*p)->siguiente;
    }
    std::cout << "null";
    std::cout << std::endl;
  }
  node<T> *&get_head() { return head; }
  ~cList() {
    node<T> *p = head;
    while (p) {
      node<T> *tmp = p;
      p = p->siguiente;
      delete tmp;
    }
  }
};
template <typename T> void merge_listas(node<T> *&h1, node<T> *&h2) {
  // node<T> *nueva_cabeza = (h1->valor > h2->valor) ? (h1) : h2;
  node<T> *h1_copia = h1;
  node<T> *h2_copia = h2;
  node<T> **p;
  if (h1->valor < h2->valor) {
    p = &h1;
    h2 = nullptr;
  } else {
    p = &h2;
    h1 = nullptr;
  }
  while (h1_copia && h2_copia) {
    if (h1_copia->valor < h2_copia->valor) {
      *p = h1_copia;
      p = &(*p)->siguiente;
      h1_copia = h1_copia->siguiente;
    } else {
      *p = h2_copia;
      p = &(*p)->siguiente;
      h2_copia = h2_copia->siguiente;
    }
  }
  if (h1_copia) {
    *p = h1_copia;
  }
  if (h2_copia) {
    *p = h2_copia;
  }
}
template <typename T> void print_merge(node<T> *head) {
  node<T> **p = &head;
  while (*p) {
    std::cout << (*p)->valor << "-->";
    p = &(*p)->siguiente;
  }
  std::cout << std::endl;
}
int main() {
  cList<int> l1;
  l1.push_back(34);
  l1.push_back(67);
  l1.push_back(89);
  std::cout << "--------Lista 1--------\n";
  l1.print();

  cList<int> l2;
  l2.push_back(2);
  l2.push_back(35);
  l2.push_back(69);
  std::cout << "--------Lista 2--------\n";
  l2.print();

  std::cout << "\n--------Listas despues del merge--------\n\n";
  merge_listas(l1.get_head(), l2.get_head());
  std::cout << "--------Lista 1--------\n";
  l1.print();
  std::cout << "--------Lista 2--------\n";
  l2.print();
  return 0;
}
