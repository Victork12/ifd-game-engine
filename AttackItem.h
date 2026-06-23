#include "Item.h"

class AttackItem : public Item
{
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

};
