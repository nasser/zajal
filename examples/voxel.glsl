#version 410

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 8) out;

void main()
{
    vec4 Pos = gl_in[0].gl_Position;
    vec4 up = vec4(0.0, 0.05, 0.0, 0.0);
    vec4 right = vec4(0.05, 0.0, 0.0, 0.0);
    vec4 forward = vec4(0.0, 0.0, 0.05, 0.0);
    
    // gl_Position = Pos;
    // EmitVertex();
    
    gl_Position = projectionMatrix * (Pos - right - up + forward);
    EmitVertex();

    gl_Position = projectionMatrix * (Pos - right + up + forward);
    EmitVertex();

    gl_Position = projectionMatrix * (Pos + right - up + forward);
    EmitVertex();

    gl_Position = projectionMatrix * (Pos + right + up + forward);
    EmitVertex();
    
    gl_Position = projectionMatrix * (Pos - right - up - forward);
    EmitVertex();

    gl_Position = projectionMatrix * (Pos - right + up - forward);
    EmitVertex();

    gl_Position = projectionMatrix * (Pos + right - up - forward);
    EmitVertex();

    gl_Position = projectionMatrix * (Pos + right + up - forward);
    EmitVertex();

    EndPrimitive();
}