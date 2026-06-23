#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif

class Merchant{

public:
/*
    uLList<Item*> merchItems;


    void printItems(){
		nodeType<Item*>* temp;
      		temp = merchItems.getFirst();
		//cout<<temp<<endl;
		if(temp == NULL){
			cout<<"I have run no more items to sell."<<endl;
		}
		else{
			cout<<"I have the following items for sale:"<<endl;
			while(temp != NULL){
				cout<<"\t"<<temp->info->getName()<<endl;
				temp = temp->link;
			}
		}
	}

    void buy(){
		cout<<"Buy what item?"<<endl;
		string n;
		getline(cin, n);
		//cout<<"Looking for item: "<<n<<endl;
      		nodeType<Item*>* temp = NULL;
		temp = merchItems.getFirst();
		//cout<<temp<<endl;
		if(temp == NULL){
			cout<<"I have no more items for sale."<<endl;
		}
		else{
			bool found = false;
			while(temp != NULL && !found){
				if(n == temp->info->getName()){
					found = true;
					//add to room list
					Player1->info.items.insertLast(temp->info);
					//delete from player list
					merchItems.deleteNode(temp->info);
				}
				else{
					temp = temp->link;
				}
			}
			if(found){
				cout<<"You have bought: "<<n<<endl;
			}
			else{
				cout<<"No item by that name in your inventory."<<endl;
			}
		}
	}


*/

};
