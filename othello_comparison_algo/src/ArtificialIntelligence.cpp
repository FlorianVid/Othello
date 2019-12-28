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
            res = makeDecisionCorner(gf);
        }
        else if(m_typeAI == "greedy"){

            res = makeDecisionGreedy(gf);//makeDecisionCorner(gf);makeDecisionGreedy
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
    cout << nbPlayablePos << " playable positions" << endl;
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

Coordinate ArtificialIntelligence::makeDecisionCorner(GameField gf) const{
//play toward positions at corner of the game field
    Mid playablePos = gf.getPlayablePos();
    Coordinate res(0,0);
    Coordinate temp(0,0);
    Coordinate corner1(0,0);
    Coordinate corner2(0,7);
    Coordinate corner3(7,0);
    Coordinate corner4(7,7);
    double distMin2corner = sqrt(2*pow(gf.get_SIZE_FIELD(), 2));//dist max
    double distMin2cornerTemp = 0;
    cout << "test" << endl;
    for (Mid::const_iterator iter = playablePos.begin(); iter != playablePos.end(); ++iter){
        temp = iter->first;
        distMin2cornerTemp = temp.computeDistance(corner1);
        if(distMin2cornerTemp < distMin2corner){
            res = temp;
            cout << "corner 1" << endl;
            distMin2corner = distMin2cornerTemp;
        }

        distMin2cornerTemp = temp.computeDistance(corner2);
        if(distMin2cornerTemp < distMin2corner){
            cout << "corner 2" << endl;
            res = temp;
            distMin2corner = distMin2cornerTemp;
        }

        distMin2cornerTemp = temp.computeDistance(corner3);
        if(distMin2cornerTemp < distMin2corner){
            cout << "corner 3" << endl;
            res = temp;
            distMin2corner = distMin2cornerTemp;
        }

        distMin2cornerTemp = temp.computeDistance(corner4);
        if(distMin2cornerTemp < distMin2corner){
            cout << "corner 4" << endl;
            res = temp;
            distMin2corner = distMin2cornerTemp;
        }
    }
    return res;
}
