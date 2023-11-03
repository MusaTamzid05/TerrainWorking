#include <iostream>
#include <cstdlib>
#include <ctime>
#include "const.h"
#include "display.h"


int main(int argc , char** argv) {
    srand(time(0));

    Display display("Display" , SCREEN_WIDTH, SCREEN_HEIGHT);
    display.run();

}
