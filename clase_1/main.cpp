#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
template <class T> class ASC {
public:
  bool operator()(T a, T b) { return a < b; }
};

template <class T, class O, int N = 10> class ListOrd {
private:
  int tam = N;
  int elem = 0;
  T Arr[N];
  O ord;

public:
  bool add(T e) {
    if (elem >= tam)
      return false;
    if (elem == 0) {
      *Arr = e;
      elem++;
      return true;
    }
    T *izq = Arr;
    T *der = Arr + elem - 1;
    T *centro;
    while (izq <= der) {
      centro = izq + (der - izq) / 2;
      if (ord(*centro, e)) {
        izq = centro + 1;
      } else {
        der = centro - 1;
      }
    }
    T *p = Arr + elem - 1;
    while (p >= izq) {
      *(p + 1) = *p;
      p--;
    }
    *izq = e;
    elem++;
    return true;
  }

  bool del(T e) {
    T *izq = Arr;
    T *der = Arr + elem - 1;
    T *centro;
    while (izq <= der) {
      centro = izq + (der - izq) / 2;
      if (*centro == e) {
        T *p = centro;
        for (; p < Arr + elem - 1; p++) {
          *p = *(p + 1);
        }
        elem--;
        return true;
      } else if (ord(*centro, e)) {
        izq = centro + 1;
      } else {
        der = centro - 1;
      }
    }
    return false;
  }

  void printarray() {
    for (T *p = Arr; p < Arr + elem; p++) {
      cout << *p << " ";
    }
  }
};
int main(int argc, char *argv[]) {
  srand(time(0));
  const int n = 10;
  ListOrd<int, ASC<int>, n> Lo;
  for (int i = 0; i < 10; i++) {
    Lo.add(rand() % 69);
  }
  cout << endl;
  Lo.printarray();
  int borrar;
  std::cout << "\nQue numero quieres borrar? : ";
  std::cin >> borrar;
  std::cout << (Lo.del(borrar) ? "\nEliminado correctamente\n"
                               : "\nEliminado incorrectamente\n")
            << std::endl;
  Lo.printarray();
  return 0;
}
