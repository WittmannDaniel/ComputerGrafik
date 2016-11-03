#include <iostream>

struct planet {
    std::string name;
    float distance;
    float speed;
    float size;
    bool is_moon;
    

    planet(std::string n, float d, float speed, float s, bool x):
        name{n},
        distance{d},
        speed{speed},
        size{s},
        is_moon{x}
        {}

};