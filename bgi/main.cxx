#include "graphics.h"
#include <iostream>
#include <string>
using namespace std;

void Circle(int xx, int yy);
void Line(int xx, int yy, int fact2);
int io_bgi(int xx, int yy, char input[]);
void click_handler(int xx, int yy);
void bgi();
void menu();

class node_bst
{
public:
	int value;
	node_bst* left, * right;
	node_bst()
	{
		value = 0;
		left = right = nullptr;
	}
};

class bst
{
private:
	node_bst* root;

	void bgi_display(node_bst* n, int xx, int yy, int fact2, char* c)
	{
		if (n)
		{
			bgi_display(n->left, xx - fact2, yy + (60 + 25), fact2 / 2, c);
			Circle(xx, yy);
			itoa(n->value, c, 10);
			moveto(xx, yy + 5);
			settextjustify(CENTER_TEXT, VCENTER_TEXT);
			settextstyle(COMPLEX_FONT, HORIZ_DIR, NORM_WIDTH);
			outtext(c);
			if (n->left)
				Line(xx, yy, xx - fact2);
			if (n->right)
				Line(xx, yy, xx + fact2);
			bgi_display(n->right, xx + fact2, yy + (60 + 25), fact2 / 2, c);
		}
	}

	void searched_node_axes(node_bst* n, int xx, int yy, int fact2, int searchvalue, int& searchx, int& searchy)
	{
		if (n)
		{
			searched_node_axes(n->left, xx - fact2, yy + 85, fact2 / 2, searchvalue, searchx, searchy);
			if (n->value == searchvalue)
			{
				searchx = xx;
				searchy = yy;
				return;
			}
			searched_node_axes(n->right, xx + fact2, yy + 85, fact2 / 2, searchvalue, searchx, searchy);
		}
	}

	void deletenode(int num, node_bst*& n)
	{
		if (!n)
		{
			char* c1 = new char[10];
			itoa(num, c1, 10);
			moveto(100, 90);
			outtext(c1);
			outtext(" does not exist!");
			delay(1000);
		}
		else if (num == n->value)
			if (n->left && n->right)
			{
				node_bst* temp = n->right;
				while (temp->left)
				{
					temp = temp->left;
				}
				n->value = temp->value;
				deletenode(temp->value, n->right);
			}
			else
			{
				deletep(n);

				char* c1 = new char[10];
				itoa(num, c1, 10);
				moveto(100, 90);
				outtext(c1);
				outtext(" has been deleted!");
				delay(1000);
			}
		else if (num < n->value)
			deletenode(num, n->left);
		else
			deletenode(num, n->right);
	}

	void deletep(node_bst*& n)
	{
		node_bst* del = nullptr;
		if (!n->left) {
			del = n;
			n = n->right;
		}
		else if (!n->right) {
			del = n;
			n = n->left;
		}
		delete del;
		del = nullptr;
	}

	void finding_height(node_bst* n, int count, int& h)
	{
		if (n)
		{
			finding_height(n->left, count + 1, h);
			if (count > h)
				h = count;
			finding_height(n->right, count + 1, h);
			if (count > h)
				h = count;
			count = count - 1;
		}
	}

	void insert(node_bst*& n, int num)
	{
		if (n)
		{
			if (num < n->value)
				insert(n->left, num);
			else if (num > n->value)
				insert(n->right, num);
			else
			{
				char* c1 = new char[10];
				itoa(num, c1, 10);
				moveto(100, 90);
				outtext(c1);
				outtext(" already exist in tree!");
				delay(1000);
			}
		}
		else
		{
			n = new node_bst();
			n->value = num;
			n->left = n->right = nullptr;
		}
	}

public:
	bst() { root = nullptr; }

	void insertnode(int num)
	{
		insert(root, num);
	}

