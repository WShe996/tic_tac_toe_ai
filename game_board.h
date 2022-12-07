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


        /// @brief Returns true if the game has reached an end state
        /// @return true if game is at end state, false if game is not
        bool check_win();


        /// @brief Returns score value of the end game
        /// @return Returns 1 if X has won the game -1 if O has won the game and 0 if it is a draw 
        int calc_end_game();


        /// @brief Returns true if move is played, false if it cant be played 
        /// @param  2d point x comp
        /// @param  2d point y comp
        /// @return 
        bool play_move(int, int); 

    private:
        vector<vector<int>> board_vector;
        bool turn;

};


bool game_board::check_win()
{
    if((board_vector[0][0]+board_vector[1][1]+board_vector[2][2]==3)||(board_vector[0][0]+board_vector[1][1]+board_vector[2][2]==-3))
    {
        return true;
    }
    else if((board_vector[2][0]+board_vector[1][1]+board_vector[0][2]==3)||(board_vector[2][0]+board_vector[1][1]+board_vector[0][2]==-3))
    {
        return true;
    }
    for(int i=0;i<3;i++)
    {
        if((board_vector[0][i]+board_vector[1][i]+board_vector[2][i]==3)||(board_vector[0][i]+board_vector[1][i]+board_vector[2][i]==-3)){return true;}
        if((board_vector[i][0]+board_vector[i][1]+board_vector[i][2]==3)||(board_vector[i][0]+board_vector[i][1]+board_vector[i][2]==-3)){return true;}
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board_vector[i][j]==0){return false;}
        }
    }
    return true;
}


bool game_board::play_move(int x, int y)
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
