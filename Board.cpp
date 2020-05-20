#include <SFML/Graphics.hpp>
#include "Board.h"
#include <map>
#include <cctype>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
using namespace sf;

Board::Board(int testCase) {
    if(testCase == 0) {
        for(int i=0;i<25;i++){
            for(int j=0;j<16;j++){
                tiles[i][j] = Tile();
            }
        }
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 16; j++) {
                tiles[i][j].setPosition(i * 32, j * 32);
            }
        }
        flags = 50;
        sf::Texture *temp = Textures::retrieveTexture("digit5");
        digit1.setTexture(*temp);
        digit1.setPosition(21, 512);
        sf::Texture *temp2 = Textures::retrieveTexture("digit0");
        digit2.setTexture(*temp2);
        digit2.setPosition(42, 512);
        sf::Texture *temp3 = Textures::retrieveTexture("faceHappy");
        face.setTexture(*temp3);
        face.setPosition(368, 512);

        setMines();
        determineAdj();
    }
    else if(testCase == 1){
        for(int i=0;i<25;i++){
            for(int j=0;j<16;j++){
                tiles[i][j] = Tile();
            }
        }
        string text = "boards/testboard.brd";
                    for(int i=0;i<25;i++){
                        for(int j=0;j<16;j++){
                tiles[i][j].setPosition(i*32,j*32);
            }
        }
        char x[25][16];

        ifstream myFile;
        myFile.open(text);
        string line;
        int i=0;
        char tempC[25];
        while(getline(myFile,line)){
            strcpy(tempC, line.c_str());
            for(int j=0;j<25;j++){
                x[j][i] = tempC[j];
            }
            i++;
        }
        myFile.close();
        string one = "1";
        int count = 0;
        for(int i=0;i<25;i++){
            for(int j=0;j<16;j++){
                string s(1, x[i][j]);
                if(s == one){
                    tiles[i][j].setMine();
                    count++;
                }
            }
        }
        flags = count;
        string tempT = "digit";
        int tempI = count/10;
        tempT+=to_string(tempI);
        sf::Texture *temp = Textures::retrieveTexture(tempT);
        digit1.setTexture(*temp);
        digit1.setPosition(21, 512);
        tempT = "digit";
        tempI = count%10;
        tempT+=to_string(tempI);
        sf::Texture *temp2 = Textures::retrieveTexture(tempT);
        digit2.setTexture(*temp2);
        digit2.setPosition(42, 512);
        sf::Texture *temp3 = Textures::retrieveTexture("faceHappy");
        face.setTexture(*temp3);
        face.setPosition(368, 512);
        determineAdj();

    }else if(testCase == 2){
        for(int i=0;i<25;i++){
            for(int j=0;j<16;j++){
                tiles[i][j] = Tile();
            }
        }
        string text = "boards/testboard2.brd";
        for(int i=0;i<25;i++){
            for(int j=0;j<16;j++){
                tiles[i][j].setPosition(i*32,j*32);
            }
        }
        char x[25][16];

        ifstream myFile;
        myFile.open(text);
        string line;
        int i=0;
        char tempC[25];
        while(getline(myFile,line)){
            strcpy(tempC, line.c_str());
            for(int j=0;j<25;j++){
                x[j][i] = tempC[j];
            }
            i++;
        }
        myFile.close();
        string one = "1";
        int count = 0;
        for(int i=0;i<25;i++){
            for(int j=0;j<16;j++){
                string s(1, x[i][j]);
                if(s == one){
                    tiles[i][j].setMine();
                    count++;
                }
            }
        }
        flags = count;
        string tempT = "digit";
        int tempI = count/10;
        tempT+=to_string(tempI);
        sf::Texture *temp = Textures::retrieveTexture(tempT);
        digit1.setTexture(*temp);
        digit1.setPosition(21, 512);
        tempT = "digit";
        tempI = count%10;
        tempT+=to_string(tempI);
        sf::Texture *temp2 = Textures::retrieveTexture(tempT);
        digit2.setTexture(*temp2);
        digit2.setPosition(42, 512);
        sf::Texture *temp3 = Textures::retrieveTexture("faceHappy");
        face.setTexture(*temp3);
        face.setPosition(368, 512);
        determineAdj();
    }

}