	node_bst* search(int value, int& xx, int& yy)
	{
		node_bst* n = root;
		int h = 0;
		finding_height(root, 0, h);
		if (h == 1)
			h = 2;
		searched_node_axes(root, (getwindowwidth() - 6) / 2, ((getwindowheight() - 29) / 6), ((h * 10) * (h + 1)), value, xx, yy);
		while (n)
		{
			if (value == n->value)
				return n;
			else if (value < n->value)
				n = n->left;
			else
				n = n->right;
		}
		return nullptr;
	}

	void display()
	{
		if (root)
		{
			int h = 0;
			finding_height(root, 0, h);
			int xx = 0, yy = 0;
			xx = (getwindowwidth() - 6) / 2;
			yy = ((getwindowheight() - 29) / 6);
			char c[10];
			if (h == 1)
				h = 2;
			bgi_display(root, xx, yy, ((h * 10) * (h + 1)), c);
		}
		else
		{
			moveto(100, 90);
			outtext("Tree is empty!");
			delay(1000);
		}
	}

	void deleten(int num)
	{
		if (!root)
		{
			moveto(100, 90);
			outtext("Tree is empty!");
			delay(1000);
		}
		else
		{
			deletenode(num, root);
		}
	}
};

class node_avl
{
public:
	int key;
	node_avl* left, * right;
	bst bst_node;
	node_avl()
	{
		key = -1;
		left = right = nullptr;
	}
};

class avl
{
private:
	node_avl* root;

	void bgi_display(node_avl* n, int xx, int yy, int fact2, char* c)
	{
		if (n)
		{
			bgi_display(n->left, xx - fact2, yy + (60 + 25), fact2 / 2, c);
			Circle(xx, yy);
			itoa(n->key, c, 10);
			moveto(xx, yy + 5);
			settextjustify(CENTER_TEXT, VCENTER_TEXT);
			settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
			outtext(c);
			if (n->left)
				Line(xx, yy, xx - fact2);
			if (n->right)
				Line(xx, yy, xx + fact2);
			bgi_display(n->right, xx + fact2, yy + (60 + 25), fact2 / 2, c);
		}
	}

	void searched_node_axes(node_avl* n, int xx, int yy, int fact2, int searchvalue, int& searchx, int& searchy)
	{
		if (n)
		{
			searched_node_axes(n->left, xx - fact2, yy + 85, fact2 / 2, searchvalue, searchx, searchy);
			if (n->key == searchvalue)
			{
				searchx = xx;
				searchy = yy;
				return;
			}
			searched_node_axes(n->right, xx + fact2, yy + 85, fact2 / 2, searchvalue, searchx, searchy);
		}
	}

	void finding_height(node_avl* n, int count, int& h)
	{
		if (n)
		{
			finding_height(n->left, count + 1, h);
			if (count > h)
				h = count;
			finding_height(n->right, count + 1, h);
			if (count > h)
				h = count;
			count = count - 1;
		}
	}

	void check_avl(int value)
	{
		node_avl* temp = root;
		node_avl* n = nullptr;
		node_avl* prev = nullptr;
		node_avl* temp1 = nullptr;
		int bf = 0;
		int bf1 = 0;
		while (temp)
		{
			bf1 = balance_fact1(temp);

			if (bf1 < -1 || bf1 > 1)
			{
				bf = bf1;
				prev = temp1;
				n = temp;
			}

			temp1 = temp;
			if (value < temp->key)
				temp = temp->left;
			else if (value > temp->key)
				temp = temp->right;
			else
				break;
		}

		if (bf < -1)
		{
			// left, right,left
			if (value > n->right->key)
			{
				// left
				if (prev)
					prev->right = rotate_left(n);
				else
					root = rotate_left(n);
			}
			else if (value < n->right->key)
			{
				// right,left
				if (prev)
					prev->right = rotate_right_left(n);
				else
					root = rotate_right_left(n);
			}
		}
		else if (bf > 1)
		{
			// right, left,right
			if (value < n->left->key)
			{
				// right
				if (prev)
					prev->left = rotate_right(n);
				else
					root = rotate_right(n);
			}

			else if (value > n->left->key)
			{
				// left,right
				if (prev)
					prev->left = rotate_left_right(n);
				else
					root = rotate_left_right(n);
			}
		}

	}

