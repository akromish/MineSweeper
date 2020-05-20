#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Board{
    int flags;
    sf::Sprite face;
    sf::Sprite digit1;
    sf::Sprite digit2;

public:
    Tile tiles[25][16];
    Board(int testCase);
    void setMines();
    void determineAdj();
    bool leftClick(int x,int y);
    void rightClick(int x,int y);
    sf::Sprite getFace();
    sf::Sprite getDigit1();
    sf::Sprite getDigit2();
    void setFace(int num);
    void setDigit1(int num);
    void setDigit2(int num);
    void setDigits();
    void tileFlagged(bool flaged);
    void checkRevealedNeighbors(Tile *tile);
    void checkRevealedNeighbors(Tile tile);

};


