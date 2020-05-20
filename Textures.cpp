#include "Textures.h"
using namespace sf;


map<string, Texture*> Textures::textures;


Textures::~Textures() {
    Texture *delT;
    for(auto it = textures.begin();it!=textures.end();++it){
        delT = it->second;
        delete delT;
    }
}

Texture *Textures::loadTexture(string name, string relativePath) {
    auto *texture = new Texture();
    texture->loadFromFile(relativePath);
    textures[name] = texture;
    return textures[name];
}

Texture *Textures::loadTexture(string name, string relativePath,int digit){
    auto *texture = new Texture();
    texture->loadFromFile(relativePath,sf::IntRect(21*digit,0,21,32));
    textures[name] = texture;
    return textures[name];
}


Texture *Textures::retrieveTexture(string name){
    return textures[name];
}





