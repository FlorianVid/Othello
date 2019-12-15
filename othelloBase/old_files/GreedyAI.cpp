#include "GreedyAI.h"
using namespace std;

//GreedyAI::GreedyAI()// : ArtificialIntelligence()
//{
    //ctor
//}

Coordinate GreedyAI::makeDecision(GameField gf){
    Mid playablePos = gf.getPlayablePos();
    int nbPosTurnedMax(0);//variable to store the number of position of the opponent that would be turned if coordinate chosen
    Coordinate res(0,0);

    for (Mid::const_iterator iter = playablePos.begin(); iter != playablePos.end(); ++iter){
        //cout << "key" << '\t'<< iter->first.row << '\t' << iter->first.col << '\n';
        //cout << "Nb pos to switch: " << iter->second.size() << endl;
        if(iter->second.size() > nbPosTurnedMax){
            res = iter->first;
            nbPosTurnedMax = iter->second.size();
        }

//        for(auto i : iter->second){
//            cout <<  "value" << '\t' << i.row << '\t' << i.col << '\n';
//        }
    }
    //cout << nbPosTurnedMax << endl;
    return res;

//    int nbPlayablePos = gf.getNbPlayablePos();
//    int randPosChosen = rand() % nbPlayablePos;
//    return gf.getNthPos(randPosChosen);

}

