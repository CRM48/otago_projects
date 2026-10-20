#version 330 core

// Input data
in vec2 UV;


// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform float opacity;

void main(){
    vec3 textureVal = texture( myTextureSampler, UV ).rgb;
    color.rgb = textureVal.rgb;
    color.a = opacity;
}
