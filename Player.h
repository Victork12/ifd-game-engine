#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif

class Player{
  public:
  	uLList<Item*> items;
    	Player(){
		lastLocation = NULL;
		currentLocation = NULL;
	}

	void setCurrent(areaNode* loc){
      		lastLocation = currentLocation;
            currentLocation = loc;
	}

	bool playerMoved(){
		return !(lastLocation == currentLocation);
	}
	areaNode* getCurrent(){
		return currentLocation;
	}

	void inventory(){
		nodeType<Item*>* temp;
      		temp = items.getFirst();
		//cout<<temp<<endl;
		if(temp == NULL){
			cout<<"No items are in your inventory."<<endl;
		}
		else{
			cout<<"You have the following items:"<<endl;
			while(temp != NULL){
				cout<<"\t"<<temp->info->getName()<<endl;
				temp = temp->link;
			}
		}
	}

	void take(string n = ""){
	    ////////////////////////////////////////////
	    if(n == ""){    // if no item was entered
            cout<<"Take what item?"<<endl;
            //string n;
            getline(cin, n);
	    }
	    ////////////////////////////////////////////

        nodeType<Item*>* temp = NULL;
		temp = currentLocation->info.items.getFirst();

		//cout<<temp<<endl;
		if(temp == NULL){
			cout<<"No items are in this room to take."<<endl;
		}
		else{
			bool found = false;
			while(temp != NULL && !found){
				if(n == temp->info->getName()){
					found = true;
					//add to player list
					items.insertLast(temp->info);
					//delete from room list
					currentLocation->info.items.deleteNode(temp->info);
				}
				else{
					temp = temp->link;
				}
			}
			if(found){
				cout<<"You have taken: "<<n<<endl;
			}
			else{
				cout<<"No item by that name here."<<endl;
			}
		}
	}

	void leave(string n = ""){
	    ////////////////////////////////////////////////////
	    if(n == ""){    // if no item was entered
            cout<<"Leave what item?"<<endl;
            //string n;
            getline(cin, n);
	    }
	    ////////////////////////////////////////////////////

        nodeType<Item*>* temp = NULL;
		temp = items.getFirst();

		//cout<<temp<<endl;
		if(temp == NULL){
			cout<<"You have no items in your inventory."<<endl;
		}
		else{
			bool found = false;
			while(temp != NULL && !found){
				if(n == temp->info->getName()){
					found = true;
					//add to room list
					currentLocation->info.items.insertLast(temp->info);
					//delete from player list
					items.deleteNode(temp->info);
				}
				else{
					temp = temp->link;
				}
			}
			if(found){
				cout<<"You have dropped: "<<n<<endl;
			}
			else{
				cout<<"No item by that name in your inventory."<<endl;
			}
		}
	}

	void examine(string n=""){
	    ////////////////////////////////////////////
	    if(n == ""){    // if no item was entered
            cout<<"Examine what item?"<<endl;
            //string n;
            getline(cin, n);
	    }
		////////////////////////////////////////////

        nodeType<Item*>* temp = NULL;
		temp = items.getFirst();

		//cout<<temp<<endl;
		if(temp == NULL){
			cout<<"You have no items in your inventory to examine."<<endl;
		}
		else{
			bool found = false;
			while(temp != NULL && !found){
				if(n == temp->info->getName()){
					found = true;
					//display item description
					cout<<temp->info->getDesc()<<endl;
				}
				else{
					temp = temp->link;
				}
			}
			if(!found){
				cout<<"No item by that name in your inventory."<<endl;
			}
		}
	}

	/* void interact(){
        if(currentLocation->info.getMerch() == 0){
            cout<<"There is nothing to interact with in this room."<<endl;
        }
        else if(currentLocation->info.getMerch() == 1){

        }

	} */


	virtual string Combat() = 0;

	virtual void setPlayerMoney(int i) = 0;     // sets player money
	virtual int getPlayerMoney() = 0;   // returns player money
	virtual void interact() = 0;
	virtual int isGameOver() = 0;
	virtual void resetPlayerStats() = 0;
	virtual void reportStats() = 0;
	virtual void consume(Map* mapptr, string) = 0;
	virtual void use(Map* mapptr, string) = 0;


  protected:
		areaNode* currentLocation;
		areaNode* lastLocation;

};


