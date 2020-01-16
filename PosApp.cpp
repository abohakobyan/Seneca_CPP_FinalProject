#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "PosApp.h"
#include "Item.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "ErrorMessage.h"
using namespace std;
namespace sict{
	PosApp::PosApp(const char* filename, const char* billfname){

		strncpy(_filename, filename, 128);
		strncpy(_billfname, billfname, 128);
	}
	int PosApp::menu(){
		char choice ;
		cout << endl;
		cout << "The OOPs Store" << endl;
		cout << "1- List items" << endl;
		cout << "2- Add Perishable item" << endl;
		cout << "3- Add Non-Perishable item" << endl;
		cout << "5- Show Item" << endl;
		cout << "6- POS" << endl;
		cout << "0- exit program" << endl;
		
		//cin.ignore();
		cin >> choice;
		
		//stringstream myStream(choice);
		
		if (choice == '1'){
			cout << endl;
			return 1;
		}
		else if (choice == '2'){
			cout << endl;
			cin.clear();
			return 2;
		}
		else if (choice == '3'){
			cout << endl;
			cin.clear();
			return 3;
		}
		else if (choice == '4'){
			cout << endl;
			return 4;
		}
		else if (choice == '5'){
			cout << endl;
			return 5;
		}
		else if (choice == '6'){
			cout << endl;
			return 6;
		}
		else if (choice == '0'){
			cout << endl;
			return 0;
		}
		else{
			cout << endl;
			choice = -1;
			return -1;
		}

	}
	void PosApp::loadRecs(){

		readIndex = 0;
		fstream _filename;
		_filename.open(_billfname, ios::in);
		if (!_filename.is_open()){ //not sure if this is right!!

			_filename.clear();
			_filename.close();
			_filename.open(_billfname, ios::out);
			_filename.close();

		}
		else if (_filename.is_open()){
			while (!_filename.fail()) {
				delete[]_items[readIndex];
				//_filename >> id;
			//	cout << id;
				char id;
				_filename.ignore(1);
				_filename >> id;
				cout << id << endl;
				cout << "yo";
				if (id == 'P' && outofPN == false){
					Perishable *peri;
					_items[readIndex] = peri;
					outofPN = true;
					
				}
				if (id == 'N' && outofPN == false){
					NonPerishable *nonperi;
					_items[readIndex] = nonperi;
					outofPN = true;

				}
				if (outofPN == true){
					_filename.ignore(1);
					_items[readIndex]->load(_filename);
					readIndex += 1;
				}
			}
		_noOfItems = readIndex;
			_filename.close();
		}

	}
	void PosApp::saveRecs(){
		
		fstream _filename;
		_filename.open(_billfname, ios::out);

		for (int i=0; i < _noOfItems; i++){
			int quant = _items[i]->quantity();
			
			if (quant < 0){
				_items[i]->save(_filename);
			}
			else if (quant > 0) {
				_filename.close();
				loadRecs();
			}
		}

	}

	int PosApp::searchItems(const char* sku)const{

		for (int i=0; i < readIndex; i++){
			int result = strcmp(_items[i]->sku(), sku);
			if (result == 0){ 
				return i;
			} 
			
		}
	
		return -1;

	}

	void PosApp::updateQty(){
		char* currsku1;

		cout << "Please enter the SKU: ";
		cin >> currsku1;
		int value = searchItems(currsku1);
		if (value = -1){
			cout << "Not found!" << endl;
		}
		else{
			_items[readIndex]->write(cout, false);
			cout << "Please enter the number of purchased items: ";
			int upd;
			cin >> upd;
			cout << endl;
			_items[readIndex] += upd;
			saveRecs();
			cout << "Updated!" << endl;
		}

	}

	void PosApp::addItem(bool isPerishable){
		int noItem;
		noItem = _noOfItems;
	
		if (isPerishable == true){
			Perishable* item;
			
			item = new Perishable;
			cin >> *item;
			if (cin.fail()){
				cin.clear();
				cout << *item;
				
			}
			else if (!cin.fail()){
				_items[readIndex] = new Perishable();
				*_items[readIndex] = *item;
				
				noItem++;
				saveRecs();
				readIndex += 1;
				cout << readIndex << endl;
				cout << "Item Added." << endl;
			}
		}
		else if (isPerishable == false){
			NonPerishable* item;
			item = new NonPerishable;
			cin >> *item;
			if (cin.fail()){
				cin.clear();
				cout << *item;

			}
			else if (!cin.fail()){
				_items[readIndex] = new NonPerishable();
				*_items[readIndex] = *item;

				noItem++;
				saveRecs();
				readIndex ++;
				cout << readIndex << endl;
				cout << "Item Added." << endl;
			}
			_noOfItems = noItem;
		}
	}

