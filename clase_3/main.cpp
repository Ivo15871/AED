#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

std::vector<char> cambiar_postfija(std::string &palabra) {
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

  for (int i = 0; i < palabra.length(); i++) {
    if (palabra[i] == '(') {
      mPila.push(palabra[i]);
    } else if (signo_operacion(palabra[i])) {
      while (!mPila.empty() && mPila.top() != '(' &&
             precedencia(mPila.top()) >= precedencia(palabra[i])) {
        mCola.push(mPila.top());
        mPila.pop();
      }
      mPila.push(palabra[i]);
    } else if (palabra[i] == ')') {
      while (mPila.top() != '(') {
        mCola.push(mPila.top());
        mPila.pop();
      }
      mPila.pop();
    } else {
      mCola.push(palabra[i]);
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

  std::vector<char> post = cambiar_postfija(s1);

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
