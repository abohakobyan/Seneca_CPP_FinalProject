#ifndef SICT_POSAPP_H__
#define SICT_POSAPP_H__
#include "Perishable.h"
#include "NonPerishable.h"
#include "Item.h"
namespace sict{
  class PosApp : public NonPerishable, Perishable, ErrorMessage, Date {
    char _filename[128];
    char _billfname[128];
    Item* _items[MAX_NO_ITEMS];
	int _noOfItems = 0;
    int menu();
	//char id;
	ErrorMessage _err;
	bool outofPN = false;
	int readIndex = 0;
    void loadRecs();
    void saveRecs();
    int searchItems(const char* sku)const;
    void updateQty();
    void addItem(bool isPerishable);
    void listItems()const;
    void showBill();
    void addToBill(Item& I);
    void POS();
  public:   
	 
    // prevent copying and assignment here!
    PosApp(const char *filename, const char *billfname);
    void run();
  };
}
#endif
