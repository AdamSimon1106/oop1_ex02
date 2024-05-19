//
// Created by Adam Simonov on 9/5/24.
//

#ifndef OOP1_EX02_BOARD_H
#define OOP1_EX02_BOARD_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Location.h"
#include "Mouse.h"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::ostream;
using std::vector;
using std::string;

class Board{
public:
    Board();
    void setNumOfKeys();
    void setNumOfCheese();
    void loadMap(const string mapName);
    void printMap() const;
    void setInanimateLocation(const char character, vector<Location>& wanted);
    void setMouseStartLocation(const Location startLocation);
    void moveMouse(int nextMouseMove);
    void interaction(const int character, bool& canOpenDoor);
    void setBottomRight();
    void resetMouse();
    void resetMap();
    int getNumOfKeys() const;
    int getNumOfChesse() const;
    int getCurrScore() const;
    int getCurrLife() const;
    bool isMapNameValid(const string& mapName) const;
    bool hasWon() const;
    bool hasLost() const;
    bool outOfBounds(const Location nextLocation) const;
    bool setMapName(ifstream& playlist);
    char getCharAtLocation(Location location) const;
    ifstream& getPlaylistStream();
    string getcurrMapName() const;
    Location getMouseStartLocation() const;
    Location getMouseCurrLocation() const;
    vector<Location>& getInanimateVector(const char character);
    Location getbottomRight() const;

private:
    vector<string> m_map;
    vector<Location> m_cheeseLocations;
    vector<Location>m_doorLocations;
    vector<Location>m_keyLocations;
    vector<Location>m_giftLocations;
    //TODO - add a cat vector
    int m_numOfKeys;
    int m_numOfCheese;
    Location m_topLeft;
    Location m_bottomRight;
    string m_playlistName;
    string m_currMapName;
    ifstream m_playlistStream;
    Mouse m_mouse;

};
#endif //OOP1_EX02_BOARD_H
