#include "GameField.h"
//#include <iostream>
using namespace std;

GameField::GameField() : m_positions(), m_activePlayer(1), m_nbTurn(0), m_nameGame("Badass Othello")
{
    int res;
    Coordinate coord(3,3);
    res = setPositions(coord, 1);
    coord.row = 4;
    coord.col = 3;
    res = setPositions(coord, 2);
    coord.row = 4;
    coord.col = 4;
    res = setPositions(coord, 1);
    coord.row = 3;
    coord.col = 4;
    res = setPositions(coord, 2);//the last one must be 2 because player 1 starts

//    m_positions[3][3] = 1;
//    m_positions[4][3] = 2;
//    m_positions[3][4] = 2;
//    m_positions[4][4] = 1;
}

void GameField::printNameGame() const
{
    cout << m_nameGame << endl;
}

int GameField::getSIZE_FIELD() const
{
    return SIZE_FIELD;
}

void GameField::nextTurn()
{
    m_nbTurn++;
}

int GameField::setPositions(Coordinate coord, int playerId)
{
    int x = coord.row;
    int y = coord.col;
    if(!checkPosInField(coord))
    {
        cout << "Unvalid position: out of range 0-7" << endl;
        return 1;
    }
    else if(!checkPlayablePos(coord) && m_nbTurn > 0)
    {
        cout << "Unvalid position: not playable" << endl;
        return 1;
    }
    else
    {
        cout << "Player " << playerId << endl;
        cout << "Valid position" << endl;
        m_positions[x][y] = playerId;
        cout << x << y << endl;
        //change status coordinates: what is eaten?
        updatePlayablePos(playerId%2 + 1);//update possible positions for next player
    }

    return 0;
}


void GameField::plotGameFieldClass() const
{
    int rownum, colnum;
    for (rownum = 0; rownum < SIZE_FIELD; rownum++)
    {
        for (colnum = 0; colnum < SIZE_FIELD; colnum++)
        {
            cout << setw(4) << m_positions[rownum][colnum];
        }
        cout << endl;
    }
}

bool GameField::checkPlayablePos(Coordinate coord) const
{
    int sizePlayablePos = m_playablePos.size();
    bool res = false;
    for (int i = 0; i < sizePlayablePos; i++)
    {
        if( (coord == m_playablePos[i]) )
        {
            res = true;
        }
    }
    return res;
}

bool GameField::checkPosInField(Coordinate coord) const
{
    if(coord.row < 0 || coord.row > SIZE_FIELD || coord.col < 0 || coord.col > SIZE_FIELD)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void GameField::updatePlayablePos(int playerId)
{
    //scan m_positions
    int rownum, colnum;
    int playablePosId = 0;
    int pos2check[8][2] = { {0,-1},
                             {-1,-1},
                             {-1,0},
                             {-1,1},
                             {0,1},
                             {1,1},
                             {1,0},
                             {1,-1}
                             };
    int directions[8][2] = { {0,1},
                             {1,1},
                             {1,0},
                             {1,-1},
                             {0,-1},
                             {-1,-1},
                             {-1,0},
                             {-1,1}
                             };
    int flag;
    int inc;

    for (rownum = 0; rownum < SIZE_FIELD; rownum++)
    {
        for (colnum = 0; colnum < SIZE_FIELD; colnum++)
        {
            if(m_positions[rownum][colnum] == playerId%2 + 1)
            //8 different possible directions to check
                for (int i = 0; i < 8; i++)
                {
                    Coordinate newPoint(rownum + pos2check[i][0],colnum + pos2check[i][1]);
                    if(checkPosInField(newPoint))
                    {
                        if(m_positions[newPoint.row][newPoint.col] == 0)
                        {
                        //cout << rownum + pos2check[i][0] << colnum + pos2check[i][1] << endl;
                        //cout << "playable pos " << playablePosId << endl;
                            inc = 1;
                            flag = 0;
                            while(flag == 0)
                            {
                                Coordinate pointTemp(rownum + inc*directions[i][0], colnum + inc*directions[i][1]);

                                if(checkPosInField(pointTemp))
                                {
                                    if ((m_positions[pointTemp.row][pointTemp.col] == 0))
                                    {
                                        flag = 1;
                                    }
                                    else if(m_positions[pointTemp.row][pointTemp.col] == playerId)
                                    //check position, if out of range or null pass
                                    {

                                        Coordinate coord2add(rownum + pos2check[i][0], colnum + pos2check[i][1]);
                                        m_playablePos.push_back(coord2add);
                                        //m_playablePos[playablePosId] = Coordinate(rownum + pos2check[i][0], colnum + pos2check[i][1]);
                                        cout << m_playablePos[playablePosId].row << m_playablePos[playablePosId].col << endl;
                                        playablePosId++;
                                        flag = 1;
                                    }
                                    else
                                    {
                                        inc++;
                                    }
                                }
                                else
                                {
                                    flag = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

//    for(int i = 0; i < m_playablePos.size(); i++)
//    {
//        cout << m_playablePos[i][0] << m_playablePos[i][1] << endl;
//    }


GameField::~GameField()
{
    //dtor
}
