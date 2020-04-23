/*
Filename: othello.h
Purpose: This file stores the declaration of the Othello class, which is derived from the game class. It will be
used to store a game board and to hold functions for how the game will be played

Functions: Othello, setPiece, make_move, clone, compute_moves, display_status, evaluate, is_game_over, is_legal
Private Variables: space board[8][8]

Nick Andujar
4/23/20
*/
#include "game.h"
#include "space.h"
#include "colors.h"

using namespace std;
using namespace main_savitch_14;

class Othello:public game{
    public:
        Othello();//default constructor, sets up the board with the original peices
        
        //setters
        void setPiece(string state, char x, char y);//sets the state of the piece at the location on the board


        //inherited functions
        void make_move(const std::string& move);//makes a move, derived from the game class, overrided in othello.cc
        // void restart();//to be used later

        virtual game* clone() const;//stubbed for now
        virtual void compute_moves(std::queue<std::string>& moves) const;//stubbed for now
        virtual void display_status() const;//displays the game board and whether or not the game is still going on
        virtual int evaluate() const;//stubbed for now
        virtual bool is_game_over() const;//checks to see if the game is over or not
        virtual bool is_legal(const std::string& move) const;//checks to see if the move is legal or not

        //helper functions
        bool isLegalHelper(const std::string& move) const;//checks to see if the coordinates are valid
        bool lookLeft(string space, string loc) const;//checks to see if there is a corrosponding piece to the left
        bool lookRight(string space, string loc) const;//checks to see if there is a corrosponding piece to the right
        bool lookUp(string space, string loc) const;//checks to see if there is a corrosponding piece upwards
        bool lookDown(string space, string loc) const;//checks to see if there is a corrosponding piece downwards
        bool lookDiagonalRU(string space, string loc) const;//checks to see if there is a corrosponding diagonally upwards and to the right
        bool lookDiagonalRD(string space, string loc) const;//checks to see if there is a corrosponding diagonally downwards and to the right
        bool lookDiagonalLU(string space, string loc) const;//checks to see if there is a corrosponding diagonally upwards and to the left
        bool lookDiagonalLD(string space, string loc) const;//checks to see if there is a corrosponding diagonally downwards and to the left
        
        void flipLeft(string space, string loc);//flips all the pieces to the left
        void flipRight(string space, string loc);//flips all the pieces to the right
        void flipUp(string space, string loc);//flips all the pieces upwards
        void flipDown(string space, string loc);//flips all the pieces downwards
        void flipDiagonalRU(string space, string loc);//flips all the pieces diagonally
        void flipDiagonalRD(string space, string loc);//flips all the pieces diagonally
        void flipDiagonalLU(string space, string loc);//flips all the pieces diagonally
        void flipDiagonalLD(string space, string loc);//flips all the pieces diagonally

    private:
        space board[8][8];//used to store the board as a grid of spaces
        int skipCounter;//counts how many skips there have been
};