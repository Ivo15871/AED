#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <optional>
#include "cTree.h"
#include "graficarArbol.h"
using namespace std;
class cTree {
private:
	Node* root;
public:
	cTree():root(0){}
	void armar_suma(int* A, int n) {
		vector<Node*> nivel;
		for (int* p = A;p < A + n;p++) {
			nivel.push_back(new Node(*p));
		}
		while (nivel.size() > 1) {
		vector<Node*> prox_nivel;
			for (int i = 0;i < nivel.size();i += 2) {
				Node* l = nivel[i];
				Node* r = nivel[i+1];
				Node* padre = new Node(l->val + r->val);
				padre->left = l;
				padre->right = r;
				prox_nivel.push_back(padre);
			}
			nivel = prox_nivel;
		}
		root = nivel[0];
	}
	void preorder(Node* p) {
		if (!p) return;
		cout << p->val << " ";
		preorder(p->left);
		preorder(p->right);
	}
	void print() {
		preorder(root);
	}
	Node* getroot() { return root; }
};
int main() { 
	const int n = 8;
	int A[n] = { 1,3,8,4,5,7,15,21 };	
	cTree tree;
	tree.armar_suma(A, n);
	dibujarTotal(tree.getroot());
	return 0; 
}