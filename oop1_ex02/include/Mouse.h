//
// Created by Adam Simonov on 9/5/24.
//

#ifndef OOP1_EX02_MOUSE_H
#define OOP1_EX02_MOUSE_H
#include "Location.h"

class Mouse{
public:
    Mouse():
    m_score(0), m_life(3),m_keys(0),m_cheese(0),m_location(Location()){};
    void setLocation(const int x,const int y);
    void setLocation(const Location& location);
    void changeLife(const int amount);
    void changeScore(const int amount);
    void changeKeys(const int amount);
    void changeCheese(const int amount);
    Location getLoction() const;
    int getKeys() const;
    int getScore() const;
    int getCheese() const;
    int getLife() const;
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
private:
    int m_score;
    int m_life;
    int m_keys;
    int m_cheese;
    Location m_location;
};
#endif //OOP1_EX02_MOUSE_H
