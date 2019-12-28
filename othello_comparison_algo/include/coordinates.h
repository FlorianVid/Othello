#ifndef COORDINATES_H_INCLUDED
#define COORDINATES_H_INCLUDED

#include <bits/stdc++.h>
#include <iostream>
#include <math.h>

struct Coordinate {
    int row, col;
    Coordinate(int x, int y) : row(x), col(y) {}

    bool operator<(const Coordinate& coord) const { //to modify to use map
    if(row < coord.row) return true;
    if(row > coord.row) return false;
    if(col < coord.col) return true;
    if(col > coord.col) return false;
    return false;
    }

    bool operator==(const Coordinate& coord) const {
        if(row == coord.row && col == coord.col)
            return true;
        return false;
    }

    inline bool isInRange(Coordinate coord, int range) const {
        if(pow(coord.row - this->row, 2) + pow(coord.col - this->col, 2) <= range*range)
            return true;
        return false;
    }

    double computeDistance(const Coordinate& coord) const {
        double dist;
        dist = sqrt(pow(row - coord.row,2) + pow(col - coord.col,2));
        return dist;
    }

};

#endif // COORDINATES_H_INCLUDED
