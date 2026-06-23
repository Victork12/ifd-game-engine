#ifndef H_Player
#define H_Player
#include "Player.h"
#endif // H_Player

class BasicPlayer : public Player
{
    public:
    BasicPlayer(){
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
	    else
            return 0;
    }

    void resetPlayerStats(){
        cout << "No player statistics to report. " << endl;
    }
	void reportStats(){
        cout << "No player statistics to report. " << endl;
	}

	void consume(Map* mapptr, string n){
            //////////////////////////////////////////////////////
            if(n == ""){    // if no item was entered
                cout<<"Consume what item?"<<endl;
                //string n;
                getline(cin, n);
            }
            //////////////////////////////////////////////////////

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


	void use(Map* mapptr, string n){
            ////////////////////////////////////////////////
            if(n == ""){    // if no item was entered
                cout<<"Use what item?"<<endl;
                //string n;
                getline(cin, n);
            }
            ////////////////////////////////////////////////

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

    void interact(){
    }

    void setPlayerMoney(int i){
        (void)i; // BasicPlayer does not track money
    }

    int getPlayerMoney(){
        return 0; // BasicPlayer does not track money
    }

    string Combat(){
        return ""; // BasicPlayer does not support combat
    }
};


