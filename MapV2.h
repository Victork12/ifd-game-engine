#include <iostream>
#include "Map.h"

#include "BasicPlayer.h"
#include "HPSPPlayer.h"
#include "UseItem.h"
#include "ConsumeItem.h"
#include "AttackItem.h"
#include "Enemy.h"

class MapV2 : public Map
{
    private:
        vector<Item*> itemsVec;     // vector for Item
        //vector<UseItem*>useitemsVec;
        vector<Item*> merchVec;
        vector<Enemy*> enemyVec;


    public:
        MapV2() : Map(){
            ifderr = false;
			parser.tokenIt();

			nextToken = parser.getNext();

			if(nextToken == "<game>"){
				parser.eatToken();
				nextToken = parser.getNext();
				while(nextToken != "</game>"){  //consider what happens when run out of tokens && not error state
					if(nextToken == "<area>"){
						parser.eatToken();
						nextToken = parser.getNext();
						makeArea();
					}
					else if(nextToken == "<ptype>"){
                        parser.eatToken();
                        nextToken = parser.getNext();
                        ptype();
					}
					else if(nextToken == "<links>"){
						parser.eatToken();
						nextToken = parser.getNext();
						makeLinks();
					}
					else if(nextToken == "<item>"){
                        parser.eatToken();
                        nextToken = parser.getNext();
                        makeItem();
					}
					else if(nextToken == "<enemy>"){
                        parser.eatToken();
                        nextToken = parser.getNext();
                        makeEnemy();
					}
                    else if(nextToken == "<merch>"){
                        parser.eatToken();
                        nextToken = parser.getNext();

                        makeMerchant();
                    }
					else{
						cout<<"Parse Error Location 1"<<endl;
						ifderr = true;
						break;
					}
					parser.eatToken();
					nextToken = parser.getNext();
				}// while !</game>

				if(ifderr){
					cout<<" :: ERROR :: IF Document Formatting Error"<<endl;
					cout<<"Game Loading Failed"<<endl;
					cout<<"General Area of Parsing Failure:"<<endl;
					cout<<"-------------------------------------"<<endl;
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					cout<<"-------------------------------------"<<endl;
					return;
				}
				//cout<<"::Found </game>::"<<endl;
			}
			else{
				cout<<" :: ERROR :: No \"<game>\" tag found."<<endl;
				cout<<"Game Loading Failed"<<endl;
			}

			//link up areas
			linkLinks();
			insertItems();  // links the items to the areas
			insertEnemy();
			insertMerch();
        }


         void ptype(){
            while(nextToken != "</ptype>"){
                if(nextToken == "basic"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    Ptype = 1;
                }
                if(nextToken == "hpsp"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    Ptype = 2;
                }
            }
        }

        int Ptype;


