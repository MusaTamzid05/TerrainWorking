#include <iostream>
#include "const.h"
#include "display.h"
#include "utils.h"


#include <ctime>


int main(int argc , char** argv) {
    srand(time(0));

    for(int i = 0; i < 10; i += 1) {
        glm::vec3 result = generate_ramdom_point(120, 120);
        std::cout << result.x << " " <<  result.y << " " << result.z << "\n";

    }
    Display display("Display" , SCREEN_WIDTH, SCREEN_HEIGHT);
    display.run();

}
