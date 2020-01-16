#include "Item.h"
#include <iomanip>
#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include "Date.h"
#include "POS.h"
#include "PosIO.h"

using namespace std;
namespace sict {
	Item::Item() {
		_name = new char[21];
		strcpy(_name, "");
		
		_price = 0;
		_taxed = 0;
		_quantity = 0;
		strcpy(_sku, "");
	}


	Item::Item(const char* sku, const char * name, double price, bool taxed){
	
		strcpy(_sku, sku);
		
		 _name = new char[21];
		
		 strcpy(_name, name);
		 
		_quantity = 0;
		_price =price;
		_taxed = taxed;
		
	}
	void Item::sku(const char* value){
		strcpy(_sku, value);
		

	}
	void Item::price(double p){
		
		_price = p;
		
	}
	void Item::name(const char * name){
		_name = new char[21];
		strcpy(_name, name);

		
	}
	void Item::taxed(bool t){
		_taxed = t;
		
	}
	void Item::quantity(int q){
		_quantity = q;
		
	}

	 const char* Item::sku() const{
		return _sku;
		
	}
	double Item::price()const {
		
		return _price;
	}
	 const char*  Item::name() const{
		return _name;
	}
	
	bool Item::taxed() const{
		
		return _taxed;

	}
	 int Item::quantity() const{
		return _quantity;
	}
	 double Item::cost() const {
		//HERE---------------------------------
		
		
		if (!_taxed) {
			
			return _price *1.13 ;
		}
		else if (_taxed)
		{
			
			return  _price;
		}
		return 0;
	}
	const bool Item::isEmpty() const
	{
		if (_price != 0  &&_quantity != 0 ){
		
			return false;
		}
		else {
			return false;
		}
	}
	bool Item::operator==(const char* thesku) const
	{
		if (this->_sku == thesku) {
			return true;
		}
		else {
			return false;
		}
		
	}
	int Item::operator+=(int sumAdd) 
	{
		int sum = sumAdd + _quantity;
		_quantity = sum;
		return _quantity;

	}
	int Item::operator-=(int sumSub) 
	{
		_quantity -= sumSub;
		return _quantity;
	}
	double operator+=(double& x, const Item& y)
	{
		x += (y.cost() * y.quantity());
		return x;
		
	}
	std::ostream & operator<<(std::ostream & Q, Item & item)
	{
		if (item.isEmpty() == false) {
			item.write(Q, true);

			return Q;
		}
		return Q;
	}
	std::istream & operator>>(std::istream & Q, Item & item)
	{
		item.read(Q);
		return Q;
	}

	Item & Item::operator=(const Item & B)
	{
	if (this->isEmpty() == false && this->_name != B._name){
		strncpy(_name, B._name, 21);
		_name[21] = '\0';
		_name = new char[21];
		strcpy(_sku, B._sku);
		strncpy(_name, B._name, 21);
		this->_quantity = B._quantity;
		_price = B._price;
		_taxed = B._taxed;
		}
	return *this;
	}

	
	Item::Item(const Item & B)	{
		*this = B;
		

		
	}
	 Item::~Item() {
		delete[] _name;
	}
}
