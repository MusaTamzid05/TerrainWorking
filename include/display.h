#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include "gl_headers.h"

#include <glm/glm.hpp>

struct Terrain;
struct Triangle;

class Display {


    public:

        Display(const std::string& window_name , const int width , const int height);
        virtual ~Display();

        void run();

        void process_input();
        void update();
        void render();
        void clear();

        bool is_close() { return m_close; }

        GLFWwindow* get_window() { return m_window; }

    protected:

        GLFWwindow* m_window;
        bool m_close;
        
        static void frambuffer_size_callback(GLFWwindow* window , int width , int height);
        static void mouse_callback(GLFWwindow* window , double xpos , double ypos);
        static void scroll_callback(GLFWwindow* window , double xoffset, double yoffset);

        void set_callbacks(bool capture_mouse = true);

        float delta_time;
        float last_frame;

        Terrain* terrain;






};




#endif
