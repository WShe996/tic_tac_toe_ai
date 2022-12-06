#pragma once
#include <vector>
#include <iostream>
using namespace std;

class game_board
{
    public:
        game_board(){
            board_vector = {{0,0,0}, {0,0,0}, {0,0,0}};
            turn = true;
        }


        bool check_win();


        /// @brief Returns true if move is played, false if it cant be played 
        /// @param  2d point x comp
        /// @param  2d point y comp
        /// @return 
        bool play_move(int, int); 

    private:
        vector<vector<int>> board_vector;
        bool turn;

};



game_board::play_move(int x, int y)
{
    if((x>=3)||(y>=3)){return false;}
    if(this->board_vector[x][y]!=0){return false;}
    else{
        if(this->turn) //X turn
        {
            this->board_vector[x][y]=1;
        }
        this->board_vector[x][y]=-1;
        this->turn = ! this->turn;
        return true;
    }
}
