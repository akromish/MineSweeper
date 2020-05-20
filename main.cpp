#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Textures.h"
#include "Tile.h"
using namespace sf;

int main() {
    Textures::loadTexture("mine", "images/mine.png");
    Textures::loadTexture("tileHidden", "images/tile_hidden.png");
    Textures::loadTexture("tileRevealed", "images/tile_revealed.png");
    Textures::loadTexture("number1", "images/number_1.png");
    Textures::loadTexture("number2", "images/number_2.png");
    Textures::loadTexture("number3", "images/number_3.png");
    Textures::loadTexture("number4", "images/number_4.png");
    Textures::loadTexture("number5", "images/number_5.png");
    Textures::loadTexture("number6", "images/number_6.png");
    Textures::loadTexture("number7", "images/number_7.png");
    Textures::loadTexture("number8", "images/number_8.png");
    Textures::loadTexture("flag", "images/flag.png");
    Textures::loadTexture("faceHappy", "images/face_happy.png");
    Textures::loadTexture("digit0", "images/digits.png",0);
    Textures::loadTexture("digit1", "images/digits.png",1);
    Textures::loadTexture("digit2", "images/digits.png",2);
    Textures::loadTexture("digit3", "images/digits.png",3);
    Textures::loadTexture("digit4", "images/digits.png",4);
    Textures::loadTexture("digit5", "images/digits.png",5);
    Textures::loadTexture("digit6", "images/digits.png",6);
    Textures::loadTexture("digit7", "images/digits.png",7);
    Textures::loadTexture("digit8", "images/digits.png",8);
    Textures::loadTexture("digit9", "images/digits.png",9);
    Textures::loadTexture("faceHappy", "images/face_happy.png");
    Textures::loadTexture("faceWin", "images/face_win.png");
    Textures::loadTexture("faceLose", "images/face_lose.png");
    Textures::loadTexture("faceLose", "images/face_lose.png");
    Textures::loadTexture("test1", "images/test_1.png");
    Textures::loadTexture("test2", "images/test_2.png");
    Textures::loadTexture("debug", "images/debug.png");

    Sprite digit0;
    sf::Texture *temp = Textures::retrieveTexture("digit0");
    digit0.setTexture(*temp);
    digit0.setPosition(0,512);

    Sprite debug;
    sf::Texture *temp1 = Textures::retrieveTexture("debug");
    debug.setTexture(*temp1);
    debug.setPosition(496,512);

    Sprite test1;
    sf::Texture *temp2 = Textures::retrieveTexture("test1");
    test1.setTexture(*temp2);
    test1.setPosition(560,512);

    Sprite test2;
    sf::Texture *temp3 = Textures::retrieveTexture("test2");
    test2.setTexture(*temp3);
    test2.setPosition(624,512);


    Board board = Board(0);
    bool debugS = false;
    bool win = false;
    bool loss = false;


    RenderWindow window(VideoMode(800,600), "Minesweeper");
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed){
                if(!win && !loss) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;
                        if (y < 512) {
                            x /= 32;
                            y /= 32;
                            if (!board.leftClick(x, y)) {
                                loss = true;
                            }
                        } else {
                            if (x >= 368 && x <= 432 && y >= 512) {
                                board = Board(0);
                                loss = false;
                            } else if (x >= 560 && x <= 624 && y >= 512) {
                                board = Board(1);
                                loss = false;
                            } else if (x > 624 && x < 688 && y >= 512) {
                                board = Board(2);
                                loss = false;
                            } else if (x >= 496 && x < 560 && y >= 512) {
                                debugS = !debugS;
                            }
                        }

                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;
                        if (y <= 512) {
                            x /= 32;
                            y /= 32;
                            board.rightClick(x, y);
                        }
                    }
                }else{
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;
                        if (x >= 368 && x <= 432 && y >= 512) {
                            board = Board(0);
                            loss = false;
                        }
                    }
                }

            }

        }


        window.clear(sf::Color::White);

        bool tempW = true;
        for(int i=0;i<25;i++) {
            for (int j = 0; j < 16; j++) {
                if(board.tiles[i][j].notMine() && !board.tiles[i][j].isRevealedTile() ){
                    tempW = false;
                }
            }
        }
        win = tempW;

        if(win){
            board.setFace(1);
            for(int i=0;i<25;i++){
                for(int j=0;j<16;j++){
                    if(board.tiles[i][j].isAMine()){
                        board.tiles[i][j].setFlagged(true);
                        board.tileFlagged(true);
                        board.setDigits();
                    }
                }
            }
        }
        if(loss){
            board.setFace(2);
        }


        for(int i=0;i<25;i++){
            for(int j=0;j<16;j++){
                window.draw(board.tiles[i][j].getSprite());
                if(board.tiles[i][j].isRevealedTile() && board.tiles[i][j].numAdjMines()>0 ){
                    window.draw(board.tiles[i][j].getNum());
                }else if(!board.tiles[i][j].isRevealedTile() && board.tiles[i][j].isFlaggedTile()){
                    window.draw(board.tiles[i][j].getFlag());
                }else if(board.tiles[i][j].isAMine() && board.tiles[i][j].isMineClicked()) {
                    window.draw(board.tiles[i][j].getMine());
                }
            }
        }

        window.draw(board.getFace());
        window.draw(digit0);
        window.draw(board.getDigit1());
        window.draw(board.getDigit2());
        window.draw(debug);
        window.draw(test1);
        window.draw(test2);
        if(debugS){
            for(int i=0;i<25;i++){
                for(int j=0;j<16;j++){
                    if(board.tiles[i][j].isAMine()){
                        window.draw(board.tiles[i][j].getDeMine());
                    }
                }
            }
        }

        window.display();

    }

    return 0;

}