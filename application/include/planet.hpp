#include <iostream>

struct planet {
    std::string name;
    float distance;
    float speed;
    float size;
    

    planet(std::string n, float d, float speed, float s):
        name{n},
        distance{d},
        speed{speed},
        size{s}
        {}

};