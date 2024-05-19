//
// Created by Adam Simonov on 9/5/24.
//

#include "Board.h"
#include "Mouse.h"
#include "io.h"

using namespace Keys;
using namespace SpecialKeys;
using namespace Characters;

class Controller;//forward declaration

Board::Board(){
    m_bottomRight.col = 0;
    m_bottomRight.row = 0; // setting topRight

    m_topLeft.col = 0;
    m_topLeft.row = 0; // setting BottomLeft

    m_numOfCheese = 0; // set NumOFCheese
    m_numOfKeys = 0; // set NumOfKeys

    //fill locations for all items on board;
    m_mouse.setLocation(0,0);
    vector<Location> emptyVector = {};
    m_cheeseLocations = emptyVector;
    m_doorLocations = emptyVector;
    m_keyLocations = emptyVector;
    m_giftLocations = emptyVector;
};
void Board::setNumOfKeys(){
    int keys = 0;
    for(string& line : m_map){
        for (char isKey : line){
            if(isKey == KEY){
                keys++;
            }
        }
    }
    m_numOfKeys =  keys;
};
void Board::setNumOfCheese(){
    int slices = 0;
    for(string& line : m_map){
        for (char isKey : line){
            if(isKey == CHEESE){
                slices++;
            }
        }
    }
    m_numOfCheese = slices;
};
void Board::loadMap(const string mapName){

    ifstream mapStream(mapName);
    if (!mapStream.is_open()) {
        cerr << "Something went wrong";
        return;
    }
    string line;
    while(getline(mapStream, line)){
        m_map.push_back(line);
    }//setting m_map, stream will close upon exiting the funtion
};
void Board::printMap() const{
    for(const string& line : m_map){
        cout << line << endl;
    }
    cout << "Score: " << m_mouse.getScore() << "| " << "Life: " << m_mouse.getLife() << "| " << "keys: " << m_mouse.getKeys() << "| " << getcurrMapName() << "| " << endl;
};
bool Board::setMapName(ifstream& playlist) {
    if (getline(playlist, m_currMapName)) {
        return true;
    };
    return false;
}
void Board::setInanimateLocation(const char character, vector<Location>& wanted){
    Location charLocation;
    int row = 0;
    int col = 0;

    for(string& line : m_map){
        for(char& a : line){
            if(a == character){
                charLocation.col = col;
                charLocation.row = row;
                wanted.push_back(charLocation);
            }
            col++;
        }
        row++;
        col = 0;
    }
}
void Board::setMouseStartLocation(const Location startLocation) {
    m_mouse.setLocation(startLocation);
};
void Board::moveMouse(int nextMouseMove)
{
    //will update location of m_mouse and update the map;
    switch (nextMouseMove) {
    case UP:
        m_map[m_mouse.getLoction().row][m_mouse.getLoction().col] = ' ';
        m_mouse.moveUp();
        m_map[m_mouse.getLoction().row][m_mouse.getLoction().col] = '%';
        break;
    case DOWN:
        m_map[m_mouse.getLoction().row][m_mouse.getLoction().col] = ' ';
        m_mouse.moveDown();
        m_map[m_mouse.getLoction().row][m_mouse.getLoction().col] = '%';
        break;
    case LEFT:
        m_map[m_mouse.getLoction().row][m_mouse.getLoction().col] = ' ';
        m_mouse.moveLeft();
        m_map[m_mouse.getLoction().row][m_mouse.getLoction().col] = '%';
        break;
    case RIGHT:
        m_map[m_mouse.getLoction().row][m_mouse.getLoction().col] = ' ';
        m_mouse.moveRight();
        m_map[m_mouse.getLoction().row][m_mouse.getLoction().col] = '%';
        break;
    default:
        break;
    }
}
void Board::interaction(const int character, bool &canOpenDoor) {
    switch (character) {
    case CHEESE:
        m_mouse.changeScore(10);
        m_mouse.changeCheese(1);
        //chesse number will update because it is removed from the board by the mouse
        break;
    case GIFT:
        m_mouse.changeScore(5);
        //TODO - remove cat
        break;
    case DOOR:
        if (!(m_mouse.getKeys() > 0)) {
            canOpenDoor = false;
            break;
        }
        m_mouse.changeScore(2);
        m_mouse.changeKeys(-1);
        break;
    case KEY:
        m_mouse.changeKeys(1);
        break;
    default: //case EMPTY
        break;
    }
}
void Board::setBottomRight() {
    m_bottomRight.col = int(m_map[0].length());
    m_bottomRight.row = int(m_map.size() - 1); // setting bottomRight

    m_topLeft.col = 0;
    m_topLeft.row = 0; // setting topLeft;
}
void Board::resetMouse() {
    m_mouse.setLocation(getMouseStartLocation());
    m_mouse.changeCheese(-m_mouse.getCheese());
    m_mouse.changeKeys(-m_mouse.getKeys());
}
void Board::resetMap() {
    vector<string> temp = {};
    m_map = temp;
};
int Board::getNumOfKeys() const{
    return m_numOfKeys;
};
int Board::getNumOfChesse() const{
    return m_numOfCheese;
};
int Board::getCurrScore() const {
    return m_mouse.getScore();
}
int Board::getCurrLife() const {
    return m_mouse.getLife();
}
bool Board::isMapNameValid(const string &mapName) const{
    ifstream map(mapName);
    if(mapName.find(".txt") ==  string::npos){
        return false;
    }

    return true;
}
bool Board::hasWon() const {
    if (m_mouse.getCheese() == m_numOfCheese) {
        return true;
    }
    return false;
}
bool Board::hasLost() const
{
    if (m_mouse.getLife() == 0) {
        return true;
    }
    return false;
}
bool Board::outOfBounds(const Location nextLocation) const
{
    if (nextLocation.col < 0 ||
        nextLocation.row < 0 ||
        nextLocation.col > getbottomRight().col-1 ||
        nextLocation.row > m_map.size()-1 ||
        nextLocation.col > m_map[nextLocation.row].size() - 1)
    {
        return true;
    }
    return false;
}
char Board::getCharAtLocation(Location location)const {
    return m_map[location.row][location.col];
}
ifstream& Board::getPlaylistStream()  {
    return m_playlistStream;
}
string Board::getcurrMapName() const {
    return m_currMapName;
}
Location Board::getbottomRight() const{
    return m_bottomRight;
};
Location Board::getMouseStartLocation() const{
    Location startLocation;
    string line;
    char character;
    for (int row = 0; row < m_map.size(); row++) {
        for (int col = 0; col < m_map[row].length(); col++) {
            character = m_map[row][col];
            if (character == MOUSE) {
                startLocation.col = col;
                startLocation.row = row;
                return startLocation;
            }
            
        }
    }
    return startLocation;
}; // returns the location of first instance of %
Location Board::getMouseCurrLocation() const {
    return m_mouse.getLoction();
}
vector<Location>& Board::getInanimateVector(const char character) {
    switch (character) {
    case CHEESE:
        return m_cheeseLocations;
        case GIFT:
            return m_giftLocations;
        case DOOR:
            return m_doorLocations;
        case KEY:
            return m_keyLocations;
        default:
            vector<Location> theCompilerIsAFriend = {};
            return theCompilerIsAFriend;
    }
};