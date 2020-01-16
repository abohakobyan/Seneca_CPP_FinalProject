#include <iostream>
#include <iomanip>
#include <string>
#include "ErrorMessage.h"
#include <ctime>
#include <string>
#include <cstring>
#include "Perishable.h"
#include "Date.h"
#include "Item.h"
using namespace std;
namespace sict {
		bool taxed3;
		Date* _expiry;
		double costtotal2;
		int q;
		Perishable::Perishable(){
			_expiry = new Date;
			dateOnly(true);
			
		}
		void Perishable::expiry(const Date &value) {
			
			*_expiry = value;
			
		}
		const Date& Perishable::expiry()const{

			return *_expiry;
		}

		fstream& Perishable::save(std::fstream& file)  const {
			
			file << "P," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << expiry()<< endl;
			//cout << price();
			return file;
		}

		fstream& Perishable::load(std::fstream& file) {
			char sku2[25];
			char name2[25];
			double price2;
			int taxed2;
			int quantity2;
			double cost2;
			
			

			file.getline(sku2, 25, ',');
			Item::sku(sku2);
			
			// -----------------------------
			file.getline(name2, 25, ',');
			Item::name(name2);
			// -----------------------------
			file << fixed;
			file << setprecision(2);
			file >> price2;
			Item::price(price2);
			file.ignore(1);
			// -----------------------------
			file >> taxed2;
			Item::taxed(taxed2);
			if (taxed2 == 'y'){
				taxed3 = true;
			}
			else if(taxed2 == 'n') {
				taxed3 = false;
			}
			file.ignore(1);
			// -----------------------------
			file >> quantity2;
			
			Item::quantity(quantity2);
			file.ignore(1);
			

			file >> cost2;
		
			return file;


		}
		ostream& Perishable::write(std::ostream& os, bool linear) const {
			
			
			if (!isClear()){
				os << message();

			}
			else if (isClear()){
				if (linear == true){
					cout << left;
					cout << setw(MAX_SKU_LEN);
					cout << sku();

					cout << "|";

					cout << left;
					cout << setw(20);
					cout << name();
					//cout << setprecision(20);
					cout << "|";

					cout << right;
					cout << setprecision(2);
					cout << fixed;
					cout << setw(7);
					cout << price();
					cout << "|";

					if (taxed() == false){
						cout << setw(3);
						cout << " p";
						cout << "|";
					}
					else if (taxed() == true){
						cout << setw(3);
						cout << " tp";
						cout << "|";
					}

					cout << right;
					cout << setw(4);
					cout << quantity();
					cout << "|";


					cout << right;

					cout << setw(9);
					cout << fixed;
					cout << setprecision(2);
					if (!taxed()) {
						cout << price() * quantity();
						
					}
					else {
						cout << price() * 1.13 * quantity();
					}
					cout << "|";
				}
				else if (linear == false){
					double costquan;
					costquan = price()* 1.13 * quantity();
					if (taxed() == true){

						cout << "Name:" << endl;
						cout << name() << endl;
						cout << "Sku: " << sku() << endl;
						cout << "Price: " << price() << endl;
						cout << "Price after tax: " << price()  * 1.13 << endl;
						cout << "Quantity: " << quantity() << endl;
						cout << "Total Cost: " << costquan << endl;
						cout << "Expiry date: " << expiry() << endl;
					}
					else if (taxed() == false){
						cout << "Name:" <<endl;
						cout <<  name() << endl;

						cout << "Sku: " << sku() << endl;
						cout << "Price: " << price() << endl;
						cout << "Price after tax: N/A" << endl;
						cout << "Quantity: " << quantity() << endl;
						cout << "Total Cost: " << price() * quantity() << endl;
						cout << "Expiry date: " << expiry() << endl;
					}

				}


			}
			return os;
		}
		istream& Perishable::read(std::istream& is) {


			char buf[2000];
			double dbuf;
			int ibuf;
cout <<"Perishable Item Entry: " <<endl;
			cout << "Sku: ";
			is >> buf;
			sku(buf);
			cout << "Name:" << endl;
			is >> buf;
			name(buf);

			cout << "Price: ";
			is >> dbuf;
			if (is.fail()){
				
				message("Invalid Price Entry");
				
				return is;
			}
			else if (!is.fail()){
				price(dbuf);
			}



			cout << "Taxed: ";
			is >> buf;

			if (buf[0] == 'y'){
				taxed(true);
			}
			else if (buf[0] == 'n'){
				taxed(false);
			}
			else {
				is.setstate(ios::failbit);
			
				message("Invalid Taxed Entry, (y)es or (n)o");
				return is;
			}
			

			cout << "Quantity: ";
			is >> ibuf;
			q = ibuf;
			if (is.fail()){
				message("Invalid Quantity Entry");


				return is;
			}
			else if (!is.fail()){
				quantity(ibuf);
			}



			cout << "Expiry date (YYYY/MM/DD) : ";
			
			Date  Q; 
			dateOnly(true);
			is >> Q;
		
			expiry(Q);
			 
			 
			
			/*if (is.fail()) {
				return is;
			}*/
				
				if (Date::errCode() == CIN_FAILED){
					message("Invalid Date Entry");
					is.setstate(ios::failbit);
					return is;
				}
				if (Date::errCode() == YEAR_ERROR){

					message("Invalid Year in Date Entry");
					is.setstate(ios::failbit);
					return is;
				}
				if (Date::errCode() == MON_ERROR){
					message("Invalid Month in Date Entry");
					is.setstate(ios::failbit);
					return is;
				}
				if (Date::errCode() == DAY_ERROR){
					message("Invalid Day in Date Entry");
					is.setstate(ios::failbit);
					return is;
				}
				
			else if (!is.fail()){
				clear();
				return is;
			}



			//is.setstate(ios::failbit);
			is.clear();

			return is;
		}
		std::ostream & operator<<(std::ostream& os, const Perishable & A){
			A.write(os, true);
			return os;
		}
		std::istream & operator>>(std::istream& os, Perishable & X){
			X.read(os);

			return os;
		}
	
	};


