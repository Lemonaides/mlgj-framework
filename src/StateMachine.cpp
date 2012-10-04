#include "StateMachine.h"

using namespace std;

StateMachine::StateMachine()
{
    // default to menu state
    gameState = MENU;

    // initialize arrow keys to UP position
    for(int i = 0; i<4; i++)
        arrowState[i] = false;
}

string StateMachine::getGameStateString()
{
    switch(gameState)
    {
        case MENU:     return "MENU";
        case NEWGAME:  return "NEWGAME";
        case CONTINUE: return "CONTINUE";
        case LOADGAME: return "LOADGAME";
        case SAVEGAME: return "SAVEGAME";
        case OPTIONS:  return "OPTIONS";
        case MAPEDITOR:  return "MAPEDITOR";
        case NPCEDITOR: return "NPCEDITOR";
        case QUIT:     return "QUIT";
        default: return "UNKNOWN STATE";
    }
}
