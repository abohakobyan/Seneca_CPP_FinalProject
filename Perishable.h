#ifndef __244_PERISHABLE_H__
#define __244_PERISHABLE_H__
#include <iostream>
#include "Item.h"
#include "Date.h"
#include "ErrorMessage.h"
using namespace std;
namespace sict{
class Perishable:public Item, Date, ErrorMessage{
	ErrorMessage _err;
	Date *_expiry;
	
	public:
	
	Perishable();
	const Date& expiry()const;
	void expiry(const Date &value);

	std::fstream& save(std::fstream& file)const;
	std::fstream& load(std::fstream& file);
	std::ostream& write(std::ostream& os, bool linear)const;
	std::istream& read(std::istream& is);
};
	std::ostream & operator<<(std::ostream& os, const Perishable & A);
	std::istream & operator>>(std::istream&, Perishable &);
}
#endif

