#include "MapV2.h"
//#include "Player.h"
//#include "BasicPlayer.h"
#ifndef ullItem
#define ullItem
    #include "ull.h"
    #include "Item.h"
#endif

class Game{
	private:
		Player* player1;
		BasicPlayer p1;
		HPSPPlayer p2;
		MapV2 map, *m = &map;

  	public:
		Game(){
		    if(map.Ptype == 1){     // if Ptype is equal to 1 set Player pointer to p1
                cout << "Creating Basic Player ... READY!" << endl;
                player1 = &p1;
		    }
		    if(map.Ptype == 2){     // if Ptype is equal to 2 set Player pointer to p2
                cout << "Creating HPSP Player ... READY!" << endl;
                player1 = &p2;
		    }

			player1->setCurrent(map.getStart());
		}

  		void play(){
      			string userInput; // action
      			string item, temp; // item, temp is if user input has 2 words
      			int linked;

                //cin.ignore();
      			while(true){
				//check game status
				if(player1->isGameOver() != 0){
					player1->getCurrent()->info.displayArea();
					return;
				}
      				//display area data
				if(player1->playerMoved()){
	    				player1->getCurrent()->info.displayArea();
				}
				else{
					if(userInput != "reset"){
						cout<<"There appears to be no way to go that direction."<<endl;
					}
				}

	  			//get movement selection
	  			cout<<"Which way would you like to go?  Enter u, d, l, or r"<<endl;
				getline(cin, userInput);    // gets action


				stringstream s(userInput);
				s>>userInput>>item >> temp; // breaks down the userInput in to separate strings

                if(temp != "")      // if item is 2 words
                    item = item + " " + temp;   // stores item + temp as one word

	  			//update area
	  			if(userInput == "u"){
       				player1->setCurrent(player1->getCurrent()->u);

       				if(player1->getCurrent()->info.getUsedAreaCurr() == false){     // if the room is not visted before
                        player1->setPlayerMoney(player1->getPlayerMoney() + player1->getCurrent()->info.getAreaCurrency()); // players currency + rooms currency
                        player1->getCurrent()->info.setAreaCurrency(0);     // sets the areas currency equal to zero
                        player1->getCurrent()->info.setUsedAreaCurr();      // sets the room to visited

                        string combat;
                        if(player1->getCurrent()->info.enemy.isEmptyList() == false && player1->getCurrent()->info.getEnemyStatus() != 0 ){
                            combat = player1->Combat();
                            if(combat == "escape")
                                player1->setCurrent(player1->getCurrent()->d);
                        }
       				}

		 		}
				else if(userInput == "d"){
					player1->setCurrent(player1->getCurrent()->d);

					if(player1->getCurrent()->info.getUsedAreaCurr() == false){ // if the room is not visted before
                        player1->setPlayerMoney(player1->getPlayerMoney() + player1->getCurrent()->info.getAreaCurrency()); // players currency + rooms currency
                        player1->getCurrent()->info.setAreaCurrency(0);     // sets the areas currency equal to zero
                        player1->getCurrent()->info.setUsedAreaCurr();      // sets the room to visited
					}

					string combat;
                        if(player1->getCurrent()->info.enemy.isEmptyList() == false && player1->getCurrent()->info.getEnemyStatus() != 0 ){
                            combat = player1->Combat();
                            if(combat == "escape")
                                player1->setCurrent(player1->getCurrent()->u);
                        }

				}
				else if(userInput == "l"){
					player1->setCurrent(player1->getCurrent()->l);

					if(player1->getCurrent()->info.getUsedAreaCurr() == false){ // if the room is not visted before
                        player1->setPlayerMoney(player1->getPlayerMoney() + player1->getCurrent()->info.getAreaCurrency()); // players currency + rooms currency
                        player1->getCurrent()->info.setAreaCurrency(0);     // sets the areas currency equal to zero
                        player1->getCurrent()->info.setUsedAreaCurr();      // sets the room to visited
                    }

                    string combat;
                        if(player1->getCurrent()->info.enemy.isEmptyList() == false && player1->getCurrent()->info.getEnemyStatus() != 0 ){
                            combat = player1->Combat();
                            if(combat == "escape")
                                player1->setCurrent(player1->getCurrent()->r);
                        }

				}
				else if(userInput == "r"){
	  				player1->setCurrent(player1->getCurrent()->r);

	  				if(player1->getCurrent()->info.getUsedAreaCurr() == false){ // if the room is not visted before
                        player1->setPlayerMoney(player1->getPlayerMoney() + player1->getCurrent()->info.getAreaCurrency()); // players currency + rooms currency
                        player1->getCurrent()->info.setAreaCurrency(0);     // sets the areas currency equal to zero
                        player1->getCurrent()->info.setUsedAreaCurr();      // sets the room to visited
	  				}

                        string combat;
                        if(player1->getCurrent()->info.enemy.isEmptyList() == false && player1->getCurrent()->info.getEnemyStatus() != 0 ){
                            combat = player1->Combat();
                            if(combat == "escape")
                                player1->setCurrent(player1->getCurrent()->l);
                        }
				}
				else if(userInput == "iseedeadpeople"){ //issdeadpeople cheat code to reveal map
					//map.print();
					cout<<map;
				}
				else if(userInput == "reset"){
					resetGame();
				}
				else if(userInput == "exit"){
					cout<<"Good bye!"<<endl;
					return;
				}
				else if(userInput == "search"){
					player1->getCurrent()->info.search();
				}
				else if(userInput == "inventory"){
					player1->inventory();
				}
				else if(userInput == "take" || userInput == "pickup"){
					player1->take(item);    // passes item entered
				}
				else if(userInput == "leave" || userInput == "drop"){
					player1->leave(item);   // passes item entered
				}
				else if(userInput == "examine"){
					player1->examine(item); // passes item entered
				}
				else if(userInput == "help"){
					cout<<"You may type: "<<endl;
					cout<<"\t u, d, l, or r: to move up, down, left or right on the map,"<<endl;
					cout<<"\t search: to search for items in current area,"<<endl;
					cout<<"\t take: to attempt to take an item,"<<endl;
					cout<<"\t leave: to attempt to leave an item,"<<endl;
					cout<<"\t examine: to examine an item in your inventory,"<<endl;
					cout<<"\t use: to use an item, "<< endl;
					cout<<"\t consume: to consume an item, "<< endl;
					cout<<"\t reset: to reset the game,"<<endl;
					cout<<"\t exit: to exit the game."<<endl;
					cout<<endl;
				}
				else if(userInput == "stats"){
                    player1->reportStats();
				}
				else if(userInput == "use"){
                    player1->use(m, item);  // passes item entered
				}
				else if(userInput == "consume"){
                    player1->consume(m, item);  // passes item entered
				}
				else if(userInput == "interact"){
                    player1->interact();
				}
				else{
					cout<<"I do not understand: "<<userInput<<endl<<endl;
				}
				item = ""; // clear item
                temp = ""; // clear temp

                //string combat;
                //if(player1->getCurrent()->info.enemy.isEmptyList() == false && player1->getCurrent()->info.getEnemyStatus() != 0 ){
                //       combat = player1->Combat();
                 //      if(combat == "escape")

                //}
                cout << endl;
			}//end while
    		}//end play()

		void resetGame(){
		    if(map.Ptype == 2){
                player1->setCurrent(map.getStart());
                //remove item from player list
                player1->items.destroyList();
                player1->resetPlayerStats();
                //remove item from each area in turn
                map.resetItems();
                map.linkLinks();
                map.resetAreaCurrency(); // resets the currency found in the all areas
		    }
		    else{
                player1->setCurrent(map.getStart());
                //remove item from player list
                player1->items.destroyList();
                //remove item from each area in turn
                map.resetItems();
                map.linkLinks();
                map.resetAreaCurrency();
		    }
		}
};
