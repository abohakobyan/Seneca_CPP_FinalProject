#include <iostream>
#include <iomanip>
#include <string>
#include "ErrorMessage.h"
#include <ctime>
#include <string>
#include <cstring>
#include "NonPerishable.h"
#include "Date.h"
#include "Item.h"
using namespace std;
namespace sict {
	
	//int q;
	    
		fstream& NonPerishable::save(std::fstream& file)  const {
			
			file << "N," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << endl;
			
			return file;
		}

		fstream& NonPerishable::load(std::fstream& file) {
			char sku2[25];
			char name2[25];
			double price2;
			int taxed2;
			int quantity2;
			



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
			
			if (taxed2 ==0){
				
				taxed(false);
				
			}
			else if (taxed2 == 1) {
				
				taxed(true);
			}
			file.ignore(1);
			// -----------------------------
			file >> quantity2;

			Item::quantity(quantity2);
			


			return file;


		}
		ostream& NonPerishable::write(std::ostream& os, bool linear) const {
			taxed();
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
					
					if (taxed()){
						cout << setw(2);
						cout << " t ";
						cout << "|";
					}
					else if (!taxed()){
						cout << setw(3);
						cout << " ";
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
						cout << price()* quantity();
					}
					else {
						cout << price()* 1.13 * quantity();
					}
					
					cout << "|";

				}
				else if (linear == false){
					double costquan;
					double taxedTotal;
					costquan = cost() * quantity();
					taxedTotal = cost() * 1.13;
					if (taxed()){
						costquan = costquan * 1.13;
						cout << "Name:" << endl;
						cout << name() << endl;
						cout << "Sku: " << sku() << endl;
						cout << "Price: " << price() << endl;
						cout << "Price after tax: " << taxedTotal << endl;
						cout << "Quantity: " << quantity() << endl;
						cout << "Total Cost: " << costquan << endl;
						
					}
					else if (!taxed()){
						costquan = costquan * 1.13;
						cout << "Sku: " << sku() << endl;
						cout << "Name:" << name()<< endl;
						cout << "Price: " << price() << endl;
						cout << "Price after tax: N/A " <<  endl;
						cout << "Quantity: " << quantity() << endl;
						cout << "Total Cost: " << costquan << endl;

					}

				}
	

			}
			return os;
		}

	    istream& NonPerishable::read(std::istream& is) {
			
			char buf[2000];
			double dbuf;
			int ibuf;
	cout<<"NonPerishable Item Entry:" <<endl;	
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
			if (buf[0] == 'n'){
				taxed(false);
			}
			else if (buf[0] == 'y'){
				taxed(true);
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


				clear();
				return is;
			



			 
		}

		
	    std::ostream& operator<<(std::ostream& os, const NonPerishable& M){
			M.write(os, true);
			return os;
		}
		
	    std::istream & operator>>(std::istream& os , NonPerishable & X){
		 X.read(os);

		 return os;
	 }
	 	
	};


