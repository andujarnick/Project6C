/*
Filename: othello.cc
Purpose: This file stores the implementation of the Othello class as well as some helper functions and some
inherited overrided functions from the game class

Functions: ctoi, to_coordinates, Othello, setPiece, make_move, clone, compute_moves, display_status, evaluate, is_game_over, is_legal
Private Variables: space board[8][8]

Nick Andujar
4/23/20
*/
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <iomanip>
#include "othello.h"

using namespace std;
using namespace main_savitch_14;

int ctoi(char c)//converts a character to an integer for values 0-9
{
    if(c == '0'){return 0;}
    else if(c == '1'){return 1;}
    else if(c == '2'){return 2;}
    else if(c == '3'){return 3;}
    else if(c == '4'){return 4;}
    else if(c == '5'){return 5;}
    else if(c == '6'){return 6;}
    else{return 7;}
}

string to_coordinates(const std::string move)//converts the user's inputs to numerical values for the array to access
{
    string tmp = "00";//defines the string as 2 characters long
    //converts the letters to numbers
    if(toupper(move[0]) == 'A'){tmp[0] = '0';}
    else if(toupper(move[0]) == 'B'){tmp[0] = '1';}
    else if(toupper(move[0]) == 'C'){tmp[0] = '2';}
    else if(toupper(move[0]) == 'D'){tmp[0] = '3';}
    else if(toupper(move[0]) == 'E'){tmp[0] = '4';}
    else if(toupper(move[0]) == 'F'){tmp[0] = '5';}
    else if(toupper(move[0]) == 'G'){tmp[0] = '6';}
    else{tmp = '7';}
    //converts the numbers to the correct numbers
    if(toupper(move[1]) == '1'){tmp[1] = '0';}
    else if(toupper(move[1]) == '2'){tmp[1] = '1';}
    else if(toupper(move[1]) == '3'){tmp[1] = '2';}
    else if(toupper(move[1]) == '4'){tmp[1] = '3';}
    else if(toupper(move[1]) == '5'){tmp[1] = '4';}
    else if(toupper(move[1]) == '6'){tmp[1] = '5';}
    else if(toupper(move[1]) == '7'){tmp[1] = '6';}
    else{tmp[1] = '7';}

    return tmp;//returns the new coordinates as a string
}

bool Othello::isLegalHelper(const std::string& move) const//checks to see if the coordinates are valid
{
    string loc = to_coordinates(move), space, spaceAtCoordinates;//used to store the location of the move, the type of space
    if(next_mover() == HUMAN){space = "X";}//assigns the type of space
    else{space = "O";}//assigns the type of space

    if(board[ctoi(loc[0])][ctoi(loc[1])].getState() != "-")//checks to see if there is already something at the location
    {return false;}
    if(lookLeft(space, loc) || lookRight(space, loc) || lookUp(space, loc) || lookDown(space, loc) || lookDiagonalRU(space, loc) || lookDiagonalRD(space, loc) || lookDiagonalLU(space, loc) || lookDiagonalLD(space, loc))//checks to see if the move can be placed
    {return true;}
    else{return false;}
}

Othello::Othello()//default constructor that sets the original 4 spaces
{
    board[3][3].setState("O");
    board[4][4].setState("O");
    board[3][4].setState("X");
    board[4][3].setState("X");
    skipCounter = 0;
}

void Othello::setPiece(string state, char x, char y)//sets a piece at the desired location
{
    if(board[ctoi(x)][ctoi(y)].getState() == "-")//checks to see if the space has not been used
    {
        board[ctoi(x)][ctoi(y)].setState(state);//sets a new piece
    }
    else
    {
        board[ctoi(x)][ctoi(y)].flip();//otherwise, just flips the piece
    }
}

