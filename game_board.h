#include <vector>
#include <iostream>
using namespace std;

class game_board
{
    public:
        

        bool check_win();


        /// @brief Returns true if move is played, false if it cant be played 
        /// @param  2d point
        /// @param  2d point
        /// @return 
        bool play_move(int, int); 

    private:
        vector<vector<int>> board_vector;

};

