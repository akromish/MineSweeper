#include "Tile.h"


Tile::Tile(){
    isMine = false;
    isFlagged = false;
    isRevealed = false;
    isSideCheck = false;
    adjMines = 0;
    xcoord = 0;
    ycord = 0;
    image = "tileHidden";
    sf::Texture *temp = Textures::retrieveTexture(image);
    sprite.setTexture(*temp);
    sf::Texture *temp2 = Textures::retrieveTexture("flag");
    flag.setTexture(*temp2);
    sf::Texture *temp3 = Textures::retrieveTexture("mine");
    mine.setTexture(*temp3);
    sf::Texture *temp4 = Textures::retrieveTexture("number1");
    num.setTexture(*temp4);
    sf::Texture *temp5 = Textures::retrieveTexture("mine");
    deMine.setTexture(*temp5);

    for (int i = 0; i < 8; ++i) {
        neighbors.push_back(nullptr);
    }
    mineClicked = false;

}

void Tile::setPosition(int x, int y) {
    xcoord = x;
    ycord = y;
    sprite.setPosition(xcoord,ycord);
    flag.setPosition(xcoord,ycord);
    mine.setPosition(xcoord,ycord);
    num.setPosition(xcoord,ycord);
    deMine.setPosition(xcoord,ycord);
}

sf::Sprite Tile::getSprite() {
    return sprite;
}

sf::Sprite Tile::getNum(){
    return num;
}

sf::Sprite Tile::getFlag(){
    return flag;
}

sf::Sprite Tile::getMine(){
    return mine;
}

sf::Sprite Tile::getDeMine(){
    return deMine;
}

bool Tile::isMineClicked(){
    return mineClicked;
}

void Tile::mineIsClicked(){
    mineClicked = true;
}

void Tile::setSprite(string sname){
    sf::Texture *temp = Textures::retrieveTexture(sname);
    sprite.setTexture(*temp);
}

void Tile::setNum(string sname){
    sf::Texture *temp = Textures::retrieveTexture(sname);
    num.setTexture(*temp);
}

void Tile::setMine(){
    isMine=true;

}

void Tile::addNeighbors(Tile &tile, int pos){
    neighbors[pos] = &tile;
}

bool Tile::isAMine() {
    return isMine;
}

void Tile::mineNeighbors(){
    for(int i=0;i<8;i++){
        if(neighbors[i]!=nullptr){
            if(neighbors[i]->isAMine()){
                adjMines++;
            }
        }
    }
}

bool Tile::isFlaggedTile() {
    if(isFlagged){
        return true;
    }
    return false;
}

bool Tile::isRevealedTile() {
    if(isRevealed){
        return true;
    }
    return false;
}

int Tile::numAdjMines(){
    return adjMines;
}

void Tile::setReveal(bool isItRevealed){
    isRevealed = isItRevealed;
}

void Tile::setFlagged(bool isItFlagged){
    isFlagged = isItFlagged;
}


void Tile::setSideCheck(){
    isSideCheck = true;
}

bool Tile::isSideChecked(){
    return isSideCheck;
}

void Tile::tileReveal(){
    setSprite("tileRevealed");
    setReveal(true);
}

bool Tile::notMine(){
    if(!isMine){
        return true;
    }
    return false;
}

Tile::~Tile() {
    Tile *delT;
    for(auto it = neighbors.begin();it!=neighbors.end();++it){
        delT = *it;
        delete delT;
    }
}
