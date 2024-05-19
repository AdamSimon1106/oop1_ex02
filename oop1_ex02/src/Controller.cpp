//
// Created by Adam Simonov on 9/5/24.
//

#include "Controller.h"
#include <thread>
#include <chrono>
#include <conio.h>
#include <io.h>

using namespace Keys;
using namespace SpecialKeys;
using namespace Characters;
using namespace std::chrono_literals;

//std::this_thread::sleep_for(200ms); // used for thread delay

Controller::Controller(){
    cout << "enter the name of playlist file you would like to load" << endl;
    cin >> m_playlistName;
    loadPlaylist();
    m_currLevelIndex = 0;
};
void Controller::startGame(){
    
     //setup Board
    while (m_currLevelIndex < m_playlist.size()){
        //-------------setup Board----------------
        //reset map and mouse
        m_board.resetMap();
        //load new data
        m_board.loadMap(m_playlist[m_currLevelIndex]);//setting m_map
        m_board.setBottomRight();
        m_board.setNumOfCheese();
        m_board.setNumOfKeys();
        m_board.resetMouse();
        
        //fill locations for all items on board.
        m_board.setInanimateLocation(CHEESE, m_board.getInanimateVector(CHEESE));
        m_board.setInanimateLocation(DOOR, m_board.getInanimateVector(DOOR));
        m_board.setInanimateLocation(KEY, m_board.getInanimateVector(KEY));
        m_board.setInanimateLocation(GIFT, m_board.getInanimateVector(GIFT));
        //---------------------------------------
        if (stageManager()) {
            m_currLevelIndex++;
            continue;
        }
        else if(m_board.getCurrLife() != 0){
            cout << "Thanks for playing! have a wondeful day" << endl;
            break;
        }
        cout << "You lost, don't worry, you can try again!" << endl;
        std::this_thread::sleep_for(1s);
        //move cats, check interaction
    }

};
bool Controller::isNextMoveValid(const Location currLocation,const Location nextLocation){
    switch (m_board.getCharAtLocation(nextLocation)) {
    case WALL:
        return false;
    default: //check if out of bounds, if not then return true
        if (m_board.outOfBounds(nextLocation)) {
            return false;
        }
        return true;
    }
}
void Controller::interactionManager(Location nextLocation) {
    switch (m_board.getCharAtLocation(nextLocation)) {
    case CAT:
        m_board.interaction(CAT);
        break;
    case CHEESE:
        m_board.interaction(CHEESE);
        break;
    case GIFT:
        m_board.interaction(GIFT);
        break;
    case DOOR:
        m_board.interaction(DOOR);
        break;
    case KEY:
        m_board.interaction(KEY);
        break;
    default: //case EMPTY
        break;
    }
}
void Controller::loadPlaylist(){
    string line;
    ifstream playlistStream(m_playlistName);
    if (!playlistStream.is_open()) {
        cerr << "Something went horribly wrong. check playlist.txt and level file for errors" << endl;
    }
    while (getline(playlistStream, line)) {
        m_playlist.push_back(line);
    }
}
bool Controller::stageManager() {
    while (!m_board.hasWon() && !m_board.hasLost()) {
        m_board.printMap();
        //--------- next move -----------
        int nextMouseMove = _getch();
        Location nextLocation;

        if (nextMouseMove == SPECIAL_KEY) {
            Location currLocation = m_board.getMouseCurrLocation();//store location
            nextMouseMove = _getch(); // get move 
            switch (nextMouseMove) {
            case UP:
                nextLocation.row += -1;
                break;
            case DOWN:
                nextLocation.row += 1;
                break;

            case LEFT:
                nextLocation.col += -1;
                break;

            case RIGHT:
                nextLocation.col += 1;
                break;
            default:
                break;
            }
            if (!isNextMoveValid(currLocation, nextLocation)) {
                continue;
            }
            //move is valid, move and check for interactions 
            interactionManager(nextLocation);
            m_board.moveMouse(nextMouseMove);

        }
        else {
            if (nextMouseMove == ESCAPE) {
                break;
            }
            if (nextMouseMove == SPACE) {
                continue;
            }
        }

    }
    if (m_board.hasWon()) {
        return true;
    }
    return false;
} // return true if the player finished the level successfully 
