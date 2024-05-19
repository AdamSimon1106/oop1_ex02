//
// Created by Adam Simonov on 9/5/24.
//

#pragma once
#ifndef OOP1_EX02_CONTROLLER_H
#define OOP1_EX02_CONTROLLER_H
#include "Board.h"
class Controller{
public:
    Controller();
    
    void startGame();
    void interactionManager(Location nextLocation);
    void loadPlaylist();
    bool stageManager();
    bool isNextMoveValid(const Location currLocation, const Location nextLocation);
  
private:
    Board m_board;
    vector <string> m_playlist;
    string m_playlistName;
    int m_currLevelIndex;
};
#endif //OOP1_EX02_CONTROLLER_H
