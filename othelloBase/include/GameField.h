#ifndef DEF_GAMEFIELD
#define DEF_GAMEFIELD

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "coordinates.h"
#include <map>
#include <tuple>
#include <stdexcept>

typedef std::multimap< Coordinate, std::vector<Coordinate>, std::less<Coordinate> > Mid;

class GameField
{
    //methods
    public:
    GameField();
    void printNameGame() const;
    int get_SIZE_FIELD() const;
    int get_m_nbTurn() const;
    void plotGameFieldClass() const;
    int setPositions(Coordinate coord, int playerId);
    void nextTurn();
    int getNbPlayablePos() const;
    Coordinate getNthPos(int n) const;
    std::tuple<int, int> getScore() const;
    Mid getPlayablePos() const;

    ~GameField();
    private:
    bool checkPlayablePos(Coordinate coord) const;
    bool checkPosInField(Coordinate coord) const;
    void updatePlayablePos(int playerId);

    //attributes
    private:
    static const int SIZE_FIELD = 8;
    int m_positions[SIZE_FIELD][SIZE_FIELD] = {0};
    int m_activePlayer;
    int m_nbTurn;
    std::string m_nameGame;
    Mid m_playablePos;//list of playable positions nx2
    std::vector<Coordinate> m_playablePosVect;

};

#endif // GAMEFIELD_H
