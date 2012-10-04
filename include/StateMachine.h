#ifndef STATEMACHINE_H_INCLUDED
#define STATEMACHINE_H_INCLUDED

#include "helper.h"
#include <iostream>

/*
 * StateMachine is useful for keeping your key states and game modes
 * (menu, in-game, etc.) outside of the various modes of your game (see
 * StateLoopIFC). Storing a pointer to this class, or possibly making it a
 * singleton allows you to transfer control of the game loop between objects,
 * as well as keep access to the same key state variables.
 */

class StateMachine
{
    public:
        StateMachine();
        ~StateMachine(){};

        bool getArrowStates(Direction arrow) { return arrowState[arrow]; }
        GameState getGameState() { return gameState; }
        GameState* getGameStatePtr() { return &gameState; }

        // Define your game states with strings so that you can test what state
        // you are in.
        std::string getGameStateString();

        void setArrowState(Direction arrow, bool down) { arrowState[arrow] = down; }
        void setGameState(GameState gameState) { this->gameState = gameState; }

    protected:
         bool arrowState[4];

    private:
         GameState gameState;
};

#endif // STATEMACHINE_H_INCLUDED
