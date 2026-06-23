#include "Item.h"

class ConsumeItem : public Item
{
    private:
        vector<Effect*> effVec;
    public:
        void setActiveMessage(string s){
            activeMessage = s;
		}
        string getActiveMessage(){
            //Objects of the Item (basic items) class don't have active messages.
            return activeMessage;
		}

		void setActiveArea(int i){
            activeArea = i;
		}
		int getActiveArea(){
            //as this is a basic item, it doesn't have an active area
            return activeArea;
		}

		void addEffect(Effect* temp){
		    Effect* e = new Effect;
		    e->effectAmt = temp->effectAmt;
		    e->effectID = temp->effectID;
            effVec.push_back(e);
			//cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have associated effects."<<endl;
		}
        vector<Effect*> getItemConsumeEffects(){
			//shouldn't ever call this method directly
			vector<Effect*> blank;
			if(!effVec.empty()){
                blank = effVec;
                return blank;
			}
			else{
                //effVec[0]->effectID = -1;
                //blank = effVec;
                return blank;
			}
		}

};
