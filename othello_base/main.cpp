#include <iostream>
#include <string>
#include "GameField.h"
#include "ArtificialIntelligence.h"
#include <tuple>
#include "updateScores.h"

using namespace std;

int main(){
    int playerId(1);//2 players id: 1 or 2 represented on the game field
    int move[2] = {0, 0}; //initialize active player's move
    int waitUserChoice(0);
    int gameOnGoing(1);
    int realPlayerId(0);// to know who start with the AI

    //initialization othello field
    GameField othelloField;
    othelloField.printNameGame();
    othelloField.plotGameFieldClass();
    int nbTurnTotal(othelloField.get_SIZE_FIELD()*othelloField.get_SIZE_FIELD());

    ArtificialIntelligence ai;//the casting looks very difficult to implement... different AI will be implemented in the same class but different methods
    int AI(0);
    int typeAI;
    cout << "Do you want to play with an AI?" << endl;
    cout << "1 -> yes" << '\n' << "0 -> no" << endl;
    int userIsChoosing(0);
    while (userIsChoosing == 0){
        cin >> AI;
        cin.ignore();
        if(AI == 0 || AI == 1){
            userIsChoosing = 1;
        }
        else{
            cout << "Choose AI = 0 or 1." << endl;
        }
    }
    if(AI == 1){
        //greedy or random
        userIsChoosing = 0;
        typeAI = 0;
        cout << "Which AI do you want to play against?" << endl;
        cout << "0 -> Level 0: random" << '\n' << "1 -> Level 1: greedy" << endl;
        while (userIsChoosing == 0){
            cin >> typeAI;
            cin.ignore();
            if(AI == 0 || AI == 1){
                userIsChoosing = 1;
            }
            else{
                cout << "Choose type AI = 0 or 1." << endl;
            }
        }

        if(typeAI == 0){
            ai.set_typeAI("random");
        }
        else{
            ai.set_typeAI("greedy");
        }

        userIsChoosing = 0;
        cout << "Do you wanna start?" << endl;
        cout << "1 -> yes" << '\n' << "0 -> no" << endl;
        while (userIsChoosing == 0){
            cin >> realPlayerId;
            cin.ignore();
            if(realPlayerId == 0 || realPlayerId == 1){
                userIsChoosing = 1;
            }
            else{
                cout << "Choose 0 or 1." << endl;
            }
        }
        if (realPlayerId == 0){
            realPlayerId = 2;
        }
        else{
            realPlayerId = 1;
        }
    }

    while( gameOnGoing == 1 ){
        waitUserChoice = 1;
        cout << "Player " << playerId << endl;
        cout << "Turn " << othelloField.get_m_nbTurn() << endl;
        //check if there is at least one playable solution
        //cout << "Number of playable positions: " << othelloField.giveNbPlayablePos() << endl;
        if(othelloField.getNbPlayablePos() > 0){
            if(AI == 1){
                if(playerId != realPlayerId){
                    Coordinate coordChosen = ai.makeDecision(othelloField);
                    cout << coordChosen.row << " " << coordChosen.col << endl;
                    othelloField.setPositions(coordChosen,playerId);
                }
                else{
                    while(waitUserChoice == 1){
                        cin >> move[0];
                        cin >> move[1];
                        cin.ignore();
                        Coordinate coordChosen(move[0],move[1]);
                        waitUserChoice = othelloField.setPositions(coordChosen,playerId);//if waitUserChoice == 0 valid position
                    }
                }
            }
            else{
                while(waitUserChoice == 1){
                    cin >> move[0];
                    cin >> move[1];
                    cin.ignore();
                    Coordinate coordChosen(move[0],move[1]);
                    waitUserChoice = othelloField.setPositions(coordChosen,playerId);//if waitUserChoice == 0 valid position
                }
            }
            othelloField.getScore();
            othelloField.nextTurn();
            playerId = playerId%2 + 1;//if playerId == 1 -> 2 if playerId == 2 -> 1
            othelloField.plotGameFieldClass();
            if(othelloField.get_m_nbTurn() == 6){//nbTurnTotal - 3){//remove the 4 original positions
                gameOnGoing = 0;
            }
        }
        else{
            othelloField.updatePlayablePos(playerId%2 + 1);
        }
    }

    tuple<int, int> res = othelloField.getScore();
    int winAI = 0;
    if(AI == 0){
        if( get<0>(res) > get<1>(res) ){
            cout << "Player 1 won";
        }
        else{
            cout << "Player 2 won";
        }
    }
    else{
        if( ( (get<0>(res) > get<1>(res)) && (realPlayerId == 1) ) || ( (get<0>(res) < get<1>(res)) && (realPlayerId == 2) ))
        {
            cout << "Congratulations you won the AI !" << endl;
            winAI = 1;
        }
        else{
            cout << "The AI won... Try again !" << endl;
        }
    }
    cout << "\n\n";//just make some space before the scoreboard

    //othelloField.plotGameFieldClass();
    if(AI == 1){
    //modify scores.txt file
        updateScores(typeAI, winAI);
    }
    return 0;
}
