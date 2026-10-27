#pragma once
struct Node {
	int val;
	Node* left;
	Node* right;
	Node(int v) :val(v), left(0), right(0) {}
};
