#ifndef GREEDYAI_H
#define GREEDYAI_H

#include <ArtificialIntelligence.h>


class GreedyAI : public ArtificialIntelligence
{
    public:
        GreedyAI(std::string name) : ArtificialIntelligence(name){}
        virtual Coordinate makeDecision(GameField gf);

    protected:

    private:
};

#endif // GREEDYAI_H
