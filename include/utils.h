#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

struct LinearInterpolator {
    LinearInterpolator(float min, float max, float output_min, float output_max);

    float map(float value);


    float x1;
    float y1;
    float x2;
    float y2;

};

std::vector<std::string> split(const std::string& line, char splitter);

#endif
