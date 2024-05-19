#pragma once

struct Location
{
    int row = 0;
    int col = 0;

    Location& operator=(const Location& other){
        if(this != &other){
            row = other.row;
            col = other.col;
        }
        return *this;
    }
};
