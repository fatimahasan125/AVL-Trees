#pragma once

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class ProductData {
	friend ostream& operator<<(ostream& out, const ProductData& obj);

	string name;
	int quantity;
public:
	ProductData() {
		quantity = 0;
		name = "\0";
	}

	ProductData(string n, int q)
		:name(n), quantity(q)
	{};
	ProductData(const ProductData& obj)
		:name(obj.name), quantity(obj.quantity)
	{};
	ProductData& operator = (const ProductData& obj) {

		name = obj.name;
		quantity = obj.quantity;
		return *this;
	}


	~ProductData() {
		//nothing to be deleted
	}
};

ostream& operator<<(ostream& out, const ProductData& obj) {
	out << left << setw(8) << obj.name << "\t" << obj.quantity;
	return out;
}
