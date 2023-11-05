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
