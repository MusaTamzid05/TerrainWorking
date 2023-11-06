#include "utils.h"

LinearInterpolator::LinearInterpolator(float min, float max, float output_min, float output_max):
    x1(min),
    x2(max),
    y1(output_min),
    y2(output_max) {

    }



float LinearInterpolator::map(float value) {
    float a = (y2 - y1) / (x2 - x1);
    float b = value - x1;

    return y1 + (a * b);

}

std::vector<std::string> split(const std::string& line, char splitter) {
    std::vector<std::string> results;
    std::string temp = "";

    for(char ch : line) {
        if(ch == ' ') {
            results.push_back(temp);
            temp = "";
            continue;
        }

        temp += ch;

    }

    results.push_back(temp);
    return results;
}
