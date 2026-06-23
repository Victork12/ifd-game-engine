#include "Item.h"

#ifndef H_UseItem
#define H_UseItem
class UseItem : public Item
{
    private:
        //Rule *rule;
        vector<Rule*> ruleVec;

    public:

        void setActiveMessage(string s){
            activeMessage = s;
            //cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have active messages."<<endl;
		}
        string getActiveMessage(){
            //Objects of the Item (basic items) class don't have active messages.
            return activeMessage;
		}

		void setActiveArea(int i){
		    activeArea = i;
            //cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have active areas."<<endl;
		}
		int getActiveArea(){
            //as this is a basic item, it doesn't have an active area
            return activeArea;
		}

		void addRule(Rule* temp){
            Rule *r = new Rule;
            r->beginRm = temp->beginRm;
            r->direction = temp->direction;
            r->destRm = temp->destRm;

            ruleVec.push_back(r);

			//cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have associated rules."<<endl;
		}

        vector<Rule*> getItemUseRules(){
            //shouldn't ever call this method directly
            vector<Rule*> blank;
            //blank = ruleVec;
            //return blank;
            if(!ruleVec.empty()){
                blank = ruleVec;
                return blank;
			}
			else{
                //ruleVec[0]->beginRm = -1;
                //blank = ruleVec;
                return blank;
			}
		}

		vector<Effect*> getItemConsumeEffects(){
			//shouldn't ever call this method directly
			vector<Effect*> blank;
			return blank;

		}

};

#endif // H_UseItem
