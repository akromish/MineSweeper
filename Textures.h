#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace std;

class Textures{

    static map<string, sf::Texture*> textures;

    Textures()= default;

public:
    ~Textures();

    static sf::Texture *loadTexture(string name, string relativePath);

    static sf::Texture *loadTexture(string name, string relativePath,int digit);

    static sf::Texture *retrieveTexture(string name);

};

