#include "updateScores.h"

using namespace std;

void updateScores(int typeAI, int winAI){
    ifstream scoresFluxRead("./scores.txt");
    vector<std::string> lines;
    string input;
    vector<string> words;
    string firstWord;
    string wordTemp;
    string newLine;
    int getWinScore;
    int getLoseScore;
    int oldScore;
    int newScore;
    while (std::getline(scoresFluxRead, input))
        lines.push_back(input);

    if(lines[0] != "%%%%%%Scores against AI%%%%%%"){
        cout << "Error: wrong file header." << endl;
    }
    for (auto& line : lines)
    {
        //if (line_needs_to_be_modified(line))
        //    modify_line_as_needed(line);
        words = split(line,' ');
        if (words.size() > 0){
            firstWord = words[0];
            if(firstWord == "Against"){
                wordTemp = words[1];//AI id
                //cout << word << endl;
                if( ((wordTemp == "random") & (typeAI == 0)) | ((wordTemp == "greedy") & (typeAI == 1)) ){
                    if(winAI == 1){
                    //replace line
                        getWinScore = 1;
                    }
                    if(winAI == 0){
                    //replace line
                        getLoseScore = 1;
                    }
                }
            }
            else if( (firstWord == "Win:") & (getWinScore == 1)){
                stringstream convert2int(words[1]);
                convert2int >> oldScore;
                newScore = oldScore + 1;
                line = "Win: " + to_string(newScore);
                getWinScore = 0;
            }
            else if( (firstWord == "Loss:") & (getLoseScore == 1)){
                stringstream convert2int(words[1]);
                convert2int >> oldScore;
                newScore = oldScore + 1;
                line = "Loss: " + to_string(newScore);
                getLoseScore = 0;
            }
        }
    }
    scoresFluxRead.close();//close to write on the file

    ofstream output_file("./scores.txt");
    for (auto const& line : lines)
        output_file << line << '\n';

    output_file.close();
    string line2print;
    scoresFluxRead.open("./scores.txt");
    if(scoresFluxRead){
        while (getline(scoresFluxRead,line2print))
            cout << line2print << endl;
    }
    else{
        cout << "Error with scores file reading" << endl;
    }
}

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
