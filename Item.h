#ifndef h_structs
#define h_structs
    #include "structs.h"
#endif

#include <string>
#include <iostream>
#include <vector>

using namespace std;

#ifndef H_Item
#define H_Item

class Item{
 	public:
        Item(){
            activeMessage = "That seems quite impossible.";
            activeArea = -1;
            type = "basic";
        }

        void setCurrency(int c){        // sets the merchant items cost
            currency = c;
        }

        int getCurrency(){      // returns the merchants items cost
            return currency;
        }

        void setName (string n){
            name = n;
        }
		void setDesc(string desc){
			description = desc;
		}
		void setSR(int rm){
			startRoom = rm;
		}
		string getName(){
            return name;
        }
        string getDesc(){
            return description;
        }
        int getSR(){
			return startRoom;
		}
		void displayName(){
			cout<<name<<endl;
		}
		void displayDesc(){
			cout<<description<<endl;
		}
		string getType(){
            return type;
		}

		virtual void setActiveMessage(string s){
            cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have active messages."<<endl;
		}
		virtual string getActiveMessage(){
            //Objects of the Item (basic items) class don't have active messages.
            string aM = "That proves impossible.";
            return aM;
		}
		virtual void setActiveArea(int i){
            cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have active areas."<<endl;
		}
		virtual int getActiveArea(){
            //as this is a basic item, it doesn't have an active area
            return -1;
		}
		virtual void addRule(Rule* temp){
			cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have associated rules."<<endl;
		}
        virtual vector<Rule*> getItemUseRules(){
            //cout << "shouldn't ever call this method directly" << endl;
            vector<Rule*> blank;
			return blank;
		}
		virtual void addEffect(Effect* temp){
			cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have associated effects."<<endl;
		}
        virtual vector<Effect*> getItemConsumeEffects(){
			//shouldn't ever call this method directly
            vector<Effect*> blank;
			return blank;
		}


	friend ostream& operator<<(ostream&, Item&);

    protected:
        string name;
    	string description;
        int startRoom;
        string activeMessage;
        int activeArea;
        string type;
        int currency;       // the cost;
};

ostream& operator<<(ostream& osObject, Item& item)
{
	osObject<<"Name: "<<item.getName()<<endl;
	osObject<<"Desc: "<<item.getDesc()<<endl;
	osObject<<"StrtRm: "<<item.getSR()<<endl;
	return osObject;
}

#endif // H_Item
