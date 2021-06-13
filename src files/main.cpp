#include <iostream>
#include"AVLMap.h"
#include "ProductData.h"
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>

#include <conio.h>
#include <string.h>
#include <time.h>
#include <chrono>

using namespace std::chrono;

void PlaceCursor(int x, int y) {
	COORD c;
	c.X = x; 
	c.Y = y;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
}

template <class K, class T>
void AVLMap<K, T>::Print(AVLNode<K, T>* ptr, int x, int y, int offset, int treeHeight, int level) {
	
	if (ptr) {
		Print(ptr->left, x-offset, y + treeHeight/level + 2, offset/2, treeHeight, level+1);			//decreasing the x coordinate when we go left
		PlaceCursor(x, y);												
		cout << ptr->key;
		if (ptr->left) {											//if the left child exists then we print "/" on the next line
			PlaceCursor(x - ptr->height-1, y + 2);
			cout << "/";
		}
		if (ptr->right) {											//if the right child exists then we print "\"
			PlaceCursor(x + ptr->height+1, y +2);
			cout << "\\";
		}
		Print(ptr->right, x + offset, y + treeHeight / level +2, offset / 2, treeHeight, level + 1);		//increasing the x coordinate when we go right
		//increase the level everytime we move to a child. Whether right or left
	}
	PlaceCursor(0, y + 22);
}




void Load(string filename, AVLMap<int, ProductData> &Tree) {

	ifstream fin(filename.c_str());
	string line;
	//ignoring the first line
	if (fin) {
		getline(fin, line);

		string temp;
		string input[3];

		while (!fin.eof()) {
			getline(fin, line);
			//associating the string (line) with a stream allowing to read from it as if it were a stream(like cin)
			stringstream data(line);
			int i = 0;
			//tokenizing the string (line) with tab as the delimiter
			//each token will be held inside the array of strings(input)
			while (getline(data, temp, '\t')) {
				input[i++] = temp;
			}
			ProductData p( input[1], atoi(input[2].c_str()));
			int key = atoi(input[0].c_str());
			Tree.Insert(key, p);
		}
		cout << endl << endl << "File loaded successfully" << endl << endl;
		//cout << "ID\tNAME\t\tQUANTITY" << endl << endl;
		//Tree.PrintInOrder();
	}
	else
		cout << endl << endl << "Error opening file" << endl << endl;

}

int main() {

	AVLMap<int, ProductData> ProductMap;

	int choice = 0;

	while (choice != -1) {
		cout << "ENTER YOUR CHOICE" << endl;
		cout << "1. Load AVL Map from file" << endl;
		cout << "2. Insert Data into AVL Map" << endl;
		cout << "3. Delete Data from Map using key" << endl;
		cout << "4. Look up data from Map using key" << endl;
		cout << "5. Print the AVL Map in order" << endl;
		cout << "6. Print the AVL Map as a tree" << endl;
		cout << "_______________________________________________" << endl;
		cout << "-1. EXIT" << endl;
		cin >> choice;

		if (choice == 1) {
			string name;
			cout << "Enter the name of the file" << endl;
			cin >> name;
			auto start = high_resolution_clock::now();
			Load(name, ProductMap);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken by function ADD to insert in an AVL TREE: "
				<< duration.count() << " microseconds" << endl;
			cout << endl << endl;
		}
		else if (choice == 2) {
			int key;
			int quantity;
			string name;
			cout << "Enter ID" << endl;
			cin >> key;
			if (ProductMap.LookUp(key)) {
				cout << "The product given above already exists with the same ID" << endl << endl << endl;
			}
			else {
				cout << "Enter name" << endl;
				cin.ignore();
				getline(cin, name);
				cout << "Enter quantity" << endl;
				cin >> quantity;
				ProductData product(name, quantity);
				ProductMap.Insert(key, product);
				cout << "Here is the new list of products" << endl << endl;
				cout << "ID\tNAME\t\tQUANTITY" << endl << endl;
				ProductMap.PrintInOrder();
				cout << endl << endl << endl;

			}


		}
		else if (choice == 3) {
			int key;
			cout << "Enter the ID to delete" << endl;
			cin >> key;
			if (ProductMap.Delete(key)) {
				cout << endl << endl << "Product deleted successfully" << endl << endl;
				cout << "Here is the new list of products" << endl << endl;
				cout << "ID\tNAME\t\tQUANTITY" << endl << endl;
				ProductMap.PrintInOrder();
				cout << endl << endl << endl;
			}
			else
				cout << endl << endl << "Product not found" << endl << endl;
		}
		else if (choice == 4) {
			int key;
			cout << "Enter ID to find" << endl;
			cin >> key;
			if (ProductMap.LookUp(key)) {
				cout << "Product FOUND!";
			}
			else
				cout << "Not Found!";
			cout << endl << endl;
		}
		else if (choice == 5) {
			ProductMap.PrintInOrder();
			cout << endl << endl;
		}
		else if (choice == 6) {
			system("CLS");
			ProductMap.Print();
		}
		else if (choice == -1)
			cout << endl << "GOODBYE!" << endl << endl;
		else{
			cout <<endl << "INVALID CHOICE" << endl << endl;
		}
	}

	//AVLMap<int, int> map;
	//int x = 1;
	//map.Insert(50, x);
	//map.Insert(20, x);
	//map.Insert(80, x);
	//map.Insert(70, x);
	//map.Insert(10, x);
	//map.Insert(30, x);
	//map.Insert(5, x);
	//map.Insert(25, x);
	//map.Insert(35, x);
	//map.Insert(22, x);




	//map.Print();

	
	
}