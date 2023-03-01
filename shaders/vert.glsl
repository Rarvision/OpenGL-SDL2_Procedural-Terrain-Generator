// ==================================================================
#version 330 core

layout(location=0)in vec3 position;
layout(location=1)in vec3 color; 
layout(location=2)in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 v_normal;
out vec3 v_color;
out vec3 FragPos;
out float visibility;

const float density = 0.01;
const float gradient = 2.0;

void main()
{
    v_normal = normal;
    v_color = color;
    
    vec4 posToCamera = view * model* vec4(position,1.0f);
    gl_Position = projection * posToCamera;
    
    FragPos = (model* vec4(position,1.0f)).xyz;
    
    float distance = length(posToCamera.xyz);
    visibility = exp(-pow((distance*density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);

}
// ==================================================================
