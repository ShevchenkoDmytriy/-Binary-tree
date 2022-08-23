#include <iostream>
using namespace std;


class tree_elem
{
public:
	int m_date;
	tree_elem* m_left;
	tree_elem* m_right;
	tree_elem(int val)
	{
		m_left = nullptr;
		m_right = nullptr;
		m_date = val;
	}
};


class binary_tree
{
private:
	tree_elem* m_root;
	int m_size;



public:
	binary_tree(int key) {
		m_root = new tree_elem(key);
		m_size = 1;
	}
	~binary_tree() {
		delete_tree(m_root);
	}
	void delete_tree(tree_elem* curr) {
		if (curr)
		{
			delete_tree(curr->m_left);
			delete_tree(curr->m_right);
			delete curr;
		}
	}
	void print() {
		print_tree(m_root);
		cout << endl;
	}
	void print_tree(tree_elem* curr) {
		if (curr)
		{
			print_tree(curr->m_left);
			cout << curr->m_date << " ";
			print_tree(curr->m_right);
		}
	}
	bool find(int key) {

		tree_elem* curr = m_root;
		while (curr && curr->m_date != key)
		{
			if (curr->m_date > key)
				curr = curr->m_left;
			else
				curr = curr->m_right;
		}
		return curr != NULL;

	}

	void insert(int key) {
		tree_elem* curr = m_root;
		while (curr && curr->m_date != key)
		{
			if (curr->m_date > key && curr->m_left == NULL)
			{
				curr->m_left = new tree_elem(key);
				++m_size;
				return;
			}
			if (curr->m_date < key && curr->m_left == NULL)
			{
				curr->m_right = new tree_elem(key);
				++m_size;
				return;
			}
			if (curr->m_date > key)
				curr = curr->m_left;
			else
				curr = curr->m_right;

		}
	}
	int size() {
		return m_size;
	}
	void erase(int key) {
		tree_elem* curr = m_root;
		tree_elem* parent = NULL;

		while (curr && curr->m_date != key)
		{
			parent = curr;
			if (curr->m_date > key)
			{
				curr = curr->m_left;
			}
			else
			{
				curr = curr->m_right;
			}
		}

		if (!curr)
			return;
		if (curr->m_left == NULL)
		{
			if (parent && parent->m_left == curr)
				parent->m_left = curr->m_right;
			if (parent && parent->m_right == curr)
				parent->m_right = curr->m_right; //
			--m_size;
			delete curr;
			return;
		}
		if (curr->m_right == NULL)
		{
			if (parent && parent->m_left == curr)
				parent->m_left = curr->m_left;
			if (parent && parent->m_right == curr)
				parent->m_right = curr->m_left; //
			--m_size;
			delete curr;
			return;
		}
		tree_elem* replace = curr->m_right;
		while (replace->m_left)
			replace = replace->m_left;
		int replace_value = replace->m_date;
		erase(replace_value);
		curr->m_date = replace_value;
	}
};


int main() {
	binary_tree l(10);
	l.insert(11);
	l.insert(5);
	l.insert(9);
	l.print();
	l.erase(5);
	l.print();
	cout << l.size();
}