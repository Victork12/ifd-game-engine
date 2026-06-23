#ifndef H_Player
#define H_Player
#include "Player.h"
#endif // H_Player

#include "UseItem.h"
#include "Merchant.h"

class HPSPPlayer : public Player
{
    private:
        int hit = 100;
        int sanity = 100;
        int money = 150;      // players starting money
    public:

        uLList<Item*> merchItems;

        HPSPPlayer(){
            //cout << "Creating Basic player"<< endl;
            lastLocation = NULL;
            currentLocation = NULL;
        }

        int isGameOver(){
            if(currentLocation->info.getID()== true){
                return 2;
            }
            else if(currentLocation->info.getGoal()==true){
                return 1;
            }
            else if(hit <= 0){
                return 2;
            }
            else if(sanity <= 0){
                return 2;
            }
            else
                return 0;
        }

        void resetPlayerStats(){
            hit = 100;
            sanity = 100;
            money = 0;          // resets players money
        }

        void reportStats(){
            cout << "Player Stats:" << endl;
            cout << "           Hit Points: " << hit << endl;
            cout << "           Sanity Points: " << sanity << endl;
            cout << "           Money: $" << money << endl;     // prints players money
        }

        void consume(Map* mapptr, string n){
            ///////////////////////////////////////////////////
            if(n == ""){    // if no item was entered
                cout<<"Consume what item?"<<endl;
                //string n;
                getline(cin, n);
            }
            ////////////////////////////////////////////////////

            nodeType<Item*>* temp = NULL;
            temp = items.getFirst();


            if(temp == NULL){
                cout<<"You have no items in your inventory."<<endl;
            }
            else{       // if inventory is not full
                bool found = false;
                while(temp != NULL && !found){      // loop until item is found
                    if(n == temp->info->getName()){
                        found = true;
                        //add to room list
                        if(temp->info->getActiveArea() == currentLocation->info.getArea()){     // if current area is equal to actar

                            vector<Effect*> b(temp->info->getItemConsumeEffects());         // passes rules to new vector pointer b

                            if(!b.empty()){
                                cout << temp->info->getActiveMessage() << endl;                 // prints actmess
                                points(b[0]->effectID,b[0]->effectAmt);

                                if(getHit() == 0 || getSanity() == 0){
                                    cout << "You have died of your wounds!!" << endl;
                                    exit(0);
                                }
                                return;
                            }
                            else{
                                cout << "That proves impossible."<< endl;       // prints when consuming wrong item
                                return;
                            }
                        }
                        cout << temp->info->getActiveMessage() << endl;
                    }
                    else{
                        temp = temp->link;
                    }
                }
            }
        }

        void setHit(int h){
            hit = h;
        }
        int getHit(){
            return hit;
        }

        void setSanity(int s){
            sanity = s;
        }

        int getSanity(){
            return sanity;
        }

        void setMoney(int m){       // sets players money
            money = m;
        }

        int getMoney(){         // returns the players money
            return money;
        }

        void interact(){
            if(currentLocation->info.getMerch() == 0){
                cout<<"There is nothing to interact with in this room."<<endl;
            }
            else if(currentLocation->info.getMerch() == 1){
                string choice;

                cout << "------------- Merchant ------------- " << endl;
                printItems();

                cout << "Would you like to buy an item? (yes/no)" << endl;
                getline(cin, choice);

                if(choice == "yes")
                    buy();  // is called if the user wants to buy from the merchant

                cout << endl;
            }

        }

        void points(int ID, int Damage){
            int tempH = getHit();
            int tempS = getSanity();
            if(ID == 0){
                tempH = tempH - Damage;
                setHit(tempH);
            }
            else if(ID == 1){
                tempH = tempH + Damage;
                setHit(tempH);
            }
            else if(ID == 2){
                tempS = tempS + Damage;
                setSanity(tempS);
            }
        }


        void use(Map* mapptr, string n){
            ///////////////////////////////////////
            if(n == ""){    // if no item was entered
                cout<<"Use what item?"<<endl;
                //string n;
                getline(cin, n);
            }
            ///////////////////////////////////////

            nodeType<Item*>* temp = NULL;
            temp = items.getFirst();


            if(temp == NULL){
                cout<<"You have no items in your inventory."<<endl;
            }
            else{       // if inventory is not full
                bool found = false;
                while(temp != NULL && !found){      // loop until item is found
                    if(n == temp->info->getName()){
                        found = true;
                        //add to room list
                        if(temp->info->getActiveArea() == currentLocation->info.getArea()){     // if current area is equal to actar
                            vector<Rule*> b(temp->info->getItemUseRules());         // passes rules to new vector pointer b

                            if(!b.empty()){
                                cout << temp->info->getActiveMessage() << endl;                 // prints actmess
                                mapptr->makeRules(b, mapptr);
                                return;
                            }
                            else{
                                cout << "That proves impossible."<< endl;
                                return;
                            }
                        }
                    }
                    else{
                        temp = temp->link;
                    }
                }
                cout << "There's no way to use this item." << endl;
            }


        }

