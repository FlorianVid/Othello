#include "../include/ArtificialIntelligence.h"
using namespace std;
ArtificialIntelligence::ArtificialIntelligence() : m_typeAI("none")
{} //string typeAI

void ArtificialIntelligence::set_typeAI(string typeAI)
{
    try
    {
        if(typeAI == "random" || typeAI == "greedy"){
            m_typeAI = typeAI;
        }
        else{
            throw string("ERROR: type of AI selected does not exist");
        }
    }
    catch(string const& chaine)
    {
        cerr << chaine << endl;
        exit(1);
    }
}

Coordinate ArtificialIntelligence::makeDecision(GameField gf) const{
    Coordinate res(0,0);
    try
    {
        if(m_typeAI == "random"){
            res = makeDecisionRandom(gf);
        }
        else if(m_typeAI == "greedy"){
            res = makeDecisionGreedy(gf);
        }
        else{
            throw string("ERROR: object type of AI was not defined");
        }
    }
    catch(string const& chaine)
    {
        cerr << chaine << endl;
    }
    return res;
}

Coordinate ArtificialIntelligence::makeDecisionRandom(GameField gf) const{
    int nbPlayablePos = gf.getNbPlayablePos();
    //cout << nbPlayablePos << " playable positions" << endl;
    int randPosChosen = rand() % nbPlayablePos;
    return gf.getNthPos(randPosChosen);
}

Coordinate ArtificialIntelligence::makeDecisionGreedy(GameField gf) const{
    Mid playablePos = gf.getPlayablePos();
    int nbPosTurnedMax(0);//variable to store the number of position of the opponent that would be turned if coordinate chosen
    Coordinate res(0,0);

    for (Mid::const_iterator iter = playablePos.begin(); iter != playablePos.end(); ++iter){
        if(iter->second.size() > nbPosTurnedMax){
            res = iter->first;
            nbPosTurnedMax = iter->second.size();
        }
    }
    return res;
}
