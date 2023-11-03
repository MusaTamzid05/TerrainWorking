#include "display.h"
#include "camera.h"
#include "terrain.h"
#include <iostream>




Display::Display(const std::string& window_name,
const int width , const int height ):m_close(false)   {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE ,GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width  , height , window_name.c_str(), nullptr , nullptr);

    if(m_window == nullptr) {
        std::cerr << "Failed to create GLFW window.\n";
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(m_window);
    set_callbacks();


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD.\n";
        exit(1);
    }

    last_frame = 0.0f;
    delta_time = 0.0f;

    terrain = new Terrain(100);
    terrain->init_mesh();

    /*
    std::vector<float> vertices = generate_terrain(100, 50);
    vertices = normalize(vertices);

    for(int i = 0; i < 100; i += 1 ) {
        std::cout <<  vertices[i] << " ";

        if(((i + 1) % 3) == 0)
            std::cout << "\n";

    }
    */

    //Terrain terrain(100);




}

Display::~Display() {
    glfwTerminate();

}

void Display::run() {

    while(!m_close) {
        update();
        render();
        process_input();
        clear();

    }

}

void Display::set_callbacks(bool capture_mouse) {
    
    glfwSetFramebufferSizeCallback(m_window , frambuffer_size_callback);

    if(capture_mouse)
        glfwSetInputMode(m_window , GLFW_CURSOR , GLFW_CURSOR_NORMAL);
    else
        glfwSetInputMode(m_window , GLFW_CURSOR , GLFW_CURSOR_DISABLED);

    glfwSetScrollCallback(m_window , scroll_callback);
    glfwSetCursorPosCallback(m_window , mouse_callback);

}




void Display::update() {
    Camera::get_instance()->update_camera_vectors();

    float current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

}

void Display::render() {
    glClearColor(0.2f , 0.3f , 0.3f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //terrain->render();

}

void Display::clear() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();

}


void Display::frambuffer_size_callback(GLFWwindow* window , int width , int height) {
    glViewport(0 , 0 , width , height);
}


void Display::mouse_callback(GLFWwindow* window , double xpos , double ypos) {
}


void Display::scroll_callback(GLFWwindow* window , double xoffset, double yoffset) {
}


void Display::process_input() {

    if(glfwGetKey(m_window ,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        m_close = true;


    if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        Camera::get_instance()->process_keyboard(Camera::Camera_Movement::FORWARD, delta_time);

    if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        Camera::get_instance()->process_keyboard(Camera::Camera_Movement::BACKWARD, delta_time);

    if(glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        Camera::get_instance()->process_keyboard(Camera::Camera_Movement::LEFT, delta_time);

    if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        Camera::get_instance()->process_keyboard(Camera::Camera_Movement::RIGHT, delta_time);


}


