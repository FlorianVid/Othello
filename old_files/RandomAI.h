#ifndef RANDOMAI_H
#define RANDOMAI_H

#include <ArtificialIntelligence.h>


class RandomAI : public ArtificialIntelligence
{
    public:
        RandomAI(std::string name) : ArtificialIntelligence(name){}
        virtual Coordinate makeDecision(GameField gf);

    protected:

    private:
};

#endif // RANDOM_H
