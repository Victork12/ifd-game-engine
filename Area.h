#include <string>
#include <iostream>

using namespace std;

#include "ull.h"
#include "Item.h"
#include "Enemy.h"

class Area{
  public:

    void setUsedAreaCurr(){     // sets ifRoomUsed to true if the function is called
        ifRoomUsed = true;
    }

    void resetRoomUsed(){
        ifRoomUsed = false;
        setAreaCurrency(getOriginalCurrency());
    }

    bool getUsedAreaCurr(){     // returns the room status
        return ifRoomUsed;
    }

    void setAreaCurrency(int c){     // sets areas currency mainly used in the parser
        areaCurrency = c;
    }

    int getAreaCurrency(){      // returns the areas currency
        return areaCurrency;
    }

    void setOriginalCurrency(int cur){
        originalareacurrency = cur;
    }

    int getOriginalCurrency(){
        return originalareacurrency;
    }


    void setDescription (string desc){
    	description = desc;
    }
    void setGoal(bool g){
	goal = g;
    }
    void setID(bool id){
	instadeath = id;
    }
    string getDescription(){
    	return description;
    }
    bool getID(){
    	return instadeath;
    }
    bool getGoal(){
	return goal;
    }
    void displayArea(){
	cout<<description<<endl;
    }
    void setMerch(int m){
        merch = m;
    }
    int getMerch(){
        return merch;
    }

    uLList<Item*> items;
    uLList<Item*> merchant; // new merchant items
    uLList<Enemy*> enemy;

    int getEnemyStatus(){
            //int status;
            nodeType<Enemy*> *temp;  // temp pointer to Item*
            temp = enemy.getFirst();
            status = temp->info->getEnemyState();
            return status;
    }

    void search(){
        if(items.isEmptyList()) // uses ull template to see if items list is empty
            cout << "No items are in this area." << endl;
        else
        {
            nodeType<Item*> *temp;  // temp pointer to Item*
            temp = items.getFirst();
            cout << "The following items are in this area:" << endl;
            while(temp != NULL){    // Loops until the end of list
                cout << "\t" << temp->info->getName() << endl;  // prints out name indented by tab
                temp=temp->link;    // next node

            }
        }
    }

    void setArea(int d){        // Sets area number
        areaNum = d;
    }

    int getArea(){                  // Gets area number
        return areaNum;
    }

    protected:
        int areaNum;
  private:
     string description;
     bool instadeath;
     bool goal;
     int merch;
     int areaCurrency = 0;  // stores the areas currency
     bool ifRoomUsed = false;   // keeps track if room is used currently set to false bc its unused
     int originalareacurrency = 0;
     int status;
};
