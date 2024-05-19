//
// Created by Adam Simonov on 9/5/24.
//

#include "Mouse.h"
#include "io.h"

void Mouse::setLocation(const int x,const int y){
    m_location.col = x;
    m_location.row = y;
};
void Mouse::setLocation(const Location& location){
    m_location = location;
};
void Mouse::changeLife(const int amount){
    m_life += amount;
};
void Mouse::changeScore(const int amount){
    m_score += amount;
};
void Mouse::changeKeys(const int amount){
    m_keys += amount;
};
void Mouse::changeCheese(const int amount)
{
    m_cheese += amount;
}
Location Mouse::getLoction() const{
    return m_location;
};
int Mouse::getKeys() const{
    return m_keys;
};
int Mouse::getScore() const{
    return m_score;
}
int Mouse::getCheese() const
{
    return m_cheese;
}

int Mouse::getLife() const {
    return m_life;
}
;
void Mouse::moveLeft(){
    setLocation(m_location.col - 1, m_location.row);
};
void Mouse::moveRight(){
    setLocation(m_location.col + 1, m_location.row);
};
void Mouse::moveUp(){
    setLocation(m_location.col, m_location.row - 1); 
};
void Mouse::moveDown(){
    setLocation(m_location.col, m_location.row + 1);
};