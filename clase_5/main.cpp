#include <iostream>
template <typename T> struct Node {
  T val;
  Node *next;
  Node(T v) : val(v), next(nullptr) {}
};
// regla general
template <typename T> struct Inicio {
  static constexpr T valor = T(1);
};
// especializacion
template <> struct Inicio<char> {
  static constexpr char valor = 'A';
};
template <typename T> class cList {
private:
  Node<T> *cola;
  int size_list;

public:
  cList(int n) : cola(nullptr), size_list(0) {
    T val = Inicio<T>::valor;
    for (int i = 0; i < n; i++, val++) {
      Node<T> *n_ptr = new Node<T>(val);
      if (size_list == 0) {
        cola = n_ptr;
        cola->next = cola;
      } else {
        n_ptr->next = cola->next;
        cola->next = n_ptr;
        cola = n_ptr;
      }
      size_list++;
    }
  }
  void kill(int k) {
    if (k <= 0 || size_list == 0)
      return;
    Node<T> *p = cola;
    while (size_list > 0) {
      for (int i = 0; i < k - 1; i++) {
        p = p->next;
      }
      Node<T> *tmp = p->next;
      if (tmp == cola) {
        cola = p;
      }
      T v = tmp->val;
      p->next = tmp->next;
      delete tmp;
      size_list--;
      if (size_list == 0)
        cola = nullptr;
      std::cout << v << "->";
    }
  }
  void print_lista() {
    if (size_list == 0)
      return;
    Node<T> *p = cola->next;
    do {
      std::cout << p->val << "->";
      p = p->next;
    } while (p != cola->next);
    std::cout << "\n";
  }
};
int main() {
  cList<char> mL(6);
  mL.print_lista();
  mL.kill(3);
  mL.print_lista();
  return 0;
}
