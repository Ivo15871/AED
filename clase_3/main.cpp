#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

std::vector<char> cambiar_postfija(char *palabra) {
  auto signo_operacion = [](char x) -> bool {
    switch (x) {
    case '+':
    case '-':
    case '*':
    case '/':
      return true;
    default:
      return false;
    }
  };

  auto precedencia = [](char x) -> int {
    if (x == '+' || x == '-')
      return 1;
    if (x == '*' || x == '/')
      return 2;
    return 0;
  };
  std::queue<char> mCola;
  std::stack<char> mPila;
  for (char *p = palabra; *p != '\0'; p++) {
    if (*p == '(') {
      mPila.push(*p);
    } else if (signo_operacion(*p)) {
      while (!mPila.empty() && mPila.top() != '(' &&
             precedencia(mPila.top()) >= precedencia(*p)) {
        mCola.push(mPila.top());
        mPila.pop();
      }
      mPila.push(*p);
    } else if (*p == ')') {
      while (mPila.top() != '(') {
        mCola.push(mPila.top());
        mPila.pop();
      }
      mPila.pop();
    } else {
      mCola.push(*p);
    }
  }

  while (!mPila.empty()) {
    mCola.push(mPila.top());
    mPila.pop();
  }

  std::vector<char> postfija;
  while (!mCola.empty()) {
    postfija.push_back(mCola.front());
    mCola.pop();
  }
  return postfija;
}

double operacion_postfija(std::vector<char> A) {
  auto signo_operacion = [](char x) -> bool {
    switch (x) {
    case '+':
    case '-':
    case '*':
    case '/':
      return true;
    default:
      return false;
    }
  };
  std::stack<double> mPila;

  for (auto letra : A) {
    if (!signo_operacion(letra)) {
      mPila.push(letra - '0');
    } else {
      double a = mPila.top();
      mPila.pop();
      double b = mPila.top();
      mPila.pop();

      if (letra == '+')
        mPila.push(b + a);
      else if (letra == '-')
        mPila.push(b - a);
      else if (letra == '*')
        mPila.push(b * a);
      else if (letra == '/')
        mPila.push(b / a);
    }
  }
  return mPila.top();
}

int main() {
  std::string s1;
  std::cout << "escribe tu notacion infija: ";
  std::cin >> s1;
  char notacion[100];
  int i = 0;
  for (; i < s1.length(); i++) {
    *(notacion + i) = s1[i];
  }
  *(notacion + i) = '\0';
  std::vector<char> post = cambiar_postfija(notacion);

  for (auto i : post) {
    std::cout << i;
  }
  std::cout << std::endl;

  std::cout << "======== sacando resultado de postfija ==================";
  std::cout << std::endl;
  std::cout << operacion_postfija(post);
  std::cout << std::endl;

  return 0;
}