	void PosApp::listItems()const{
		int totalasset = 0;
		int xd = _noOfItems;
		cout << "Row  | SKU    | Item Name          | Price |TX |Qty |   Total |" << endl;
		cout << "-----|--------|--------------------|-------|---|----|---------|" << endl;
		
		int x = 0;
			for (int i = 0; i < xd; i++){
			if (i == 0){
				x = i + 1;
				cout << "   "<< x << " | ";
				x++;
			}
			else {

				cout << "   " << x << " | ";
				x++;
			}
			_items[i]->write(cout, true) << endl;
			_items[i]->write(cout, true) << endl;

			 totalasset += _items[i]->cost();
		}
		cout << "-----^--------^--------------------^-------^---^----^---------^" << endl;
		cout << "Total Asset: $" << totalasset << endl;
	}

	void PosApp::showBill(){
		Date* currdate;
		currdate= new Date;
		fstream _filename;
		int totalasset = 0;
		_filename.open(_billfname, ios::in);
		cout << "v--------------------------------------------------------v" << endl;
		cout << "| " << *currdate << "                                        |" << endl;
		cout << "| SKU    | Item Name          | Price |TX |Qty |   Total |" << endl;
		cout << "|--------|--------------------|-------|---|----|---------|" << endl;
		if (!_filename.is_open()){ //not sure if this is right!!

			_filename.clear();
			_filename.close();
			_filename.open(_billfname, ios::out);
			_filename.close();

		}
		else if (_filename.is_open()){
			while (!_filename.fail()){
				char id;
			_filename >> id;
			cout << id << endl;
				
				if (id == 'P' ){
					Perishable *peri;
					_items[readIndex] = peri;
					_items[readIndex]->write(cout, true);
					totalasset += _items[readIndex]->cost();
					readIndex += 1;
					
				}
				if (id == 'N' ){
					NonPerishable *nonperi;
					_items[readIndex] = nonperi;
					_items[readIndex]->write(cout, true);
					totalasset += _items[readIndex]->cost();
					readIndex += 1;
					
				}
				cout << "^--------^--------------------^-------^---^----^---------^" << endl;
				cout << "Total $" << totalasset << endl;

			}
		//_noOfItems = readIndex;
			_filename.close();
		}

	}

	void PosApp::addToBill(Item& I) {

		int qty = I.quantity();
		I.quantity(1);
		fstream _filename;
		_filename.open(_billfname, ios::out | ios::app);
		if (!_filename.is_open()) { //not sure if this is right!!

			_filename.clear();
			_filename.close();
			_filename.open(_billfname, ios::out | ios::app);
			_filename.close();

		}
		I.save(_filename);
		if (qty != 0)
		{
			qty -= 1;
		}
		I.quantity(qty);
		saveRecs();

	}
	void PosApp::POS(){
		string in = "";
		int n = 0;
		int q = 0;
		bool done = false;
		char _sku[MAX_SKU_LEN + 1];
		while (done == false) {





			_items[readIndex]->sku();
			if (_items[readIndex]->sku() == "") {
				showBill();
				done = true;
			}
			
			cin.clear();
			if (q == 0) {
				cin.ignore(1);
			}
			
		cout << "Sku: ";
		getline(cin, in);
		int i;
		q++;
			 for (i = 0; i < in.size(); i++) {
				 _sku[i] = in[i];
			 }
			 _sku[i] = '\0';
			if (in == "") {
				showBill();
				
				exit(0);
			}
			else {
				int value = searchItems(_sku);

				if (value >= 0) {
					cout << "v-----------------------------------v" << endl;
					cout << "| " << _items[value]->name() << endl;
					cout << "^-----------------------------------^" << endl;
					addToBill(*_items[value]);
				}
				else if (value == -1) {
					cout << "Not Found!" << endl;
				}



			}
		}
	}
	void _pause(){
		cout << "****press enter to continue...";
		cin.ignore(1000, '\n');
	}
	void PosApp::run(){
		//_noOfItems = 0;
		bool run = true;
		int currsele;
		char _sku[MAX_SKU_LEN + 1];
		
		while (run == true){
			
			currsele = menu();
			if (currsele == 1){
				listItems();
				
			}
			else if (currsele == 2){
				addItem(true);
				
			}
			else if (currsele == 3){
				addItem(false);
				
				
			}
			else if (currsele == 4){
				updateQty();
				
				
			}
			else if (currsele == 5){
				cout << "Please enter the SKU: ";
				cin >> _sku;
				int value = searchItems(_sku);
				
				if (value >= 0){
					cout << "v-----------------------------------v" << endl;
					_items[value]->write(cout, false);
					cout << "^-----------------------------------^" << endl;
				}
				else if (value == -1){
					cout << "Not Found!" << endl;
				}
				
				
			}
			else if (currsele == 6){
				POS();
				
				
			}
			else if (currsele == 0){
				
				cout << "Goodbye!" << endl;
				_pause();
				exit(0);
				
			}
			else{
				cout << "=== Invalid Selection, try again ===" << endl;
			}

		}

	}

}
