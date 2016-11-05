#include <iostream>

struct planet {
    std::string name;
    float distance;
    float speed;
    float size;
    bool is_moon;
	float rgb_color[3];
    

    planet(std::string n, float d, float speed, float s, bool x,float red, float green, float blue):
        name{n},
        distance{d},
        speed{speed},
        size{s},
        is_moon{x}
		{
		rgb_color[0] = red; rgb_color[1] = green; rgb_color[2] = blue;
		}

};