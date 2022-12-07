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

        void print_board();

        vector<int> get_game_vector();

    private:
        vector<vector<int>> board_vector = {{}};
        bool turn;

};


int game_board::calc_end_game()
{
    if(check_win())
    {
        for(int i=0;i<3;i++)
        {
            int sum_x = (board_vector[0][i] + board_vector[1][i] + board_vector[2][i]);
            int sum_y = (board_vector[i][0] + board_vector[i][1] + board_vector[i][2]);
            if(sum_y * sum_y == 9){return sum_y/3;}
            else if(sum_x * sum_x == 9){return sum_x/3;}
        }
        int diag_positive = board_vector[0][2] + board_vector[1][1] + board_vector[2][0];
        int diag_negitive = board_vector[0][0] + board_vector[1][1] + board_vector [2][2];
        if(diag_positive * diag_positive == 9){return diag_positive/3;}
        else if(diag_negitive * diag_negitive == 9){return diag_negitive/3;}
        else{return 0;}
    }
    else
    {
        throw std::invalid_argument("This is not an endgame board");
    }
}

bool game_board::check_win()
{
    int player_multiplyer = 0;
    if(turn){player_multiplyer=-1;}
    else{player_multiplyer=1;}
    if(board_vector[0][0]+board_vector[1][1]+board_vector[2][2]== player_multiplyer*3)
    {
        return true;
    }
    else if(board_vector[2][0]+board_vector[1][1]+board_vector[0][2]==  player_multiplyer*3)
    {
        return true;
    }
    for(int i=0;i<3;i++)
    {
        if(board_vector[0][i]+board_vector[1][i]+board_vector[2][i]== player_multiplyer*3){return true;}
        else if(board_vector[i][0]+board_vector[i][1]+board_vector[i][2]== player_multiplyer*3){return true;}
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
        else {
            this->board_vector[x][y]=-1;
        }
        this->turn = !this->turn;
        return true;
    }
}

void game_board::print_board()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board_vector[i][j] == 1){cout << "X";}
            else if(board_vector[i][j] == 0){cout << " ";}
            else{cout << "O";}
        }
        cout << "\n";
    }
}

vector<int> game_board::get_game_vector()
{
    vector<int> nums;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            nums.push_back(board_vector[i][j]);
        }
    }
    return nums;
}