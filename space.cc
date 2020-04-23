/*
Filename: space.cc
Purpose: This file stores the implementation of the space class functions

Functions: space, setState, flip, getState, operator <<
Private Variables: state

Nick Andujar
4/23/20
*/
#include <string>
#include <iostream>
#include "colors.h"
#include "space.h"

using namespace std;

space::space()//default constructor, sets the state to -
{
    state = "-";
}

void space::flip()//flips the state of the space
{
    if(state == "X")
    {
        state = "O";
    }
    else
    {
        state = "X";
    }
}

ostream& operator <<(ostream& outs, const space sp)//overrided << function to output the state
{
    //changes the color based on the state
    if(sp.state == "X")
    {
        outs << RED << sp.state;
    }
    else if(sp.state == "O")
    {
        outs << BLUE << sp.state;
    }
    else
    {
        outs << GREEN << sp.state;
    }
    
    return outs;//returns outs so you can chain <<
}