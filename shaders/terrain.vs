#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 Color;

void main() {
    float color_value = aPos.y * 10.0f;

    if(color_value <= 0.2)
        Color = vec4(vec3(0.0f, 0.3f, 0.7), 1.0f);
    else if(color_value >= 0.2 && color_value <= 0.3)
        Color = vec4(vec3(0.545, 0.270, 0.074),1.f);
    else
        Color = vec4(vec3(0.0f, color_value, 0.0f), 1.0f);

    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
