#include <iostream>
#include <string>
#include "./include/GameField.h"
#include "./include/ArtificialIntelligence.h"
#include "./include/coordinates.h"
#include <tuple>

#include <ctime>
#include <cmath>

using namespace std;

int main(){

    cout << "%%%%%%\nRandom AI against greedy AI... \nwho will win?\n%%%%%%" << endl;
    srand(time(NULL));
    //launch 100 games, see who win each time
    int nbIt = 1;//number of iterations
    //define AI that fight
    ArtificialIntelligence aiRandom;
    aiRandom.set_typeAI("random");
    int playerRandomId = 1;
    ArtificialIntelligence aiGreedy;
    aiGreedy.set_typeAI("greedy");
    int playerGreedyId = 2;

    //initialization othello field
    GameField othelloField;
    othelloField.printNameGame();
    othelloField.plotGameFieldClass();
    int nbTurnTotal(othelloField.get_SIZE_FIELD()*othelloField.get_SIZE_FIELD());

    int gameOnGoing;
    int playerId = 1;//here random starts
    Coordinate coordChosen(0,0);
    for(int i = 0; i<nbIt; i++){
        gameOnGoing = 1;
        while( gameOnGoing == 1 ){
            if(playerId == playerRandomId){
                coordChosen = aiRandom.makeDecision(othelloField);
            }
            else if(playerId == playerGreedyId){
                coordChosen = aiGreedy.makeDecision(othelloField);//aiGreedy
            }
            cout << coordChosen.row << " " << coordChosen.col << endl;
            othelloField.setPositions(coordChosen,playerId);

            othelloField.nextTurn();
            playerId = playerId%2 + 1;//if playerId == 1 -> 2 if playerId == 2 -> 1
            //othelloField.plotGameFieldClass();
            if(othelloField.get_m_nbTurn() == nbTurnTotal - 3){//remove the 4 original positions
                gameOnGoing = 0;
            }
        }
    }

    tuple<int, int> res = othelloField.getScore();
    if( get<0>(res) > get<1>(res) ){
        cout << "Random player won " << get<0>(res) << " against " << get<1>(res) << endl;
    }
    else{
        cout << "Greedy player won " << get<1>(res) << " against " << get<0>(res) << endl;
    }

    //othelloField.plotGameFieldClass();
//    const int NUMBERS = 10;
//    double randvalue;
//    int n;
//    srand(1);
//    for (n = 0; n<NUMBERS; n++){
//        randvalue = rand();
//        cout << randvalue << endl;
//    }

    return 0;
}
