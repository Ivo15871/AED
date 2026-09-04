#include <iostream>
struct div3 {
  bool operator()(int a) { return a % 3 == 0; }
};
template <typename O> class util {
private:
  O condicion;

public:
  void split(int *ini, int *fin) {
    int *q = ini;
    for (int *p = ini; p < fin; p++) {
      if (condicion(*p)) {
        int tmp = *p;
        int *k = p;
        while (k > q) {
          *k = *(k - 1);
          k--;
        }
        *q = tmp;
        q++;
      }
    }
  }
  void merge(int *ini, int *med, int *fin) {
    while (ini < med && med < fin) {
      if (*med < *ini) {
        int tmp = *med;
        int *p = med;
        for (; p > ini; p--) {
          *p = *(p - 1);
        }
        *p = tmp;
        med++;
      }
      ini++;
    }
  }
  void alternative_merge(int *ini, int *med, int *fin) {
    int n = fin - ini;
    auto gap_calculate = [](int x) -> int {
      if (x <= 1)
        return 0;
      return (x / 2) + x % 2;
    };
    auto cambio = [](int *a, int *b) {
      int tmp = *a;
      *a = *b;
      *b = tmp;
    };
    int gap = gap_calculate(n);
    while (gap > 0) {
      int *p = ini;
      int *q = ini + gap;
      while (q < fin) {
        if (*p > *q) {
          cambio(p, q);
        }
        p++;
        q++;
      }
      gap = gap_calculate(gap);
    }
  }
  void merge_swap(int *ini, int *med, int *fin) {
    auto cambio = [](int *a, int *b) {
      int tmp = *a;
      *a = *b;
      *b = tmp;
    };
    while (ini < med) {
      if (*ini > *med) {
        cambio(ini, med);
        int *p = med;
        while (p < fin - 1 && *p > *(p + 1)) {
          cambio(p, p + 1);
          p++;
        }
      }
      ini++;
    }
  }
};
void printarray(int *A, int n) {
  for (int *p = A; p < A + n; p++)
    std::cout << *p << " ";
}
int main() {
  // Ejercicio merge main

  const int n = 10;
  int array[n] = {1, 4, 7, 8, 21, 3, 4, 5, 6, 9};
  printarray(array, n);
  util<int> miobj;
  miobj.merge_swap(array, array + 5, array + 10);
  std::cout << "\n Modificando el array\n";
  printarray(array, n);

  // Ejercicio split
  //
  /*
  const int n = 11;
  int array[n] = {3, 2, 1, 5, 9, 7, 11, 8, 33, 25, 4};
  util<div3> miobj;
  printarray(array, n);
  std::cout << "\n Seleccionando multiplos de 3\n";
  miobj.split(array, array + n);
  printarray(array, n);
   */
  return 0;
}