// void Othello::make_move(const std::string& move)//sets the piece at the desired location
// {
//     compute_moves(moves);
//     if(move=="XX" && move=="xx"){game::make_move(move);}
//     else if(moves.empty()){cout << endl << "no possible moves, skipping turn" << endl << endl; game::make_move(move);}
//     else
//     {
//         string loc = to_coordinates(move), space;//gets the coordinates so the computer can read them
//         if(next_mover() == HUMAN){space = "X";}//assigns the type of space
//         else{space = "O";}//assigns the type of space
//         setPiece(space, loc[0], loc[1]);//sets the piece at the location
//         flipLeft(space, loc);
//         flipRight(space, loc);
//         flipUp(space, loc);
//         flipDown(space, loc);
//         flipDiagonalRU(space, loc);
//         flipDiagonalRD(space, loc);
//         flipDiagonalLU(space, loc);
//         flipDiagonalLD(space, loc);
//         game::make_move(move);
//         skipCounter = 0;
//     }
// }

void Othello::make_move(const std::string& move)//sets the piece at the desired location
{
    if(move!="XX" && move!="xx")
    {
        string loc = to_coordinates(move), space;//gets the coordinates so the computer can read them
        if(next_mover() == HUMAN){space = "X";}//assigns the type of space
        else{space = "O";}//assigns the type of space
        setPiece(space, loc[0], loc[1]);//sets the piece at the location
        flipLeft(space, loc);
        flipRight(space, loc);
        flipUp(space, loc);
        flipDown(space, loc);
        flipDiagonalRU(space, loc);
        flipDiagonalRD(space, loc);
        flipDiagonalLU(space, loc);
        flipDiagonalLD(space, loc);
        game::make_move(move);
        skipCounter = 0;
    }
    else{cout << endl << "no possible moves, skipping turn" << endl << endl; game::make_move(move); skipCounter++;}
}

game* Othello::clone() const{return NULL;}//stubbed
void Othello::compute_moves(std::queue<std::string>& moves) const
{
    string loc = "00";
    for(char i='1'; i<'9'; i++)
    {
        for(char j='A'; j<'I'; j++)
        {
            loc[0] = j;
            loc[1] = i;
            if(isLegalHelper(loc))
            {
                moves.push(loc);
            }
        }
    }
}

void Othello::display_status() const//outputs the game board as well as if the game is over or not
{
    if(is_game_over() == false)//outputs that the game is in session as long as the game isn't over
    {
        if((next_mover() == HUMAN))
        {
            cout << B_BLACK << "   ";
            cout << B_BLUE << WHITE << setw(33) << left << "  You are the X's" << RESET << endl;
            cout << B_BLACK << "   ";
            cout << B_BLUE << WHITE << setw(33) << left << "  Enter xx or XX to pass" << RESET << endl;
            cout << B_BLACK << "   ";
            cout << B_BLUE << WHITE << setw(33) << left << "  Game is still in session" << RESET << endl;
        }
        else
        {
            cout << B_BLACK << "   ";
            cout << B_BLUE << WHITE << setw(33) << left << "  You are the O's" << RESET << endl;
            cout << B_BLACK << "   ";
            cout << B_BLUE << WHITE << setw(33) << left << "  Enter xx or XX to pass" << RESET << endl;
            cout << B_BLACK << "   ";
            cout << B_BLUE << WHITE << setw(33) << left << "  Game is still in session" << RESET << endl;
        }
    }
    else//outputs that the game is over
    {
        cout << B_BLACK << "   ";
        cout << B_BLUE << WHITE << setw(33) << left << "  Game is over   " << endl;
    }
    
    //formats the board and outputs it
    cout << B_BLACK << "   ";
    cout << B_RED << WHITE << "  A  " << " B  " << " C  " << " D  " << " E  " << " F  " << " G  " << " H  " << RESET << endl;
    cout << B_RED << "   " << B_BLACK << WHITE << "|---|" << "---|" << "---|" << "---|" << "---|" << "---|" << "---|" << "---|" << RESET << endl;
    for(int i=0; i<8; i++)
    {
        cout << B_RED << WHITE << " " << i+1 << " ";
        for(int j=0; j<8; j++)
        {
            cout << B_BLACK << WHITE << "| " << board[j][i] << " ";
            if(j == 7){cout << WHITE << "|" << RESET;}
        }
        cout << endl << B_RED << "   ";
        cout << B_BLACK << WHITE << "|---|" << "---|" << "---|" << "---|" << "---|" << "---|" << "---|" << "---|" << RESET << endl;;
    }
    cout << RESET;//resets the colors after the board is done being shown
}
int Othello::evaluate() const{return 0;}//stubbed

