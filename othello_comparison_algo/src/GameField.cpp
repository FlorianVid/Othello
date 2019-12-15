#include "../include/GameField.h"
using namespace std;

GameField::GameField() : m_positions(), m_activePlayer(1), m_nbTurn(0), m_nameGame("%%%%%%Badass Othello%%%%%%")
{
    Coordinate coord(3,3);
    setPositions(coord, 1);
    coord.row = 4;
    coord.col = 3;
    setPositions(coord, 2);
    coord.row = 4;
    coord.col = 4;
    setPositions(coord, 1);
    coord.row = 3;
    coord.col = 4;
    setPositions(coord, 2);//the last one must be 2 because player 1 starts
    nextTurn();
//    m_positions[3][3] = 1;
//    m_positions[4][3] = 2;
//    m_positions[3][4] = 2;
//    m_positions[4][4] = 1;
}

void GameField::printNameGame() const{
    cout << m_nameGame << endl;
}

std::tuple<int, int> GameField::getScore() const{//return score player 1 and player 2
    int score1(0);
    int score2(0);
    for( int r(0); r < SIZE_FIELD; r++ ){
        for ( int c(0); c < SIZE_FIELD; c++){
            if(m_positions[r][c] == 1){
                score1++;
            }
            else if(m_positions[r][c]){
                score2++;
            }
        }
    }

    tuple<int, int> res;
    res = {score1, score2};
    cout << "Score: Player1: " << get<0>(res) << '\t' << "Player2: " << get<1>(res) << endl;
    return res;
}

int GameField::get_SIZE_FIELD() const{
    return SIZE_FIELD;
}

int GameField::get_m_nbTurn() const{
    return m_nbTurn;
}

void GameField::nextTurn()
{
    m_nbTurn++;
}

int GameField::setPositions(Coordinate coord, int playerId){ //check if given coordinates by user is valid and update the game field and possible for next player
    int x = coord.row;
    int y = coord.col;
    if(!checkPosInField(coord)){
        cout << "Unvalid position: out of range 0-7" << endl;
        return 1;
    }
    else if(!checkPlayablePos(coord) && m_nbTurn > 0){
        cout << "Unvalid position: not playable" << endl;
        return 1;
    }
    else{
        //change status coordinates: what is eaten?
        cout << "Player " << playerId << endl;
        cout << "Valid position" << endl;
        m_positions[x][y] = playerId;
        cout << "Coordinate chosen: " << x << " " << y << endl;
        Coordinate pointChosen(x,y);

        //flip opponent's positions
        for(Mid::const_iterator iterMap = m_playablePos.begin(); iterMap != m_playablePos.end(); ++iterMap){
            if(iterMap->first == pointChosen){
                for(vector<Coordinate>::const_iterator iterVect = iterMap->second.begin(); iterVect != iterMap->second.end(); ++iterVect){
                    m_positions[iterVect->row][iterVect->col] = playerId;
                    //cout << "flip" << iterVect->row << iterVect->col << endl;
                }
            }
        }
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
    //cout << "nb playable pos: " << m_playablePos.size() << endl;
    for (Mid::const_iterator iter = m_playablePos.begin(); iter != m_playablePos.end(); ++iter){
        cout << "key" << '\t'<< iter->first.row << '\t' << iter->first.col << '\n';
        //cout << "Nb pos to switch: " << iter->second.size() << endl;
        for(auto i : iter->second){
            cout <<  "value" << '\t' << i.row << '\t' << i.col << '\n';
        }
        //cout <<  "value" << '\t' << iter->second[0].row << '\t' << iter->second[0].col << '\n';

        if(iter->first == coord){
            return true;
        }
    }
    return false;
}

int GameField::getNbPlayablePos() const{
    return m_playablePos.size();
}

Coordinate GameField::getNthPos(int n) const{
    return m_playablePosVect[n];
}

bool GameField::checkPosInField(Coordinate coord) const
{
    if(coord.row < 0 || coord.row > SIZE_FIELD-1 || coord.col < 0 || coord.col > SIZE_FIELD-1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void GameField::updatePlayablePos(int playerId)//update for the next player to play
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
    vector<Coordinate> flippedPos;//empty vectors
    //empty m_playablePos
    m_playablePos.clear();
    m_playablePosVect.clear();
    for (rownum = 0; rownum < SIZE_FIELD; rownum++)
    {
        for (colnum = 0; colnum < SIZE_FIELD; colnum++)
        {
            if(m_positions[rownum][colnum] == playerId%2 + 1)
            //8 different possible directions to check
                for (int i = 0; i < 8; i++)
                {
                    Coordinate newPoint(rownum + pos2check[i][0],colnum + pos2check[i][1]);
                    flippedPos.erase( flippedPos.begin(), flippedPos.end() );//set to empty
                    if(checkPosInField(newPoint))
                    {
                        if(m_positions[newPoint.row][newPoint.col] == 0)
                        {
                        //cout << rownum + pos2check[i][0] << colnum + pos2check[i][1] << endl;
                        //cout << "playable pos " << playablePosId << endl;
                            inc = 0;
                            flag = 0;
                            while(flag == 0)
                            {
                                Coordinate pointTemp(rownum + inc*directions[i][0], colnum + inc*directions[i][1]);

                                if(checkPosInField(pointTemp)){
                                    if ((m_positions[pointTemp.row][pointTemp.col] == 0))
                                    {
                                        flag = 1;
                                    }
                                    else if(m_positions[pointTemp.row][pointTemp.col] == playerId){
                                    //check position, if out of range or null pass
                                        //cout << "to flip" << flippedPos[0].row << flippedPos[0].col << endl;
                                        Coordinate coord2add(rownum + pos2check[i][0], colnum + pos2check[i][1]);
                                        //m_playablePos.push_back(coord2add);
                                        m_playablePos.insert(Mid::value_type(newPoint,flippedPos));//flippedPos[0]
                                        m_playablePosVect.push_back(newPoint);
                                        //cout << m_playablePos[playablePosId].row << m_playablePos[playablePosId].col << endl;
                                        playablePosId++;
                                        flag = 1;
                                    }
                                    else{
                                        inc++;
                                        flippedPos.push_back(pointTemp);
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
Mid GameField::getPlayablePos() const{
    return m_playablePos;
}

GameField::~GameField()
{
    //dtor
}