	int balance_fact1(node_avl* n)
	{
		if (n)
		{
			int hl = 0;
			int hr = 0;
			if (n->left)
				finding_height(n->left, 0, hl);
			else
				hl = -1;
			if (n->right)
				finding_height(n->right, 0, hr);
			else
				hr = -1;
			return (hl - hr);
		}
		return -999;
	}

	node_avl* rotate_left(node_avl*& n)
	{
		node_avl* t1 = n;
		n = t1->right;
		node_avl* t2 = n->left;
		n->left = t1;
		t1->right = t2;
		return n;
	}

	node_avl* rotate_right(node_avl*& n)
	{
		node_avl* t1 = n;
		n = t1->left;
		node_avl* t2 = n->right;
		n->right = t1;
		t1->left = t2;
		return n;
	}

	node_avl* rotate_left_right(node_avl* n)
	{
		node_avl* t1 = n->left;
		node_avl* t2 = t1->right->left;
		n->left = t1->right;
		n->left->left = t1;
		t1->right = t2;
		return rotate_right(n);
	}

	node_avl* rotate_right_left(node_avl* n)
	{
		node_avl* t1 = n->right;
		node_avl* t2 = t1->left->right;
		n->right = t1->left;
		n->right->right = t1;
		t1->left = t2;
		return rotate_left(n);
	}

	void insert(node_avl*& n, int num)
	{
		if (n)
		{
			if (num < n->key)
				insert(n->left, num);
			else if (num > n->key)
				insert(n->right, num);
			else
			{
				char* c1 = new char[10];
				itoa(num, c1, 10);
				moveto(100, 90);
				outtext(c1);
				outtext(" already exist in tree!");
				delay(1000);
			}
		}
		else
		{
			n = new node_avl();
			n->key = num;
			n->left = n->right = nullptr;
		}
	}

public:
	avl()
	{
		root = nullptr;
	}

	void insert_bst(int value, int hash_key)
	{
		node_avl* n = search(hash_key);
		if (!n)
		{
			insertnode(hash_key);
			n = search(hash_key);
		}
		n->bst_node.insertnode(value);
	}

	void insertnode(int value)
	{
		insert(root, value);
		check_avl(value);
	}

	void display()
	{
		if (root)
		{
			int h = 0;
			finding_height(root, 0, h);
			if (h == 1)
				h = 2;
			char c[5];
			moveto(100, 90);
			outtext("AVL:");
			bgi_display(root, (getwindowwidth() - 6) / 2, ((getwindowheight() - 29) / 6), ((h * 10) * (h + 1)), c);
		}
	}

	node_bst* search_bst(int value, int hash_key)
	{
		int xx = 0, yy = 0;
		int xx2 = 0, yy2 = 0;
		node_avl* n = search(hash_key);
		int h = 0;
		finding_height(root, 0, h);
		if (h == 1)
			h = 2;
		searched_node_axes(root, (getwindowwidth() - 6) / 2, ((getwindowheight() - 29) / 6), ((h * 10) * (h + 1)), hash_key, xx, yy);

		if (n)
		{
			if (n->bst_node.search(value, xx2, yy2))
			{
				display();
				setcolor(COLOR(255, 128, 213));
				setlinestyle(0, 1, THICK_WIDTH);
				circle(xx, yy, 25);
				delay(1000);
				cleardevice();
				menu();
				n->bst_node.display();
				setcolor(COLOR(255, 128, 213));
				setlinestyle(0, 1, THICK_WIDTH);
				circle(xx2, yy2, 25);
			}
			return n->bst_node.search(value, xx2, yy2);
		}
		else
			return nullptr;
	}

