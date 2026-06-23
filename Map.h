#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "IFDParser.h"
#include "LinkData.h"
#include "Area.h"

using namespace std;

struct areaNode
{
	Area info;
	areaNode *u;
	areaNode *d;
	areaNode *l;
	areaNode *r;
};

class Map{
	protected:
		vector<areaNode*> areasVec;
		int areacnt =0;

		//Here is the instance of IFDParser
	  	IFDParser parser;

		//Some additional class attributes here
        vector<LinkData*> linkVec;
		string nextToken;

		bool ifderr;

	public:
		Map(){
		}//constructor

		void makeArea(){
			int id;
			int goal;
			string xstr;
            int mch;

			areaNode* tempNodePtr = new areaNode;

			while(nextToken != "</area>"){
                if(nextToken == "<acurr>"){
                    parser.eatToken();
                    nextToken = parser.getNext();

                    int tempcur;

                    istringstream ss(nextToken);        // turns the string to int
                    getline(ss, xstr);
                    tempcur = atoi(xstr.c_str());

                    tempNodePtr->info.setAreaCurrency(tempcur); // sets area currency
                    tempNodePtr->info.setOriginalCurrency(tempcur); // keeps track of original area currency
                }
				else if(nextToken == "<desc>"){
					parser.eatToken();
					nextToken = parser.getNext();

					tempNodePtr->info.setDescription(nextToken);
				}
				else if(nextToken == "<feats>"){
					parser.eatToken();
					nextToken = parser.getNext();

					istringstream ss(nextToken);
          				getline(ss, xstr, ',');
          				tempNodePtr->info.setID(atoi(xstr.c_str()));

          				getline(ss, xstr, ',');
					tempNodePtr->info.setGoal(atoi(xstr.c_str()));
				}
				else if(nextToken == "<mrc>"){
                    parser.eatToken();
					nextToken = parser.getNext();

                    istringstream ss(nextToken);
                    getline(ss, xstr);
                    tempNodePtr->info.setMerch(atoi(xstr.c_str()));

				}
				else if(nextToken == "</desc>" || nextToken == "</feats>" || nextToken == "</mrc>" || nextToken == "</acurr>"){
				  //do nothing
				}
				else{
					cout<<"Parse Error Location 2"<<endl;
					ifderr = true;
					break;
				}

				parser.eatToken();
				nextToken = parser.getNext();

			}//while !</area>

            areacnt++;          // Sets Area Number
            tempNodePtr->info.setArea(areacnt); // Sets Area Number
			//add area to vector
			areasVec.push_back(tempNodePtr);

		} //end makeArea()

		void makeLinks(){
			string xstr;
			int u, d, l, r;
			while(nextToken != "</links>"){
				if(nextToken == "<linkset>"){
					parser.eatToken();
			  		nextToken = parser.getNext();

					LinkData* tempLDPtr = new LinkData;

					istringstream ss(nextToken);
        				getline(ss, xstr, ',');
        				u = atoi(xstr.c_str());
        				getline(ss, xstr, ',');
        				d = atoi(xstr.c_str());
                        getline(ss, xstr, ',');
        				l = atoi(xstr.c_str());
                        getline(ss, xstr, ',');
                        r = atoi(xstr.c_str());

					tempLDPtr->setDigits(u, d, l, r);
          				linkVec.push_back(tempLDPtr);
				}
				else if(nextToken == "</linkset>"){
					//do nothing
				}
				else{
					cout<<"Parse Error Location 3"<<endl;
					ifderr = true;
					break;
				}
				parser.eatToken();
			  	nextToken = parser.getNext();
			}//while !</links>
		}//makeLinks()


		void linkLinks(){
			for(int i=0; i<linkVec.size(); i++){
					areasVec[i]->u = areasVec[(linkVec[i]->getDigit(0))-1];
					areasVec[i]->d = areasVec[(linkVec[i]->getDigit(1))-1];
					areasVec[i]->l = areasVec[(linkVec[i]->getDigit(2))-1];
					areasVec[i]->r = areasVec[(linkVec[i]->getDigit(3))-1];
			}
		}


		void makeRules(vector<Rule*> temp, Map* map){
            for(int i=0; i<temp.size(); i++){
                    if(temp[i]->direction == 'u'){
                        map->areasVec[temp[i]->beginRm-1]->u = map->areasVec[temp[i]->destRm-1];
                    }
                    if(temp[i]->direction == 'd'){
                        map->areasVec[temp[i]->beginRm-1]->d = map->areasVec[temp[i]->destRm-1];
                    }
                    if(temp[i]->direction == 'l'){
                        map->areasVec[temp[i]->beginRm-1]->l = map->areasVec[temp[i]->destRm-1];
                    }
                    if(temp[i]->direction == 'r'){
                        map->areasVec[temp[i]->beginRm-1]->r = map->areasVec[temp[i]->destRm-1];
                    }
			}
        }


		areaNode* getStart(){
			return areasVec[0];  //returns a pointer to the first area listed
		}

		void print(){
			cout<<"******************************************************************"<<endl;
			cout<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
			cout<<"******************************************************************"<<endl;
			for(int i=0; i<areasVec.size(); i++){
				cout<<"This is area: "<<i+1<<endl;
				cout<<areasVec[i]->info.getDescription()<<endl;
				if(areasVec[i]->info.getID() == 1){
					cout<<"Area is INSTADEATH."<<endl;
				}
				if(areasVec[i]->info.getGoal() == 1){
					cout<<"Area is GOAL."<<endl;
				}
				cout<<"Connections:"<<endl;
				cout<<"\t u: Area #"<<reverseLookUp(areasVec[i]->u)<<endl;
				cout<<"\t d: Area #"<<reverseLookUp(areasVec[i]->d)<<endl;
				cout<<"\t l: Area #"<<reverseLookUp(areasVec[i]->l)<<endl;
				cout<<"\t r: Area #"<<reverseLookUp(areasVec[i]->r)<<endl;
			}
		}

        friend ostream& operator<<(ostream& os, Map&mp){
            os<<"******************************************************************"<<endl;
			os<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
			os<<"******************************************************************"<<endl;
			for(int i=0; i<mp.areasVec.size(); i++){
				os<<"This is area: "<<i+1<<endl;
				os<<mp.areasVec[i]->info.getDescription()<<endl;
				if(mp.areasVec[i]->info.getID() == 1){
					os<<"Area is INSTADEATH."<<endl;
				}
				if(mp.areasVec[i]->info.getGoal() == 1){
					os<<"Area is GOAL."<<endl;
				}
				os<<"Connections:"<<endl;
				os<<"\t u: Area #"<<mp.reverseLookUp(mp.areasVec[i]->u)<<endl;
				os<<"\t d: Area #"<<mp.reverseLookUp(mp.areasVec[i]->d)<<endl;
				os<<"\t l: Area #"<<mp.reverseLookUp(mp.areasVec[i]->l)<<endl;
				os<<"\t r: Area #"<<mp.reverseLookUp(mp.areasVec[i]->r)<<endl;
			}
			return os;
		}

		int reverseLookUp(areaNode* addy){
			for(int i=0; i<areasVec.size(); i++){
				if(areasVec[i] == addy){
					return i+1;
				}
			}
			//this should not happen
			return -1;
		}


};
