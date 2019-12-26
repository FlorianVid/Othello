#ifndef UPDATESCORES_H
#define UPDATESCORES_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

void updateScores(int idWinner);

#endif // ARTIFICIALINTELLIGENCE_H