bool Othello::is_game_over() const
{if(skipCounter >= 2){return true;}
else{return false;}}

bool Othello::is_legal(const std::string& move) const//checks to see if the coordinates are valid
{
    queue <string> moves;
    compute_moves(moves);
    string loc = to_coordinates(move), space, spaceAtCoordinates;//used to store the location of the move, the type of space
    if(next_mover() == HUMAN){space = "X";}//assigns the type of space
    else{space = "O";}//assigns the type of space

    if(move=="XX" || move=="xx")
    {
        if(moves.empty()){return true;}
        else{return false;}
    }

    if(board[ctoi(loc[0])][ctoi(loc[1])].getState() != "-")//checks to see if there is already something at the location
    {return false;}
    if(lookLeft(space, loc) || lookRight(space, loc) || lookUp(space, loc) || lookDown(space, loc) || lookDiagonalRU(space, loc) || lookDiagonalRD(space, loc) || lookDiagonalLU(space, loc) || lookDiagonalLD(space, loc))//checks to see if the move can be placed
    {return true;}
    else{return false;}
}


//helper functions
bool Othello::lookLeft(string space, string loc) const//checks to see if there is a corrosponding piece to the left
{
    if(loc[0]!='0')
    {
        if(board[ctoi(loc[0])-1][ctoi(loc[1])].getState() == space || board[ctoi(loc[0])-1][ctoi(loc[1])].getState() == "-"){return false;}//checks to see if there is a space the same as the requested right next to it 
        for(int i=(ctoi(loc[0])-2); i>-1; i--)//checks to see if there is a space of the same kind to the left in that row
        {
            if(board[i][ctoi(loc[1])].getState() == "-"){return false;}//checks for "-" spaces
            if(board[i][ctoi(loc[1])].getState() == space){return true;}//checks for the space of the same type
        }
        return false;
    }
    else{return false;}
}
bool Othello::lookRight(string space, string loc) const//checks to see if there is a corrosponding piece to the right
{
    if(loc[0]!='7')
    {
        if(board[ctoi(loc[0])+1][ctoi(loc[1])].getState() == space || board[ctoi(loc[0])+1][ctoi(loc[1])].getState() == "-"){return false;}//checks to see if there is a space the same as the requested right next to it 
        for(int i=(ctoi(loc[0])+2); i<8; i++)//checks to see if there is a space of the same kind to the left in that row
        {
            if(board[i][ctoi(loc[1])].getState() == "-"){return false;}//checks for "-" spaces
            if(board[i][ctoi(loc[1])].getState() == space){return true;}//checks for the space of the same type
        }
        return false;
    }
    else{return false;}
}
bool Othello::lookUp(string space, string loc) const//checks to see if there is a corrosponding piece upwards
{
    if(loc[1]!='0')
    {
        if(board[ctoi(loc[0])][ctoi(loc[1])-1].getState() == space || board[ctoi(loc[0])][ctoi(loc[1])-1].getState() == "-"){return false;}//checks to see if there is a space the same as the requested right next to it 
        for(int i=(ctoi(loc[1])-2); i>-1; i--)//checks to see if there is a space of the same kind to the left in that row
        {
            if(board[ctoi(loc[0])][i].getState() == "-"){return false;}//checks for "-" spaces
            if(board[ctoi(loc[0])][i].getState() == space){return true;}//checks for the space of the same type
        }
        return false;
    }
    else{return false;}
}
bool Othello::lookDown(string space, string loc) const//checks to see if there is a corrosponding piece downwards
{
    if(loc[1]!='7')
    {
        if(board[ctoi(loc[0])][ctoi(loc[1])+1].getState() == space || board[ctoi(loc[0])][ctoi(loc[1])+1].getState() == "-"){return false;}//checks to see if there is a space the same as the requested right next to it 
        for(int i=(ctoi(loc[1])+2); i<8; i++)//checks to see if there is a space of the same kind to the left in that row
        {
            if(board[ctoi(loc[0])][i].getState() == "-"){return false;}//checks for "-" spaces
            if(board[ctoi(loc[0])][i].getState() == space){return true;}//checks for the space of the same type
        }
        return false;
    }
    else{return false;}
}
bool Othello::lookDiagonalRU(string space, string loc) const//checks to see if there is a corrosponding diagonally upwards and to the right
{
    if(loc[0]!='7'&&loc[1]!='0')
    {
        int i=0, j=0;
        if(board[ctoi(loc[0])+1][ctoi(loc[1])-1].getState() == space || board[ctoi(loc[0])+1][ctoi(loc[1])-1].getState() == "-"){return false;}//checks to see if there is a space the same as the requested right next to it 
        for(i=(ctoi(loc[0])+2), j=(ctoi(loc[1])-2); i<8 && j>-1; i++, j--)//checks to see if there is a space of the same kind to the left in that row
        {
            if(board[i][j].getState() == "-"){return false;}//checks for "-" spaces
            if(board[i][j].getState() == space){return true;}//checks for the space of the same type
        }
        return false;
    }
    else{return false;}
}
bool Othello::lookDiagonalRD(string space, string loc) const//checks to see if there is a corrosponding diagonally downwards and to the right
{
    if(loc[0]!='7'&&loc[1]!='7')
    {
        int i=0, j=0;
        if(board[ctoi(loc[0])+1][ctoi(loc[1])+1].getState() == space || board[ctoi(loc[0])+1][ctoi(loc[1])+1].getState() == "-"){return false;}//checks to see if there is a space the same as the requested right next to it 
        for(i=(ctoi(loc[0])+2), j=(ctoi(loc[1])+2); i<8 && j<8; i++, j++)//checks to see if there is a space of the same kind to the left in that row
        {
            if(board[i][j].getState() == "-"){return false;}//checks for "-" spaces
            if(board[i][j].getState() == space){return true;}//checks for the space of the same type
        }
        return false;
    }
    else{return false;}
}
bool Othello::lookDiagonalLU(string space, string loc) const//checks to see if there is a corrosponding diagonally upwards and to the left
{
    if(loc[0]!='0'&&loc[1]!='0')
    {
        int i=0, j=0;
        if(board[ctoi(loc[0])-1][ctoi(loc[1])-1].getState() == space || board[ctoi(loc[0])-1][ctoi(loc[1])-1].getState() == "-"){return false;}//checks to see if there is a space the same as the requested right next to it 
        for(i=(ctoi(loc[0])-2), j=(ctoi(loc[1])-2); i>-1 && j>-1; i--, j--)//checks to see if there is a space of the same kind to the left in that row
        {
            if(board[i][j].getState() == "-"){return false;}//checks for "-" spaces
            if(board[i][j].getState() == space){return true;}//checks for the space of the same type
        }
        return false;
    }
    else{return false;}
}
bool Othello::lookDiagonalLD(string space, string loc) const//checks to see if there is a corrosponding diagonally downwards and to the left
{
    if(loc[0]!='0'&&loc[1]!='7')
    {
        int i=0, j=0;
        if(board[ctoi(loc[0])-1][ctoi(loc[1])+1].getState() == space || board[ctoi(loc[0])-1][ctoi(loc[1])+1].getState() == "-"){return false;}//checks to see if there is a space the same as the requested right next to it 
        for(i=(ctoi(loc[0])-2), j=(ctoi(loc[1])+2); i>-1 && j>-1; i--, j++)//checks to see if there is a space of the same kind to the left in that row
        {
            if(board[i][j].getState() == "-"){return false;}//checks for "-" spaces
            if(board[i][j].getState() == space){return true;}//checks for the space of the same type
        }
        return false;
    }
    else{return false;}
}







