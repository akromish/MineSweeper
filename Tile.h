#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Textures.h"

class Tile {
    bool isMine;
    bool mineClicked;
    bool isFlagged;
    bool isRevealed;
    bool isSideCheck;
    int adjMines;
    int xcoord;
    int ycord;
    std::string image;
    sf::Sprite sprite;
    sf::Sprite flag;
    sf::Sprite mine;
    sf::Sprite num;
    sf::Sprite deMine;

public:

    std::vector<Tile*> neighbors;

    Tile();

    void setPosition(int x, int y);

    sf::Sprite getSprite();

    sf::Sprite getNum();

    sf::Sprite getFlag();

    sf::Sprite getMine();

    sf::Sprite getDeMine();

    void setSprite(string name);

    void
    \();

    bool isAMine();

    void setReveal(bool isItRevealed);

    void setFlagged(bool isItFlagged);

    void addNeighbors(Tile &tile, int pos);

    void mineNeighbors();

    bool isFlaggedTile();

    bool isRevealedTile();

    int numAdjMines();

    void setNum(string sname);

    void mineIsClicked();

    bool isMineClicked();

    void setSideCheck();

    bool isSideChecked();

    void tileReveal();

    bool notMine();

    ~Tile();

};