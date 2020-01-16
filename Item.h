#ifndef SICT_ITEM_H__
#define SICT_ITEM_H__
#include "PosIO.h"
#include "POS.h"
namespace sict {
	class Item :public PosIO{
		char _sku[MAX_SKU_LEN + 1];
		char* _name = '\0';
		double _price;
		
		int _quantity;
	public:
		Item();
		~Item();
		Item(const char* sku, const char* name, double price, bool taxed = true);
		bool _taxed;
		void sku(const char* value);
		void price(double p);
		void name(const char* n);
		void taxed(bool t);
		void quantity(int q);

		const char* sku()const;
		 double price() const;
		const char*  name() const;
		bool taxed() const;
		 int quantity() const;
		 double cost() const ;
		const bool isEmpty() const;
		
		bool operator==(const char* thesku) const;
		int operator+=(int) ;
		int operator-=(int) ;
		Item & operator=(const Item & B);
		 Item(const Item & B);
		//virtual Item::~Item();
	};
	double operator+=(double &x, const Item &y);
	std::ostream & operator<<(std::ostream&, Item &);
	std::istream & operator>>(std::istream&, Item &);
	
}

#endif