	node_avl* search(int value)
	{
		node_avl* n = root;
		while (n)
		{
			if (value == n->key)
				return n;
			else if (value < n->key)
				n = n->left;
			else
				n = n->right;
		}
		return nullptr;
	}

	void del_bst(int value, int hash_key)
	{
		node_avl* n = search(hash_key);
		if (n)
			n->bst_node.deleten(value);
		else
		{
			moveto(100, 90);
			outtext(" AVL key not found!");
			delay(1000);
		}
	}
};

class hashing
{
private:
	avl hash_table;

	int hash(int value)
	{
		return value % 10;
	}

public:

	void display(int check)
	{
		if (check == 0)       // 0 for avl
			hash_table.display();
		else if (check == 1)  // 1 for bst
		{
			moveto(100, 90);
			outtext("Enter key of AVL tree from 0 - 9 to see its corresponding bst:  ");
			char input[5] = { '\0' };
			io_bgi(1176, 30, input);
			if (input[1] != '\0')
			{;
				moveto(100, 90);
				outtext("Invalid Key input!");
				delay(1000);
			}

			else
			{
				check = (int(input[0]) - 48);
				node_avl* n = hash_table.search(check);
				if (n)
				{
					n->bst_node.display();
					delay(3000);
				}
				else
				{
					moveto(100, 90);
					outtext("Invalid Key input!");
					delay(1000);
				}
			}
		}
	}

	void insert()
	{
		char input[5] = { '\0' };
		if (io_bgi(180, 30, input) == 1)
		{
			int value = 0;
			int factor = 1;
			int i = 0;
			for (i = 0; i < 4; i++)
			{
				if (input[i] != '\0')
				{
					factor = factor * 10;
				}
			}
			factor = factor / 10;
			i = 0;
			while (factor > 0)
			{
				value = value + ((int(input[i]) - 48) * factor);
				factor = factor / 10;
				i++;
			}
			hash_table.insert_bst(value, hash(value));
		}
	}

	void search()
	{
		char input[5] = { '\0' };
		if (io_bgi(460, 30, input) == 1)
		{
			int value = 0;
			int factor = 1;
			int i = 0;
			for (i = 0; i < 4; i++)
			{
				if (input[i] != '\0')
				{
					factor = factor * 10;
				}
			}
			factor = factor / 10;
			i = 0;
			while (factor > 0)
			{
				value = value + ((int(input[i]) - 48) * factor);
				factor = factor / 10;
				i++;
			}
			if (hash_table.search_bst(value, hash(value)))
			{
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				settextjustify(LEFT_TEXT, TOP_TEXT);
				setcolor(LIGHTGRAY);
				char* c1 = new char[10];
				itoa(value, c1, 10);
				moveto(100, 90);
				outtext(c1);
				outtext(" Found!");
				delay(2000);
			}
			else
			{
				char* c1 = new char[10];
				itoa(value, c1, 10);
				moveto(100, 90);
				outtext(c1);
				outtext(" does not exist in tree!");
				delay(1000);
			}
		}
	}

	void del()
	{
		char input[5] = { '\0' };
		if (io_bgi(750, 30, input) == 1)
		{
			int value = 0;
			int factor = 1;
			int i = 0;
			for (i = 0; i < 4; i++)
			{
				if (input[i] != '\0')
				{
					factor = factor * 10;
				}
			}
			factor = factor / 10;
			i = 0;
			while (factor > 0)
			{
				value = value + ((int(input[i]) - 48) * factor);
				factor = factor / 10;
				i++;
			}

			hash_table.del_bst(value, hash(value));
		}
	}

	~hashing()
	{

	}
};

int main()
{
	bgi();
	closegraph();
	return 0;
}

void Circle(int xx, int yy)
{
	setlinestyle(4, 1, 2);
	circle(xx, yy, 25);
	delay(30);
	setlinestyle(1, 1, 2);
	circle(xx, yy, 25);
	delay(30);
	setlinestyle(3, 1, 2);
	circle(xx, yy, 25);
	delay(30);
	setlinestyle(0, 1, 2);
	circle(xx, yy, 25);
}