void Board::setMines() {
    vector<int> temp;
    for(int i=0;i<400;i++) {
        temp.push_back(i);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (temp.begin(), temp.end(), std::default_random_engine(seed));
    vector<int> randomInts;
    for(int i=0;i<50;i++) {
        randomInts.push_back(temp[i]);
    }
    int count=0;
    for(int i=0;i<25;i++){
        for(int j=0;j<16;j++){
            if(std::find(randomInts.begin(), randomInts.end(), count) != randomInts.end()) {
                tiles[i][j].setMine();
            }
            count++;
        }
    }
}

void Board::determineAdj() {
    for(int i=0;i<25;i++){
        for(int j=0;j<16;j++){
            if(i == 0){
                if(j == 0){
                    tiles[i][j].addNeighbors(tiles[i+1][j],3);
                    tiles[i][j].addNeighbors(tiles[i+1][j+1],4);
                    tiles[i][j].addNeighbors(tiles[i][j+1],5);
                }else if(j == 15){
                    tiles[i][j].addNeighbors(tiles[i][j-1],1);
                    tiles[i][j].addNeighbors(tiles[i+1][j-1],2);
                    tiles[i][j].addNeighbors(tiles[i+1][j],3);
                }else{
                    tiles[i][j].addNeighbors(tiles[i][j-1],1);
                    tiles[i][j].addNeighbors(tiles[i+1][j-1],2);
                    tiles[i][j].addNeighbors(tiles[i+1][j],3);
                    tiles[i][j].addNeighbors(tiles[i+1][j+1],4);
                    tiles[i][j].addNeighbors(tiles[i][j+1],5);
                }
            }else if(i == 24){
                if(j == 0){
                    tiles[i][j].addNeighbors(tiles[i][j+1],5);
                    tiles[i][j].addNeighbors(tiles[i-1][j+1],6);
                    tiles[i][j].addNeighbors(tiles[i-1][j],7);
                }else if(j == 15){
                    tiles[i][j].addNeighbors(tiles[i-1][j],7);
                    tiles[i][j].addNeighbors(tiles[i-1][j-1],0);
                    tiles[i][j].addNeighbors(tiles[i][j-1],1);
                }else{
                    tiles[i][j].addNeighbors(tiles[i][j+1],5);
                    tiles[i][j].addNeighbors(tiles[i-1][j+1],6);
                    tiles[i][j].addNeighbors(tiles[i-1][j],7);
                    tiles[i][j].addNeighbors(tiles[i-1][j-1],0);
                    tiles[i][j].addNeighbors(tiles[i][j-1],1);
                }
            }else if(j == 0){
                tiles[i][j].addNeighbors(tiles[i+1][j],3);
                tiles[i][j].addNeighbors(tiles[i+1][j+1],4);
                tiles[i][j].addNeighbors(tiles[i][j+1],5);
                tiles[i][j].addNeighbors(tiles[i-1][j+1],6);
                tiles[i][j].addNeighbors(tiles[i-1][j],7);
            }else if(j == 15){
                tiles[i][j].addNeighbors(tiles[i-1][j-1],0);
                tiles[i][j].addNeighbors(tiles[i][j-1],1);
                tiles[i][j].addNeighbors(tiles[i+1][j-1],2);
                tiles[i][j].addNeighbors(tiles[i+1][j],3);
                tiles[i][j].addNeighbors(tiles[i-1][j],7);
            }else {
                tiles[i][j].addNeighbors(tiles[i - 1][j - 1], 0);
                tiles[i][j].addNeighbors(tiles[i][j - 1], 1);
                tiles[i][j].addNeighbors(tiles[i + 1][j - 1], 2);
                tiles[i][j].addNeighbors(tiles[i + 1][j], 3);
                tiles[i][j].addNeighbors(tiles[i + 1][j + 1], 4);
                tiles[i][j].addNeighbors(tiles[i][j + 1], 5);
                tiles[i][j].addNeighbors(tiles[i - 1][j + 1], 6);
                tiles[i][j].addNeighbors(tiles[i - 1][j], 7);
            }
        }


    }
    for(int i=0;i<25;i++){
        for(int j=0;j<16;j++){
            tiles[i][j].mineNeighbors();
        }
    }

}

bool Board::leftClick(int x, int y) {
    if(tiles[x][y].isFlaggedTile() || tiles[x][y].isRevealedTile()){
        return true;
    }
    if(!tiles[x][y].isAMine()){
        int tempN = tiles[x][y].numAdjMines();
        if(tempN!=0) {
            string text = "number";
            text += std::to_string(tempN);
            tiles[x][y].tileReveal();
            tiles[x][y].setNum(text);

        }else{
            Tile *tile = &tiles[x][y];
            checkRevealedNeighbors(tile);

        }
        return true;
    }
    else if(tiles[x][y].isAMine()){
        for(int i=0;i<25;i++){
            for(int j=0;j<16;j++){
                if(tiles[i][j].isAMine()){
                    tiles[i][j].setSprite("tileRevealed");
                    tiles[i][j].mineIsClicked();
                }
            }
        }
        return false;

    }


}




void Board::rightClick(int x, int y) {
    if(!tiles[x][y].isRevealedTile()){
        if(!tiles[x][y].isFlaggedTile()){
            tiles[x][y].setFlagged(true);
            tileFlagged(true);
        }else{
            tiles[x][y].setFlagged(false);
            tileFlagged(false);
        }
    }
    setDigits();
}



sf::Sprite Board::getFace(){
    return face;
}

sf::Sprite Board::getDigit1(){
    return digit1;
}

sf::Sprite Board::getDigit2(){
    return digit2;
}

void Board::setFace(int num){
    if(num == 0){
        face.setTexture(*Textures::retrieveTexture("faceHappy"));
    }
    else if(num == 1){
        face.setTexture(*Textures::retrieveTexture("faceWin"));
    }
    else if(num == 2){
        face.setTexture(*Textures::retrieveTexture("faceLose"));
    }
}

void Board::setDigit1(int num){
    string text = "digit";
    text+= std::to_string(num);
    digit1.setTexture(*Textures::retrieveTexture(text));
}

void Board::setDigit2(int num){
    string text = "digit";
    text+= std::to_string(num);
    digit2.setTexture(*Textures::retrieveTexture(text));
}

void Board::setDigits(){
    if(flags>=0) {
        setDigit1(flags / 10);
        setDigit2(flags % 10);
    }
    else{
        setDigit1(0);
        setDigit2(0);
    }
}

void Board::tileFlagged(bool flagged){
    if(flagged){
        flags--;
    }else{
        flags++;
    }
}

void Board::checkRevealedNeighbors(Tile *tile){
    if(tile != nullptr && !tile->isSideChecked() && tile->numAdjMines() == 0){
        tile->tileReveal();
        tile->setSideCheck();
        for(int i=0;i<8;i++){
            if(tile->neighbors[i]!=nullptr && tile->neighbors.size()>0){
                checkRevealedNeighbors(tile->neighbors[i]);

            }
        }
    }else if(tile != nullptr && tile->numAdjMines() != 0){
        tile->setSideCheck();
        int tempN = tile->numAdjMines();
        string text = "number";
        text += std::to_string(tempN);
        tile->tileReveal();
        tile->setNum(text);
    }

}

void Board::checkRevealedNeighbors(Tile tile){
    if(!tile.isSideChecked() && tile.numAdjMines() == 0){
        tile.tileReveal();
        tile.setSideCheck();
        for(int i=0;i<8;i++){
            if(tile.neighbors[i]!=nullptr){
                checkRevealedNeighbors(*tile.neighbors[i]);

            }
        }
    }else if(tile.numAdjMines() != 0){
        tile.setSideCheck();
        int tempN = tile.numAdjMines();
        string text = "number";
        text += std::to_string(tempN);
        tile.tileReveal();
        tile.setNum(text);
    }

}







