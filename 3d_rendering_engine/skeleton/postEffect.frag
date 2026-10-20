#version 330 core

// Interpolated values from the vertex shaders
// e.g.

in vec2 UV;

// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;
uniform float time;


void main(){
    color.rgb = texture( myTextureSampler, UV + 0.005*vec2( sin(time+1024.0*UV.x),cos(time+768.0*UV.y)) ).xyz ;
    color.a = 1.0;
}