        void setPlayerMoney(int i){  // abstract function
            money = i;
        }

        int getPlayerMoney(){   // abstract function
            return money;
        }




        void printItems(){
            nodeType<Item*>* temp;
            temp = currentLocation->info.merchant.getFirst();    //merchVec.getFirst();
            //cout<<temp<<endl;
            if(temp == NULL){
                cout<<"I have run no more items to sell."<<endl;    // prints if merchant has no items
            }
            else{
                cout<<"I have the following items for sale:"<<endl;     // prints the items for sale and their cost
                while(temp != NULL){
                    cout<<"\t"<<temp->info->getName()<< "   $" << temp->info->getCurrency() <<endl;
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
		temp = currentLocation->info.merchant.getFirst();
		//cout<<temp<<endl;
		if(temp == NULL){
			cout<<"I have no more items for sale."<<endl;
		}
		else{
			bool found = false;
			bool bought = false;    // keeps track if item is bought
			while(temp != NULL && !found){
				if(n == temp->info->getName()){
					found = true;
					//add to room list
					if(money >= temp->info->getCurrency()){  // will only allow user to buy is their money is greater than the cost of the item
                        int cost = temp->info->getCurrency();  // cache cost before the node is freed below
                        items.insertLast(temp->info);
                        //delete from player list
                        currentLocation->info.merchant.deleteNode(temp->info);  // deletes the item from the merchant
                        bought = true;  // sets bought equal to true if the item is bought

                        money = money - cost;  // updates the players money by subtracting the cost of them item
					}
					else
                        cout << "not enough money! " << endl;   // if the user does not have enough money for the purchase
				}
				else{
					temp = temp->link;
				}
			}
			if(bought){
				cout<<"You have bought: "<<n<<endl; // prints message and item that has been bought
			}
			if(!found){
                cout<<"Merchant does not have that item."<<endl; // prints if the merchant does not have item entered
			}
		}
	}


	string Combat(){
	    string n;


	    nodeType<Enemy*>* temp;
	    nodeType<Item*>* it;
        it = items.getFirst();
        temp = currentLocation->info.enemy.getFirst();

       if (temp->info->getEnemyState() == 0)
            return ""; // enemy already defeated, skip combat entirely
        cout << endl << "A " << temp->info->getEnemyName() << " attacked you!" << endl;

        while(temp->info->getEnemyState() != 0){

            int tempH = getHit();
            tempH = tempH - temp->info->getEnemyDamage();
            setHit(tempH);

            cout << "It did " << temp->info->getEnemyDamage() << " damage to you!" << endl << endl;

            cout << "Attack " << temp->info->getEnemyName() << " with: ";
            getline(cin, n);

            if(it == NULL){
                cout<<"No items are in your inventory."<<endl;
            }
            else{
                bool found = false;
                while(it != NULL && !found){
                    if(n == it->info->getName()){
                        found = true;
                    }
                    else
                        it = it->link;
                }

                if(!found){
                    cout << "No item by that name in your inventory." << endl;
                    cout << "Enter escape to run!" << endl;
                    getline(cin, n);
                }
                else if(n == "Sword" && found){
                    temp->info->setEnemyState(0);
                    cout << temp->info->getEnemyName() << " is now dead! Don't have to worry about it anymore. " << endl;
                    return n;
                }
                else if(n == "Dagger" && found){
                    temp->info->setEnemyState(0);

                    cout << temp->info->getEnemyName() << " is now dead! Don't have to worry about it anymore. " << endl << endl;
                    return n;
               }
               else if(found && n != "Sword" && n != "Dagger"){
                    cout << "This item cannot be used Attack" << endl;
                    cout << "Enter escape to run!" << endl;
                    getline(cin, n);
               }
               else if(!found && n != "Sword" && n != "Dagger"){
                    cout << "Item not in inventory" << endl;
                    cout << "Enter escape to run!" << endl;
                    getline(cin, n);
               }

               if(n == "escape")
               {
                   temp->info->setEnemyState(1);
                   return n;
                  // break;
               }
            }
        }
        return n; // safety net: loop always exits via return above, but this guarantees defined behavior
	}


};
