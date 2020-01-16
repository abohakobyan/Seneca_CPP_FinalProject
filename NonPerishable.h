#ifndef __244_NONPERISHABLE_H__
#define __244_NONPERISHABLE_H__
#include <iostream>
#include "Item.h"
#include "Date.h"
#include "ErrorMessage.h"

using namespace std;
namespace sict {

	class NonPerishable :public Item, public Date, public ErrorMessage {
		ErrorMessage _err;
	public:
		int q;
		std::fstream& save(std::fstream& file)const ;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);
		
		//std::istream & operator>>(std::istream&, const NonPerishable &);
	};
	std::ostream & operator<<(std::ostream& os, const NonPerishable & A);
	std::istream & operator>>(std::istream&, NonPerishable &);
}
#endif

