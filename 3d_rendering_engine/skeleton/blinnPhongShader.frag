#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 posWorldspace;
in vec3 normalCameraspace;
in vec3 eyeDirectionCameraspace;
in vec3 lightDirectionCameraspace;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh
uniform sampler2D myTextureSampler;
uniform vec4 diffuseColor;
uniform vec4 ambientColor;
uniform vec4 specularColor;
uniform float opacity;
uniform float ns;

void main() {
    vec3 textureVal = texture(myTextureSampler, UV).rgb;

    // calculate cosTheta
    vec3 N = normalize(normalCameraspace);
    vec3 L = normalize(lightDirectionCameraspace);
    float cosTheta = clamp(dot(N, L), 0, 1);

    // calculate cosAlpha
    vec3 E = normalize(eyeDirectionCameraspace);
    vec3 H = normalize(L + E); // Halfway vector
    float cosAlpha = clamp(dot(N, H), 0, 1); // Cosine of the angle between N and H

    // compute each component
    vec3 diffuseComponent = diffuseColor.rgb * textureVal * cosTheta;
    vec3 ambientComponent = ambientColor.rgb * textureVal;
    vec3 specularComponent = specularColor.rgb * textureVal * pow(cosAlpha, ns);

    // compute overall color using each component
    color.rgb = diffuseComponent + ambientComponent + specularComponent;
    // set the alpha level to the opacity level
    color.a = opacity;
}

