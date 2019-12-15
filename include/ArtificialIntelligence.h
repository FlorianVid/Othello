#ifndef ARTIFICIALINTELLIGENCE_H
#define ARTIFICIALINTELLIGENCE_H

#include <string>
#include <iostream>
#include "coordinates.h"
#include "GameField.h"
#include <cstdlib>

class ArtificialIntelligence
{
    //methods
    public:
        ArtificialIntelligence();
        ArtificialIntelligence(std::string nom);
        Coordinate makeDecision(GameField gf) const;
        void set_typeAI(std::string typeAI);
    private:
        Coordinate makeDecisionRandom(GameField gf) const;
        Coordinate makeDecisionGreedy(GameField gf) const;

    protected:

    //attributes
    private:
    std::string m_typeAI;

    protected:

};

#endif // ARTIFICIALINTELLIGENCE_H
