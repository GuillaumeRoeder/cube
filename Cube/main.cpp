#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

bool posInit = false;
double xInit;
double yInit;

double totalSpeedx = 0;
double totalSpeedy = 0;




void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
///////////////////////////////////////////////////
static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
void mousClickCallback(GLFWwindow* window, int Button, int action, int mods);
/// <summary>
/// //////////////////////////////////////////////////
/// </summary>
/// <param name="centerPosX"></param>
/// <param name="centerPosY"></param>
/// <param name="centerPosZ"></param>
/// <param name="edgeLength"></param>

void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;



int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

    ///////////////////////////////////////////////////
    //mouse inputs
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetMouseButtonCallback(window, mousClickCallback);
    ////////////////////////////////////////////////////////


    //keyboard inputs
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);


    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000); // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); // same as above comment

    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;




    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        

        // Render OpenGL here

        glPushMatrix();
        
        glTranslatef(halfScreenWidth, halfScreenHeight, -500);
        glRotatef((int)(rotationX +=totalSpeedx )%360, 1, 0, 0);
        glRotatef((int)(rotationY += totalSpeedy )%360, 0, 1, 0);


 
        
        std::cout << rotationX << std::endl;
    
        
        
        
        glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);
     
       
        DrawCube(halfScreenWidth, halfScreenHeight, -500, 200);
        /*
       
        if (rotationY + rotationX + rotationZ >= 180.0 || rotationY + rotationX + rotationZ  <= -180.0) {
            rotationY += 180.0;
            rotationX += 180.0;
            rotationZ += 180.0;
            
        }*/
      




       glPopMatrix();
       std::cout << "fin "  << rotationX << std::endl;

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}



static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {

    double x = xInit;
    double y = yInit;
 
    GLfloat rotateSpeedx = 0;
    GLfloat rotateSpeedy = 0;


   
    if (posInit) {
        
        x = xPos;
        y = yPos;
        int a = -1;
        int b = -1;

        if (rotationX >= 90 || rotationX <= -90) {
            b = -b;
        }
        if (rotationY  >= 90 || rotationY <= -90) {
            a = -a;
        }


        rotateSpeedy = b*(x - xInit)*0.02 ;
        rotateSpeedx = a*(y - yInit) *0.02 ;
 

       
    }
    else if (!posInit) {
        xInit = xPos;
        yInit = yPos;

        posInit = true;
    }

    

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        
        totalSpeedx += rotateSpeedx;
        totalSpeedy += rotateSpeedy;
        posInit = false;
        return;
      
    }

    
    //modify rotation
    
}


void mousClickCallback(GLFWwindow* winodw, int Button, int action, int mods) {


   

    if (Button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS ) {
        totalSpeedy -= totalSpeedy;
        totalSpeedx -= totalSpeedx;
       
        

        std::cout << "press" << totalSpeedx<< std::endl;
    }

}




void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << key << std::endl;

    const GLfloat rotationSpeed = 10;

    // actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            rotationX -= rotationSpeed;
            break;
        case GLFW_KEY_DOWN:
            rotationX += rotationSpeed;
            break;
        case GLFW_KEY_RIGHT:
            rotationY += rotationSpeed;
            break;
        case GLFW_KEY_LEFT:
            rotationY -= rotationSpeed;
            break;
        }


    }
}


void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
    {
        // front face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // back face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left

        // left face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // right face
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // top face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left

        // top face
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
    };

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glColor3f( colour[0], colour[1], colour[2] );
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
}