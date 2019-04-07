#include "main.h"
#include "timer.h"
#include "platform.h"
#include "ball.h"
#include "player.h"
#include "trampoline.h"
#include "pond.h"
#include "plank.h"
#include "porc.h"
#include "magnet.h"
#include <bits/stdc++.h>
using namespace std;


float rand_FloatRange(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}


GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;



/**************************
* Customizable functions *
**************************/
Platform platform1;
Platform platform2;
Trampoline trampoline;
Plank plank[10];
Pond pond;
Porc porc1,porc2;
Player player;
Ball ball[10005];
Magnet magnet;

int count1=0,count2=0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    platform2.draw(VP);
    platform1.draw(VP);
    trampoline.draw(VP);
    pond.draw(VP);
    magnet.draw(VP);
    for(int i = 0;i<10;i++)
    {
        ball[i].draw(VP);
    }
    for(int i = 0;i<3;i++)
    {
        plank[i].draw(VP);
    }
    porc1.draw(VP);
    
    porc2.draw(VP);
    player.draw(VP);
    
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    if (left  && !check_tramp(player.bounding_box(),trampoline.bounding_box())) {
        if(player.position.x>=-2.5 && player.position.x<=.50 && player.position.y<-1.5)
        {
            player.position.x-=0.03;
            player.speed_x=0;
        }
        else
        {
            player.position.x-=0.1;
            player.speed_x=0;
        }
        // Do something
    }
    if(right && !check_tramp(player.bounding_box(),trampoline.bounding_box())){
        if(player.position.x>=-2.51 && player.position.x<=.5 && player.position.y<-1.5)
        {
            player.position.x+=0.03;
            player.speed_x=0;
        }
        else
        {
            player.position.x+=0.1;
            player.speed_x=0;
        }

    }
    if(up && player.position.y<-1.49)
    {
        if(player.position.x>=-2.5&& player.position.x<=.5 && player.position.y<-1.5)
        {
            player.position.y+=0.05;
        }
        else if(player.position.x>=-2.5&& player.position.x<=.5)
        {
            player.speed_y=0.1;
        }
        else     
        {
            player.speed_y=0.2;
        }
    }
}

