
#include "MTLShader.hpp"
// complete the setters with the appropriate method for passing information to the shaders
#include "Texture.hpp"
#include "iostream"

MTLShader::MTLShader(){

}

// version of constructor that allows for  vertex and fragment shader with differnt names

MTLShader::MTLShader(std::string vertexshaderName, std::string fragmentshaderName): Shader(vertexshaderName, fragmentshaderName){

    setUpShaderParameters();

}

// version of constructor that assumes that vertex and fragment shader have same name
MTLShader::MTLShader(std::string shaderName): Shader(shaderName){

    setUpShaderParameters();

}

MTLShader::~MTLShader(){
    glDeleteTextures(1, &m_TextureID);

}

void MTLShader::setUpShaderParameters(){
    // default variables
    m_ambientColor = glm::vec4(1.0);
    m_diffuseColor = glm::vec4(1.0);
    m_specularColor = glm::vec4(1.0);
    m_opacity = 1.0;
    m_ns = 1.0;
    m_lightPos = glm::vec3(1, 0, 0);
    m_texture = NULL;

    // retrieve uniform variable locations from the shader program
    timeID = glGetUniformLocation(programID, "time");
    m_TextureID = glGetUniformLocation(programID, "myTextureSampler");
    ambientcolorID = glGetUniformLocation(programID, "ambientColor");
    diffusecolorID = glGetUniformLocation(programID, "diffuseColor");
    specularcolorID = glGetUniformLocation(programID, "specularColor");
    nsID = glGetUniformLocation(programID, "ns");
    opacityID = glGetUniformLocation(programID, "opacity");
    m_lightPosID = glGetUniformLocation(programID, "LightPosition_worldspace");
    
    // set initial default values for the uniform variables
    glProgramUniform4fv(programID, ambientcolorID, 1, &m_ambientColor[0]); 
    glProgramUniform4fv(programID, diffusecolorID, 1, &m_diffuseColor[0]);
    glProgramUniform4fv(programID, specularcolorID, 1, &m_specularColor[0]);
    glProgramUniform1f(programID, nsID, m_ns);
    glProgramUniform1f(programID, opacityID, m_opacity);
    glProgramUniform3f(programID, m_lightPosID, m_lightPos.x, m_lightPos.y, m_lightPos.z); 
}

void MTLShader::setTexture(Texture* texture){
    m_texture = texture;
    glUniform1i(m_TextureID, m_texture->getTextureID());
}


void MTLShader::setLightPos(glm::vec3 lightPos){
    m_lightPos = lightPos;
    glProgramUniform3f(programID, m_lightPosID, m_lightPos.x, m_lightPos.y, m_lightPos.z);
}

void MTLShader::setDiffuse(glm::vec3 diffuse){
    m_diffuseColor = glm::vec4(diffuse[0], diffuse[1], diffuse[2], 1.0);
    glProgramUniform4fv(programID,diffusecolorID,1, &m_diffuseColor[0]);
}
void MTLShader::setAmbient(glm::vec3 ambient){
    m_ambientColor = glm::vec4(ambient[0],ambient[1],ambient[2],1.0);
    glProgramUniform4fv(programID, ambientcolorID, 1, &m_ambientColor[0]);

}
void MTLShader::setSpecular(glm::vec3 specular){
    m_specularColor = glm::vec4(specular[0],specular[1],specular[2],1.0);
    glProgramUniform4fv(programID, specularcolorID, 1, &m_specularColor[0]);
}

void MTLShader::setOpacity(float opacity){
    m_opacity = opacity;
    glProgramUniform1f(programID, opacityID, m_opacity);
}

void MTLShader::setSpecularExponent(float ns) {
    m_ns = ns;
    glProgramUniform1f(programID, nsID, m_ns);
}

void MTLShader::setTime(float t) {
    glUniform1f(timeID, t);

}

void MTLShader::bind(){
    // Use our shader
    glUseProgram(programID);
    // Bind our texture in Texture Unit 0
    if(m_texture!=NULL){
        m_texture->bindTexture();
        // Set our "myTextureSampler" sampler to user Texture Unit 0 using glUniform1i
        glUniform1i(m_TextureID, 0); 
    }

}
