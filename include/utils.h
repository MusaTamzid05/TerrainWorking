#ifndef UTILS_H
#define UTILS_H

struct LinearInterpolator {
    LinearInterpolator(float min, float max, float output_min, float output_max);

    float map(float value);


    float x1;
    float y1;
    float x2;
    float y2;



};

#endif