void tick_elements() {
    char title[100005];
    count1++;
    if(player.level==1 && player.score<70)
    {
        int p =count1/60;
        sprintf(title,"Score -> %d Level -> %d  Score Required -> 70 Time remaining -> %d",player.score,player.level,20-p);
        if(20-p==0)
        {
            sprintf(title,"Game Over");
            glfwSetWindowTitle(window,title);
            for(int i=0;i<1000000000;i++);
            quit(window);    

        }
        glfwSetWindowTitle(window,title);
    }
    else if( player.level==1 && player.score>=70)
    {
        player.level++;
        player.score=0;
        porc1=Porc(-6,-2,0.5,0.5,COLOR_GREEN);   
        porc2=Porc(1.2,-2,0.5,0.5,COLOR_GREEN);   
        count2=0;
        sprintf(title,"Score -> %d Level -> %d  Score Required -> 120 Time remaining -> %d",player.score,player.level,25);
        glfwSetWindowTitle(window,title);   
        for(int i=0;i<1000000000;i++);
           
    }

    if(player.level == 2 && player.score < 120 )
    {
        count2++;
        int p =count2/60;
        sprintf(title,"Score -> %d Level -> %d  Score Required -> 120 Time remaining -> %d",player.score,player.level,25-p);
        if(25-p==0)
        {
            sprintf(title,"Game Over");
            glfwSetWindowTitle(window,title);
            for(int i=0;i<1000000000;i++);
            quit(window);    

        }
        glfwSetWindowTitle(window,title);   
    }
    else if(player.level == 2 && player.score >=120)
    {
        player.level++;
        player.score=0;
        count2=0;
        porc1=Porc(-6,-2,0.5,0.5,COLOR_GREEN);   
        porc2=Porc(1.2,-2,0.5,0.5,COLOR_GREEN);    
        sprintf(title,"Score -> %d Level -> %d  Score Required -> 120 Time remaining -> %d",player.score,player.level,30);
        glfwSetWindowTitle(window,title);   
        for(int i=0;i<1000000000;i++);
        
    }
    if(player.level == 3 && player.score < 180 )
    {
        count2++;
        int p =count2/60;
        sprintf(title,"Score -> %d Level -> %d  Score Required -> 180 Time remaining -> %d",player.score,player.level,30-p);
        if(30-p==0)
        {
            sprintf(title,"Game Over");
            glfwSetWindowTitle(window,title);
            for(int i=0;i<1000000000;i++);
            quit(window);    

        }
        glfwSetWindowTitle(window,title);   
    }
    else if(player.level == 3 && player.score >=180)
    {
           sprintf(title,"You Won the Game");
            glfwSetWindowTitle(window,title);
            for(int i=0;i<1000000000;i++);
            quit(window);

            
    }
    porc1.tick();
    porc2.tick();
        

    for(int i=0;i<10;i++)
        ball[i].tick();
    for(int i = 0;i<3;i++)
    {
        plank[i].tick();
        
    }

    player.tick();
    if(count1%480>240 && player.level == 3)
    {
        magnet = Magnet(-7,3,1,2,COLOR_RED);
        if( player.position.x > -6)
            player.position.x += -0.04;
    }
    else
    {
        magnet = Magnet(-100,3,1.5,2,COLOR_RED);
    }

    if (detect_collision_porc(porc1.bounding_box(), player.bounding_box()) ) {
        
            porc1=Porc(-100,2,0.5,0.5,COLOR_GREEN);
            player.score-=20;   
        }
    if (detect_collision_porc(porc2.bounding_box(), player.bounding_box()) ) {
        
            porc2=Porc(100,2,0.5,0.5,COLOR_GREEN);
            player.score-=20;   
        }
    for(int i=0;i<3;i++)
    {
        if (detect_collision(plank[i].bounding_box(), player.bounding_box()) && player.speed_y<0 && player.position.y>plank[i].position.y+plank[i].radius+0.1 ) {
        
            float p = rand_FloatRange(-30,-8);
            float q = rand_FloatRange(0,6);
            float r = rand_FloatRange(0.2,0.5);
            float angle = ((plank[i].rotation)*M_PI)/180;
            // printf(" angle %f\n",angle);
            
            player.speed_y = (player.speed_x*sin(2*angle)-player.speed_y*cos(2*angle));
            player.speed_x= -1.2*(player.speed_y*sin(2*angle)+player.speed_x*cos(2*angle));
            // printf("%f %f\n",player.speed_x,player.speed_y);
            player.score+=(scorecalc(plank[i].colour));
            plank[i]=Plank(p,q,r,colorpicker());   
        }
    }
    for(int i=0;i<10;i++)
    {
        if (detect_collision(ball[i].bounding_box(), player.bounding_box()) && player.speed_y<0 && player.position.y>ball[i].position.y+ball[i].radius-0.1) {
            float p = rand_FloatRange(-30,-8);
            float q = rand_FloatRange(0,6);
            float r = rand_FloatRange(0.2,0.5);
            player.score+=(scorecalc(ball[i].colour));
            ball[i]=Ball(p,q,r,colorpicker());
            player.speed_y=0.15;  
        }
    }
        if (detect_collision_tramp(player.bounding_box(), trampoline.bounding_box()) && player.speed_y<0)
        {
            player.speed_y=.28;
        }

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    platform1 = Platform(-100,-3,100,-6,COLOR_BROWN);
    platform2 = Platform(-100,-2,100,-3,COLOR_GREYE);
    trampoline = Trampoline(5,-2,1.5,2,COLOR_BRICK);
    pond= Pond(-1,-2,2,COLOR_BLUE);
    magnet = Magnet(-100,3,1.5,2,COLOR_RED);
    for(int i=0;i<10;i++)
    {
        float p = rand_FloatRange(-30,-8);
        float q = rand_FloatRange(0,6);
        float r = rand_FloatRange(0.2,0.5);
        ball[i]=Ball(p,q,r,colorpicker());   
    }
    for(int i=0;i<3;i++)
    {
        float p = rand_FloatRange(-30,-8);
        float q = rand_FloatRange(0,6);
        float r = rand_FloatRange(0.2,0.5);
        plank[i]=Plank(p,q,r,colorpicker());   
    }
    
    porc1=Porc(-100,-2,0.5,0.5,COLOR_GREEN);   
    porc2=Porc(100,-2,0.5,0.5,COLOR_GREEN);   
    
    // Create and compile our GLSL program from the shaders
    player = Player(2,1,COLOR_BALL);
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BLACK.r / 256.0, COLOR_BLACK.g / 256.0, COLOR_BLACK.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0))  ;
    int width  = 1200;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (sqrt(pow(a.x - b.x,2)+pow(a.y-b.y,2)) < (a.r + b.r)) ;
}
bool detect_collision_plank(bounding_box_plank a, bounding_box_t b) {
    return (sqrt(pow(a.x - b.x,2)+pow(a.y-b.y,2)) < (a.r + b.r)) ;
}

bool detect_collision_tramp(bounding_box_t player, bounding_box_tramp tramp) {
    return ((player.y - player.r<tramp.y-0.1) && 
        (player.x+player.r-0.1 >= tramp.x - tramp.l/2 && player.x-player.r+0.1<= tramp.x + tramp.l/2 )) ;
}
bool check_tramp(bounding_box_t player, bounding_box_tramp tramp) {
    return ((player.y - player.r<tramp.y) &&  
        (player.x +player.r >= tramp.x - tramp.l/2 && player.x-player.r<= tramp.x + tramp.l/2)) ;
}
bool detect_collision_porc(bounding_box_porc a, bounding_box_t b) {
    return (a.x < b.x  && a.x+2*a.l>b.x && a.h > b.y) ;
}

color_t colorpicker()
{
    int p = rand()%5;
    if(p==0)
        return COLOR_YELLOW;
    if(p==1)
        return COLOR_PINK;
    if(p==2)
        return COLOR_ORANGE;
    if(p==3)
        return COLOR_RED;
    if(p==4)
        return COLOR_CYAN;
}

int scorecalc(color_t color)
{
    if(color.r == COLOR_YELLOW.r && color.g == COLOR_YELLOW.g && color.b == COLOR_YELLOW.b)
        return 4;
    if(color.r == COLOR_PINK.r && color.g == COLOR_PINK.g && color.b == COLOR_PINK.b)
        return 8;
    if(color.r == COLOR_CYAN.r && color.g == COLOR_CYAN.g && color.b == COLOR_CYAN.b)
        return 12;
    if(color.r == COLOR_RED.r && color.g == COLOR_RED.g && color.b == COLOR_RED.b)
        return 15;
    if(color.r == COLOR_ORANGE.r && color.g == COLOR_ORANGE.g && color.b == COLOR_ORANGE.b)
        return 10;

}

void reset_screen() {
    float top    = screen_center_y + 8 / screen_zoom;
    float bottom = screen_center_y - 6 / screen_zoom;
    float left   = screen_center_x - 8/ screen_zoom;
    float right  = screen_center_x + 8 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
