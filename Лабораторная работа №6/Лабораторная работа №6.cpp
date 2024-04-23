#include <iostream>
using namespace std;

void instruction() {
	cout << "1 - добавить элемент в дерево\n";
	cout << "2 - посчитать количество элементов в дереве\n";
	cout << "3 - проверить, содержится ли указанный элемент в дереве\n";
	cout << "4 - очистить дерево\n";
	cout << "5 - удалить указанный элемент из дерева\n";
	cout << "0 - завершение работы программы\n\n";
}

struct Node {
	int param = 0;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* up = nullptr;
};

struct Tree {
	int counting = 0;
	Node* root = nullptr;

	int count() { return counting; }

	Node* addElement(int value) {
		Node* node = new Node();
		node->param = value;
		counting++;
		return node;
	}

	void add(int value, Node* node = nullptr) {
		if (node == nullptr) {
			node = root;
			if (counting == 0) {
				root = addElement(value);
				return;
			}
		}

		if (value >= node->param) {
			if (node->right == nullptr) {
				node->right = addElement(value);
				node->right->up = node;
				return;
			}
			else { add(value, node->right); }
		}
		else {
			if (node->left == nullptr) {
				node->left = addElement(value);
				node->left->up = node;
				return;
			}
			else { add(value, node->left); }
		}
	}
	
	bool contains(int value, Node* node = nullptr) {
		if (node == nullptr) { 
			node = root;
			if (counting == 0) { return false; }
		}
		if (node->param == value) { return true; }
		if (value > node->param) {
			if (node->right == nullptr) { return false; }
			else { contains(value, node->right); }
		}
		else {
			if (node->left == nullptr) { return false; }
			else { contains(value, node->left); }
		}
	}

	int minimum(Node* node) {
		if (node->left == nullptr) { return node->param; }
		else { minimum(node->left); }
	}

	void remove(int value, Node* node = nullptr) {
		if (node == nullptr) {
			node = root;
			if (!contains(value)) { return; }
			if (counting == 1) {
				clear();
				return;
			}
		}
		if (value > node->param) { remove(value, node->right); }
		else if (value < node->param) { remove(value, node->left); }
		else {
			if (node->right != nullptr && node->left != nullptr) {
				node->param = minimum(node->right);
				remove(node->param, node->right);
			}
			else {
				if (node == root) {
					if (node->left == nullptr) { root = node->right; }
					else { root = node->left; }
					root->up = nullptr;
				}
				else if (node->left == nullptr) {
					if (node->up->left == node) { node->up->left = node->right; }
					else { node->up->right = node->right; }
				}
				else if (node->right == nullptr) {
					if (node->up->right == node) { node->up->right = node->left; }
					else { node->up->left = node->left; }
				}
				delete node;
				counting--;
			}
		}
	}

	void clear(Node* node = nullptr) {
		if (node == nullptr) { 
			node = root;
			if (counting == 0) { return; }
		}
		if (node->left != nullptr) { clear(node->left); }
		if (node->right != nullptr) { clear(node->right); }
		if (node == root) {
			root = nullptr;
			counting = 0;
		}
		delete node;
	}
};
int main() {
	system("chcp 1251>NULL");
	instruction();
	Tree tree;
	while (true) {
		cout << "\nВведите команду: ";
		int par;
		cin >> par;
		switch (par) {
		case 1:
			cout << "Введите число: ";
			cin >> par;
			tree.add(par);
			break;
		case 2:
			cout << "Количество элементов: " << tree.count() << endl;
			break;
		case 3:
			cout << "Введите число: ";
			cin >> par;
			if (tree.contains(par)) { cout << "Число содержится в дереве\n"; }
			else { cout << "Число не содержится в дереве\n"; }
			break;
		case 4:
			tree.clear();
			break;
		case 5:
			cout << "Введите число: ";
			cin >> par;
			tree.remove(par);
			break;
		case 0:
			return 0;
		default:
			cout << "Некорректная команда!";
		}
	}
}