        void makeEnemy(){
            string xstr;
            Enemy* en = new Enemy;
            int room;
            double status;

            while(nextToken != "</enemy>"){
                if(nextToken == "<name>"){
                    parser.eatToken();
                    nextToken = parser.getNext();

                    en->setEnemyName(nextToken);
                }
                else if(nextToken == "<desc>"){
                    parser.eatToken();
                    nextToken = parser.getNext();

                    en->setEnemyDesc(nextToken);    // sets nextToken to Desc
                }
                else if(nextToken == "<star>"){
                    parser.eatToken();
                    nextToken = parser.getNext();

                    istringstream ss(nextToken);        // turns the string to int
                    getline(ss, xstr);
                    room = atoi(xstr.c_str());
                    en->setEnemySR(room);       // sets room to Set Room
                }
                //else if(Ptype == 2){
                else if(nextToken == "<actmess>"){
                    parser.eatToken();
                    nextToken = parser.getNext();

                    en->setEnemyAm(nextToken);
                }
                else if(nextToken == "<enemyAct>"){
                    parser.eatToken();
                    nextToken = parser.getNext();

                    istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    status = (atoi(xstr.c_str()));
                    en->setEnemyState(status);

                    getline(ss, xstr, ',');
					en->setEnemyDamage(atoi(xstr.c_str()));
                }
                else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>" || nextToken == "</actmess>" || nextToken == "</actar>" || nextToken == "</enemyAct>" ){
                            // do nothing
                }
                parser.eatToken();
                nextToken = parser.getNext();
                enemyVec.push_back(en);
            }
            //parser.eatToken();
           // nextToken = parser.getNext();
        }


        void makeMerchant(){
            while(nextToken != "</merch>"){
                if(nextToken == "<item>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeMerch2();
                }
            }
        }

        void makeMerch2(){
            string xstr;
            int room;

            Item* tempNodeptr = new Item;
            UseItem* ptr = new UseItem;
            ConsumeItem* cptr = new ConsumeItem;
            AttackItem* attack = new AttackItem;
            Rule* temp = new Rule;

            Effect* eff, e;
            eff = &e;

            while(nextToken != "</item>"){  // Loops until </item>
                if(nextToken == "<basic>"){
                    while(nextToken != "</basic>"){
                        if(nextToken == "<name>"){
                            parser.eatToken();
                            nextToken = parser.getNext();
                            tempNodeptr->setName(nextToken);
                        }
                        else if(nextToken == "<desc>"){
                            parser.eatToken();
                            nextToken = parser.getNext();
                            tempNodeptr->setDesc(nextToken);    // sets nextToken to Desc
                        }
                        else if(nextToken == "<star>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            istringstream ss(nextToken);        // turns the string to int
                            getline(ss, xstr);
                            room = atoi(xstr.c_str());
                            tempNodeptr->setSR(room);       // sets room to Set Room
                        }
                        else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>"){
                            // do nothing
                        }
                        parser.eatToken();
                        nextToken = parser.getNext();
                    }
                    merchVec.push_back(tempNodeptr);
                }
                if(nextToken == "<use>"){

                    while(nextToken != "</use>"){
                        if(nextToken == "<name>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            ptr->setName(nextToken);
                        }
                        else if(nextToken == "<desc>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            ptr->setDesc(nextToken);    // sets nextToken to Desc
                        }
                        else if(nextToken == "<star>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            istringstream ss(nextToken);        // turns the string to int
                            getline(ss, xstr);
                            room = atoi(xstr.c_str());
                            ptr->setSR(room);       // sets room to Set Room
                        }
                        //else if(Ptype == 2){
                            else if(nextToken == "<actmess>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                ptr->setActiveMessage(nextToken);
                            }
                            else if(nextToken == "<actar>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                istringstream ss(nextToken);        // turns the string to int
                                getline(ss, xstr);
                                room = atoi(xstr.c_str());
                                ptr->setActiveArea(room);
                            }
                            else if(nextToken == "<rule>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                string d;

                                istringstream ss(nextToken);
                                getline(ss, xstr, ',');
                                temp->beginRm = atoi(xstr.c_str());

                                getline(ss, xstr, ',');
                                d = xstr;
                                if(d== "u")
                                    temp->direction = 'u';
                                if(d== "d")
                                    temp->direction = 'd';
                                if(d== "l")
                                    temp->direction = 'l';
                                if(d== "r")
                                    temp->direction = 'r';

                                getline(ss, xstr, ',');
                                temp->destRm = atoi(xstr.c_str());

                                ptr->addRule(temp);
                            }
                            else if(nextToken == "<currency>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                int tempcur;

                                istringstream ss(nextToken);        // turns the string to int
                                getline(ss, xstr);
                                tempcur = atoi(xstr.c_str());

                                cptr->setCurrency(tempcur);

                            }
                    //}
                        else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>" || nextToken == "</actmess>" || nextToken == "</actar>" || nextToken == "</rule>" ){
                            // do nothing
                        }
                        parser.eatToken();
                        nextToken = parser.getNext();
                        //cout << nextToken;
                    }
                    merchVec.push_back(ptr);
                }
                if(nextToken == "<consume>"){
                    while(nextToken != "</consume>"){
                        if(nextToken == "<name>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            cptr->setName(nextToken);
                        }
                        else if(nextToken == "<desc>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            cptr->setDesc(nextToken);    // sets nextToken to Desc
                        }
                        else if(nextToken == "<star>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            istringstream ss(nextToken);        // turns the string to int
                            getline(ss, xstr);
                            room = atoi(xstr.c_str());
                            cptr->setSR(room);       // sets room to Set Room
                        }
                        //else if(Ptype == 2){
                        else if(nextToken == "<actmess>"){
                                parser.eatToken();
                                nextToken = parser.getNext();


                                cptr->setActiveMessage(nextToken);
                        }
                        else if(Ptype == 2){
                            if(nextToken == "<actar>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                istringstream ss(nextToken);        // turns the string to int
                                getline(ss, xstr);
                                room = atoi(xstr.c_str());
                                cptr->setActiveArea(room);
                            }
                            else if(nextToken == "<effect>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                istringstream ss(nextToken);
                                getline(ss, xstr, ',');
                                eff->effectID = atoi(xstr.c_str());

                                getline(ss, xstr, ',');
                                eff->effectAmt = atoi(xstr.c_str());

                                cptr->addEffect(eff);

                            }
                            else if(nextToken == "<currency>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                int tempcur;

                                istringstream ss(nextToken);        // turns the string to int
                                getline(ss, xstr);
                                tempcur = atoi(xstr.c_str());

                                cptr->setCurrency(tempcur);

                            }
                        }
                        else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>" || nextToken == "</actmess>" || nextToken == "</actar>" || nextToken == "</effect>" || nextToken == "</currency>"){
                            // do nothing
                        }
                        parser.eatToken();
                        nextToken = parser.getNext();

                    }
                    merchVec.push_back(cptr);
                }
                if(nextToken == "<attack>"){
                    while(nextToken != "</attack>"){
                        if(nextToken == "<name>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            attack->setName(nextToken);
                        }
                        else if(nextToken == "<desc>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            attack->setDesc(nextToken);    // sets nextToken to Desc
                        }
                        else if(nextToken == "<star>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            istringstream ss(nextToken);        // turns the string to int
                            getline(ss, xstr);
                            room = atoi(xstr.c_str());
                            attack->setSR(room);       // sets room to Set Room
                        }
                        //else if(Ptype == 2){
                        else if(nextToken == "<actmess>"){
                                parser.eatToken();
                                nextToken = parser.getNext();


                                attack->setActiveMessage(nextToken);
                        }
                        else if(Ptype == 2){
                            if(nextToken == "<actar>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                istringstream ss(nextToken);        // turns the string to int
                                getline(ss, xstr);
                                room = atoi(xstr.c_str());
                                attack->setActiveArea(room);
                            }
                            else if(nextToken == "<currency>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                int tempcur;

                                istringstream ss(nextToken);        // turns the string to int
                                getline(ss, xstr);
                                tempcur = atoi(xstr.c_str());

                                attack->setCurrency(tempcur);

                            }
                        }
                        else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>" || nextToken == "</actmess>" || nextToken == "</actar>" || nextToken == "</currency>"){
                            // do nothing
                        }
                        parser.eatToken();
                        nextToken = parser.getNext();
                    }
                    merchVec.push_back(attack);
                }
                parser.eatToken();
                nextToken = parser.getNext();
            }
            parser.eatToken();
            nextToken = parser.getNext();
        }

        void makeItem(){
            string xstr;
            int room;

            Item* tempNodeptr = new Item;
            UseItem* ptr = new UseItem;
            ConsumeItem* cptr = new ConsumeItem;
            Rule* temp = new Rule;

            Effect* eff, e;
            eff = &e;

            while(nextToken != "</item>"){  // Loops until </item>
                if(nextToken == "<basic>"){
                    while(nextToken != "</basic>"){
                        if(nextToken == "<name>"){
                            parser.eatToken();
                            nextToken = parser.getNext();
                            tempNodeptr->setName(nextToken);
                        }
                        else if(nextToken == "<desc>"){
                            parser.eatToken();
                            nextToken = parser.getNext();
                            tempNodeptr->setDesc(nextToken);    // sets nextToken to Desc
                        }
                        else if(nextToken == "<star>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            istringstream ss(nextToken);        // turns the string to int
                            getline(ss, xstr);
                            room = atoi(xstr.c_str());
                            tempNodeptr->setSR(room);       // sets room to Set Room
                        }
                        else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>"){
                            // do nothing
                        }
                        parser.eatToken();
                        nextToken = parser.getNext();
                    }
                    itemsVec.push_back(tempNodeptr);
                }
                if(nextToken == "<use>"){

                    while(nextToken != "</use>"){
                        if(nextToken == "<name>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            ptr->setName(nextToken);
                        }
                        else if(nextToken == "<desc>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            ptr->setDesc(nextToken);    // sets nextToken to Desc
                        }
                        else if(nextToken == "<star>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            istringstream ss(nextToken);        // turns the string to int
                            getline(ss, xstr);
                            room = atoi(xstr.c_str());
                            ptr->setSR(room);       // sets room to Set Room
                        }
                        //else if(Ptype == 2){
                            else if(nextToken == "<actmess>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                ptr->setActiveMessage(nextToken);
                            }
                            else if(nextToken == "<actar>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                istringstream ss(nextToken);        // turns the string to int
                                getline(ss, xstr);
                                room = atoi(xstr.c_str());
                                ptr->setActiveArea(room);
                            }
                            else if(nextToken == "<rule>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                string d;

                                istringstream ss(nextToken);
                                getline(ss, xstr, ',');
                                temp->beginRm = atoi(xstr.c_str());

                                getline(ss, xstr, ',');
                                d = xstr;
                                if(d== "u")
                                    temp->direction = 'u';
                                if(d== "d")
                                    temp->direction = 'd';
                                if(d== "l")
                                    temp->direction = 'l';
                                if(d== "r")
                                    temp->direction = 'r';

                                getline(ss, xstr, ',');
                                temp->destRm = atoi(xstr.c_str());

                                ptr->addRule(temp);
                            }
                    //}
                        else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>" || nextToken == "</actmess>" || nextToken == "</actar>" || nextToken == "</rule>" ){
                            // do nothing
                        }
                        parser.eatToken();
                        nextToken = parser.getNext();
                        //cout << nextToken;
                    }
                    itemsVec.push_back(ptr);
                }
                if(nextToken == "<consume>"){
                    while(nextToken != "</consume>"){
                        if(nextToken == "<name>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            cptr->setName(nextToken);
                        }
                        else if(nextToken == "<desc>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            cptr->setDesc(nextToken);    // sets nextToken to Desc
                        }
                        else if(nextToken == "<star>"){
                            parser.eatToken();
                            nextToken = parser.getNext();

                            istringstream ss(nextToken);        // turns the string to int
                            getline(ss, xstr);
                            room = atoi(xstr.c_str());
                            cptr->setSR(room);       // sets room to Set Room
                        }
                        //else if(Ptype == 2){
                        else if(nextToken == "<actmess>"){
                                parser.eatToken();
                                nextToken = parser.getNext();


                                cptr->setActiveMessage(nextToken);
                        }
                        else if(Ptype == 2){
                            if(nextToken == "<actar>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                istringstream ss(nextToken);        // turns the string to int
                                getline(ss, xstr);
                                room = atoi(xstr.c_str());
                                cptr->setActiveArea(room);
                            }
                            else if(nextToken == "<effect>"){
                                parser.eatToken();
                                nextToken = parser.getNext();

                                istringstream ss(nextToken);
                                getline(ss, xstr, ',');
                                eff->effectID = atoi(xstr.c_str());

                                getline(ss, xstr, ',');
                                eff->effectAmt = atoi(xstr.c_str());

                                cptr->addEffect(eff);

                            }
                        }
                        else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>" || nextToken == "</actmess>" || nextToken == "</actar>" || nextToken == "</affect>" ){
                            // do nothing
                        }
                        parser.eatToken();
                        nextToken = parser.getNext();
                    }
                    itemsVec.push_back(cptr);
                }
                parser.eatToken();
                nextToken = parser.getNext();
            }

            //itemsVec.push_back(tempNodeptr);    // adds the tempNodeptr to the itemsVec vector
            //itemsVec.push_back(ptr);
        }

        void insertItems(){     // sets the Items to the Areas
            for(int i=0; i<areasVec.size();i++){
                for(int j=0; j<itemsVec.size();j++)
                    if(itemsVec[j]->getSR()== i+1)  //Loop for verifying itemVec is equal to the set room area
                        areasVec[i]->info.items.insertLast(itemsVec[j]);    // adds node at the end of items

                }
        }


        void insertMerch(){
            for(int i=0; i<areasVec.size();i++){
                for(int j=0; j<merchVec.size();j++)
                    if(merchVec[j]->getSR()== i+1)  //Loop for verifying itemVec is equal to the set room area
                        areasVec[i]->info.merchant.insertLast(merchVec[j]);    // adds node at the end of items
                }

        }

        void insertEnemy(){     // sets the Items to the Areas
            for(int i=0; i<areasVec.size();i++){
                for(int j=0; j<enemyVec.size();j++)
                    if(enemyVec[j]->getEnemySR()== i+1)  //Loop for verifying itemVec is equal to the set room area
                        areasVec[i]->info.enemy.insertLast(enemyVec[j]);    // adds node at the end of items

                }
        }

        void resetItems(){
            for(int i=0; i<areasVec.size(); i++)        // Loops through all areas initializing
                areasVec[i]->info.items.initializeList();
            insertItems();      // sets items to areas

        }

        void resetAreaCurrency(){
            for(int i=0; i<areasVec.size(); i++){       // Loops through all areas initializing
                areasVec[i]->info.merchant.initializeList();
                //areasVec[i]->info.setAreaCurrency(areasVec[i]->info.getOriginalCurrency());
                areasVec[i]->info.resetRoomUsed();
            }
            insertMerch();      // sets items to areas
        }

        friend ostream& operator<<(ostream& os, MapV2&mp){
            mp.print(); // prints the area cheat from Map
            os<<"******************************************************************"<<endl;
			os<<"CHEATING!!!! ITEM LOCATIONS FOR ALL NON-INVENTORY ITEMS."<<endl;
			os<<"******************************************************************"<<endl;

            for(int i=0; i<mp.areasVec.size(); i++){    // for loop for area
				os<<"Items for area "<<i << ": ";
				os<<mp.areasVec[i]->info.getDescription()<<endl;    // prints area desc
				if(mp.areasVec[i]->info.items.isEmptyList()){   // if theres no items in the area
                    cout << "No items in list." << endl;
				}
				for(int j=0; j<mp.itemsVec.size(); j++){    // loop for item
                    if(mp.itemsVec[j]->getSR() == i+1)  // if the Item set room is equal to the area
                        os<<"\t" << mp.itemsVec[j]->getName()<< endl;
				}
            }
            return os;
        }
};
