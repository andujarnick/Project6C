/*
Filename: space.h
Purpose: This file stores the implementation of the space class, which is used to hold the state of the space, and it has functions
to change the state

Functions: space, setState, flip, getState, operator <<
Private Variables: state

Nick Andujar
4/23/20
*/
#include <string>

using namespace std;

class space{
    public:
        space();//default constructor, sets all the states to -
        void setState(string type){state = type;};//changes the state to whatever you want
        void flip();//flips the state

        string getState(){return state;}//returns the state
        string getState() const{return state;}//returns the state
        friend ostream& operator <<(ostream& outs, const space sp);//overrided << operator to output the state
    private:
        string state;//stores the current state (-, X, O)
};