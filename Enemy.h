#include <iostream>
#include <vector>
#include <string>
using namespace std;

#ifndef H_Enemy
#define H_Enemy

class Enemy{
    public:
        void setEnemyName(string n){
            enemyName = n;
        }

        string getEnemyName(){
            return enemyName;
        }

        void setEnemyDesc(string d){
            enemyDesc = d;
        }

        string getEnemyDesc(){
            return enemyDesc;
        }

        void setEnemySR(int s){
            enemySR = s;
        }

        int getEnemySR(){
            return enemySR;
        }

        void setEnemyAm(string a){
            enemyAm = a;
        }

        string getEnemyAm(){
            return enemyAm;
        }

        double getEnemyState(){
            return enemyState;
        }

        void setEnemyState(double s){
            enemyState = s;
        }


        int getEnemyDamage(){
            return enemyDamage;
        }

        void setEnemyDamage(int d){
            enemyDamage = d;
        }


    protected:
        string enemyName;
        string enemyDesc;
        int enemySR;
        string enemyAm;
        double enemyState;
        int enemyDamage;
};

#endif // H_Item
