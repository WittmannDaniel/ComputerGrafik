#include <iostream>
#include "pixel_data.hpp"


struct planet {
    std::string name;
    float distance;
    float speed;
    float size;
    bool is_moon;
	float rgb_color[3];
	pixel_data texture;
    

    planet(std::string n, float d, float speed, float s, bool x,float red, float green, float blue):
        name{n},
        distance{d},
        speed{speed},
        size{s},
        is_moon{x}
		{
			rgb_color[0] = red; rgb_color[1] = green; rgb_color[2] = blue;
		}

	planet(std::string n, float d, float speed, float s, bool x, pixel_data tex):
		name{ n },
		distance{ d },
		speed{ speed },
		size{ s },
		is_moon{ x },
		texture(tex) 
		{
			rgb_color[0] = 1.0f; rgb_color[1] = 1.0f; rgb_color[2] = 1.0f;
		}
};