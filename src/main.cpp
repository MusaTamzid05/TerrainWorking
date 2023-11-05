#include <iostream>
#include "const.h"
#include "display.h"


int main(int argc , char** argv) {

    Display display("Display" , SCREEN_WIDTH, SCREEN_HEIGHT);
    display.run();

}
