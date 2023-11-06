#include "camera.h"
#include "const.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Camera* Camera::instance = nullptr;

Camera::Camera(glm::vec3 position  ,
               glm::vec3 up ,
               float yaw ,
               float pitch 
        ):front(glm::vec3(0.0f , 0.0f , -1.0f)),
movement_speed(SPEED),
mouse_sensitivity(SENSITIVITY),
zoom(ZOOM) {

    this->position = position;
    world_up= up;
    this->yaw = yaw;
    this->pitch = pitch;
    update_camera_vectors();

    projection = glm::perspective(
            glm::radians(45.0f),
            (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT,
            0.1f,
            100.0f
            );

}

Camera::Camera(float posX , float posY , float posZ , float upX , float upY , float upZ , float yaw, float pitch):front(glm::vec3(0.0f , 0.0f , -1.0f)),
movement_speed(SPEED),
mouse_sensitivity(SENSITIVITY),
zoom(ZOOM){

    position = glm::vec3(posX , posY , posZ);
    world_up = glm::vec3(upX , upY , upZ);
    pitch = pitch;
    update_camera_vectors();

    projection = glm::perspective(
            glm::radians(45.0f),
            (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT,
            0.1f,
            100.0f
            );
}


void Camera::update_camera_vectors() {

    glm::vec3 temp_front;


    temp_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    temp_front.y = sin(glm::radians(pitch));
    temp_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(temp_front);


    right =  glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));

}

glm::mat4 Camera::get_view_matrix() {
    return glm::lookAt(position, position + front, up);
}


void Camera::process_keyboard(Camera_Movement direction , float delta_time) {


    float velocity = movement_speed* delta_time;

    if(direction == FORWARD)
        position += front * velocity;

    if(direction == BACKWARD)
        position -= front * velocity;

    if(direction == LEFT)
        position -= right * velocity;

    if(direction == RIGHT)
        position += right * velocity;

    if(direction == UP)
        position += up * velocity;

    if(direction == DOWN)
        position -= up * velocity;

}

void Camera::process_mouse_movement(float xoffset , float yoffset , bool constrainPitch ) {

    xoffset *= mouse_sensitivity;
    yoffset *= mouse_sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(constrainPitch) {

        if(pitch > 89.0f)
            pitch = 89.0f;

        if(pitch < -89.0f)
            pitch = -89.0f;

    }
    
    update_camera_vectors();
}

void Camera::process_mouse_scroll(float yoffset) {

    if(zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;

    if(zoom <= 1.0f)
        zoom = 1.0f;

    if(zoom >= 45.0f)
        zoom = 45.0f;
}


Camera* Camera::get_instance() {

    if(instance == nullptr) 
        instance = new Camera();

    return instance;

}