void Line(int xx, int yy, int fact2)
{
	setlinestyle(4, 1, 2);
	line(xx, yy + 25, fact2, yy + 60);
	delay(30);
	setlinestyle(1, 1, 2);
	line(xx, yy + 25, fact2, yy + 60);
	delay(30);
	setlinestyle(3, 1, 2);
	line(xx, yy + 25, fact2, yy + 60);
	delay(30);
	setlinestyle(0, 1, 2);
	line(xx, yy + 25, fact2, yy + 60);
}

int io_bgi(int xx, int yy, char input[])
{
	cleardevice();
	menu();
	int count = 0;
	char check = '\0';
	while (kbhit())
		getch();
	while (1)
	{
		moveto(100, 90);
		outtext("Enter ESC key if you want to stop giving input.");
		check = getch();

		if (int(check) != 13)
		{
			if (check >= '0' && check <= '9' && count < 4)
			{
				input[count] = check;
				count++;
			}
			else if (int(check) == 8)
			{
				count--;
				if (count < 0)
					count = 0;
				input[count] = '\0';
				cleardevice();
				menu();
			}
			if (int(check) == 27)
			{
				return -1;
			}
			moveto(xx + 5, yy);
			outtext(input);
			continue;
		}
		if (input[0] != '\0')
			break;
	}
	cleardevice();
	menu();
	return 1;
}

bool exit_clicked = false;
bool insert_clicked = false;
bool search_clicked = false;
bool delete_clicked = false;
bool display_clicked = false;

void bgi()
{
	initwindow(1366, 760, "Hybrid Chaining Model");
	registermousehandler(WM_LBUTTONDOWN, click_handler);

	hashing h;

	while (1)
	{
		exit_clicked = false;
		insert_clicked = false;
		search_clicked = false;
		delete_clicked = false;
		display_clicked = false;
		menu();
		h.display(0);
		clearmouseclick(WM_LBUTTONDOWN);
		while (!ismouseclick(WM_LBUTTONDOWN)) { system("cls"); }
		delay(100);
		if (insert_clicked)
		{
			h.insert();
		}
		else if (search_clicked)
		{
			h.search();
		}
		else if (delete_clicked)
		{
			h.del();
		}
		else if (display_clicked)
		{
			h.display(1);
		}
		else if (exit_clicked)
		{
			break;
		}

		if (exit_clicked == true || insert_clicked == true || search_clicked == true || delete_clicked == true || display_clicked == true)
			cleardevice();
	}
}

void click_handler(int xx, int yy)
{
	if (xx >= 100 && xx <= 150 && yy >= 700 && yy <= 720)
		exit_clicked = true;
	else if (xx >= 100 && xx <= 170 && yy >= 30 && yy <= 50)
		insert_clicked = true;
	else if (xx >= 380 && xx <= 450 && yy >= 30 && yy <= 50)
		search_clicked = true;
	else if (xx >= 670 && xx <= 740 && yy >= 30 && yy <= 50)
		delete_clicked = true;
	else if (xx >= 1000 && xx <= 1166 && yy >= 30 && yy <= 50)
		display_clicked = true;
}

void menu()
{
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setlinestyle(0, 1, NORM_WIDTH);
	setcolor(LIGHTGRAY);

	rectangle(180, 25, 250, 55);
	rectangle(460, 25, 530, 55);
	rectangle(750, 25, 820, 55);
	rectangle(1176, 25, 1246, 55);

	setbkcolor(LIGHTGRAY);
	setcolor(BLACK);

	moveto(100, 30);
	outtext("INSERT");

	moveto(380, 30);
	outtext("SEARCH");

	moveto(670, 30);
	outtext("DELETE");

	moveto(1000, 30);
	outtext("DISPLAY BST OF");

	moveto(100, 700);
	outtext("EXIT");

	setbkcolor(0);
	setcolor(LIGHTGRAY);
}