void Othello::flipLeft(string space, string loc)//checks to see if there is a corrosponding piece to the left
{
    if(lookLeft(space, loc))
    {
        for(int i=(ctoi(loc[0])-1); i>-1 && board[i][ctoi(loc[1])].getState() != space; i--)//checks to see if there is a space of the same kind to the left in that row
        {
            board[i][ctoi(loc[1])].flip();
        }
    }
}
void Othello::flipRight(string space, string loc)//checks to see if there is a corrosponding piece to the right
{
    if(lookRight(space, loc))
    {
        for(int i=(ctoi(loc[0])+1); i<8 && board[i][ctoi(loc[1])].getState() != space; i++)//checks to see if there is a space of the same kind to the left in that row
        {
            board[i][ctoi(loc[1])].flip();
        }
    }
}
void Othello::flipUp(string space, string loc)//checks to see if there is a corrosponding piece upwards
{
    if(lookUp(space, loc))
    {
        for(int i=(ctoi(loc[1])-1); i>-1 && board[ctoi(loc[0])][i].getState() != space; i--)//checks to see if there is a space of the same kind to the left in that row
        {
            board[ctoi(loc[0])][i].flip();
        }
    }
}
void Othello::flipDown(string space, string loc)//checks to see if there is a corrosponding piece downwards
{
    if(lookDown(space, loc))
    {
        for(int i=(ctoi(loc[1])+1); i<8 && board[ctoi(loc[0])][i].getState() != space; i++)//checks to see if there is a space of the same kind to the left in that row
        {
            board[ctoi(loc[0])][i].flip();
        }
    }
}
void Othello::flipDiagonalRU(string space, string loc)//checks to see if there is a corrosponding diagonally upwards and to the right
{
    int i=0, j=0;
    if(lookDiagonalRU(space ,loc))
    {
        for(i=(ctoi(loc[0])+1), j=(ctoi(loc[1])-1); i<8 && j>-1 && board[i][j].getState() != space; i++, j--)//checks to see if there is a space of the same kind to the left in that row
        {
            board[i][j].flip();
        }
    }
}
void Othello::flipDiagonalRD(string space, string loc)//checks to see if there is a corrosponding diagonally downwards and to the right
{
    int i=0, j=0;
    if(lookDiagonalRD(space, loc))
    {
        for(i=(ctoi(loc[0])+1), j=(ctoi(loc[1])+1); i<8 && j<8 && board[i][j].getState() != space; i++, j++)//checks to see if there is a space of the same kind to the left in that row
        {
            board[i][j].flip();
        }
    }
}
void Othello::flipDiagonalLU(string space, string loc)//checks to see if there is a corrosponding diagonally upwards and to the left
{
    int i=0, j=0;
    if(lookDiagonalLU(space, loc))
    {
        for(i=(ctoi(loc[0])-1), j=(ctoi(loc[1])-1); i>-1 && j>-1 && board[i][j].getState() != space; i--, j--)//checks to see if there is a space of the same kind to the left in that row
        {
            board[i][j].flip();
        }
    }
}
void Othello::flipDiagonalLD(string space, string loc)//checks to see if there is a corrosponding diagonally downwards and to the left
{
    int i=0, j=0;
    if(lookDiagonalLD(space, loc))
    {
        for(i=(ctoi(loc[0])-1), j=(ctoi(loc[1])+1); i>-1 && j>-1 && board[i][j].getState() != space; i--, j++)//checks to see if there is a space of the same kind to the left in that row
        {
            board[i][j].flip();
        }
    }
}