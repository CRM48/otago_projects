/*
 * renderApp.cpp
 *
 * by Stefanie Zollmann
 *
 * Basic model loading with assimp library
 *
 */


// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION


// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;


// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/Shader.hpp>
#include <common/Object.hpp>
#include <common/Scene.hpp>
#include <common/Triangle.hpp>
#include <common/BasicMaterialShader.hpp>
#include <common/Mesh.hpp>
#include <common/Controls.hpp>
#include <common/Group.hpp>
#include <common/Objloader.hpp>
#include <common/Quad.hpp>

#include <iostream>

bool spacePressed = false;
int windowWidth = 1024;
int windowHeight = 768;

bool initWindow(std::string windowName){
    
    // Initialise GLFW
    if( !glfwInit() ){
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return false;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n" );
        getchar();
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    
    return true;
    
}

// Function to set up framebuffer
bool setupFramebuffer(GLuint& framebufferName, GLuint& renderedTexture) {
    // Generate framebuffer
    glGenFramebuffers(1, &framebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferName);

    // Generate texture
    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 

    // Attach texture to framebuffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

    // Create depth buffer
    GLuint depthBuffer;
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);

    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH_COMPONENT24,
        windowWidth,
        windowHeight
    );

    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_RENDERBUFFER,
        depthBuffer
    );

    // Check framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        // Handle framebuffer completeness error
        return false;
    }

    return true;
}



int main( int argc, char *argv[] ){

    initWindow("renderEngine Skeleton");
    glfwMakeContextCurrent(window);
    
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to initialize OpenGL context\n");
        return -1;
    }

    std::cout << "Kia ora" << std::endl;
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, windowWidth/2, windowHeight/2);
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Allows for transparent images dictated by the alpha value
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
   
    //create a Vertex Array Object and set it as the current one
    //we will not go into detail here. but this can be used to optimise the performance by storing all of the state needed to supply vertex data
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    /*
     * Create Scene
     * With a object and texture loaded from loader
     */
    
    Scene* myScene = new Scene();
    
    // Read our .obj files - this is hard coded for testing - you can pass obj file names as arguments instead to make the code more flexible
    
    if(argc==1){
        // if nothing specified we load default objects
        // person obj
        Group* person = new Group("phongShader");
        bool res = loadOBJMTL("person.obj", person);
        if (res) {
            person->init(); 
            //add objects to the scene
            myScene->addObject(person); 
        }
        else {
            printf("Failed to load person.obj\n");
        }
        
    }
    else{
        
        for (int a = 1; a < argc; ++a) {
            Group* objGroup = new Group("phongShader"); //change shader being called by changing parameter, default : basicShader
            // Creates a material instance in objloader which parces all the data
            //from argv[1] path mtl file into a material instance which is then applied
            //to objGroup
            bool res = loadOBJMTL(argv[a], objGroup);
            if(res){
                //Then initialises the group. This creates a MTL shader which sets
                //all the relevant values from the MTL file and then assigns the MTL shader
                //to a regular shader object
                objGroup->init();
                //add objects to the scene
                myScene->addObject(objGroup);
            }
            else {
                printf("Failed to load ");
                printf(argv[a] + '\n');
            }
        }
    }
    
    
    Camera* myCamera = new Camera();
    myCamera->setPosition(glm::vec3(0,100,200)); //set camera to show the models
    Controls* myControls = new Controls(myCamera);
    myControls->setSpeed(30);

    // create a Framebuffer and renderedTexture GLuint
    GLuint FramebufferName = 0; 
    GLuint renderedTexture; 
    
    // setup the frame buffer and texture
    if (!setupFramebuffer(FramebufferName, renderedTexture)) {
        return false;
    }
    
    // create a postEffect MTLShader and quad instance
    MTLShader* postEffectShader = new MTLShader("postEffect");  
    Quad* outputQuad = new Quad();
    outputQuad->setShader(postEffectShader);
    

    // For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;
    //Render loop
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 ){// Clear the screen
        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago 
            // printf and reset
            printf("%f ms/frame\n", 1000.0 / double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        // track a space press and flip the value
        static bool previousSpace = false;
        bool currentSpace = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;

        if (currentSpace && !previousSpace) {
            spacePressed = !spacePressed;
        }

        previousSpace = currentSpace;
        
        
        
        if (spacePressed) {
            // bind the scene to a frame buffer
            glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        }
        else {
            // otherwise just bind the already initialised non-animated framebuffer to the screen
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Also clear the depth buffer!!! 

        // update camera controls with mouse input
        myControls->update(); 
        //float m = myScene->getRenderMode();//change render mode based on key input
        // takes care of all the rendering automatically
        myScene->render(myCamera); 
        
        if (spacePressed) { 
            // bind the frame buffer to the screen
            glBindFramebuffer(GL_FRAMEBUFFER, 0); 
            glViewport(0, 0, windowWidth, windowHeight); 
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);

            // bind the post-processing shader
            postEffectShader->bind(); 
            glActiveTexture(GL_TEXTURE0);  
            glBindTexture(GL_TEXTURE_2D, renderedTexture);

            // set the time for animation effect in shader
            postEffectShader->setTime((float)(glfwGetTime() * 10.0f));

            //call render directly to render quad only without transformations 
            outputQuad->directRender();
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
        }
                
        // Swap buffers
        glfwSwapBuffers(window); 
        glfwPollEvents();       
    }
    
    
    glDeleteVertexArrays(1, &VertexArrayID);
    //delete texture;
    delete myScene;
    delete myCamera;
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}



