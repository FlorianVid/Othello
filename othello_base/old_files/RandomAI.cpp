#include "RandomAI.h"
using namespace std;

//RandomAI::RandomAI(string nom)
//{
//ArtificialIntelligence(string nom)
//}

Coordinate RandomAI::makeDecision(GameField gf){
    int nbPlayablePos = gf.getNbPlayablePos();
    cout << nbPlayablePos << " playable positions" << endl;
    int randPosChosen = rand() % nbPlayablePos;
    return gf.getNthPos(randPosChosen);
}

