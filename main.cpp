#include <windows.h>
#include <GL/glut.h>
#include<math.h>
#include<cstdio>
#include<fstream>
#include<iostream>
#include<bits/stdc++.h>//mahir 
#include <stdlib.h>
#include <GL/gl.h>
#include <cstdlib>
#include <ctime>
#include <string>

namespace HighScores{



int carHighScore = 0;
int spaceHighScore = 0;
int birdHighScore = 0;

// Function to render bitmap text
void renderBitmapString(float x, float y, float z, void *font, const char *string)
{
    const char *c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}
void keyboard(unsigned char key, int x, int y) {

        if (key == 'X' || key == 'x') {
            //go to Level2 game
            exit(0);
        }

    //glutPostRedisplay();
}

// Function to load a score from a file
int loadScoreFromFile(const std::string &filepath)
{
    int score = 0;
    std::ifstream file(filepath);
    if (file.is_open())
    {
        file >> score;
        file.close();
        std::cout << "Loaded score from " << filepath << ": " << score << std::endl;
    }
    else
    {
        std::cout << "Failed to open file: " << filepath << std::endl;
    }
    return score;
}

// Display function
void display()
{
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // High Score Title Header
    glColor3f(1.0f, 0.8f, 0.0f);
    renderBitmapString(-0.25f, 0.9f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "HIGH SCORES");

    // Subtitle
    glColor3f(0.8f, 0.8f, 0.8f);
    renderBitmapString(-0.35f, 0.82f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Computer Graphics Games");

    // Decorative separator
    glColor3f(0.5f, 0.5f, 0.7f);
    renderBitmapString(-0.85f, 0.75f, 0.0f, GLUT_BITMAP_HELVETICA_10, "================================================================================");

    // Game 1: Car Obstacle High Scores
    glColor3f(0.0f, 1.0f, 0.5f);
    renderBitmapString(-0.85f, 0.65f, 0.0f, GLUT_BITMAP_HELVETICA_18, "CAR OBSTACLE GAME");

    glColor3f(1.0f, 1.0f, 1.0f);
    std::string carScoreText = "Highest Score: " + std::to_string(carHighScore);
    renderBitmapString(-0.80f, 0.60f, 0.0f, GLUT_BITMAP_HELVETICA_12, carScoreText.c_str());

    // Game 2: Space Shooting High Scores
    glColor3f(0.0f, 1.0f, 0.5f);
    renderBitmapString(-0.85f, 0.29f, 0.0f, GLUT_BITMAP_HELVETICA_18, "SPACE SHOOTING GAME");

    glColor3f(1.0f, 1.0f, 1.0f);
    std::string spaceScoreText = "Highest Score: " + std::to_string(spaceHighScore);
    renderBitmapString(-0.80f, 0.24f, 0.0f, GLUT_BITMAP_HELVETICA_12, spaceScoreText.c_str());

    // Game 3: Bird Hunting High Scores
    glColor3f(0.0f, 1.0f, 0.5f);
    renderBitmapString(-0.85f, -0.07f, 0.0f, GLUT_BITMAP_HELVETICA_18, "BIRD HUNTING GAME");

    glColor3f(1.0f, 1.0f, 1.0f);
    std::string birdScoreText = "Highest Score: " + std::to_string(birdHighScore);
    renderBitmapString(-0.80f, -0.12f, 0.0f, GLUT_BITMAP_HELVETICA_12, birdScoreText.c_str());

    // Decorative separator
    glColor3f(0.5f, 0.5f, 0.7f);
    renderBitmapString(-0.85f, -0.43f, 0.0f, GLUT_BITMAP_HELVETICA_10, "================================================================================");

    // Navigation Info
    glColor3f(1.0f, 0.0f, 0.0f);
    renderBitmapString(-0.85f, -0.77f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Beat these scores and become the champion!");

    // Footer
    glColor3f(0.5f, 0.5f, 0.5f);
    renderBitmapString(-0.25f, -0.85f, 0.0f, GLUT_BITMAP_HELVETICA_10, "Press X to Exit");

    glFlush(); // Render now
}

// Initialization
void play()
{
    // Load scores from files
    carHighScore = loadScoreFromFile("C:\\Users\\LENOVO\\Documents\\car.txt");
    spaceHighScore = loadScoreFromFile("C:\\Users\\LENOVO\\Documents\\Airshoot.txt");
    birdHighScore = loadScoreFromFile("C:\\Users\\LENOVO\\Documents\\testfile.txt");

    glutInitWindowSize(900, 600);
    glutInitWindowPosition(50, 1);
    glutCreateWindow("High Scores");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}


}



namespace CarObstacle{



#define PI 3.14159265358979323846




/* Global variables */
GLfloat car_y_offset = 0.0f;
GLfloat speed = 0.05f;
bool game_over = false;
int Scoreer = 0;
bool sound_stopped = false;
int highScore = 0;
char high_score_buffer[50];

// Individual positions for each vehicle
GLfloat position_blue_i = 1.5f;
GLfloat position_blue_ii = 2.8f;
GLfloat position_green_iii = 1.6f;
GLfloat position_truck_i = 1.5f;
GLfloat position_truck_iv = 1.9f;
GLfloat position_red_ii =1.5f;
GLfloat position_yellow_ii =1.5f;
GLfloat position_red_iv =1.5f;
GLfloat position_yellow_iii =1.5f;


GLfloat position_upper_scene =0.0f;
void sound()
{
    PlaySound("b.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}
void stop_sound()
{
    PlaySound(NULL, 0, 0); // This stops any currently playing sound
}
void loadHighScore() {
    std::ifstream file("C:\\Users\\LENOVO\\Documents\\car.txt");

    if (file.is_open()) {
        file >> highScore;
        file.close();
        printf("High score loaded: %d\n", highScore);
    } else {
        highScore = 0;
        printf("No car.txt found, creating new file with score 0\n");

        std::ofstream newFile("C:\\Users\\LENOVO\\Documents\\car.txt");
        if (newFile.is_open()) {
            newFile << "0";
            newFile.close();
            printf("Created car.txt successfully\n");
        } else {
            printf("Error: Cannot create car.txt file\n");
        }
    }
}
void saveHighScore() {
    if (Scoreer > highScore) {
        std::ofstream file("C:\\Users\\LENOVO\\Documents\\car.txt");

        if (file.is_open()) {
            file << Scoreer;
            file.close();
            highScore = Scoreer; // update in memory too
            printf("New high score saved: %d\n", Scoreer);
        } else {
            printf("Error: Cannot write to car.txt\n");
        }
    }
}



bool checkCollision() {
    // F1 car bounding box

    float f1_x_min = -0.955f;
    float f1_x_max = -0.600f;
    float f1_y_min = 0.050f + car_y_offset;
    float f1_y_max = 0.260f + car_y_offset;

    // Red truck bounding box
    float truck_x_min = 0.410f + position_truck_iv;
    float truck_x_max = 0.900f + position_truck_iv;
    float truck_y_min = -0.560f;
    float truck_y_max = -0.350f;

        // Green truck bounding box
    float truck_x_min1 = 0.785f + position_truck_i;
    float truck_x_max1 = 1.275f + position_truck_i;
    float truck_y_min1 = 0.350f;
    float truck_y_max1 = 0.560f;

    // Blue pickup bounding box
    float blue_x_min = 0.140f + position_blue_i;
    float blue_x_max = 0.410f + position_blue_i;
    float blue_y_min = 0.365f;
    float blue_y_max = 0.545f;

        // Blue pickup 2 bounding box
    float blue2_x_min = 0.140f + position_blue_ii;
    float blue2_x_max = 0.410f + position_blue_ii;
    float blue2_y_min = 0.065f;
    float blue2_y_max = 0.245f;
    // Green car bounding box
    float green_x_min = -0.260f + position_green_iii;
    float green_x_max = 0.030f + position_green_iii;
    float green_y_min = -0.235f;
    float green_y_max = -0.055f;

    // Red 2 car bounding box
    float red2_x_min = 0.640f + position_red_ii;
    float red2_x_max = 0.930f + position_red_ii;
    float red2_y_min = 0.030f;
    float red2_y_max = 0.260f;
    // Yellow 2 car bounding box
    float yellow2_x_min = -0.760f + position_yellow_ii;
    float yellow2_x_max = -0.470f + position_yellow_ii;
    float yellow2_y_min = 0.030f;
    float yellow2_y_max = 0.260f;
// Red 4 car bounding box
    float red4_x_min = -0.760f + position_red_iv;
    float red4_x_max = -0.470f + position_red_iv;
    float red4_y_min = -0.570f;
    float red4_y_max = -0.340f;
    // Yellow 3 car bounding box
    float yellow3_x_min = 1.740f + position_yellow_iii;
    float yellow3_x_max = 2.030f + position_yellow_iii;
    float yellow3_y_min = -0.270f;
    float yellow3_y_max = -0.065f;







    bool collidesWithTruck = (f1_x_max >= truck_x_min && f1_x_min <= truck_x_max &&
                              f1_y_max >= truck_y_min && f1_y_min <= truck_y_max);
     bool collidesWithTruck1 = (f1_x_max >= truck_x_min1 && f1_x_min <= truck_x_max1 &&
                              f1_y_max >= truck_y_min1 && f1_y_min <= truck_y_max1);
    bool collidesWithBlue1 = (f1_x_max >= blue_x_min && f1_x_min <= blue_x_max &&
                             f1_y_max >= blue_y_min && f1_y_min <= blue_y_max);
    bool collidesWithBlue2 = (f1_x_max >= blue2_x_min && f1_x_min <= blue2_x_max &&
                             f1_y_max >= blue2_y_min && f1_y_min <= blue2_y_max);

    bool collidesWithGreen3 = (f1_x_max >= green_x_min && f1_x_min <= green_x_max &&
                              f1_y_max >= green_y_min && f1_y_min <= green_y_max);

    bool collidesWithRed2 = (f1_x_max >= red2_x_min && f1_x_min <= red2_x_max &&
                              f1_y_max >= red2_y_min && f1_y_min <= red2_y_max);
    bool collidesWithYellow2 = (f1_x_max >= yellow2_x_min && f1_x_min <= yellow2_x_max &&
                              f1_y_max >= yellow2_y_min && f1_y_min <= yellow2_y_max);
    bool collidesWithRed4 = (f1_x_max >= red4_x_min && f1_x_min <= red4_x_max &&
                              f1_y_max >= red4_y_min && f1_y_min <= red4_y_max);

    bool collidesWithyellow3 = (f1_x_max >= yellow3_x_min && f1_x_min <= yellow3_x_max &&
                              f1_y_max >= yellow3_y_min && f1_y_min <= yellow3_y_max);





    return collidesWithRed2 ||collidesWithRed4|| collidesWithYellow2  || collidesWithyellow3  ||
     collidesWithTruck1 || collidesWithTruck || collidesWithBlue1 || collidesWithBlue2 || collidesWithGreen3;
}

void update(int value) {
    if (!game_over) {
        // Move vehicles left
        position_blue_i -= speed / 3.0f;
        position_blue_ii -= speed / 3.0f;
        position_green_iii -= speed / 3.0f;
        position_truck_iv -= speed / 3.0f;
        position_truck_i -= speed / 3.0f;
        position_red_ii -= speed / 3.0f;
        position_yellow_ii -= speed / 3.0f;
        position_red_iv -= speed / 3.0f;
        position_yellow_iii -= speed / 3.0f;


        position_upper_scene -= speed / 8.0f;
        if (position_upper_scene < -1.2f) {
            position_upper_scene = 2.0f;
            }

        // Reset vehicles when off-screen
        if (position_blue_i < -3.0f) {
            position_blue_i = 1.5f;
            }
        if (position_blue_ii < -3.0f) {
            position_blue_ii = 1.5f;
            }
        if (position_green_iii < -3.0f) {
            position_green_iii = 1.5f;
            }
        if (position_truck_iv < -3.0f) {
            position_truck_iv = 1.5f;
             }
        if (position_truck_i < -3.0f) {
            position_truck_i = 1.5f;
             }

         if (position_red_ii < -3.0f) {
            position_red_ii = 1.5f;
             }

         if (position_yellow_ii < -3.0f) {
           position_yellow_ii = 1.5f;
             }
         if (position_red_iv < -3.0f) {
            position_red_iv = 1.5f;
             }
        if (position_yellow_iii < -3.0f) {
           position_yellow_iii = 1.5f;
             }




        if (checkCollision()) {
            game_over = true;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(16, update, 0); // ~60 FPS
}





void drawText(const char *text, float x, float y) {
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}




//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************





void drawF1Car() {
//The F1 Car
//x axis=155



glPushMatrix(); // Save the current matrix state
glTranslatef(0.0f, car_y_offset, 0.0f); // Apply y-offset to car only

//upper rear tier
glBegin(GL_QUADS);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.935f, 0.260f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.910f, 0.260f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.910f, 0.220f);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.935f, 0.220f);
glEnd();
glBegin(GL_QUADS);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.885f, 0.260f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.910f, 0.260f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.910f, 0.220f);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.885f, 0.220f);
glEnd();
//lower rear tier
glBegin(GL_QUADS);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.935f, 0.090f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.910f, 0.090f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.910f, 0.050f);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.935f, 0.050f);
glEnd();
glBegin(GL_QUADS);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.885f, 0.090f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.910f, 0.090f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.910f, 0.050f);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.885f, 0.050f);
glEnd();




//front upper tier
glBegin(GL_QUADS);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.695f, 0.260f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.670f, 0.260f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.670f, 0.220f);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.695f, 0.220f);
glEnd();
glBegin(GL_QUADS);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.645f, 0.260f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.670f, 0.260f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.670f, 0.220f);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.645f, 0.220f);
glEnd();
//front lower tier
glBegin(GL_QUADS);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.695f, 0.090f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.670f, 0.090f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.670f, 0.050f);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.695f, 0.050f);
glEnd();
glBegin(GL_QUADS);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.645f, 0.090f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.670f, 0.090f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.670f, 0.050f);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(-0.645f, 0.050f);
glEnd();



//rear big winglet
glColor3f(0.5f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.955f, 0.220f);
glVertex2f(-0.915f, 0.220f);
glVertex2f(-0.915f, 0.090f);
glVertex2f(-0.955f, 0.090f);
glEnd();
glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.945f, 0.220f);
glVertex2f(-0.915f, 0.220f);
glVertex2f(-0.915f, 0.090f);
glVertex2f(-0.945f, 0.090f);
glEnd();
//slim line on rear winglet
//upper
glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.965f, 0.220f);
glVertex2f(-0.915f, 0.220f);
glVertex2f(-0.915f, 0.215f);
glVertex2f(-0.965f, 0.215f);
glEnd();
//lower
glBegin(GL_QUADS);
glVertex2f(-0.965f, 0.095f);
glVertex2f(-0.915f, 0.095f);
glVertex2f(-0.915f, 0.090f);
glVertex2f(-0.965f, 0.090f);
glEnd();
//middle
glBegin(GL_QUADS);
glVertex2f(-0.965f, 0.157f);
glVertex2f(-0.915f, 0.157f);
glVertex2f(-0.915f, 0.153f);
glVertex2f(-0.965f, 0.153f);
glEnd();

//uper side pade,
glBegin(GL_QUADS);
glVertex2f(-0.905f, 0.210f);
glVertex2f(-0.880f, 0.210f);
glVertex2f(-0.880f, 0.200f);
glVertex2f(-0.905f, 0.200f);
glEnd();
glBegin(GL_QUADS);
glVertex2f(-0.890f, 0.235f);
glVertex2f(-0.870f, 0.235f);
glVertex2f(-0.870f, 0.200f);
glVertex2f(-0.890f, 0.200f);
glEnd();

glBegin(GL_TRIANGLES);
glVertex2f(-0.880f, 0.235f);
glVertex2f(-0.820f, 0.235f);
glVertex2f(-0.880f, 0.180f);
glEnd();


//lower side pade,
glBegin(GL_QUADS);
glVertex2f(-0.905f, 0.110f);
glVertex2f(-0.880f, 0.110f);
glVertex2f(-0.880f, 0.100f);
glVertex2f(-0.905f, 0.100f);
glEnd();
glBegin(GL_QUADS);
glVertex2f(-0.890f, 0.110f);
glVertex2f(-0.870f, 0.110f);
glVertex2f(-0.870f, 0.075f);
glVertex2f(-0.890f, 0.075f);
glEnd();

glBegin(GL_TRIANGLES);
glVertex2f(-0.880f, 0.075f);
glVertex2f(-0.820f, 0.075f);
glVertex2f(-0.880f, 0.130f);
glEnd();

//upper pad with white strip
glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_TRIANGLES);
glVertex2f(-0.850f, 0.242f);
glVertex2f(-0.800f, 0.242f);
glVertex2f(-0.850f, 0.180f);
glEnd();
//mirror
glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_TRIANGLES);
glVertex2f(-0.850f, 0.068f);
glVertex2f(-0.800f, 0.068f);
glVertex2f(-0.850f, 0.130f);
glEnd();







// upper bar

glBegin(GL_QUADS);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex2f(-0.770f, 0.220f);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex2f(-0.745f, 0.225f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.745f, 0.213f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.770f, 0.203f);
glEnd();

glBegin(GL_QUADS);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex2f(-0.745f, 0.225f);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex2f(-0.685f, 0.155f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.695f, 0.155f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.748f, 0.213f);
glEnd();

// Mirrored lower bar

glBegin(GL_QUADS);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.770f, 0.090f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.745f, 0.085f);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex2f(-0.745f, 0.097f);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex2f(-0.770f, 0.107f);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.745f, 0.085f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.685f, 0.155f);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex2f(-0.695f, 0.155f);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex2f(-0.748f, 0.097f);
glEnd();

//Rod of front tier (fat)
glBegin(GL_QUADS);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.670f, 0.220f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.658f, 0.220f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.658f, 0.090f);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.670f, 0.090f);
glEnd();

//Rod of front tier (slim)
glBegin(GL_QUADS);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.682f, 0.220f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.673f, 0.220f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.673f, 0.090f);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.682f, 0.090f);
glEnd();

//Triangluar upper Rod of front tier

glBegin(GL_QUADS);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.710f, 0.155f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.675f, 0.218f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.675f, 0.216f);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.690f, 0.155f);
glEnd();

//mirror

glBegin(GL_QUADS);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.710f, 0.155f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.675f, 0.092f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.675f, 0.094f);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.690f, 0.155f);
glEnd();

//Rod of rear tier (fat)
glBegin(GL_QUADS);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.915f, 0.220f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.905f, 0.220f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(-0.905f, 0.090f);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex2f(-0.915f, 0.090f);
glEnd();





//upper main frame
glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.900f, 0.170f);
glVertex2f(-0.800f, 0.245f);
glVertex2f(-0.800f, 0.190f);
glVertex2f(-0.900f, 0.145f);
glEnd();

glBegin(GL_QUADS);
glVertex2f(-0.800f, 0.245f);
glVertex2f(-0.785f, 0.245f);
glVertex2f(-0.785f, 0.190f);
glVertex2f(-0.800f, 0.190f);
glEnd();

glBegin(GL_QUADS);
glVertex2f(-0.785f, 0.245f);
glVertex2f(-0.740f, 0.160f);
glVertex2f(-0.765f, 0.150f);
glVertex2f(-0.795f, 0.200f);
glEnd();


//lower main frame
glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.900f, 0.160f);
glVertex2f(-0.800f, 0.130f);
glVertex2f(-0.800f, 0.065f);
glVertex2f(-0.900f, 0.140f);
glEnd();

glBegin(GL_QUADS);
glVertex2f(-0.800f, 0.130f);
glVertex2f(-0.785f, 0.130f);
glVertex2f(-0.785f, 0.065f);
glVertex2f(-0.800f, 0.065f);
glEnd();

glBegin(GL_QUADS);
glVertex2f(-0.795f, 0.110f);
glVertex2f(-0.765f, 0.160f);
glVertex2f(-0.740f, 0.150f);
glVertex2f(-0.785f, 0.065f);
glEnd();
//tail main frame
glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.915f, 0.170f);
glVertex2f(-0.900f, 0.170f);
glVertex2f(-0.900f, 0.140f);
glVertex2f(-0.915f, 0.140f);
glEnd();

//behind cocpit
//water drop


      float acx =-0.833f , acy = 0.155f;
    float aradius = 0.5f/8.0f;
    int anum_segments = 100;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.7f, 0.0f, 0.0f); // Light blue color for water drop
    glVertex2f(acx, acy); // Center

    for (int i = 0; i <= anum_segments; ++i) {
        float angle = 2.0f * 3.1415926f * float(i) / float(anum_segments);

        float a = cos(angle);

        // Create a water drop shape:
        float b = sin(angle);

        // Stretch the top, compress the bottom:
        b = b * (0.5f + 0.5f * cos(angle));

        glVertex2f(acx + a * aradius, acy + b * aradius);
    }

    glEnd();


    float bradius = 0.5f/13.0f;


    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.2f, 0.2f); // Light blue color for water drop
    glVertex2f(acx, acy); // Center

    for (int i = 0; i <= anum_segments; ++i) {
        float angle = 2.0f * 3.1415926f * float(i) / float(anum_segments);

        float a = cos(angle);

        // Create a water drop shape:
        float b = sin(angle);

        // Stretch the top, compress the bottom:
        b = b * (0.5f + 0.5f * cos(angle));

        glVertex2f(acx + a * bradius, acy + b * bradius);
    }

    glEnd();


glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.815f, 0.180f);
glVertex2f(-0.800f, 0.180f);
glVertex2f(-0.800f, 0.130f);
glVertex2f(-0.815f, 0.130f);
glEnd();



//front main frame
glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.765f, 0.185f);
glVertex2f(-0.605f, 0.165f);
glVertex2f(-0.605f, 0.145f);
glVertex2f(-0.765f, 0.125f);
glEnd();





//cocpit
glColor3f(1.0f, 0.8f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.800f, 0.175f);
glVertex2f(-0.750f, 0.175f);
glVertex2f(-0.750f, 0.135f);
glVertex2f(-0.800f, 0.135f);
glEnd();

GLfloat x=-0.783f; GLfloat y=0.155f; GLfloat radius =.015f;
	int triangleAmount = 100; //# of lines used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(int i = 0; i <= triangleAmount;i++) {
			glVertex2f( x + (radius * cos(i *  twicePi / triangleAmount)),
                        y + (radius * sin(i * twicePi / triangleAmount)) );
		}
	glEnd();


	//Front winglet

glBegin(GL_QUADS);
glVertex2f(-0.640f, 0.240f);
glVertex2f(-0.600f, 0.240f);
glVertex2f(-0.600f, 0.225f);
glVertex2f(-0.640f, 0.225f);
glEnd();
glBegin(GL_QUADS);
glVertex2f(-0.640f, 0.075f);
glVertex2f(-0.600f, 0.075f);
glVertex2f(-0.600f, 0.060f);
glVertex2f(-0.640f, 0.060f);
glEnd();
glBegin(GL_QUADS);
glVertex2f(-0.600f, 0.240f);
glVertex2f(-0.615f, 0.240f);
glVertex2f(-0.615f, 0.060f);
glVertex2f(-0.600f, 0.060f);
glEnd();

//padel of front winglet

glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.635f, 0.225f);
glVertex2f(-0.615f, 0.225f);
glVertex2f(-0.615f, 0.210f);
glVertex2f(-0.615f, 0.200f);
glEnd();
glBegin(GL_QUADS);
glVertex2f(-0.635f, 0.075f);
glVertex2f(-0.615f, 0.100f);
glVertex2f(-0.615f, 0.080f);
glVertex2f(-0.615f, 0.075f);
glEnd();
glBegin(GL_QUADS);
glVertex2f(-0.620f, 0.225f);
glVertex2f(-0.610f, 0.225f);
glVertex2f(-0.610f, 0.075f);
glVertex2f(-0.620f, 0.075f);
glEnd();

glPopMatrix();




}



//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************



void drawBluePickup() {

 glPushMatrix();
    glTranslatef(position_blue_i, 0.0f, 0.0f);


//upper mirror
float cenerX = 0.30f, cenerY = 0.55f;
float widh = 0.005f;          // Half-width of the magazine
float aius = 0.3f / 4.2;     // Curve radius (controls curvature)
int segmens = 100;

glColor3f(0.46f, 0.62f, 0.76f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segmens; ++i) {
    float t = float(i) / segmens;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = cenerX - cos(angle) * (aius + widh);
    float yOuter = cenerY + sin(angle) * (aius + widh);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = cenerX - cos(angle) * (aius - widh);
    float yInner = cenerY + sin(angle) * (aius - widh);
    glVertex2f(xInner, yInner);
}
glEnd();
// mirror lower
float cnerX = 0.30f, cnerY = 0.55f;
float wdh = 0.005f;          // Half-width of the magazine
float aus = 0.3f / 4.2;     // Curve radius (controls curvature)
int egmens = 100;

glColor3f(0.46f, 0.62f, 0.76f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= egmens; ++i) {
    float t = float(i) / egmens;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = cnerX - cos(angle) * (aus + wdh);
    float yOuter = 0.360f - sin(angle) * (aus + wdh);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = cnerX - cos(angle) * (aus - wdh);
    float yInner = 0.360f - sin(angle) * (aus - wdh);
    glVertex2f(xInner, yInner);
}
glEnd();

//front bumper
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.540f);
glVertex2f(0.140f, 0.540f);
glVertex2f(0.140f, 0.370f);
glVertex2f(0.150f, 0.370f);
glEnd();
//rear bumper

glColor3f(0.46f, 0.64f, 0.77f);
glBegin(GL_QUADS);
glVertex2f(0.410f, 0.540f);
glVertex2f(0.400f, 0.540f);
glVertex2f(0.400f, 0.370f);
glVertex2f(0.410f, 0.370f);
glEnd();
//upper bumper
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.140f, 0.545f);
glVertex2f(0.410f, 0.545f);
glVertex2f(0.410f, 0.535f);
glVertex2f(0.140f, 0.535f);
glEnd();
//lower
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.140f, 0.375f);
glVertex2f(0.410f, 0.375f);
glVertex2f(0.410f, 0.365f);
glVertex2f(0.140f, 0.365f);
glEnd();

//bonet

glColor3f(0.56f, 0.79f, 0.97f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.535f);
glVertex2f(0.230f, 0.535f);
glVertex2f(0.230f, 0.375f);
glVertex2f(0.150f, 0.375f);
glEnd();


//winsheild
float centerX = 0.500f, centerY = 0.455f;
float width = 0.05f;          // Half-width of the magazine
float adius = 0.3f / 1.2;     // Curve radius (controls curvature)
int segments = 100;

glColor3f(0.32f, 0.30f, 0.30f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments; ++i) {
    float t = float(i) / segments;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = centerX - cos(angle) * (adius + width);
    float yOuter = centerY + sin(angle) * (adius + width);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = centerX - cos(angle) * (adius - width);
    float yInner = centerY + sin(angle) * (adius - width);
    glVertex2f(xInner, yInner);
}
glEnd();


float centerXx = 0.485f, centerYy = 0.455f;
float widthx = 0.05f;          // Half-width of the magazine
float adis = 0.3f / 1.4;     // Curve radius (controls curvature)
int segmen = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segmen; ++i) {
    float t = float(i) / segmen;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = centerXx - cos(angle) * (adis + widthx);
    float yOuter = centerYy + sin(angle) * (adis + widthx);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = centerXx - cos(angle) * (adis - widthx);
    float yInner = centerYy + sin(angle) * (adis - widthx);
    glVertex2f(xInner, yInner);
}
glEnd();

//roof

float centerXxx = 0.475f, centeryYy = 0.455f;
float withx = 0.05f;          // Half-width of the magazine
float ads = 0.3f / 1.6;     // Curve radius (controls curvature)
int segen = 100;

glColor3f(0.56f, 0.79f, 0.97f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segen; ++i) {
    float t = float(i) / segen;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = centerXxx - cos(angle) * (ads + withx);
    float yOuter = centeryYy + sin(angle) * (ads + withx);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = centerXxx - cos(angle) * (ads - withx);
    float yInner = centeryYy + sin(angle) * (ads - withx);
    glVertex2f(xInner, yInner);
}
glEnd();
// square roof
glColor3f(0.56f, 0.79f, 0.97f);
glBegin(GL_QUADS);
glVertex2f(0.245f, 0.515f);
glVertex2f(0.310f, 0.515f);
glVertex2f(0.310f, 0.395f);
glVertex2f(0.245f, 0.395f);
glEnd();
//door shutter up
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.290f, 0.535f);
glVertex2f(0.310f, 0.535f);
glVertex2f(0.310f, 0.515f);
glVertex2f(0.290f, 0.515f);
glEnd();
//door shutter down

glBegin(GL_QUADS);
glVertex2f(0.290f, 0.375f);
glVertex2f(0.310f, 0.375f);
glVertex2f(0.310f, 0.395f);
glVertex2f(0.290f, 0.395f);
glEnd();


//product space

glColor3f(0.0f, 0.5f, 0.7f);
glBegin(GL_QUADS);
glVertex2f(0.310f, 0.535f);
glVertex2f(0.400f, 0.535f);
glVertex2f(0.400f, 0.375f);
glVertex2f(0.310f, 0.375f);
glEnd();

//rear upper tier
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.33f, 0.535f);
glVertex2f(0.37f, 0.535f);
glVertex2f(0.37f, 0.505f);
glVertex2f(0.33f, 0.505f);
glEnd();
glColor3f(0.38f, 0.47f, 0.54f);
glBegin(GL_QUADS);
glVertex2f(0.37f, 0.535f);
glVertex2f(0.38f, 0.535f);
glVertex2f(0.38f, 0.505f);
glVertex2f(0.37f, 0.505f);
glEnd();
//rear lower tier
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.33f, 0.405f);
glVertex2f(0.37f, 0.405f);
glVertex2f(0.37f, 0.375f);
glVertex2f(0.33f, 0.375f);
glEnd();
glColor3f(0.38f, 0.47f, 0.54f);
glBegin(GL_QUADS);
glVertex2f(0.37f, 0.405f);
glVertex2f(0.38f, 0.405f);
glVertex2f(0.38f, 0.375f);
glVertex2f(0.37f, 0.375f);
glEnd();

glColor3f(0.46f, 0.62f, 0.76f);
//windsheld holder upper
glBegin(GL_QUADS);
glVertex2f(0.222f, 0.535f);
glVertex2f(0.252f, 0.515f);
glVertex2f(0.242f, 0.515f);
glVertex2f(0.21f, 0.535f);
glEnd();
//windsheld holder lower
glBegin(GL_QUADS);
glVertex2f(0.222f, 0.375f);
glVertex2f(0.252f, 0.395f);
glVertex2f(0.242f, 0.395f);
glVertex2f(0.210f, 0.375f);
glEnd();

//headlight upper
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.530f);
glVertex2f(0.140f, 0.530f);
glVertex2f(0.140f, 0.485f);
glVertex2f(0.150f, 0.485f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.530f);
glVertex2f(0.140f, 0.530f);
glVertex2f(0.140f, 0.52f);
glVertex2f(0.150f, 0.52f);
glEnd();
//headlight lower
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.380f);
glVertex2f(0.140f, 0.380f);
glVertex2f(0.140f, 0.425f);
glVertex2f(0.150f, 0.425f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.380f);
glVertex2f(0.140f, 0.380f);
glVertex2f(0.140f, 0.390f);
glVertex2f(0.150f, 0.390f);

//tail light upper
glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.410f, 0.520f);
glVertex2f(0.400f, 0.520f);
glVertex2f(0.400f, 0.480f);
glVertex2f(0.410f, 0.480f);
glEnd();
//tail light lower
glBegin(GL_QUADS);
glVertex2f(0.410f, 0.390f);
glVertex2f(0.400f, 0.390f);
glVertex2f(0.400f, 0.430f);
glVertex2f(0.410f, 0.430f);
glEnd();
//window upper
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.222f, 0.535f);
glVertex2f(0.292f, 0.535f);
glVertex2f(0.292f, 0.525f);
glVertex2f(0.240f, 0.525f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(0.240f, 0.525f);
glVertex2f(0.292f, 0.525f);
glVertex2f(0.292f, 0.515f);
glVertex2f(0.258f, 0.515f);
glEnd();

//lower
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.222f, 0.375f);
glVertex2f(0.292f, 0.375f);
glVertex2f(0.292f, 0.385f);
glVertex2f(0.240f, 0.385f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(0.240f, 0.385f);
glVertex2f(0.292f, 0.385f);
glVertex2f(0.292f, 0.395f);
glVertex2f(0.258f, 0.395f);
glEnd();

//square on trunk  upper
glColor3f(0.6f, 0.79f, 0.94f);
glBegin(GL_QUADS);
glVertex2f(0.310f, 0.535f);
glVertex2f(0.400f, 0.535f);
glVertex2f(0.400f, 0.53f);
glVertex2f(0.310f, 0.53f);
glEnd();
//lower
glBegin(GL_QUADS);
glVertex2f(0.310f, 0.375f);
glVertex2f(0.400f, 0.375f);
glVertex2f(0.400f, 0.380f);
glVertex2f(0.310f, 0.380f);
glEnd();
glBegin(GL_QUADS);
glVertex2f(0.396f, 0.535f);
glVertex2f(0.400f, 0.535f);
glVertex2f(0.400f, 0.380f);
glVertex2f(0.396f, 0.380f);
glEnd();

  glPopMatrix();
}


//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************

void drawGreenCar_i() {
glPushMatrix();
glTranslatef(position_green_iii, 0.0f, 0.0f);




// upper mirror
float centerX1 = 0.30f - 0.4f, centerY1 = 0.55f - 0.6f; // centerX1 = -0.10f, centerY1 = -0.05f
float width1 = 0.005f;          // Half-width of the magazine
float radius1 = 0.3f / 4.2;     // Curve radius (controls curvature)
int segments1 = 100;

glColor3f(0.1f, 0.52f, 0.12f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments1; ++i) {
    float t = float(i) / segments1;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.10f - cos(angle) * (radius1 + width1);
    float yOuter = -0.05f + sin(angle) * (radius1 + width1);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.10f - cos(angle) * (radius1 - width1);
    float yInner = -0.05f + sin(angle) * (radius1 - width1);
    glVertex2f(xInner, yInner);
}
glEnd();

// mirror lower
float centerX2 = 0.30f - 0.4f, centerY2 = 0.55f - 0.6f; // centerX2 = -0.10f, centerY2 = -0.05f
float width2 = 0.005f;          // Half-width of the magazine
float radius2 = 0.3f / 4.2;     // Curve radius (controls curvature)
int segments2 = 100;

glColor3f(0.1f, 0.52f, 0.12f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments2; ++i) {
    float t = float(i) / segments2;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.10f - cos(angle) * (radius2 + width2);
    float yOuter = -0.24f - sin(angle) * (radius2 + width2); // 0.360f - 0.6f = -0.24f
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.10f - cos(angle) * (radius2 - width2);
    float yInner = -0.24f - sin(angle) * (radius2 - width2);
    glVertex2f(xInner, yInner);
}
glEnd();

// front bumper
glColor3f(0.1f, 0.52f, 0.12f);
glBegin(GL_QUADS);
glVertex2f(-0.250f, -0.060f);
glVertex2f(-0.260f, -0.060f);
glVertex2f(-0.260f, -0.230f);
glVertex2f(-0.250f, -0.230f);
glEnd();

// rear bumper
glColor3f(0.1f, 0.52f, 0.12f);
glBegin(GL_QUADS);
glVertex2f(0.030f, -0.060f);
glVertex2f(0.020f, -0.060f);
glVertex2f(0.020f, -0.230f);
glVertex2f(0.030f, -0.230f);
glEnd();

// upper bumper
glColor3f(0.1f, 0.52f, 0.12f);
glBegin(GL_QUADS);
glVertex2f(-0.260f, -0.055f);
glVertex2f(0.030f, -0.055f);
glVertex2f(0.030f, -0.065f);
glVertex2f(-0.260f, -0.065f);
glEnd();

// lower bumper
glColor3f(0.1f, 0.52f, 0.12f);
glBegin(GL_QUADS);
glVertex2f(-0.260f, -0.225f);
glVertex2f(0.030f, -0.225f);
glVertex2f(0.030f, -0.235f);
glVertex2f(-0.260f, -0.235f);
glEnd();

// bonnet
glColor3f(0.1f, 0.72f, 0.12f);
glBegin(GL_QUADS);
glVertex2f(-0.250f, -0.065f);
glVertex2f(-0.170f, -0.065f);
glVertex2f(-0.170f, -0.225f);
glVertex2f(-0.250f, -0.225f);
glEnd();

// trunk
glBegin(GL_QUADS);
glVertex2f(0.020f, -0.065f);
glVertex2f(-0.025f, -0.065f);
glVertex2f(-0.025f, -0.225f);
glVertex2f(0.020f, -0.225f);
glEnd();

// windshield
float centerX3 = 0.500f - 0.4f, centerY3 = 0.455f - 0.6f; // centerX3 = 0.100f, centerY3 = -0.145f
float width3 = 0.05f;          // Half-width of the magazine
float radius3 = 0.3f / 1.2;    // Curve radius (controls curvature)
int segments3 = 100;

glColor3f(0.32f, 0.30f, 0.30f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments3; ++i) {
    float t = float(i) / segments3;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 0.100f - cos(angle) * (radius3 + width3);
    float yOuter = -0.145f + sin(angle) * (radius3 + width3);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 0.100f - cos(angle) * (radius3 - width3);
    float yInner = -0.145f + sin(angle) * (radius3 - width3);
    glVertex2f(xInner, yInner);
}
glEnd();

// windshield inner left
float centerX4 = 0.485f - 0.4f, centerY4 = 0.455f - 0.6f; // centerX4 = 0.085f, centerY4 = -0.145f
float width4 = 0.05f;          // Half-width of the magazine
float radius4 = 0.3f / 1.4;    // Curve radius (controls curvature)
int segments4 = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments4; ++i) {
    float t = float(i) / segments4;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 0.085f - cos(angle) * (radius4 + width4);
    float yOuter = -0.145f + sin(angle) * (radius4 + width4);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 0.085f - cos(angle) * (radius4 - width4);
    float yInner = -0.145f + sin(angle) * (radius4 - width4);
    glVertex2f(xInner, yInner);
}
glEnd();

// right
float centerX44 = -0.285f, centerY44 = -0.145f;
float width44 = 0.05f;          // Half-width of the magazine
float radius44 = 0.3f / 1.35f;   // Curve radius (controls curvature)
int segments44 = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments44; ++i) {
    float t = float(i) / segments44;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.285f + cos(angle) * (radius44 + width44);
    float yOuter = -0.145f + sin(angle) * (radius44 + width44);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.285f + cos(angle) * (radius44 - width44);
    float yInner = -0.145f + sin(angle) * (radius44 - width44);
    glVertex2f(xInner, yInner);
}
glEnd();

// roof left
float centerX5 = 0.475f - 0.4f, centerY5 = 0.455f - 0.6f; // centerX5 = 0.075f, centerY5 = -0.145f
float width5 = 0.05f;          // Half-width of the magazine
float radius5 = 0.3f / 1.6;    // Curve radius (controls curvature)
int segments5 = 100;

glColor3f(0.1f, 0.72f, 0.12f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments5; ++i) {
    float t = float(i) / segments5;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 0.075f - cos(angle) * (radius5 + width5);
    float yOuter = -0.145f + sin(angle) * (radius5 + width5);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 0.075f - cos(angle) * (radius5 - width5);
    float yInner = -0.145f + sin(angle) * (radius5 - width5);
    glVertex2f(xInner, yInner);
}
glEnd();

// right
// roof
float centerX55 = -0.275f, centerY55 = -0.145f;
float width55 = 0.05f;          // Half-width of the magazine
float radius55 = 0.3f / 1.6f;   // Curve radius (controls curvature)
int segments55 = 100;

glColor3f(0.1f, 0.72f, 0.12f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments55; ++i) {
    float t = float(i) / segments55;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.275f + cos(angle) * (radius55 + width55);
    float yOuter = -0.145f + sin(angle) * (radius55 + width55);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.275f + cos(angle) * (radius55 - width55);
    float yInner = -0.145f + sin(angle) * (radius55 - width55);
    glVertex2f(xInner, yInner);
}
glEnd();

// square roof
glColor3f(0.1f, 0.72f, 0.12f);
glBegin(GL_QUADS);
glVertex2f(-0.155f, -0.085f);
glVertex2f(-0.050f, -0.085f);
glVertex2f(-0.050f, -0.205f);
glVertex2f(-0.155f, -0.205f);
glEnd();

// headlight upper
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(-0.250f, -0.070f);
glVertex2f(-0.260f, -0.070f);
glVertex2f(-0.260f, -0.115f);
glVertex2f(-0.250f, -0.115f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(-0.250f, -0.070f);
glVertex2f(-0.260f, -0.070f);
glVertex2f(-0.260f, -0.080f);
glVertex2f(-0.250f, -0.080f);
glEnd();

// headlight lower
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(-0.250f, -0.220f);
glVertex2f(-0.260f, -0.220f);
glVertex2f(-0.260f, -0.175f);
glVertex2f(-0.250f, -0.175f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(-0.250f, -0.220f);
glVertex2f(-0.260f, -0.220f);
glVertex2f(-0.260f, -0.210f);
glVertex2f(-0.250f, -0.210f);
glEnd();

// tail light upper
glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.030f, -0.080f);
glVertex2f(0.020f, -0.080f);
glVertex2f(0.020f, -0.120f);
glVertex2f(0.030f, -0.120f);
glEnd();

// tail light lower
glBegin(GL_QUADS);
glVertex2f(0.030f, -0.210f);
glVertex2f(0.020f, -0.210f);
glVertex2f(0.020f, -0.170f);
glVertex2f(0.030f, -0.170f);
glEnd();

// window upper left side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f, -0.065f);
glVertex2f(-0.105f, -0.065f);
glVertex2f(-0.105f, -0.075f);
glVertex2f(-0.160f, -0.075f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.160f, -0.075f);
glVertex2f(-0.105f, -0.075f);
glVertex2f(-0.105f, -0.085f);
glVertex2f(-0.142f, -0.085f);
glEnd();

// window upper right side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f, -0.065f);
glVertex2f(-0.095f, -0.065f);
glVertex2f(-0.095f, -0.075f);
glVertex2f(-0.040f, -0.075f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.040f, -0.075f);
glVertex2f(-0.095f, -0.075f);
glVertex2f(-0.095f, -0.085f);
glVertex2f(-0.058f, -0.085f);
glEnd();

// window lower
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f, -0.225f);
glVertex2f(-0.105f, -0.225f);
glVertex2f(-0.105f, -0.215f);
glVertex2f(-0.160f, -0.215f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.160f, -0.215f);
glVertex2f(-0.105f, -0.215f);
glVertex2f(-0.105f, -0.205f);
glVertex2f(-0.142f, -0.205f);
glEnd();

// right side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f, -0.225f);
glVertex2f(-0.095f, -0.225f);
glVertex2f(-0.095f, -0.215f);
glVertex2f(-0.040f, -0.215f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.040f, -0.215f);
glVertex2f(-0.095f, -0.215f);
glVertex2f(-0.095f, -0.205f);
glVertex2f(-0.058f, -0.205f);
glEnd();

// door shutter up
glColor3f(0.1f, 0.52f, 0.12f);
glBegin(GL_QUADS);
glVertex2f(-0.105f, -0.065f);
glVertex2f(-0.095f, -0.065f);
glVertex2f(-0.095f, -0.085f);
glVertex2f(-0.105f, -0.085f);
glEnd();

// door shutter down
glBegin(GL_QUADS);
glVertex2f(-0.105f, -0.225f);
glVertex2f(-0.095f, -0.225f);
glVertex2f(-0.095f, -0.205f);
glVertex2f(-0.105f, -0.205f);
glEnd();

// windshield holder upper left
glColor3f(0.1f, 0.52f, 0.12f);
glBegin(GL_QUADS);
glVertex2f(-0.178f, -0.065f);
glVertex2f(-0.148f, -0.085f);
glVertex2f(-0.158f, -0.085f);
glVertex2f(-0.190f, -0.065f);
glEnd();

// right
// windshield holder upper
glColor3f(0.1f, 0.52f, 0.12f);
glBegin(GL_QUADS);
glVertex2f(-0.022f, -0.065f);
glVertex2f(-0.052f, -0.085f);
glVertex2f(-0.042f, -0.085f);
glVertex2f(-0.010f, -0.065f);
glEnd();

// windshield holder lower
glBegin(GL_QUADS);
glVertex2f(-0.178f, -0.225f);
glVertex2f(-0.148f, -0.205f);
glVertex2f(-0.158f, -0.205f);
glVertex2f(-0.190f, -0.225f);
glEnd();

// right
// windshield holder upper
glColor3f(0.1f, 0.52f, 0.12f);
glBegin(GL_QUADS);
glVertex2f(-0.022f, -0.225f);
glVertex2f(-0.052f, -0.205f);
glVertex2f(-0.042f, -0.205f);
glVertex2f(-0.010f, -0.225f);
glEnd();



glPopMatrix();

}

//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************



void drawRedTruck() {

 glPushMatrix();
  glTranslatef(position_truck_iv, 0.0f, 0.0f);


//trailer
glColor3f(1.0f, 1.0f, 1.0f);
glBegin(GL_QUADS);
glVertex2f(0.550f, -0.350f);
glVertex2f(0.900f, -0.350f);
glVertex2f(0.900f, -0.560f);
glVertex2f(0.550f, -0.560f);
glEnd();
glColor3f(0.4f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.550f, -0.350f);
glVertex2f(0.555f, -0.350f);
glVertex2f(0.555f, -0.560f);
glVertex2f(0.550f, -0.560f);
glEnd();
glBegin(GL_QUADS);
glVertex2f(0.895f, -0.350f);
glVertex2f(0.900f, -0.350f);
glVertex2f(0.900f, -0.560f);
glVertex2f(0.895f, -0.560f);
glEnd();
glBegin(GL_QUADS);
glVertex2f(0.550f, -0.350f);
glVertex2f(0.900f, -0.350f);
glVertex2f(0.900f, -0.355f);
glVertex2f(0.550f, -0.355f);
glEnd();
glBegin(GL_QUADS);
glVertex2f(0.550f, -0.555f);
glVertex2f(0.900f, -0.555f);
glVertex2f(0.900f, -0.560f);
glVertex2f(0.550f, -0.560f);
glEnd();


//connector from up
glColor3f(0.3f, 0.3f, 0.3f);
glBegin(GL_QUADS);
glVertex2f(0.525f, -0.385f);
glVertex2f(0.550f, -0.385f);
glVertex2f(0.550f, -0.395f);
glVertex2f(0.525f, -0.395f);
glEnd();
glColor3f(0.83f, 0.79f, 0.79f);
glBegin(GL_QUADS);
glVertex2f(0.525f, -0.405f);
glVertex2f(0.550f, -0.405f);
glVertex2f(0.550f, -0.395f);
glVertex2f(0.525f, -0.395f);
glEnd();
glColor3f(0.68f, 0.66f, 0.66f);
glBegin(GL_QUADS);
glVertex2f(0.525f, -0.405f);
glVertex2f(0.550f, -0.405f);
glVertex2f(0.550f, -0.435f);
glVertex2f(0.525f, -0.435f);
glEnd();
glColor3f(0.83f, 0.79f, 0.79f);
glBegin(GL_QUADS);
glVertex2f(0.525f, -0.445f);
glVertex2f(0.550f, -0.445f);
glVertex2f(0.550f, -0.435f);
glVertex2f(0.525f, -0.435f);
glEnd();
//middle
glColor3f(0.42f, 0.4f, 0.4f);
glBegin(GL_QUADS);
glVertex2f(0.525f, -0.445f);
glVertex2f(0.550f, -0.445f);
glVertex2f(0.550f, -0.465f);
glVertex2f(0.525f, -0.465f);
glEnd();

//from bottom
glColor3f(0.3f, 0.3f, 0.3f);
glBegin(GL_QUADS);
glVertex2f(0.525f, -0.525f);
glVertex2f(0.550f, -0.525f);
glVertex2f(0.550f, -0.515f);
glVertex2f(0.525f, -0.515f);
glEnd();
glColor3f(0.83f, 0.79f, 0.79f);
glBegin(GL_QUADS);
glVertex2f(0.525f, -0.505f);
glVertex2f(0.550f, -0.505f);
glVertex2f(0.550f, -0.515f);
glVertex2f(0.525f, -0.515f);
glEnd();
glColor3f(0.68f, 0.66f, 0.66f);
glBegin(GL_QUADS);
glVertex2f(0.525f, -0.505f);
glVertex2f(0.550f, -0.505f);
glVertex2f(0.550f, -0.475f);
glVertex2f(0.525f, -0.475f);
glEnd();
glColor3f(0.83f, 0.79f, 0.79f);
glBegin(GL_QUADS);
glVertex2f(0.525f, -0.465f);
glVertex2f(0.550f, -0.465f);
glVertex2f(0.550f, -0.475f);
glVertex2f(0.525f, -0.475f);
glEnd();

//WHOLE SEating area
glColor3f(0.4f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.530f, -0.370f);
glVertex2f(0.410f, -0.370f);
glVertex2f(0.410f, -0.540f);
glVertex2f(0.530f, -0.540f);
glEnd();
//1st black line
glBegin(GL_QUADS);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(0.420f, -0.370f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(0.410f, -0.370f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(0.410f, -0.540f);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(0.420f, -0.540f);
glEnd();
//2nd black line
glBegin(GL_QUADS);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(0.427f, -0.385f);
glColor3f(0.8f, 0.8f, 0.8f);
glVertex2f(0.440f, -0.385f);
glColor3f(0.8f, 0.8f, 0.8f);
glVertex2f(0.440f, -0.525f);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(0.427f, -0.525f);
glEnd();
//upper line
glBegin(GL_QUADS);
glColor3f(0.5f, 0.5f, 0.5f);
glVertex2f(0.435f, -0.374f);
glColor3f(0.5f, 0.5f, 0.5f);
glVertex2f(0.480f, -0.374f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(0.480f, -0.382f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(0.435f, -0.382f);
glEnd();
//lower line

glBegin(GL_QUADS);
glColor3f(0.5f, 0.5f, 0.5f);
glVertex2f(0.435f, -0.536f);
glColor3f(0.5f, 0.5f, 0.5f);
glVertex2f(0.480f, -0.536f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(0.480f, -0.528f);
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(0.435f, -0.528f);
glEnd();
//main cocpit
glBegin(GL_QUADS);
glColor3f(0.4f, 0.4f, 0.4f);
glVertex2f(0.465f, -0.415f);
glColor3f(0.8f, 0.8f, 0.8f);
glVertex2f(0.51f, -0.415f);
glColor3f(0.8f, 0.8f, 0.8f);
glVertex2f(0.51f, -0.495f);
glColor3f(0.4f, 0.4f, 0.4f);
glVertex2f(0.465f, -0.495f);
glEnd();

//yellow dots
glBegin(GL_QUADS);
glColor3f(1.0f, 0.7f, 0.0f);
glVertex2f(0.445f, -0.408f);
glVertex2f(0.453f, -0.408f);
glVertex2f(0.453f, -0.422f);
glVertex2f(0.445f, -0.422f);
glEnd();

glBegin(GL_QUADS);
glVertex2f(0.445f, -0.434f);
glVertex2f(0.453f, -0.434f);
glVertex2f(0.453f, -0.45f);
glVertex2f(0.445f, -0.45f);
glEnd();


glBegin(GL_QUADS);
glVertex2f(0.445f, -0.476f);
glVertex2f(0.453f, -0.476f);
glVertex2f(0.453f, -0.46f);
glVertex2f(0.445f, -0.46f);
glEnd();


glColor3f(1.0f, 0.7f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.445f, -0.502f);
glVertex2f(0.453f, -0.502f);
glVertex2f(0.453f, -0.488f);
glVertex2f(0.445f, -0.488f);
glEnd();


glColor3f(0.4f, 0.0f, 0.0f);
glBegin(GL_TRIANGLES);
glVertex2f(0.550f, -0.350f);
glVertex2f(0.510f, -0.470f);
glVertex2f(0.510f, -0.400f);
glEnd();


glBegin(GL_TRIANGLES);
glVertex2f(0.550f, -0.560f);
glVertex2f(0.510f, -0.440f);
glVertex2f(0.510f, -0.510f);
glEnd();



glPopMatrix();
}
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************





void drawGreenTruck() {

 glPushMatrix();
  glTranslatef(position_truck_i, 0.0f, 0.0f);



// Truck of 1st lane

// Trailer (dark green)
// Dark Green Truck centered at (1.1f, 0.455f)

// Trailer
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(1.100f - 0.175f + 1.0f, 0.455f + 0.105f); // (0.925 + 1.0, 0.560) = (1.925, 0.560)
glVertex2f(1.100f + 0.175f + 1.0f, 0.455f + 0.105f); // (1.275 + 1.0, 0.560) = (2.275, 0.560)
glVertex2f(1.275f + 1.0f, 0.455f - 0.105f);          // (1.275 + 1.0, 0.350) = (2.275, 0.350)
glVertex2f(0.925f + 1.0f, 0.350f);                   // (0.925 + 1.0, 0.350) = (1.925, 0.350)
glEnd();

// Trailer Borders
glColor3f(0.1f, 0.2f, 0.1f); // darker shade
// Left border
glBegin(GL_QUADS);
glVertex2f(0.925f + 1.0f, 0.560f); // (1.925, 0.560)
glVertex2f(0.930f + 1.0f, 0.560f); // (1.930, 0.560)
glVertex2f(0.930f + 1.0f, 0.350f); // (1.930, 0.350)
glVertex2f(0.925f + 1.0f, 0.350f); // (1.925, 0.350)
glEnd();
// Right border
glBegin(GL_QUADS);
glVertex2f(1.270f + 1.0f, 0.560f); // (2.270, 0.560)
glVertex2f(1.275f + 1.0f, 0.560f); // (2.275, 0.560)
glVertex2f(1.275f + 1.0f, 0.350f); // (2.275, 0.350)
glVertex2f(1.270f + 1.0f, 0.350f); // (2.270, 0.350)
glEnd();
// Top border
glBegin(GL_QUADS);
glVertex2f(0.925f + 1.0f, 0.560f); // (1.925, 0.560)
glVertex2f(1.275f + 1.0f, 0.560f); // (2.275, 0.560)
glVertex2f(1.275f + 1.0f, 0.555f); // (2.275, 0.555)
glVertex2f(0.925f + 1.0f, 0.555f); // (1.925, 0.555)
glEnd();
// Bottom border
glBegin(GL_QUADS);
glVertex2f(0.925f + 1.0f, 0.355f); // (1.925, 0.355)
glVertex2f(1.275f + 1.0f, 0.355f); // (2.275, 0.355)
glVertex2f(1.275f + 1.0f, 0.350f); // (2.275, 0.350)
glVertex2f(0.925f + 1.0f, 0.350f); // (1.925, 0.350)
glEnd();

// Connector from Top
glColor3f(0.3f, 0.3f, 0.3f);
glBegin(GL_QUADS);
glVertex2f(0.900f + 1.0f, 0.525f); // (1.900, 0.525)
glVertex2f(0.925f + 1.0f, 0.525f); // (1.925, 0.525)
glVertex2f(0.925f + 1.0f, 0.515f); // (1.925, 0.515)
glVertex2f(0.900f + 1.0f, 0.515f); // (1.900, 0.515)
glEnd();
glColor3f(0.83f, 0.79f, 0.79f);
glBegin(GL_QUADS);
glVertex2f(0.900f + 1.0f, 0.505f); // (1.900, 0.505)
glVertex2f(0.925f + 1.0f, 0.505f); // (1.925, 0.505)
glVertex2f(0.925f + 1.0f, 0.515f); // (1.925, 0.515)
glVertex2f(0.900f + 1.0f, 0.515f); // (1.900, 0.515)
glEnd();
glColor3f(0.68f, 0.66f, 0.66f);
glBegin(GL_QUADS);
glVertex2f(0.900f + 1.0f, 0.505f); // (1.900, 0.505)
glVertex2f(0.925f + 1.0f, 0.505f); // (1.925, 0.505)
glVertex2f(0.925f + 1.0f, 0.475f); // (1.925, 0.475)
glVertex2f(0.900f + 1.0f, 0.475f); // (1.900, 0.475)
glEnd();
glColor3f(0.83f, 0.79f, 0.79f);
glBegin(GL_QUADS);
glVertex2f(0.900f + 1.0f, 0.465f); // (1.900, 0.465)
glVertex2f(0.925f + 1.0f, 0.465f); // (1.925, 0.465)
glVertex2f(0.925f + 1.0f, 0.475f); // (1.925, 0.475)
glVertex2f(0.900f + 1.0f, 0.475f); // (1.900, 0.475)
glEnd();
// Middle
glColor3f(0.42f, 0.4f, 0.4f);
glBegin(GL_QUADS);
glVertex2f(0.900f + 1.0f, 0.465f); // (1.900, 0.465)
glVertex2f(0.925f + 1.0f, 0.465f); // (1.925, 0.465)
glVertex2f(0.925f + 1.0f, 0.445f); // (1.925, 0.445)
glVertex2f(0.900f + 1.0f, 0.445f); // (1.900, 0.445)
glEnd();

// Connector from Bottom
glColor3f(0.3f, 0.3f, 0.3f);
glBegin(GL_QUADS);
glVertex2f(0.900f + 1.0f, 0.385f); // (1.900, 0.385)
glVertex2f(0.925f + 1.0f, 0.385f); // (1.925, 0.385)
glVertex2f(0.925f + 1.0f, 0.395f); // (1.925, 0.395)
glVertex2f(0.900f + 1.0f, 0.395f); // (1.900, 0.395)
glEnd();
glColor3f(0.83f, 0.79f, 0.79f);
glBegin(GL_QUADS);
glVertex2f(0.900f + 1.0f, 0.405f); // (1.900, 0.405)
glVertex2f(0.925f + 1.0f, 0.405f); // (1.925, 0.405)
glVertex2f(0.925f + 1.0f, 0.395f); // (1.925, 0.395)
glVertex2f(0.900f + 1.0f, 0.395f); // (1.900, 0.395)
glEnd();
glColor3f(0.68f, 0.66f, 0.66f);
glBegin(GL_QUADS);
glVertex2f(0.900f + 1.0f, 0.405f); // (1.900, 0.405)
glVertex2f(0.925f + 1.0f, 0.405f); // (1.925, 0.405)
glVertex2f(0.925f + 1.0f, 0.435f); // (1.925, 0.435)
glVertex2f(0.900f + 1.0f, 0.435f); // (1.900, 0.435)
glEnd();
glColor3f(0.83f, 0.79f, 0.79f);
glBegin(GL_QUADS);
glVertex2f(0.900f + 1.0f, 0.445f); // (1.900, 0.445)
glVertex2f(0.925f + 1.0f, 0.445f); // (1.925, 0.445)
glVertex2f(0.925f + 1.0f, 0.435f); // (1.925, 0.435)
glVertex2f(0.900f + 1.0f, 0.435f); // (1.900, 0.435)
glEnd();

// Seating Area
glColor3f(0.0f, 0.2f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.905f + 1.0f, 0.540f); // (1.905, 0.540)
glVertex2f(0.785f + 1.0f, 0.540f); // (1.785, 0.540)
glVertex2f(0.785f + 1.0f, 0.370f); // (1.785, 0.370)
glVertex2f(0.905f + 1.0f, 0.370f); // (1.905, 0.370)
glEnd();

// First Black Line
glColor3f(0.1f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(0.795f + 1.0f, 0.540f); // (1.795, 0.540)
glVertex2f(0.785f + 1.0f, 0.540f); // (1.785, 0.540)
glVertex2f(0.785f + 1.0f, 0.370f); // (1.785, 0.370)
glVertex2f(0.795f + 1.0f, 0.370f); // (1.795, 0.370)
glEnd();

// Second Black Line
glBegin(GL_QUADS);
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(0.802f + 1.0f, 0.525f); // (1.802, 0.525)
glColor3f(0.8f, 0.8f, 0.8f);
glVertex2f(0.815f + 1.0f, 0.525f); // (1.815, 0.525)
glColor3f(0.8f, 0.8f, 0.8f);
glVertex2f(0.815f + 1.0f, 0.385f); // (1.815, 0.385)
glColor3f(0.1f, 0.1f, 0.1f);
glVertex2f(0.802f + 1.0f, 0.385f); // (1.802, 0.385)
glEnd();

// Upper Line
glBegin(GL_QUADS);
glColor3f(0.5f, 0.5f, 0.5f);
glVertex2f(0.810f + 1.0f, 0.536f); // (1.810, 0.536)
glVertex2f(0.855f + 1.0f, 0.536f); // (1.855, 0.536)
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(0.855f + 1.0f, 0.528f); // (1.855, 0.528)
glVertex2f(0.810f + 1.0f, 0.528f); // (1.810, 0.528)
glEnd();

// Lower Line
glBegin(GL_QUADS);
glColor3f(0.5f, 0.5f, 0.5f);
glVertex2f(0.810f + 1.0f, 0.374f); // (1.810, 0.374)
glVertex2f(0.855f + 1.0f, 0.374f); // (1.855, 0.374)
glColor3f(0.3f, 0.3f, 0.3f);
glVertex2f(0.855f + 1.0f, 0.382f); // (1.855, 0.382)
glVertex2f(0.810f + 1.0f, 0.382f); // (1.810, 0.382)
glEnd();

// Main Cockpit
glBegin(GL_QUADS);
glColor3f(0.4f, 0.4f, 0.4f);
glVertex2f(0.840f + 1.0f, 0.495f); // (1.840, 0.495)
glColor3f(0.8f, 0.8f, 0.8f);
glVertex2f(0.885f + 1.0f, 0.495f); // (1.885, 0.495)
glVertex2f(0.885f + 1.0f, 0.415f); // (1.885, 0.415)
glColor3f(0.4f, 0.4f, 0.4f);
glVertex2f(0.840f + 1.0f, 0.415f); // (1.840, 0.415)
glEnd();

// Yellow Dots
glBegin(GL_QUADS);
glColor3f(1.0f, 0.7f, 0.0f);
glVertex2f(0.820f + 1.0f, 0.502f); // (1.820, 0.502)
glVertex2f(0.828f + 1.0f, 0.502f); // (1.828, 0.502)
glVertex2f(0.828f + 1.0f, 0.488f); // (1.828, 0.488)
glVertex2f(0.820f + 1.0f, 0.488f); // (1.820, 0.488)
glEnd();

glBegin(GL_QUADS);
glVertex2f(0.820f + 1.0f, 0.476f); // (1.820, 0.476)
glVertex2f(0.828f + 1.0f, 0.476f); // (1.828, 0.476)
glVertex2f(0.828f + 1.0f, 0.460f); // (1.828, 0.460)
glVertex2f(0.820f + 1.0f, 0.460f); // (1.820, 0.460)
glEnd();

glBegin(GL_QUADS);
glVertex2f(0.820f + 1.0f, 0.434f); // (1.820, 0.434)
glVertex2f(0.828f + 1.0f, 0.434f); // (1.828, 0.434)
glVertex2f(0.828f + 1.0f, 0.450f); // (1.828, 0.450)
glVertex2f(0.820f + 1.0f, 0.450f); // (1.820, 0.450)
glEnd();

glBegin(GL_QUADS);
glVertex2f(0.820f + 1.0f, 0.408f); // (1.820, 0.408)
glVertex2f(0.828f + 1.0f, 0.408f); // (1.828, 0.408)
glVertex2f(0.828f + 1.0f, 0.422f); // (1.828, 0.422)
glVertex2f(0.820f + 1.0f, 0.422f); // (1.820, 0.422)
glEnd();

// Front Triangles
glColor3f(0.0f, 0.2f, 0.0f);
glBegin(GL_TRIANGLES);
glVertex2f(0.925f + 1.0f, 0.560f); // (1.925, 0.560)
glVertex2f(0.885f + 1.0f, 0.440f); // (1.885, 0.440)
glVertex2f(0.885f + 1.0f, 0.510f); // (1.885, 0.510)
glEnd();

glBegin(GL_TRIANGLES);
glVertex2f(0.925f + 1.0f, 0.350f); // (1.925, 0.350)
glVertex2f(0.885f + 1.0f, 0.470f); // (1.885, 0.470)
glVertex2f(0.885f + 1.0f, 0.400f); // (1.885, 0.400)
glEnd();







glPopMatrix();
}


















//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************


void drawRedCar_ii() {
glPushMatrix();
glTranslatef(position_red_ii, 0.0f, 0.0f);



// red car of 2nd lane




float centerX1we = 0.8f, centerY1we = 0.24f; // New center
float width1we = 0.005f;          // Half-width of the magazine
float radius1we = 0.3f / 4.2;     // Curve radius (controls curvature)
int segments1we = 100;

glColor3f(0.5f, 0.1f, 0.1f);  // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments1we; ++i) {
    float t = float(i) / segments1we;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 0.8f - cos(angle) * (radius1we + width1we);
    float yOuter = 0.24f + sin(angle) * (radius1we + width1we);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 0.8f - cos(angle) * (radius1we - width1we);
    float yInner = 0.24f + sin(angle) * (radius1we - width1we);
    glVertex2f(xInner, yInner);
}
glEnd();

// Mirror lower
float centerX2we = 0.8f, centerY2we = 0.24f; // New center
float width2we = 0.005f;          // Half-width of the magazine
float radius2we = 0.3f / 4.2;     // Curve radius (controls curvature)
int segments2we = 100;

glColor3f(0.5f, 0.1f, 0.1f);  // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments2we; ++i) {
    float t = float(i) / segments2we;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 0.8f - cos(angle) * (radius2we + width2we);
    float yOuter = 0.24f - 0.19f - sin(angle) * (radius2we + width2we); // -0.24f + 0.29f - 0.05f = 0.05f
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 0.8f - cos(angle) * (radius2we - width2we);
    float yInner = 0.24f - 0.19f - sin(angle) * (radius2we - width2we);
    glVertex2f(xInner, yInner);
}
glEnd();

// Front bumper
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f, -0.060f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.060f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.230f + 0.29f);
glVertex2f(-0.250f + 0.9f, -0.230f + 0.29f);
glEnd();

// Rear bumper
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f, -0.060f + 0.29f);
glVertex2f(0.020f + 0.9f, -0.060f + 0.29f);
glVertex2f(0.020f + 0.9f, -0.230f + 0.29f);
glVertex2f(0.030f + 0.9f, -0.230f + 0.29f);
glEnd();

// Upper bumper
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.260f + 0.9f, -0.055f + 0.29f);
glVertex2f(0.030f + 0.9f, -0.055f + 0.29f);
glVertex2f(0.030f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.065f + 0.29f);
glEnd();

// Lower bumper
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.260f + 0.9f, -0.225f + 0.29f);
glVertex2f(0.030f + 0.9f, -0.225f + 0.29f);
glVertex2f(0.030f + 0.9f, -0.235f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.235f + 0.29f);
glEnd();

// Bonnet
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.170f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.170f + 0.9f, -0.225f + 0.29f);
glVertex2f(-0.250f + 0.9f, -0.225f + 0.29f);
glEnd();

// Trunk
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(0.020f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.025f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.025f + 0.9f, -0.225f + 0.29f);
glVertex2f(0.020f + 0.9f, -0.225f + 0.29f);
glEnd();

// Windshield
float centerX3we = 0.8f + 0.2f, centerY3we = 0.24f - 0.05f; // centerX3 = 0.100f + 0.9f, centerY3 = -0.145f + 0.29f
float width3we = 0.05f;          // Half-width of the magazine
float radius3we = 0.3f / 1.2;    // Curve radius (controls curvature)
int segments3we = 100;

glColor3f(0.32f, 0.30f, 0.30f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments3we; ++i) {
    float t = float(i) / segments3we;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 1.0f - cos(angle) * (radius3we + width3we);
    float yOuter = 0.145f + sin(angle) * (radius3we + width3we);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 1.0f - cos(angle) * (radius3we - width3we);
    float yInner = 0.145f + sin(angle) * (radius3we - width3we);
    glVertex2f(xInner, yInner);
}
glEnd();

// Windshield inner left
float centerX4we = 0.8f + 0.185f, centerY4we = 0.24f - 0.05f; // centerX4 = 0.085f + 0.9f, centerY4 = -0.145f + 0.29f
float width4we = 0.05f;          // Half-width of the magazine
float radius4we = 0.3f / 1.4;    // Curve radius (controls curvature)
int segments4we = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments4we; ++i) {
    float t = float(i) / segments4we;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 0.985f - cos(angle) * (radius4we + width4we);
    float yOuter = 0.145f + sin(angle) * (radius4we + width4we);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 0.985f - cos(angle) * (radius4we - width4we);
    float yInner = 0.145f + sin(angle) * (radius4we - width4we);
    glVertex2f(xInner, yInner);
}
glEnd();

// Windshield inner right
float centerX44we = 0.8f - 0.485f, centerY44we = 0.24f - 0.05f; // centerX44 = -0.285f + 0.9f, centerY44 = -0.145f + 0.29f
float width44we = 0.05f;          // Half-width of the magazine
float radius44we = 0.3f / 1.35f;   // Curve radius (controls curvature)
int segments44we = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments44we; ++i) {
    float t = float(i) / segments44we;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 0.61f + cos(angle) * (radius44we + width44we);
    float yOuter = 0.145f + sin(angle) * (radius44we + width44we);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 0.61f + cos(angle) * (radius44we - width44we);
    float yInner = 0.145f + sin(angle) * (radius44we - width44we);
    glVertex2f(xInner, yInner);
}
glEnd();

// Roof left
float centerX5we = 0.8f + 0.175f, centerY5we = 0.24f - 0.05f; // centerX5 = 0.075f + 0.9f, centerY5 = -0.145f + 0.29f
float width5we = 0.05f;          // Half-width of the magazine
float radius5we = 0.3f / 1.6;    // Curve radius (controls curvature)
int segments5we = 100;

glColor3f(0.5f, 0.1f, 0.1f);  // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments5we; ++i) {
    float t = float(i) / segments5we;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 0.975f - cos(angle) * (radius5we + width5we);
    float yOuter = 0.145f + sin(angle) * (radius5we + width5we);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 0.975f - cos(angle) * (radius5we - width5we);
    float yInner = 0.145f + sin(angle) * (radius5we - width5we);
    glVertex2f(xInner, yInner);
}
glEnd();

// Roof right
float centerX55we = 0.8f - 0.475f, centerY55we = 0.24f - 0.05f; // centerX55 = -0.275f + 0.9f, centerY55 = -0.145f + 0.29f
float width55we = 0.05f;          // Half-width of the magazine
float radius55we = 0.3f / 1.6;   // Curve radius (controls curvature)
int segments55we = 100;

glColor3f(0.5f, 0.1f, 0.1f);  // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments55we; ++i) {
    float t = float(i) / segments55we;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 0.62f + cos(angle) * (radius55we + width55we);
    float yOuter = 0.145f + sin(angle) * (radius55we + width55we);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 0.62f + cos(angle) * (radius55we - width55we);
    float yInner = 0.145f + sin(angle) * (radius55we - width55we);
    glVertex2f(xInner, yInner);
}
glEnd();

// Square roof
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.155f + 0.9f, -0.085f + 0.29f);
glVertex2f(-0.050f + 0.9f, -0.085f + 0.29f);
glVertex2f(-0.050f + 0.9f, -0.205f + 0.29f);
glVertex2f(-0.155f + 0.9f, -0.205f + 0.29f);
glEnd();

// Headlight upper
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f, -0.070f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.070f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.115f + 0.29f);
glVertex2f(-0.250f + 0.9f, -0.115f + 0.29f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f, -0.070f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.070f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.080f + 0.29f);
glVertex2f(-0.250f + 0.9f, -0.080f + 0.29f);
glEnd();

// Headlight lower
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f, -0.220f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.220f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.175f + 0.29f);
glVertex2f(-0.250f + 0.9f, -0.175f + 0.29f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f, -0.220f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.220f + 0.29f);
glVertex2f(-0.260f + 0.9f, -0.210f + 0.29f);
glVertex2f(-0.250f + 0.9f, -0.210f + 0.29f);
glEnd();

// Tail light upper
glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f, -0.080f + 0.29f);
glVertex2f(0.020f + 0.9f, -0.080f + 0.29f);
glVertex2f(0.020f + 0.9f, -0.120f + 0.29f);
glVertex2f(0.030f + 0.9f, -0.120f + 0.29f);
glEnd();

// Tail light lower
glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f, -0.210f + 0.29f);
glVertex2f(0.020f + 0.9f, -0.210f + 0.29f);
glVertex2f(0.020f + 0.9f, -0.170f + 0.29f);
glVertex2f(0.030f + 0.9f, -0.170f + 0.29f);
glEnd();

// Window upper left side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.105f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.105f + 0.9f, -0.075f + 0.29f);
glVertex2f(-0.160f + 0.9f, -0.075f + 0.29f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.160f + 0.9f, -0.075f + 0.29f);
glVertex2f(-0.105f + 0.9f, -0.075f + 0.29f);
glVertex2f(-0.105f + 0.9f, -0.085f + 0.29f);
glVertex2f(-0.142f + 0.9f, -0.085f + 0.29f);
glEnd();

// Window upper right side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.075f + 0.29f);
glVertex2f(-0.040f + 0.9f, -0.075f + 0.29f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.040f + 0.9f, -0.075f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.075f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.085f + 0.29f);
glVertex2f(-0.058f + 0.9f, -0.085f + 0.29f);
glEnd();

// Window lower
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f, -0.225f + 0.29f);
glVertex2f(-0.105f + 0.9f, -0.225f + 0.29f);
glVertex2f(-0.105f + 0.9f, -0.215f + 0.29f);
glVertex2f(-0.160f + 0.9f, -0.215f + 0.29f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.160f + 0.9f, -0.215f + 0.29f);
glVertex2f(-0.105f + 0.9f, -0.215f + 0.29f);
glVertex2f(-0.105f + 0.9f, -0.205f + 0.29f);
glVertex2f(-0.142f + 0.9f, -0.205f + 0.29f);
glEnd();

// Window right side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f, -0.225f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.225f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.215f + 0.29f);
glVertex2f(-0.040f + 0.9f, -0.215f + 0.29f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.040f + 0.9f, -0.215f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.215f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.205f + 0.29f);
glVertex2f(-0.058f + 0.9f, -0.205f + 0.29f);
glEnd();

// Door shutter up
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.105f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.085f + 0.29f);
glVertex2f(-0.105f + 0.9f, -0.085f + 0.29f);
glEnd();

// Door shutter down
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.105f + 0.9f, -0.225f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.225f + 0.29f);
glVertex2f(-0.095f + 0.9f, -0.205f + 0.29f);
glVertex2f(-0.105f + 0.9f, -0.205f + 0.29f);
glEnd();

// Windshield holder upper left
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.148f + 0.9f, -0.085f + 0.29f);
glVertex2f(-0.158f + 0.9f, -0.085f + 0.29f);
glVertex2f(-0.190f + 0.9f, -0.065f + 0.29f);
glEnd();

// Windshield holder upper right
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f, -0.065f + 0.29f);
glVertex2f(-0.052f + 0.9f, -0.085f + 0.29f);
glVertex2f(-0.042f + 0.9f, -0.085f + 0.29f);
glVertex2f(-0.010f + 0.9f, -0.065f + 0.29f);
glEnd();

// Windshield holder lower left
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f, -0.225f + 0.29f);
glVertex2f(-0.148f + 0.9f, -0.205f + 0.29f);
glVertex2f(-0.158f + 0.9f, -0.205f + 0.29f);
glVertex2f(-0.190f + 0.9f, -0.225f + 0.29f);
glEnd();

// Windshield holder lower right
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f, -0.225f + 0.29f);
glVertex2f(-0.052f + 0.9f, -0.205f + 0.29f);
glVertex2f(-0.042f + 0.9f, -0.205f + 0.29f);
glVertex2f(-0.010f + 0.9f, -0.225f + 0.29f);
glEnd();






glPopMatrix();
}





//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************








void drawYellowCar_ii() {
glPushMatrix();
glTranslatef(position_yellow_ii, 0.0f, 0.0f);





// yellow car of 2nd lane

//y 240 center

float centerX1ef = 0.8f - 1.4f, centerY1ef = 0.24f; // New center: (0.8f - 1.4f, 0.24f) = (-0.6f, 0.24f)
float width1ef = 0.005f;          // Half-width of the magazine
float radius1ef = 0.3f / 4.2;     // Curve radius (controls curvature)
int segments1ef = 100;

glColor3f(0.9f, 0.9f, 0.0f);  // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments1ef; ++i) {
    float t = float(i) / segments1ef;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.6f - cos(angle) * (radius1ef + width1ef);
    float yOuter = 0.24f + sin(angle) * (radius1ef + width1ef);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.6f - cos(angle) * (radius1ef - width1ef);
    float yInner = 0.24f + sin(angle) * (radius1ef - width1ef);
    glVertex2f(xInner, yInner);
}
glEnd();

// Mirror lower
float centerX2ef = -0.6f, centerY2ef = 0.24f; // New center
float width2ef = 0.005f;          // Half-width of the magazine
float radius2ef = 0.3f / 4.2;     // Curve radius (controls curvature)
int segments2ef = 100;

glColor3f(0.9f, 0.9f, 0.0f);   // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments2ef; ++i) {
    float t = float(i) / segments2ef;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.6f - cos(angle) * (radius2ef + width2ef);
    float yOuter = 0.24f - 0.19f - sin(angle) * (radius2ef + width2ef); // 0.05f
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.6f - cos(angle) * (radius2ef - width2ef);
    float yInner = 0.24f - 0.19f - sin(angle) * (radius2ef - width2ef);
    glVertex2f(xInner, yInner);
}
glEnd();

// Front bumper
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.060f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.060f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.230f + 0.29f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.230f + 0.29f);
glEnd();

// Rear bumper

glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f - 1.4f, -0.060f + 0.29f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.060f + 0.29f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.230f + 0.29f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.230f + 0.29f);
glEnd();

// Upper bumper

glBegin(GL_QUADS);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.055f + 0.29f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.055f + 0.29f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.065f + 0.29f);
glEnd();

// Lower bumper

glBegin(GL_QUADS);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.235f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.235f + 0.29f);
glEnd();

// Bonnet

glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.170f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.170f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.225f + 0.29f);
glEnd();

// Trunk

glBegin(GL_QUADS);
glVertex2f(0.020f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.025f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.025f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.225f + 0.29f);
glEnd();

// Windshield
float centerX3ef = -0.6f + 0.2f, centerY3ef = 0.24f - 0.05f; // centerX3 = 1.0f - 1.4f, centerY3 = 0.145f
float width3ef = 0.05f;          // Half-width of the magazine
float radius3ef = 0.3f / 1.2;    // Curve radius (controls curvature)
int segments3ef = 100;

glColor3f(0.32f, 0.30f, 0.30f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments3ef; ++i) {
    float t = float(i) / segments3ef;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.4f - cos(angle) * (radius3ef + width3ef);
    float yOuter = 0.145f + sin(angle) * (radius3ef + width3ef);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.4f - cos(angle) * (radius3ef - width3ef);
    float yInner = 0.145f + sin(angle) * (radius3ef - width3ef);
    glVertex2f(xInner, yInner);
}
glEnd();

// Windshield inner left
float centerX4ef = -0.6f + 0.185f, centerY4ef = 0.24f - 0.05f; // centerX4 = 0.985f - 1.4f, centerY4 = 0.145f
float width4ef = 0.05f;          // Half-width of the magazine
float radius4ef = 0.3f / 1.4;    // Curve radius (controls curvature)
int segments4ef = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments4ef; ++i) {
    float t = float(i) / segments4ef;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.415f - cos(angle) * (radius4ef + width4ef);
    float yOuter = 0.145f + sin(angle) * (radius4ef + width4ef);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.415f - cos(angle) * (radius4ef - width4ef);
    float yInner = 0.145f + sin(angle) * (radius4ef - width4ef);
    glVertex2f(xInner, yInner);
}
glEnd();

// Windshield inner right
float centerX44ef = -0.6f - 0.485f, centerY44ef = 0.24f - 0.05f; // centerX44 = 0.61f - 1.4f, centerY44 = 0.145f
float width44ef = 0.05f;          // Half-width of the magazine
float radius44ef = 0.3f / 1.35f;   // Curve radius (controls curvature)
int segments44ef = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments44ef; ++i) {
    float t = float(i) / segments44ef;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.79f + cos(angle) * (radius44ef + width44ef);
    float yOuter = 0.145f + sin(angle) * (radius44ef + width44ef);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.79f + cos(angle) * (radius44ef - width44ef);
    float yInner = 0.145f + sin(angle) * (radius44ef - width44ef);
    glVertex2f(xInner, yInner);
}
glEnd();

// Roof left
float centerX5ef = -0.6f + 0.175f, centerY5ef = 0.24f - 0.05f; // centerX5 = 0.975f - 1.4f, centerY5 = 0.145f
float width5ef = 0.05f;          // Half-width of the magazine
float radius5ef = 0.3f / 1.6;    // Curve radius (controls curvature)
int segments5ef = 100;

glColor3f(0.9f, 0.9f, 0.0f);  // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments5ef; ++i) {
    float t = float(i) / segments5ef;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.425f - cos(angle) * (radius5ef + width5ef);
    float yOuter = 0.145f + sin(angle) * (radius5ef + width5ef);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.425f - cos(angle) * (radius5ef - width5ef);
    float yInner = 0.145f + sin(angle) * (radius5ef - width5ef);
    glVertex2f(xInner, yInner);
}
glEnd();

// Roof right
float centerX55ef = -0.6f - 0.475f, centerY55ef = 0.24f - 0.05f; // centerX55 = 0.62f - 1.4f, centerY55 = 0.145f
float width55ef = 0.05f;          // Half-width of the magazine
float radius55ef = 0.3f / 1.6;   // Curve radius (controls curvature)
int segments55ef = 100;

glColor3f(0.9f, 0.9f, 0.0f); // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments55ef; ++i) {
    float t = float(i) / segments55ef;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.78f + cos(angle) * (radius55ef + width55ef);
    float yOuter = 0.145f + sin(angle) * (radius55ef + width55ef);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.78f + cos(angle) * (radius55ef - width55ef);
    float yInner = 0.145f + sin(angle) * (radius55ef - width55ef);
    glVertex2f(xInner, yInner);
}
glEnd();

// Square roof
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.155f + 0.9f - 1.4f, -0.085f + 0.29f);
glVertex2f(-0.050f + 0.9f - 1.4f, -0.085f + 0.29f);
glVertex2f(-0.050f + 0.9f - 1.4f, -0.205f + 0.29f);
glVertex2f(-0.155f + 0.9f - 1.4f, -0.205f + 0.29f);
glEnd();

// Headlight upper
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.070f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.070f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.115f + 0.29f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.115f + 0.29f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.070f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.070f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.080f + 0.29f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.080f + 0.29f);
glEnd();

// Headlight lower
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.220f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.220f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.175f + 0.29f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.175f + 0.29f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.220f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.220f + 0.29f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.210f + 0.29f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.210f + 0.29f);
glEnd();

// Tail light upper
glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f - 1.4f, -0.080f + 0.29f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.080f + 0.29f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.120f + 0.29f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.120f + 0.29f);
glEnd();

// Tail light lower
glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f - 1.4f, -0.210f + 0.29f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.210f + 0.29f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.170f + 0.29f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.170f + 0.29f);
glEnd();

// Window upper left side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.075f + 0.29f);
glVertex2f(-0.160f + 0.9f - 1.4f, -0.075f + 0.29f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.160f + 0.9f - 1.4f, -0.075f + 0.29f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.075f + 0.29f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.085f + 0.29f);
glVertex2f(-0.142f + 0.9f - 1.4f, -0.085f + 0.29f);
glEnd();

// Window upper right side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.075f + 0.29f);
glVertex2f(-0.040f + 0.9f - 1.4f, -0.075f + 0.29f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.040f + 0.9f - 1.4f, -0.075f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.075f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.085f + 0.29f);
glVertex2f(-0.058f + 0.9f - 1.4f, -0.085f + 0.29f);
glEnd();

// Window lower
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.215f + 0.29f);
glVertex2f(-0.160f + 0.9f - 1.4f, -0.215f + 0.29f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.160f + 0.9f - 1.4f, -0.215f + 0.29f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.215f + 0.29f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.205f + 0.29f);
glVertex2f(-0.142f + 0.9f - 1.4f, -0.205f + 0.29f);
glEnd();

// Window right side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.215f + 0.29f);
glVertex2f(-0.040f + 0.9f - 1.4f, -0.215f + 0.29f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.040f + 0.9f - 1.4f, -0.215f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.215f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.205f + 0.29f);
glVertex2f(-0.058f + 0.9f - 1.4f, -0.205f + 0.29f);
glEnd();

// Door shutter up
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.085f + 0.29f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.085f + 0.29f);
glEnd();

// Door shutter down

glBegin(GL_QUADS);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.205f + 0.29f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.205f + 0.29f);
glEnd();

// Windshield holder upper left

glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.148f + 0.9f - 1.4f, -0.085f + 0.29f);
glVertex2f(-0.158f + 0.9f - 1.4f, -0.085f + 0.29f);
glVertex2f(-0.190f + 0.9f - 1.4f, -0.065f + 0.29f);
glEnd();

// Windshield holder upper right

glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f, -0.065f + 0.29f);
glVertex2f(-0.052f + 0.9f - 1.4f, -0.085f + 0.29f);
glVertex2f(-0.042f + 0.9f - 1.4f, -0.085f + 0.29f);
glVertex2f(-0.010f + 0.9f - 1.4f, -0.065f + 0.29f);
glEnd();

// Windshield holder lower left

glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(-0.148f + 0.9f - 1.4f, -0.205f + 0.29f);
glVertex2f(-0.158f + 0.9f - 1.4f, -0.205f + 0.29f);
glVertex2f(-0.190f + 0.9f - 1.4f, -0.225f + 0.29f);
glEnd();

// Windshield holder lower right

glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f, -0.225f + 0.29f);
glVertex2f(-0.052f + 0.9f - 1.4f, -0.205f + 0.29f);
glVertex2f(-0.042f + 0.9f - 1.4f, -0.205f + 0.29f);
glVertex2f(-0.010f + 0.9f - 1.4f, -0.225f + 0.29f);
glEnd();

glPopMatrix();
}








//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************








void drawRedCar_iv() {
glPushMatrix();
glTranslatef(position_red_iv, 0.0f, 0.0f);






// red car of 4th lane









float centerX1ek = -0.6f, centerY1ek = 0.24f - 0.6f; // New center: (-0.6f, 0.24f - 0.6f) = (-0.6f, -0.36f)
float width1ek = 0.005f;          // Half-width of the magazine
float radius1ek = 0.3f / 4.2;     // Curve radius (controls curvature)
int segments1ek = 100;

glColor3f(0.5f, 0.1f, 0.1f);  // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments1ek; ++i) {
    float t = float(i) / segments1ek;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.6f - cos(angle) * (radius1ek + width1ek);
    float yOuter = -0.36f + sin(angle) * (radius1ek + width1ek);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.6f - cos(angle) * (radius1ek - width1ek);
    float yInner = -0.36f + sin(angle) * (radius1ek - width1ek);
    glVertex2f(xInner, yInner);
}
glEnd();

// Mirror lower
float centerX2ek = -0.6f, centerY2ek = -0.36f; // New center
float width2ek = 0.005f;          // Half-width of the magazine
float radius2ek = 0.3f / 4.2;     // Curve radius (controls curvature)
int segments2ek = 100;

glColor3f(0.5f, 0.1f, 0.1f);  // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments2ek; ++i) {
    float t = float(i) / segments2ek;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.6f - cos(angle) * (radius2ek + width2ek);
    float yOuter = -0.36f - 0.19f - sin(angle) * (radius2ek + width2ek); // 0.05f - 0.6f = -0.55f
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.6f - cos(angle) * (radius2ek - width2ek);
    float yInner = -0.36f - 0.19f - sin(angle) * (radius2ek - width2ek);
    glVertex2f(xInner, yInner);
}
glEnd();

// Front bumper
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.060f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.060f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.230f + 0.29f - 0.6f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.230f + 0.29f - 0.6f);
glEnd();

// Rear bumper
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f - 1.4f, -0.060f + 0.29f - 0.6f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.060f + 0.29f - 0.6f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.230f + 0.29f - 0.6f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.230f + 0.29f - 0.6f);
glEnd();

// Upper bumper
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.055f + 0.29f - 0.6f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.055f + 0.29f - 0.6f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glEnd();

// Lower bumper
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.235f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.235f + 0.29f - 0.6f);
glEnd();

// Bonnet
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.170f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.170f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glEnd();

// Trunk
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(0.020f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.025f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.025f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glEnd();

// Windshield
float centerX3ek = -0.4f, centerY3ek = 0.145f - 0.6f; // centerY3 = 0.145f - 0.6f = -0.455f
float width3ek = 0.05f;          // Half-width of the magazine
float radius3ek = 0.3f / 1.2;    // Curve radius (controls curvature)
int segments3ek = 100;

glColor3f(0.32f, 0.30f, 0.30f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments3ek; ++i) {
    float t = float(i) / segments3ek;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.4f - cos(angle) * (radius3ek + width3ek);
    float yOuter = -0.455f + sin(angle) * (radius3ek + width3ek);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.4f - cos(angle) * (radius3ek - width3ek);
    float yInner = -0.455f + sin(angle) * (radius3ek - width3ek);
    glVertex2f(xInner, yInner);
}
glEnd();

// Windshield inner left
float centerX4ek = -0.415f, centerY4ek = 0.145f - 0.6f; // centerY4 = 0.145f - 0.6f = -0.455f
float width4ek = 0.05f;          // Half-width of the magazine
float radius4ek = 0.3f / 1.4;    // Curve radius (controls curvature)
int segments4ek = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments4ek; ++i) {
    float t = float(i) / segments4ek;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.415f - cos(angle) * (radius4ek + width4ek);
    float yOuter = -0.455f + sin(angle) * (radius4ek + width4ek);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.415f - cos(angle) * (radius4ek - width4ek);
    float yInner = -0.455f + sin(angle) * (radius4ek - width4ek);
    glVertex2f(xInner, yInner);
}
glEnd();

// Windshield inner right
float centerX44ek = -0.79f, centerY44ek = 0.145f - 0.6f; // centerY44 = 0.145f - 0.6f = -0.455f
float width44ek = 0.05f;          // Half-width of the magazine
float radius44ek = 0.3f / 1.35f;   // Curve radius (controls curvature)
int segments44ek = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments44ek; ++i) {
    float t = float(i) / segments44ek;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.79f + cos(angle) * (radius44ek + width44ek);
    float yOuter = -0.455f + sin(angle) * (radius44ek + width44ek);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.79f + cos(angle) * (radius44ek - width44ek);
    float yInner = -0.455f + sin(angle) * (radius44ek - width44ek);
    glVertex2f(xInner, yInner);
}
glEnd();

// Roof left
float centerX5ek = -0.425f, centerY5ek = 0.145f - 0.6f; // centerY5 = 0.145f - 0.6f = -0.455f
float width5ek = 0.05f;          // Half-width of the magazine
float radius5ek = 0.3f / 1.6;    // Curve radius (controls curvature)
int segments5ek = 100;

glColor3f(0.5f, 0.1f, 0.1f);  // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments5ek; ++i) {
    float t = float(i) / segments5ek;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.425f - cos(angle) * (radius5ek + width5ek);
    float yOuter = -0.455f + sin(angle) * (radius5ek + width5ek);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.425f - cos(angle) * (radius5ek - width5ek);
    float yInner = -0.455f + sin(angle) * (radius5ek - width5ek);
    glVertex2f(xInner, yInner);
}
glEnd();

// Roof right
float centerX55ek = -0.78f, centerY55ek = 0.145f - 0.6f; // centerY55 = 0.145f - 0.6f = -0.455f
float width55ek = 0.05f;          // Half-width of the magazine
float radius55ek = 0.3f / 1.6;   // Curve radius (controls curvature)
int segments55ek = 100;

glColor3f(0.5f, 0.1f, 0.1f);  // Dark red for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments55ek; ++i) {
    float t = float(i) / segments55ek;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = -0.78f + cos(angle) * (radius55ek + width55ek);
    float yOuter = -0.455f + sin(angle) * (radius55ek + width55ek);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = -0.78f + cos(angle) * (radius55ek - width55ek);
    float yInner = -0.455f + sin(angle) * (radius55ek - width55ek);
    glVertex2f(xInner, yInner);
}
glEnd();

// Square roof
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.155f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glVertex2f(-0.050f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glVertex2f(-0.050f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glVertex2f(-0.155f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glEnd();

// Headlight upper
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.070f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.070f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.115f + 0.29f - 0.6f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.115f + 0.29f - 0.6f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.070f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.070f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.080f + 0.29f - 0.6f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.080f + 0.29f - 0.6f);
glEnd();

// Headlight lower
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.220f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.220f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.175f + 0.29f - 0.6f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.175f + 0.29f - 0.6f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.220f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.220f + 0.29f - 0.6f);
glVertex2f(-0.260f + 0.9f - 1.4f, -0.210f + 0.29f - 0.6f);
glVertex2f(-0.250f + 0.9f - 1.4f, -0.210f + 0.29f - 0.6f);
glEnd();

// Tail light upper
glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f - 1.4f, -0.080f + 0.29f - 0.6f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.080f + 0.29f - 0.6f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.120f + 0.29f - 0.6f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.120f + 0.29f - 0.6f);
glEnd();

// Tail light lower
glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f - 1.4f, -0.210f + 0.29f - 0.6f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.210f + 0.29f - 0.6f);
glVertex2f(0.020f + 0.9f - 1.4f, -0.170f + 0.29f - 0.6f);
glVertex2f(0.030f + 0.9f - 1.4f, -0.170f + 0.29f - 0.6f);
glEnd();

// Window upper left side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.075f + 0.29f - 0.6f);
glVertex2f(-0.160f + 0.9f - 1.4f, -0.075f + 0.29f - 0.6f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.160f + 0.9f - 1.4f, -0.075f + 0.29f - 0.6f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.075f + 0.29f - 0.6f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glVertex2f(-0.142f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glEnd();

// Window upper right side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.075f + 0.29f - 0.6f);
glVertex2f(-0.040f + 0.9f - 1.4f, -0.075f + 0.29f - 0.6f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.040f + 0.9f - 1.4f, -0.075f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.075f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glVertex2f(-0.058f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glEnd();

// Window lower
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.215f + 0.29f - 0.6f);
glVertex2f(-0.160f + 0.9f - 1.4f, -0.215f + 0.29f - 0.6f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.160f + 0.9f - 1.4f, -0.215f + 0.29f - 0.6f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.215f + 0.29f - 0.6f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glVertex2f(-0.142f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glEnd();

// Window right side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.215f + 0.29f - 0.6f);
glVertex2f(-0.040f + 0.9f - 1.4f, -0.215f + 0.29f - 0.6f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.040f + 0.9f - 1.4f, -0.215f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.215f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glVertex2f(-0.058f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glEnd();

// Door shutter up
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glEnd();

// Door shutter down
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(-0.095f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glVertex2f(-0.105f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glEnd();

// Windshield holder upper left
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.148f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glVertex2f(-0.158f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glVertex2f(-0.190f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glEnd();

// Windshield holder upper right
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glVertex2f(-0.052f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glVertex2f(-0.042f + 0.9f - 1.4f, -0.085f + 0.29f - 0.6f);
glVertex2f(-0.010f + 0.9f - 1.4f, -0.065f + 0.29f - 0.6f);
glEnd();

// Windshield holder lower left
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(-0.148f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glVertex2f(-0.158f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glVertex2f(-0.190f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glEnd();

// Windshield holder lower right
glColor3f(0.5f, 0.1f, 0.1f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glVertex2f(-0.052f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glVertex2f(-0.042f + 0.9f - 1.4f, -0.205f + 0.29f - 0.6f);
glVertex2f(-0.010f + 0.9f - 1.4f, -0.225f + 0.29f - 0.6f);
glEnd();












glPopMatrix();
}








//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************








void drawYellowCar_iv() {
glPushMatrix();
glTranslatef(position_yellow_iii, 0.0f, 0.0f);







// yellow car of 4th lane



float centerX1emr = -0.6f + 2.5f, centerY1emr = 0.24f - 0.6f + 0.3f; // New center: (1.9f, -0.36f + 0.3f) = (1.9f, -0.06f)
float width1emr = 0.005f;          // Half-width of the magazine
float radius1emr = 0.3f / 4.2;     // Curve radius (controls curvature)
int segments1emr = 100;

glColor3f(0.9f, 0.9f, 0.0f);  // Yellow for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments1emr; ++i) {
    float t = float(i) / segments1emr;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 1.9f - cos(angle) * (radius1emr + width1emr);
    float yOuter = -0.06f + sin(angle) * (radius1emr + width1emr);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 1.9f - cos(angle) * (radius1emr - width1emr);
    float yInner = -0.06f + sin(angle) * (radius1emr - width1emr);
    glVertex2f(xInner, yInner);
}
glEnd();

// Mirror lower
float centerX2emr = -0.6f + 2.5f, centerY2emr = -0.36f + 0.3f; // New center: (1.9f, -0.36f + 0.3f) = (1.9f, -0.06f)
float width2emr = 0.005f;          // Half-width of the magazine
float radius2emr = 0.3f / 4.2;     // Curve radius (controls curvature)
int segments2emr = 100;

glColor3f(0.9f, 0.9f, 0.0f);  // Yellow for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments2emr; ++i) {
    float t = float(i) / segments2emr;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 1.9f - cos(angle) * (radius2emr + width2emr);
    float yOuter = -0.06f - 0.19f - sin(angle) * (radius2emr + width2emr); // -0.25f
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 1.9f - cos(angle) * (radius2emr - width2emr);
    float yInner = -0.06f - 0.19f - sin(angle) * (radius2emr - width2emr);
    glVertex2f(xInner, yInner);
}
glEnd();

// Front bumper
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.060f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.060f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.230f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.230f + 0.29f - 0.6f + 0.3f);
glEnd();

// Rear bumper
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f - 1.4f + 2.5f, -0.060f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.020f + 0.9f - 1.4f + 2.5f, -0.060f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.020f + 0.9f - 1.4f + 2.5f, -0.230f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.030f + 0.9f - 1.4f + 2.5f, -0.230f + 0.29f - 0.6f + 0.3f);
glEnd();

// Upper bumper
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.055f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.030f + 0.9f - 1.4f + 2.5f, -0.055f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.030f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glEnd();

// Lower bumper
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.030f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.030f + 0.9f - 1.4f + 2.5f, -0.235f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.235f + 0.29f - 0.6f + 0.3f);
glEnd();

// Bonnet
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.170f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.170f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glEnd();

// Trunk
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.020f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.025f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.025f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.020f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glEnd();

// Windshield
float centerX3emr = -0.4f + 2.5f, centerY3emr = 0.145f - 0.6f + 0.3f; // centerX3 = 2.1f, centerY3 = -0.455f + 0.3f = -0.155f
float width3emr = 0.05f;          // Half-width of the magazine
float radius3emr = 0.3f / 1.2;    // Curve radius (controls curvature)
int segments3emr = 100;

glColor3f(0.32f, 0.30f, 0.30f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments3emr; ++i) {
    float t = float(i) / segments3emr;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 2.1f - cos(angle) * (radius3emr + width3emr);
    float yOuter = -0.155f + sin(angle) * (radius3emr + width3emr);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 2.1f - cos(angle) * (radius3emr - width3emr);
    float yInner = -0.155f + sin(angle) * (radius3emr - width3emr);
    glVertex2f(xInner, yInner);
}
glEnd();

// Windshield inner left
float centerX4emr = -0.415f + 2.5f, centerY4emr = 0.145f - 0.6f + 0.3f; // centerX4 = 2.085f, centerY4 = -0.155f
float width4emr = 0.05f;          // Half-width of the magazine
float radius4emr = 0.3f / 1.4;    // Curve radius (controls curvature)
int segments4emr = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments4emr; ++i) {
    float t = float(i) / segments4emr;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 2.085f - cos(angle) * (radius4emr + width4emr);
    float yOuter = -0.155f + sin(angle) * (radius4emr + width4emr);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 2.085f - cos(angle) * (radius4emr - width4emr);
    float yInner = -0.155f + sin(angle) * (radius4emr - width4emr);
    glVertex2f(xInner, yInner);
}
glEnd();

// Windshield inner right
float centerX44emr = -0.79f + 2.5f, centerY44emr = 0.145f - 0.6f + 0.3f; // centerX44 = 1.71f, centerY44 = -0.155f
float width44emr = 0.05f;          // Half-width of the magazine
float radius44emr = 0.3f / 1.35f;   // Curve radius (controls curvature)
int segments44emr = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments44emr; ++i) {
    float t = float(i) / segments44emr;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 1.71f + cos(angle) * (radius44emr + width44emr);
    float yOuter = -0.155f + sin(angle) * (radius44emr + width44emr);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 1.71f + cos(angle) * (radius44emr - width44emr);
    float yInner = -0.155f + sin(angle) * (radius44emr - width44emr);
    glVertex2f(xInner, yInner);
}
glEnd();

// Roof left
float centerX5emr = -0.425f + 2.5f, centerY5emr = 0.145f - 0.6f + 0.3f; // centerX5 = 2.075f, centerY5 = -0.155f
float width5emr = 0.05f;          // Half-width of the magazine
float radius5emr = 0.3f / 1.6;    // Curve radius (controls curvature)
int segments5emr = 100;

glColor3f(0.9f, 0.9f, 0.0f);  // Yellow for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments5emr; ++i) {
    float t = float(i) / segments5emr;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 2.075f - cos(angle) * (radius5emr + width5emr);
    float yOuter = -0.155f + sin(angle) * (radius5emr + width5emr);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 2.075f - cos(angle) * (radius5emr - width5emr);
    float yInner = -0.155f + sin(angle) * (radius5emr - width5emr);
    glVertex2f(xInner, yInner);
}
glEnd();

// Roof right
float centerX55emr = -0.78f + 2.5f, centerY55emr = 0.145f - 0.6f + 0.3f; // centerX55 = 1.72f, centerY55 = -0.155f
float width55emr = 0.05f;          // Half-width of the magazine
float radius55emr = 0.3f / 1.6;   // Curve radius (controls curvature)
int segments55emr = 100;

glColor3f(0.9f, 0.9f, 0.0f);  // Yellow for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments55emr; ++i) {
    float t = float(i) / segments55emr;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = 1.72f + cos(angle) * (radius55emr + width55emr);
    float yOuter = -0.155f + sin(angle) * (radius55emr + width55emr);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = 1.72f + cos(angle) * (radius55emr - width55emr);
    float yInner = -0.155f + sin(angle) * (radius55emr - width55emr);
    glVertex2f(xInner, yInner);
}
glEnd();

// Square roof
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.155f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.050f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.050f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.155f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glEnd();

// Headlight upper
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.070f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.070f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.115f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.115f + 0.29f - 0.6f + 0.3f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.070f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.070f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.080f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.080f + 0.29f - 0.6f + 0.3f);
glEnd();

// Headlight lower
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.220f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.220f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.175f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.175f + 0.29f - 0.6f + 0.3f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.220f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.220f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.260f + 0.9f - 1.4f + 2.5f, -0.210f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.250f + 0.9f - 1.4f + 2.5f, -0.210f + 0.29f - 0.6f + 0.3f);
glEnd();

// Tail light upper
glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f - 1.4f + 2.5f, -0.080f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.020f + 0.9f - 1.4f + 2.5f, -0.080f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.020f + 0.9f - 1.4f + 2.5f, -0.120f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.030f + 0.9f - 1.4f + 2.5f, -0.120f + 0.29f - 0.6f + 0.3f);
glEnd();

// Tail light lower
glBegin(GL_QUADS);
glVertex2f(0.030f + 0.9f - 1.4f + 2.5f, -0.210f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.020f + 0.9f - 1.4f + 2.5f, -0.210f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.020f + 0.9f - 1.4f + 2.5f, -0.170f + 0.29f - 0.6f + 0.3f);
glVertex2f(0.030f + 0.9f - 1.4f + 2.5f, -0.170f + 0.29f - 0.6f + 0.3f);
glEnd();

// Window upper left side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.075f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.160f + 0.9f - 1.4f + 2.5f, -0.075f + 0.29f - 0.6f + 0.3f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.160f + 0.9f - 1.4f + 2.5f, -0.075f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.075f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.142f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glEnd();

// Window upper right side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.075f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.040f + 0.9f - 1.4f + 2.5f, -0.075f + 0.29f - 0.6f + 0.3f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.040f + 0.9f - 1.4f + 2.5f, -0.075f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.075f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.058f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glEnd();

// Window lower
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.215f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.160f + 0.9f - 1.4f + 2.5f, -0.215f + 0.29f - 0.6f + 0.3f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.160f + 0.9f - 1.4f + 2.5f, -0.215f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.215f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.142f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glEnd();

// Window right side
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.215f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.040f + 0.9f - 1.4f + 2.5f, -0.215f + 0.29f - 0.6f + 0.3f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(-0.040f + 0.9f - 1.4f + 2.5f, -0.215f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.215f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.058f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glEnd();

// Door shutter up
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glEnd();

// Door shutter down
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.095f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.105f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glEnd();

// Windshield holder upper left
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.148f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.158f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.190f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glEnd();

// Windshield holder upper right
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.052f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.042f + 0.9f - 1.4f + 2.5f, -0.085f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.010f + 0.9f - 1.4f + 2.5f, -0.065f + 0.29f - 0.6f + 0.3f);
glEnd();

// Windshield holder lower left
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.178f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.148f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.158f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.190f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glEnd();

// Windshield holder lower right
glColor3f(0.9f, 0.9f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-0.022f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.052f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.042f + 0.9f - 1.4f + 2.5f, -0.205f + 0.29f - 0.6f + 0.3f);
glVertex2f(-0.010f + 0.9f - 1.4f + 2.5f, -0.225f + 0.29f - 0.6f + 0.3f);
glEnd();







glPopMatrix();
}







//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************




void drawBluePickup2() {

 glPushMatrix();
    glTranslatef(position_blue_ii, 0.0f, 0.0f);



// Upper mirror
float centerXvsd = 0.30f, centerYvsd = 0.55f - 0.3f; // New center: (0.30f, 0.55f - 0.3f) = (0.30f, 0.25f)
float widthvsd = 0.005f;          // Half-width of the magazine
float radiusvsd = 0.3f / 4.2;     // Curve radius (controls curvature)
int segmentsvsd = 100;

glColor3f(0.46f, 0.62f, 0.76f);  // Dark gray/blue for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segmentsvsd; ++i) {
    float t = float(i) / segmentsvsd;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = centerXvsd - cos(angle) * (radiusvsd + widthvsd);
    float yOuter = centerYvsd + sin(angle) * (radiusvsd + widthvsd);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = centerXvsd - cos(angle) * (radiusvsd - widthvsd);
    float yInner = centerYvsd + sin(angle) * (radiusvsd - widthvsd);
    glVertex2f(xInner, yInner);
}
glEnd();

// Mirror lower
float cnerXvsd = 0.30f, cnerYvsd = 0.55f - 0.3f; // New center: (0.30f, 0.55f - 0.3f) = (0.30f, 0.25f)
float wdhvsd = 0.005f;          // Half-width of the magazine
float ausvsd = 0.3f / 4.2;      // Curve radius (controls curvature)
int egmensvsd = 100;

glColor3f(0.46f, 0.62f, 0.76f);  // Dark gray/blue for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= egmensvsd; ++i) {
    float t = float(i) / egmensvsd;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = cnerXvsd - cos(angle) * (ausvsd + wdhvsd);
    float yOuter = 0.360f - 0.3f - sin(angle) * (ausvsd + wdhvsd); // 0.360f - 0.3f = 0.060f
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = cnerXvsd - cos(angle) * (ausvsd - wdhvsd);
    float yInner = 0.360f - 0.3f - sin(angle) * (ausvsd - wdhvsd);
    glVertex2f(xInner, yInner);
}
glEnd();

// Front bumper
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.540f - 0.3f);
glVertex2f(0.140f, 0.540f - 0.3f);
glVertex2f(0.140f, 0.370f - 0.3f);
glVertex2f(0.150f, 0.370f - 0.3f);
glEnd();

// Rear bumper
glColor3f(0.46f, 0.64f, 0.77f);
glBegin(GL_QUADS);
glVertex2f(0.410f, 0.540f - 0.3f);
glVertex2f(0.400f, 0.540f - 0.3f);
glVertex2f(0.400f, 0.370f - 0.3f);
glVertex2f(0.410f, 0.370f - 0.3f);
glEnd();

// Upper bumper
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.140f, 0.545f - 0.3f);
glVertex2f(0.410f, 0.545f - 0.3f);
glVertex2f(0.410f, 0.535f - 0.3f);
glVertex2f(0.140f, 0.535f - 0.3f);
glEnd();

// Lower bumper
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.140f, 0.375f - 0.3f);
glVertex2f(0.410f, 0.375f - 0.3f);
glVertex2f(0.410f, 0.365f - 0.3f);
glVertex2f(0.140f, 0.365f - 0.3f);
glEnd();

// Bonnet
glColor3f(0.56f, 0.79f, 0.97f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.535f - 0.3f);
glVertex2f(0.230f, 0.535f - 0.3f);
glVertex2f(0.230f, 0.375f - 0.3f);
glVertex2f(0.150f, 0.375f - 0.3f);
glEnd();

// Windshield
float centerX1vsd = 0.500f, centerY1vsd = 0.455f - 0.3f; // New center: (0.500f, 0.455f - 0.3f) = (0.500f, 0.155f)
float width1vsd = 0.05f;          // Half-width of the magazine
float radius1vsd = 0.3f / 1.2;    // Curve radius (controls curvature)
int segments1vsd = 100;

glColor3f(0.32f, 0.30f, 0.30f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segments1vsd; ++i) {
    float t = float(i) / segments1vsd;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = centerX1vsd - cos(angle) * (radius1vsd + width1vsd);
    float yOuter = centerY1vsd + sin(angle) * (radius1vsd + width1vsd);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = centerX1vsd - cos(angle) * (radius1vsd - width1vsd);
    float yInner = centerY1vsd + sin(angle) * (radius1vsd - width1vsd);
    glVertex2f(xInner, yInner);
}
glEnd();

// Windshield inner
float centerXxvsd = 0.485f, centerYyvsd = 0.455f - 0.3f; // New center: (0.485f, 0.155f)
float widthxvsd = 0.05f;          // Half-width of the magazine
float radiusxvsd = 0.3f / 1.4;    // Curve radius (controls curvature)
int segmenvsd = 100;

glColor3f(0.38f, 0.36f, 0.36f);  // Dark gray/black for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segmenvsd; ++i) {
    float t = float(i) / segmenvsd;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = centerXxvsd - cos(angle) * (radiusxvsd + widthxvsd);
    float yOuter = centerYyvsd + sin(angle) * (radiusxvsd + widthxvsd);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = centerXxvsd - cos(angle) * (radiusxvsd - widthxvsd);
    float yInner = centerYyvsd + sin(angle) * (radiusxvsd - widthxvsd);
    glVertex2f(xInner, yInner);
}
glEnd();

// Roof
float centerXxxvsd = 0.475f, centerYyyvsd = 0.455f - 0.3f; // New center: (0.475f, 0.155f)
float widthxxvsd = 0.05f;          // Half-width of the magazine
float radiusxxvsd = 0.3f / 1.6;    // Curve radius (controls curvature)
int segmenxxvsd = 100;

glColor3f(0.56f, 0.79f, 0.97f);  // Light blue for metal

glBegin(GL_QUAD_STRIP);
for (int i = 0; i <= segmenxxvsd; ++i) {
    float t = float(i) / segmenxxvsd;
    float angle = -0.2618f + t * 0.5236f;  // Angle range in radians (~-15° to +15°)

    // Outer curved edge vertex
    float xOuter = centerXxxvsd - cos(angle) * (radiusxxvsd + widthxxvsd);
    float yOuter = centerYyyvsd + sin(angle) * (radiusxxvsd + widthxxvsd);
    glVertex2f(xOuter, yOuter);

    // Inner curved edge vertex
    float xInner = centerXxxvsd - cos(angle) * (radiusxxvsd - widthxxvsd);
    float yInner = centerYyyvsd + sin(angle) * (radiusxxvsd - widthxxvsd);
    glVertex2f(xInner, yInner);
}
glEnd();

// Square roof
glColor3f(0.56f, 0.79f, 0.97f);
glBegin(GL_QUADS);
glVertex2f(0.245f, 0.515f - 0.3f);
glVertex2f(0.310f, 0.515f - 0.3f);
glVertex2f(0.310f, 0.395f - 0.3f);
glVertex2f(0.245f, 0.395f - 0.3f);
glEnd();

// Door shutter up
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.290f, 0.535f - 0.3f);
glVertex2f(0.310f, 0.535f - 0.3f);
glVertex2f(0.310f, 0.515f - 0.3f);
glVertex2f(0.290f, 0.515f - 0.3f);
glEnd();

// Door shutter down
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.290f, 0.375f - 0.3f);
glVertex2f(0.310f, 0.375f - 0.3f);
glVertex2f(0.310f, 0.395f - 0.3f);
glVertex2f(0.290f, 0.395f - 0.3f);
glEnd();

// Product space
glColor3f(0.0f, 0.5f, 0.7f);
glBegin(GL_QUADS);
glVertex2f(0.310f, 0.535f - 0.3f);
glVertex2f(0.400f, 0.535f - 0.3f);
glVertex2f(0.400f, 0.375f - 0.3f);
glVertex2f(0.310f, 0.375f - 0.3f);
glEnd();

// Rear upper tier
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.33f, 0.535f - 0.3f);
glVertex2f(0.37f, 0.535f - 0.3f);
glVertex2f(0.37f, 0.505f - 0.3f);
glVertex2f(0.33f, 0.505f - 0.3f);
glEnd();
glColor3f(0.38f, 0.47f, 0.54f);
glBegin(GL_QUADS);
glVertex2f(0.37f, 0.535f - 0.3f);
glVertex2f(0.38f, 0.535f - 0.3f);
glVertex2f(0.38f, 0.505f - 0.3f);
glVertex2f(0.37f, 0.505f - 0.3f);
glEnd();

// Rear lower tier
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.33f, 0.405f - 0.3f);
glVertex2f(0.37f, 0.405f - 0.3f);
glVertex2f(0.37f, 0.375f - 0.3f);
glVertex2f(0.33f, 0.375f - 0.3f);
glEnd();
glColor3f(0.38f, 0.47f, 0.54f);
glBegin(GL_QUADS);
glVertex2f(0.37f, 0.405f - 0.3f);
glVertex2f(0.38f, 0.405f - 0.3f);
glVertex2f(0.38f, 0.375f - 0.3f);
glVertex2f(0.37f, 0.375f - 0.3f);
glEnd();

// Windshield holder upper
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.222f, 0.535f - 0.3f);
glVertex2f(0.252f, 0.515f - 0.3f);
glVertex2f(0.242f, 0.515f - 0.3f);
glVertex2f(0.210f, 0.535f - 0.3f);
glEnd();

// Windshield holder lower
glColor3f(0.46f, 0.62f, 0.76f);
glBegin(GL_QUADS);
glVertex2f(0.222f, 0.375f - 0.3f);
glVertex2f(0.252f, 0.395f - 0.3f);
glVertex2f(0.242f, 0.395f - 0.3f);
glVertex2f(0.210f, 0.375f - 0.3f);
glEnd();

// Headlight upper
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.530f - 0.3f);
glVertex2f(0.140f, 0.530f - 0.3f);
glVertex2f(0.140f, 0.485f - 0.3f);
glVertex2f(0.150f, 0.485f - 0.3f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.530f - 0.3f);
glVertex2f(0.140f, 0.530f - 0.3f);
glVertex2f(0.140f, 0.520f - 0.3f);
glVertex2f(0.150f, 0.520f - 0.3f);
glEnd();

// Headlight lower
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.380f - 0.3f);
glVertex2f(0.140f, 0.380f - 0.3f);
glVertex2f(0.140f, 0.425f - 0.3f);
glVertex2f(0.150f, 0.425f - 0.3f);
glEnd();
glColor3f(0.91f, 0.49f, 0.13f);
glBegin(GL_QUADS);
glVertex2f(0.150f, 0.380f - 0.3f);
glVertex2f(0.140f, 0.380f - 0.3f);
glVertex2f(0.140f, 0.390f - 0.3f);
glVertex2f(0.150f, 0.390f - 0.3f);
glEnd();

// Tail light upper
glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.410f, 0.520f - 0.3f);
glVertex2f(0.400f, 0.520f - 0.3f);
glVertex2f(0.400f, 0.480f - 0.3f);
glVertex2f(0.410f, 0.480f - 0.3f);
glEnd();

// Tail light lower
glColor3f(0.7f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.410f, 0.390f - 0.3f);
glVertex2f(0.400f, 0.390f - 0.3f);
glVertex2f(0.400f, 0.430f - 0.3f);
glVertex2f(0.410f, 0.430f - 0.3f);
glEnd();

// Window upper
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.222f, 0.535f - 0.3f);
glVertex2f(0.292f, 0.535f - 0.3f);
glVertex2f(0.292f, 0.525f - 0.3f);
glVertex2f(0.240f, 0.525f - 0.3f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(0.240f, 0.525f - 0.3f);
glVertex2f(0.292f, 0.525f - 0.3f);
glVertex2f(0.292f, 0.515f - 0.3f);
glVertex2f(0.258f, 0.515f - 0.3f);
glEnd();

// Window lower
glColor3f(0.3f, 0.3f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(0.222f, 0.375f - 0.3f);
glVertex2f(0.292f, 0.375f - 0.3f);
glVertex2f(0.292f, 0.385f - 0.3f);
glVertex2f(0.240f, 0.385f - 0.3f);
glEnd();

glColor3f(0.38f, 0.36f, 0.36f);
glBegin(GL_QUADS);
glVertex2f(0.240f, 0.385f - 0.3f);
glVertex2f(0.292f, 0.385f - 0.3f);
glVertex2f(0.292f, 0.395f - 0.3f);
glVertex2f(0.258f, 0.395f - 0.3f);
glEnd();

// Square on trunk upper
glColor3f(0.6f, 0.79f, 0.94f);
glBegin(GL_QUADS);
glVertex2f(0.310f, 0.535f - 0.3f);
glVertex2f(0.400f, 0.535f - 0.3f);
glVertex2f(0.400f, 0.530f - 0.3f);
glVertex2f(0.310f, 0.530f - 0.3f);
glEnd();

// Square on trunk lower
glColor3f(0.6f, 0.79f, 0.94f);
glBegin(GL_QUADS);
glVertex2f(0.310f, 0.375f - 0.3f);
glVertex2f(0.400f, 0.375f - 0.3f);
glVertex2f(0.400f, 0.380f - 0.3f);
glVertex2f(0.310f, 0.380f - 0.3f);
glEnd();

// Square on trunk side
glColor3f(0.6f, 0.79f, 0.94f);
glBegin(GL_QUADS);
glVertex2f(0.396f, 0.535f - 0.3f);
glVertex2f(0.400f, 0.535f - 0.3f);
glVertex2f(0.400f, 0.380f - 0.3f);
glVertex2f(0.396f, 0.380f - 0.3f);
glEnd();







glPopMatrix();
}


//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************



void display()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)
    glPointSize(10);



//sceen

glColor3f(0.86f, 0.59f, 0.17f);

glBegin(GL_QUADS);
glVertex2f(-1.0f, 1.0f);
glVertex2f(1.0f, 1.0f);
glVertex2f(1.0f, 0.600f);
glVertex2f(-1.0f, 0.600f);
glEnd();

glBegin(GL_QUADS);
glVertex2f(-1.0f, -0.600f);
glVertex2f(1.0f, -0.600f);
glVertex2f(1.0f, -1.0f);
glVertex2f(-1.0f, -1.0f);
glEnd();

//divider of road and sceen
glColor3f(0.76f, 0.73f, 0.73f);
glBegin(GL_QUADS);
glVertex2f(-1.0f, 0.630f);
glVertex2f(1.0f, 0.630f);
glVertex2f(1.0f, 0.600f);
glVertex2f(-1.0f, 0.600f);
glEnd();

glBegin(GL_QUADS);
glVertex2f(-1.0f, -0.600f);
glVertex2f(1.0f, -0.600f);
glVertex2f(1.0f, -0.630f);
glVertex2f(-1.0f, -0.630f);
glEnd();


//road

glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2f(-1.0f, 0.600f);
glVertex2f(1.0f, 0.600f);
glVertex2f(1.0f, 0.310f);
glVertex2f(-1.0f, 0.310f);
glEnd();

glBegin(GL_QUADS);
glVertex2f(-1.0f, 0.290f);
glVertex2f(1.0f, 0.290f);
glVertex2f(1.0f, -0.0f);
glVertex2f(-1.0f, -0.0f);
glEnd();

glBegin(GL_QUADS);
glVertex2f(-1.0f, -0.00f);
glVertex2f(1.0f, -0.00f);
glVertex2f(1.0f, -0.290f);
glVertex2f(-1.0f, -0.290f);
glEnd();

glBegin(GL_QUADS);
glVertex2f(-1.0f, -0.310f);
glVertex2f(1.0f, -0.310f);
glVertex2f(1.0f, -0.600f);
glVertex2f(-1.0f, -0.600f);
glEnd();

//divider
glColor3f(1.0f, 1.0f, 1.0f);
  for (float x = -1.0f; x < 1.0f; x += 0.1f) {
        glBegin(GL_QUADS);
        glVertex2f(x, 0.015f);
        glVertex2f(x + 0.08f, 0.015f);
        glVertex2f(x + 0.08f, -0.015f);
        glVertex2f(x, -0.015f);
        glEnd();
    }

//************************************************************************





//The F1 Car
//x axis=155



drawF1Car();





//************************************************************************************************************


//blue pickup
//x axis == 455



drawBluePickup();




//**********************************************************************************************************




//Red Truck

drawRedTruck();



//****************************************************************************



// green car
// x axis == -455
// y axis == -145
// Translation offsets
drawGreenCar_i();






//***********************************************************************************


drawGreenTruck();


//***********************************************************************************




drawRedCar_ii();




//***********************************************************************************

drawYellowCar_ii();






//***********************************************************************************



drawRedCar_iv();








//***********************************************************************************


drawYellowCar_iv();


//***********************************************************************************

drawBluePickup2();

//***********************************************************************************



//***********************************************************************************




//***********************************************************************************

  //bush 1


glPushMatrix();
glTranslatef(position_upper_scene, 0.0f, 0.0f);





// First Wavy Circle
GLfloat xe = 0.0f * 0.7f + 0.7f;  // 0.0f + 0.7f = 0.7f
GLfloat ye = 0.0f * 0.7f - 0.8f;  // 0.0f - 0.8f = -0.8f
GLfloat baseRedi = 0.15f * 0.7f;  // 0.105f
GLfloat maxWaveAmplitude = 0.035f;  // maximum wave height
GLfloat waveFrequency = 18.0f;  // controls number of waves
GLfloat tpie = 2.0f * 3.14159265359f;  // 2 * PI
int trianglemount = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat aspectRatio = 1200.0f / 800.0f;
GLfloat rediX, rediY;

glColor3f(0.16f, 0.38f, 0.01f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xe, ye);  // center of the wavy circle
    for (int i = 0; i <= trianglemount; i++) {
        GLfloat angle = i * tpie / trianglemount;
        // Combine sine functions for irregular wave sizes
        GLfloat wave1 = (sinf(waveFrequency * angle) + 1.0f) / 2.0f;  // primary wave
        GLfloat wave2 = (sinf(waveFrequency * 1.618f * angle + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat amplitude = 0.55f * wave1 + 0.45f * wave2;  // weighted combination
        GLfloat redi = baseRedi + maxWaveAmplitude * amplitude;  // radius with uneven waves
        rediX = redi / aspectRatio;  // adjust x for aspect ratio
        rediY = redi;  // y remains unscaled
        glVertex2f(
            xe + rediX * cosf(angle),
            ye + rediY * sinf(angle)
        );
    }
glEnd();

// Second Wavy Circle
GLfloat circleX = (-0.02f * 0.7f) + 0.7f;  // -0.014f + 0.7f = 0.686f
GLfloat circleY = (0.03f * 0.7f) - 0.8f;   // 0.021f - 0.8f = -0.779f
GLfloat coreRadius = 0.13f * 0.7f;  // 0.091f
GLfloat peakWaveHeight = 0.035f;  // maximum wave height
GLfloat waveCount = 14.0f;  // controls number of waves
GLfloat twoPi = 2.0f * 3.14159265359f;  // 2 * PI
int segmentCount = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat displayRatio = 1200.0f / 800.0f;
GLfloat radiusX, radiusY;

glColor3f(0.3f, 0.52f, 0.07f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(circleX, circleY);  // center of the wavy circle
    for (int i = 0; i <= segmentCount; i++) {
        GLfloat theta = i * twoPi / segmentCount;
        // Combine sine functions for irregular wave sizes
        GLfloat waveA = (sinf(waveCount * theta) + 1.0f) / 2.0f;  // primary wave
        GLfloat waveB = (sinf(waveCount * 1.618f * theta + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat waveBlend = 0.55f * waveA + 0.45f * waveB;  // weighted combination
        GLfloat radius = coreRadius + peakWaveHeight * waveBlend;  // radius with uneven waves
        radiusX = radius / displayRatio;  // adjust x for aspect ratio
        radiusY = radius;  // y remains unscaled
        glVertex2f(
            circleX + radiusX * cosf(theta),
            circleY + radiusY * sinf(theta)
        );
    }
glEnd();

// Third Wavy Circle
GLfloat originX = (-0.02f * 0.7f) + 0.7f;  // -0.014f + 0.7f = 0.686f
GLfloat originY = (0.04f * 0.7f) - 0.8f;   // 0.028f - 0.8f = -0.772f
GLfloat mainRadius = 0.08f * 0.7f;  // 0.056f
GLfloat maxWaveSize = 0.035f;  // maximum wave height
GLfloat waveRate = 14.0f;  // controls number of waves
GLfloat piDouble = 2.0f * 3.14159265359f;  // 2 * PI
int numSegments = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/1000 = 1.2)
GLfloat screenRatio = 1200.0f / 1000.0f;
GLfloat radX, radY;

glColor3f(0.55f, 0.72f, 0.25f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(originX, originY);  // center of the wavy circle
    for (int i = 0; i <= numSegments; i++) {
        GLfloat phi = i * piDouble / numSegments;
        // Combine sine functions for irregular wave sizes
        GLfloat wavePrimary = (sinf(waveRate * phi) + 1.0f) / 2.0f;  // primary wave
        GLfloat waveSecondary = (sinf(waveRate * 1.618f * phi + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat waveMix = 0.55f * wavePrimary + 0.45f * waveSecondary;  // weighted combination
        GLfloat rad = mainRadius + maxWaveSize * waveMix;  // radius with uneven waves
        radX = rad / screenRatio;  // adjust x for aspect ratio
        radY = rad;  // y remains unscaled
        glVertex2f(
            originX + radX * cosf(phi),
            originY + radY * sinf(phi)
        );
    }
glEnd();

// Pebbles
GLfloat circleConstant = 2.0f * 3.14159265359f;  // 2 * PI
int segmentTotal = 100;  // number of segments for smooth rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat viewScale = 1200.0f / 800.0f;
GLfloat radX1, radY1;

// Pebble 1
GLfloat centerX12 = ((0.2f / 8.0f) * 0.7f - 0.02f) + 0.7f;   // 0.0175f - 0.02f + 0.7f = 0.6975f
GLfloat centerY12 = ((0.4f / 8.0f) * 0.7f + 0.02f) - 0.8f;   // 0.035f + 0.02f - 0.8f = -0.745f
GLfloat radBaseX1 = 0.12f / 8.0f * 0.7f;  // 0.0105f
GLfloat radBaseY1 = 0.08f / 8.0f * 0.7f;  // 0.007f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX12, centerY12);  // center
    for (int i1 = 0; i1 <= segmentTotal; i1++) {
        GLfloat angle1 = i1 * circleConstant / segmentTotal;
        radX1 = radBaseX1 / viewScale;  // adjust x
        radY1 = radBaseY1;  // y unscaled
        glVertex2f(centerX12 + radX1 * cosf(angle1), centerY12 + radY1 * sinf(angle1));
    }
glEnd();

// Pebble 2
GLfloat centerX23 = ((-0.2f / 8.0f) * 0.7f - 0.02f) + 0.7f;   // -0.0175f - 0.02f + 0.7f = 0.6625f
GLfloat centerY23 = ((0.3f / 8.0f) * 0.7f + 0.02f) - 0.8f;   // 0.02625f + 0.02f - 0.8f = -0.75375f
GLfloat radBaseX2 = 0.1f / 8.0f * 0.7f;    // 0.00875f
GLfloat radBaseY2 = 0.08f / 8.0f * 0.7f;   // 0.007f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX23, centerY23);  // center
    for (int i2 = 0; i2 <= segmentTotal; i2++) {
        GLfloat angle2 = i2 * circleConstant / segmentTotal;
        radX1 = radBaseX2 / viewScale;  // adjust x
        radY1 = radBaseY2;  // y unscaled
        glVertex2f(centerX23 + radX1 * cosf(angle2), centerY23 + radY1 * sinf(angle2));
    }
glEnd();

// Pebble 3
GLfloat centerX34 = ((0.4f / 8.0f) * 0.7f - 0.02f) + 0.7f;    // 0.035f - 0.02f + 0.7f = 0.715f
GLfloat centerY34 = ((0.1f / 8.0f) * 0.7f + 0.02f) - 0.8f;    // 0.00875f + 0.02f - 0.8f = -0.77125f
GLfloat radBaseX3 = 0.08f / 8.0f * 0.7f;   // 0.007f
GLfloat radBaseY3 = 0.1f / 8.0f * 0.7f;    // 0.00875f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX34, centerY34);  // center
    for (int i3 = 0; i3 <= segmentTotal; i3++) {
        GLfloat angle3 = i3 * circleConstant / segmentTotal;
        radX1 = radBaseX3 / viewScale;  // adjust x
        radY1 = radBaseY3;  // y unscaled
        glVertex2f(centerX34 + radX1 * cosf(angle3), centerY34 + radY1 * sinf(angle3));
    }
glEnd();

// Pebble 4
GLfloat centerX45 = ((-0.0f / 8.0f) * 0.7f - 0.02f) + 0.7f;   // 0.0f - 0.02f + 0.7f = 0.68f
GLfloat centerY45 = ((-0.2f / 8.0f) * 0.7f + 0.02f) - 0.8f;   // -0.0175f + 0.02f - 0.8f = -0.7975f
GLfloat radBaseX4 = 0.14f / 8.0f * 0.7f;   // 0.01225f
GLfloat radBaseY4 = 0.1f / 8.0f * 0.7f;    // 0.00875f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX45, centerY45);  // center
    for (int i4 = 0; i4 <= segmentTotal; i4++) {
        GLfloat angle4 = i4 * circleConstant / segmentTotal;
        radX1 = radBaseX4 / viewScale;  // adjust x
        radY1 = radBaseY4;  // y unscaled
        glVertex2f(centerX45 + radX1 * cosf(angle4), centerY45 + radY1 * sinf(angle4));
    }
glEnd();

// Pebble 5
GLfloat centerX56 = ((0.3f / 8.0f) * 0.7f - 0.02f) + 0.7f;    // 0.02625f - 0.02f + 0.7f = 0.70625f
GLfloat centerY56 = ((-0.3f / 8.0f) * 0.7f + 0.02f) - 0.8f;   // -0.02625f + 0.02f - 0.8f = -0.80625f
GLfloat radBaseX5 = 0.07f / 8.0f * 0.7f;   // 0.006125f
GLfloat radBaseY5 = 0.05f / 8.0f * 0.7f;   // 0.004375f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX56, centerY56);  // center
    for (int i5 = 0; i5 <= segmentTotal; i5++) {
        GLfloat angle5 = i5 * circleConstant / segmentTotal;
        radX1 = radBaseX5 / viewScale;  // adjust x
        radY1 = radBaseY5;  // y unscaled
        glVertex2f(centerX56 + radX1 * cosf(angle5), centerY56 + radY1 * sinf(angle5));
    }
glEnd();

// Pebble 6
GLfloat centerX6 = ((-0.3f / 8.0f) * 0.7f - 0.02f) + 0.7f;    // -0.02625f - 0.02f + 0.7f = 0.65375f
GLfloat centerY6 = ((-0.05f / 8.0f) * 0.7f + 0.02f) - 0.8f;   // -0.004375f + 0.02f - 0.8f = -0.784375f
GLfloat radBaseX6 = 0.09f / 8.0f * 0.7f;   // 0.007875f
GLfloat radBaseY6 = 0.07f / 8.0f * 0.7f;   // 0.006125f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX6, centerY6);  // center
    for (int i6 = 0; i6 <= segmentTotal; i6++) {
        GLfloat angle6 = i6 * circleConstant / segmentTotal;
        radX1 = radBaseX6 / viewScale;  // adjust x
        radY1 = radBaseY6;  // y unscaled
        glVertex2f(centerX6 + radX1 * cosf(angle6), centerY6 + radY1 * sinf(angle6));
    }
glEnd();

// Pebble 7
GLfloat centerX7 = ((-0.4f / 8.0f) * 0.7f - 0.02f) + 0.7f;    // -0.035f - 0.02f + 0.7f = 0.645f
GLfloat centerY7 = ((0.5f / 8.0f) * 0.7f + 0.02f) - 0.8f;    // 0.04375f + 0.02f - 0.8f = -0.73625f
GLfloat radBaseX7 = 0.06f / 8.0f * 0.7f;   // 0.00525f
GLfloat radBaseY7 = 0.06f / 8.0f * 0.7f;   // 0.00525f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX7, centerY7);  // center
    for (int i7 = 0; i7 <= segmentTotal; i7++) {
        GLfloat angle7 = i7 * circleConstant / segmentTotal;
        radX1 = radBaseX7 / viewScale;  // adjust x
        radY1 = radBaseY7;  // y unscaled
        glVertex2f(centerX7 + radX1 * cosf(angle7), centerY7 + radY1 * sinf(angle7));
    }
glEnd();

// Pebble 8 (labeled as Pebble 7 in the code)
GLfloat centerX77 = ((-0.1f / 8.0f) * 0.7f - 0.02f) + 0.7f;    // -0.00875f - 0.02f + 0.7f = 0.67125f
GLfloat centerY77 = ((0.65f / 8.0f) * 0.7f + 0.02f) - 0.8f;   // 0.056875f + 0.02f - 0.8f = -0.723125f
GLfloat radBaseX77 = 0.07f / 8.0f * 0.7f;   // 0.006125f
GLfloat radBaseY77 = 0.06f / 8.0f * 0.7f;   // 0.00525f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX77, centerY77);  // center
    for (int i7 = 0; i7 <= segmentTotal; i7++) {
        GLfloat angle7 = i7 * circleConstant / segmentTotal;
        radX1 = radBaseX77 / viewScale;  // adjust x
        radY1 = radBaseY77;  // y unscaled
        glVertex2f(centerX77 + radX1 * cosf(angle7), centerY77 + radY1 * sinf(angle7));
    }
glEnd();



glPopMatrix();





glPushMatrix();
glTranslatef(position_upper_scene, 0.0f, 0.0f);


// bush 2










// First Wavy Circle
GLfloat xStart = 0.0f * 0.8f - 0.5f;  // 0.0f - 0.5f = -0.5f
GLfloat yStart = 0.0f * 0.8f - 0.8f;  // 0.0f - 0.8f = -0.8f
GLfloat initRadius = 0.15f * 0.8f;  // 0.12f
GLfloat wavePeak = 0.035f;  // maximum wave height
GLfloat waveCycle = 18.0f;  // controls number of waves
GLfloat fullCircle = 2.0f * 3.14159265359f;  // 2 * PI
int segmentNum = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat viewAspect = 1200.0f / 800.0f;
GLfloat raadX, raadY;

glColor3f(0.16f, 0.38f, 0.01f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xStart, yStart);  // center of the wavy circle
    for (int j = 0; j <= segmentNum; j++) {
        GLfloat theta = j * fullCircle / segmentNum;
        // Combine sine functions for irregular wave sizes
        GLfloat waveA = (sinf(waveCycle * theta) + 1.0f) / 2.0f;  // primary wave
        GLfloat waveB = (sinf(waveCycle * 1.618f * theta + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat ampBlend = 0.55f * waveA + 0.45f * waveB;  // weighted combination
        GLfloat rad = initRadius + wavePeak * ampBlend;  // radius with uneven waves
        raadX = rad / viewAspect;  // adjust x for aspect ratio
        raadY = rad;  // y remains unscaled
        glVertex2f(
            xStart + raadX * cosf(theta),
            yStart + raadY * sinf(theta)
        );
    }
glEnd();

// Second Wavy Circle
GLfloat xPos = (-0.02f * 0.8f) - 0.5f;  // -0.016f - 0.5f = -0.516f
GLfloat yPos = (0.03f * 0.8f) - 0.8f;   // 0.024f - 0.8f = -0.776f
GLfloat baseRad = 0.13f * 0.8f;  // 0.104f
GLfloat waveMax = 0.035f;  // maximum wave height
GLfloat waveFreq = 14.0f;  // controls number of waves
GLfloat fullTurn = 2.0f * 3.14159265359f;  // 2 * PI
int segCount = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat displayProp = 1200.0f / 800.0f;
GLfloat radX2, radY2;

glColor3f(0.3f, 0.52f, 0.07f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xPos, yPos);  // center of the wavy circle
    for (int k = 0; k <= segCount; k++) {
        GLfloat phi = k * fullTurn / segCount;
        // Combine sine functions for irregular wave sizes
        GLfloat waveC = (sinf(waveFreq * phi) + 1.0f) / 2.0f;  // primary wave
        GLfloat waveD = (sinf(waveFreq * 1.618f * phi + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat waveMix = 0.55f * waveC + 0.45f * waveD;  // weighted combination
        GLfloat rad = baseRad + waveMax * waveMix;  // radius with uneven waves
        radX2 = rad / displayProp;  // adjust x for aspect ratio
        radY2 = rad;  // y remains unscaled
        glVertex2f(
            xPos + radX2 * cosf(phi),
            yPos + radY2 * sinf(phi)
        );
    }
glEnd();

// Third Wavy Circle
GLfloat xOrigin = (-0.02f * 0.8f) - 0.5f;  // -0.016f - 0.5f = -0.516f
GLfloat yOrigin = (0.04f * 0.8f) - 0.8f;   // 0.032f - 0.8f = -0.768f
GLfloat rootRad = 0.08f * 0.8f;  // 0.064f
GLfloat waveHeight = 0.035f;  // maximum wave height
GLfloat waveSpeed = 14.0f;  // controls number of waves
GLfloat fullRot = 2.0f * 3.14159265359f;  // 2 * PI
int segTotal = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/1000 = 1.2)
GLfloat screenScale = 1200.0f / 1000.0f;
GLfloat radX3, radY3;

glColor3f(0.55f, 0.72f, 0.25f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xOrigin, yOrigin);  // center of the wavy circle
    for (int l = 0; l <= segTotal; l++) {
        GLfloat psi = l * fullRot / segTotal;
        // Combine sine functions for irregular wave sizes
        GLfloat waveE = (sinf(waveSpeed * psi) + 1.0f) / 2.0f;  // primary wave
        GLfloat waveF = (sinf(waveSpeed * 1.618f * psi + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat waveComb = 0.55f * waveE + 0.45f * waveF;  // weighted combination
        GLfloat rad = rootRad + waveHeight * waveComb;  // radius with uneven waves
        radX3 = rad / screenScale;  // adjust x for aspect ratio
        radY3 = rad;  // y remains unscaled
        glVertex2f(
            xOrigin + radX3 * cosf(psi),
            yOrigin + radY3 * sinf(psi)
        );
    }
glEnd();

// Pebbles
GLfloat circleAngle = 2.0f * 3.14159265359f;  // 2 * PI
int segAmount = 100;  // number of segments for smooth rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat viewRatio = 1200.0f / 800.0f;
GLfloat radX4, radY4;

// Pebble 1
GLfloat posX1 = ((0.2f / 8.0f) * 0.8f - 0.02f) - 0.5f;   // 0.02f - 0.02f - 0.5f = -0.5f
GLfloat posY1 = ((0.4f / 8.0f) * 0.8f + 0.02f) - 0.8f;   // 0.04f + 0.02f - 0.8f = -0.74f
GLfloat baseX1 = 0.12f / 8.0f * 0.8f;  // 0.012f
GLfloat baseY1 = 0.08f / 8.0f * 0.8f;  // 0.008f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX1, posY1);  // center
    for (int m = 0; m <= segAmount; m++) {
        GLfloat angleA = m * circleAngle / segAmount;
        radX4 = baseX1 / viewRatio;  // adjust x
        radY4 = baseY1;  // y unscaled
        glVertex2f(posX1 + radX4 * cosf(angleA), posY1 + radY4 * sinf(angleA));
    }
glEnd();

// Pebble 2
GLfloat posX2 = ((-0.2f / 8.0f) * 0.8f - 0.02f) - 0.5f;   // -0.02f - 0.02f - 0.5f = -0.54f
GLfloat posY2 = ((0.3f / 8.0f) * 0.8f + 0.02f) - 0.8f;   // 0.03f + 0.02f - 0.8f = -0.75f
GLfloat baseX2 = 0.1f / 8.0f * 0.8f;    // 0.01f
GLfloat baseY2 = 0.08f / 8.0f * 0.8f;   // 0.008f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX2, posY2);  // center
    for (int n = 0; n <= segAmount; n++) {
        GLfloat angleB = n * circleAngle / segAmount;
        radX4 = baseX2 / viewRatio;  // adjust x
        radY4 = baseY2;  // y unscaled
        glVertex2f(posX2 + radX4 * cosf(angleB), posY2 + radY4 * sinf(angleB));
    }
glEnd();

// Pebble 3
GLfloat posX3 = ((0.4f / 8.0f) * 0.8f - 0.02f) - 0.5f;    // 0.04f - 0.02f - 0.5f = -0.48f
GLfloat posY3 = ((0.1f / 8.0f) * 0.8f + 0.02f) - 0.8f;    // 0.01f + 0.02f - 0.8f = -0.77f
GLfloat baseX3 = 0.08f / 8.0f * 0.8f;   // 0.008f
GLfloat baseY3 = 0.1f / 8.0f * 0.8f;    // 0.01f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX3, posY3);  // center
    for (int o = 0; o <= segAmount; o++) {
        GLfloat angleC = o * circleAngle / segAmount;
        radX4 = baseX3 / viewRatio;  // adjust x
        radY4 = baseY3;  // y unscaled
        glVertex2f(posX3 + radX4 * cosf(angleC), posY3 + radY4 * sinf(angleC));
    }
glEnd();

// Pebble 4
GLfloat posX4 = ((-0.0f / 8.0f) * 0.8f - 0.02f) - 0.5f;   // 0.0f - 0.02f - 0.5f = -0.52f
GLfloat posY4 = ((-0.2f / 8.0f) * 0.8f + 0.02f) - 0.8f;   // -0.02f + 0.02f - 0.8f = -0.8f
GLfloat baseX4 = 0.14f / 8.0f * 0.8f;   // 0.014f
GLfloat baseY4 = 0.1f / 8.0f * 0.8f;    // 0.01f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX4, posY4);  // center
    for (int p = 0; p <= segAmount; p++) {
        GLfloat angleD = p * circleAngle / segAmount;
        radX4 = baseX4 / viewRatio;  // adjust x
        radY4 = baseY4;  // y unscaled
        glVertex2f(posX4 + radX4 * cosf(angleD), posY4 + radY4 * sinf(angleD));
    }
glEnd();

// Pebble 5
GLfloat posX5 = ((0.3f / 8.0f) * 0.8f - 0.02f) - 0.5f;    // 0.03f - 0.02f - 0.5f = -0.49f
GLfloat posY5 = ((-0.3f / 8.0f) * 0.8f + 0.02f) - 0.8f;   // -0.03f + 0.02f - 0.8f = -0.81f
GLfloat baseX5 = 0.07f / 8.0f * 0.8f;   // 0.007f
GLfloat baseY5 = 0.05f / 8.0f * 0.8f;   // 0.005f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX5, posY5);  // center
    for (int q = 0; q <= segAmount; q++) {
        GLfloat angleE = q * circleAngle / segAmount;
        radX4 = baseX5 / viewRatio;  // adjust x
        radY4 = baseY5;  // y unscaled
        glVertex2f(posX5 + radX4 * cosf(angleE), posY5 + radY4 * sinf(angleE));
    }
glEnd();

// Pebble 6
GLfloat posX6 = ((-0.3f / 8.0f) * 0.8f - 0.02f) - 0.5f;    // -0.03f - 0.02f - 0.5f = -0.55f
GLfloat posY6 = ((-0.05f / 8.0f) * 0.8f + 0.02f) - 0.8f;   // -0.005f + 0.02f - 0.8f = -0.785f
GLfloat baseX6 = 0.09f / 8.0f * 0.8f;   // 0.009f
GLfloat baseY6 = 0.07f / 8.0f * 0.8f;   // 0.007f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX6, posY6);  // center
    for (int r = 0; r <= segAmount; r++) {
        GLfloat angleF = r * circleAngle / segAmount;
        radX4 = baseX6 / viewRatio;  // adjust x
        radY4 = baseY6;  // y unscaled
        glVertex2f(posX6 + radX4 * cosf(angleF), posY6 + radY4 * sinf(angleF));
    }
glEnd();

// Pebble 7
GLfloat posX7 = ((-0.4f / 8.0f) * 0.8f - 0.02f) - 0.5f;    // -0.04f - 0.02f - 0.5f = -0.56f
GLfloat posY7 = ((0.5f / 8.0f) * 0.8f + 0.02f) - 0.8f;    // 0.05f + 0.02f - 0.8f = -0.73f
GLfloat baseX7 = 0.06f / 8.0f * 0.8f;   // 0.006f
GLfloat baseY7 = 0.06f / 8.0f * 0.8f;   // 0.006f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX7, posY7);  // center
    for (int s = 0; s <= segAmount; s++) {
        GLfloat angleG = s * circleAngle / segAmount;
        radX4 = baseX7 / viewRatio;  // adjust x
        radY4 = baseY7;  // y unscaled
        glVertex2f(posX7 + radX4 * cosf(angleG), posY7 + radY4 * sinf(angleG));
    }
glEnd();

// Pebble 8
GLfloat posX8 = ((-0.1f / 8.0f) * 0.8f - 0.02f) - 0.5f;    // -0.01f - 0.02f - 0.5f = -0.53f
GLfloat posY8 = ((0.65f / 8.0f) * 0.8f + 0.02f) - 0.8f;   // 0.065f + 0.02f - 0.8f = -0.715f
GLfloat baseX8 = 0.07f / 8.0f * 0.8f;   // 0.007f
GLfloat baseY8 = 0.06f / 8.0f * 0.8f;   // 0.006f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX8, posY8);  // center
    for (int t = 0; t <= segAmount; t++) {
        GLfloat angleH = t * circleAngle / segAmount;
        radX4 = baseX8 / viewRatio;  // adjust x
        radY4 = baseY8;  // y unscaled
        glVertex2f(posX8 + radX4 * cosf(angleH), posY8 + radY4 * sinf(angleH));
    }
glEnd();





glPopMatrix();







glPushMatrix();
glTranslatef(position_upper_scene, 0.0f, 0.0f);



// bush 3

// First Wavy Circle
GLfloat xBase = 0.0f * 0.5f - 0.8f;  // 0.0f - 0.8f = -0.8f
GLfloat yBase = 0.0f * 0.5f + 0.8f;  // 0.0f + 0.8f = 0.8f
GLfloat startRad = 0.15f * 0.5f;  // 0.075f
GLfloat waveAmp = 0.035f;  // maximum wave height
GLfloat waveNum = 18.0f;  // controls number of waves
GLfloat tau = 2.0f * 3.14159265359f;  // 2 * PI
int polyCount = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat screenAspect = 1200.0f / 800.0f;
GLfloat rX, rY;

glColor3f(0.16f, 0.38f, 0.01f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xBase, yBase);  // center of the wavy circle
    for (int a = 0; a <= polyCount; a++) {
        GLfloat alpha = a * tau / polyCount;
        // Combine sine functions for irregular wave sizes
        GLfloat wave1 = (sinf(waveNum * alpha) + 1.0f) / 2.0f;  // primary wave
        GLfloat wave2 = (sinf(waveNum * 1.618f * alpha + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat waveBlend = 0.55f * wave1 + 0.45f * wave2;  // weighted combination
        GLfloat r = startRad + waveAmp * waveBlend;  // radius with uneven waves
        rX = r / screenAspect;  // adjust x for aspect ratio
        rY = r;  // y remains unscaled
        glVertex2f(
            xBase + rX * cosf(alpha),
            yBase + rY * sinf(alpha)
        );
    }
glEnd();

// Second Wavy Circle
GLfloat xLoc = (-0.02f * 0.5f) - 0.8f;  // -0.01f - 0.8f = -0.81f
GLfloat yLoc = (0.03f * 0.5f) + 0.8f;   // 0.015f + 0.8f = 0.815f
GLfloat midRad = 0.13f * 0.5f;  // 0.065f
GLfloat waveTop = 0.035f;  // maximum wave height
GLfloat waveRate4 = 14.0f;  // controls number of waves
GLfloat tau2 = 2.0f * 3.14159265359f;  // 2 * PI
int polyNum = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat viewProp = 1200.0f / 800.0f;
GLfloat rX2, rY2;

glColor3f(0.3f, 0.52f, 0.07f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xLoc, yLoc);  // center of the wavy circle
    for (int b = 0; b <= polyNum; b++) {
        GLfloat beta = b * tau2 / polyNum;
        // Combine sine functions for irregular wave sizes
        GLfloat wave3 = (sinf(waveRate4 * beta) + 1.0f) / 2.0f;  // primary wave
        GLfloat wave4 = (sinf(waveRate4 * 1.618f * beta + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat waveMix2 = 0.55f * wave3 + 0.45f * wave4;  // weighted combination
        GLfloat r = midRad + waveTop * waveMix2;  // radius with uneven waves
        rX2 = r / viewProp;  // adjust x for aspect ratio
        rY2 = r;  // y remains unscaled
        glVertex2f(
            xLoc + rX2 * cosf(beta),
            yLoc + rY2 * sinf(beta)
        );
    }
glEnd();

// Third Wavy Circle
GLfloat xCenter = (-0.02f * 0.5f) - 0.8f;  // -0.01f - 0.8f = -0.81f
GLfloat yCenter = (0.04f * 0.5f) + 0.8f;   // 0.02f + 0.8f = 0.82f
GLfloat coreRad = 0.08f * 0.5f;  // 0.04f
GLfloat waveSize = 0.035f;  // maximum wave height
GLfloat waveFlow = 14.0f;  // controls number of waves
GLfloat tau3 = 2.0f * 3.14159265359f;  // 2 * PI
int polyTotal = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/1000 = 1.2)
GLfloat viewScale2 = 1200.0f / 1000.0f;
GLfloat rX3, rY3;

glColor3f(0.55f, 0.72f, 0.25f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xCenter, yCenter);  // center of the wavy circle
    for (int c = 0; c <= polyTotal; c++) {
        GLfloat gamma = c * tau3 / polyTotal;
        // Combine sine functions for irregular wave sizes
        GLfloat wave5 = (sinf(waveFlow * gamma) + 1.0f) / 2.0f;  // primary wave
        GLfloat wave6 = (sinf(waveFlow * 1.618f * gamma + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat waveMix3 = 0.55f * wave5 + 0.45f * wave6;  // weighted combination
        GLfloat r = coreRad + waveSize * waveMix3;  // radius with uneven waves
        rX3 = r / viewScale2;  // adjust x for aspect ratio
        rY3 = r;  // y remains unscaled
        glVertex2f(
            xCenter + rX3 * cosf(gamma),
            yCenter + rY3 * sinf(gamma)
        );
    }
glEnd();

// Pebbles
GLfloat circleConst = 2.0f * 3.14159265359f;  // 2 * PI
int polyAmount = 100;  // number of segments for smooth rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat viewAdjust = 1200.0f / 800.0f;
GLfloat rX4, rY4;

// Pebble 1
GLfloat locX1 = ((0.2f / 8.0f) * 0.5f - 0.02f) - 0.8f;   // 0.0125f - 0.02f - 0.8f = -0.8075f
GLfloat locY1 = ((0.4f / 8.0f) * 0.5f + 0.02f) + 0.8f;   // 0.025f + 0.02f + 0.8f = 0.845f
GLfloat dimX1 = 0.12f / 8.0f * 0.5f;  // 0.0075f
GLfloat dimY1 = 0.08f / 8.0f * 0.5f;  // 0.005f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(locX1, locY1);  // center
    for (int d = 0; d <= polyAmount; d++) {
        GLfloat angle1 = d * circleConst / polyAmount;
        rX4 = dimX1 / viewAdjust;  // adjust x
        rY4 = dimY1;  // y unscaled
        glVertex2f(locX1 + rX4 * cosf(angle1), locY1 + rY4 * sinf(angle1));
    }
glEnd();

// Pebble 2
GLfloat locX2 = ((-0.2f / 8.0f) * 0.5f - 0.02f) - 0.8f;   // -0.0125f - 0.02f - 0.8f = -0.8325f
GLfloat locY2 = ((0.3f / 8.0f) * 0.5f + 0.02f) + 0.8f;   // 0.01875f + 0.02f + 0.8f = 0.83875f
GLfloat dimX2 = 0.1f / 8.0f * 0.5f;    // 0.00625f
GLfloat dimY2 = 0.08f / 8.0f * 0.5f;   // 0.005f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(locX2, locY2);  // center
    for (int e = 0; e <= polyAmount; e++) {
        GLfloat angle2 = e * circleConst / polyAmount;
        rX4 = dimX2 / viewAdjust;  // adjust x
        rY4 = dimY2;  // y unscaled
        glVertex2f(locX2 + rX4 * cosf(angle2), locY2 + rY4 * sinf(angle2));
    }
glEnd();

// Pebble 3
GLfloat locX3 = ((0.4f / 8.0f) * 0.5f - 0.02f) - 0.8f;    // 0.025f - 0.02f - 0.8f = -0.795f
GLfloat locY3 = ((0.1f / 8.0f) * 0.5f + 0.02f) + 0.8f;    // 0.00625f + 0.02f + 0.8f = 0.82625f
GLfloat dimX3 = 0.08f / 8.0f * 0.5f;   // 0.005f
GLfloat dimY3 = 0.1f / 8.0f * 0.5f;    // 0.00625f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(locX3, locY3);  // center
    for (int f = 0; f <= polyAmount; f++) {
        GLfloat angle3 = f * circleConst / polyAmount;
        rX4 = dimX3 / viewAdjust;  // adjust x
        rY4 = dimY3;  // y unscaled
        glVertex2f(locX3 + rX4 * cosf(angle3), locY3 + rY4 * sinf(angle3));
    }
glEnd();

// Pebble 4
GLfloat locX4 = ((-0.0f / 8.0f) * 0.5f - 0.02f) - 0.8f;   // 0.0f - 0.02f - 0.8f = -0.82f
GLfloat locY4 = ((-0.2f / 8.0f) * 0.5f + 0.02f) + 0.8f;   // -0.0125f + 0.02f + 0.8f = 0.8075f
GLfloat dimX4 = 0.14f / 8.0f * 0.5f;   // 0.00875f
GLfloat dimY4 = 0.1f / 8.0f * 0.5f;    // 0.00625f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(locX4, locY4);  // center
    for (int g = 0; g <= polyAmount; g++) {
        GLfloat angle4 = g * circleConst / polyAmount;
        rX4 = dimX4 / viewAdjust;  // adjust x
        rY4 = dimY4;  // y unscaled
        glVertex2f(locX4 + rX4 * cosf(angle4), locY4 + rY4 * sinf(angle4));
    }
glEnd();

// Pebble 5
GLfloat locX5 = ((0.3f / 8.0f) * 0.5f - 0.02f) - 0.8f;    // 0.01875f - 0.02f - 0.8f = -0.80125f
GLfloat locY5 = ((-0.3f / 8.0f) * 0.5f + 0.02f) + 0.8f;   // -0.01875f + 0.02f + 0.8f = 0.80125f
GLfloat dimX5 = 0.07f / 8.0f * 0.5f;   // 0.004375f
GLfloat dimY5 = 0.05f / 8.0f * 0.5f;   // 0.003125f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(locX5, locY5);  // center
    for (int h = 0; h <= polyAmount; h++) {
        GLfloat angle5 = h * circleConst / polyAmount;
        rX4 = dimX5 / viewAdjust;  // adjust x
        rY4 = dimY5;  // y unscaled
        glVertex2f(locX5 + rX4 * cosf(angle5), locY5 + rY4 * sinf(angle5));
    }
glEnd();

// Pebble 6
GLfloat locX6 = ((-0.3f / 8.0f) * 0.5f - 0.02f) - 0.8f;    // -0.01875f - 0.02f - 0.8f = -0.83875f
GLfloat locY6 = ((-0.05f / 8.0f) * 0.5f + 0.02f) + 0.8f;   // -0.003125f + 0.02f + 0.8f = 0.816875f
GLfloat dimX6 = 0.09f / 8.0f * 0.5f;   // 0.005625f
GLfloat dimY6 = 0.07f / 8.0f * 0.5f;   // 0.004375f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(locX6, locY6);  // center
    for (int i = 0; i <= polyAmount; i++) {
        GLfloat angle6 = i * circleConst / polyAmount;
        rX4 = dimX6 / viewAdjust;  // adjust x
        rY4 = dimY6;  // y unscaled
        glVertex2f(locX6 + rX4 * cosf(angle6), locY6 + rY4 * sinf(angle6));
    }
glEnd();

// Pebble 7
GLfloat locX7 = ((-0.4f / 8.0f) * 0.5f - 0.02f) - 0.8f;    // -0.025f - 0.02f - 0.8f = -0.845f
GLfloat locY7 = ((0.5f / 8.0f) * 0.5f + 0.02f) + 0.8f;    // 0.03125f + 0.02f + 0.8f = 0.85125f
GLfloat dimX7 = 0.06f / 8.0f * 0.5f;   // 0.00375f
GLfloat dimY7 = 0.06f / 8.0f * 0.5f;   // 0.00375f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(locX7, locY7);  // center
    for (int j = 0; j <= polyAmount; j++) {
        GLfloat angle7 = j * circleConst / polyAmount;
        rX4 = dimX7 / viewAdjust;  // adjust x
        rY4 = dimY7;  // y unscaled
        glVertex2f(locX7 + rX4 * cosf(angle7), locY7 + rY4 * sinf(angle7));
    }
glEnd();

// Pebble 8
GLfloat locX8 = ((-0.1f / 8.0f) * 0.5f - 0.02f) - 0.8f;    // -0.00625f - 0.02f - 0.8f = -0.82625f
GLfloat locY8 = ((0.65f / 8.0f) * 0.5f + 0.02f) + 0.8f;   // 0.040625f + 0.02f + 0.8f = 0.860625f
GLfloat dimX8 = 0.07f / 8.0f * 0.5f;   // 0.004375f
GLfloat dimY8 = 0.06f / 8.0f * 0.5f;   // 0.00375f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(locX8, locY8);  // center
    for (int k = 0; k <= polyAmount; k++) {
        GLfloat angle8 = k * circleConst / polyAmount;
        rX4 = dimX8 / viewAdjust;  // adjust x
        rY4 = dimY8;  // y unscaled
        glVertex2f(locX8 + rX4 * cosf(angle8), locY8 + rY4 * sinf(angle8));
    }
glEnd();


glPopMatrix();






glPushMatrix();
glTranslatef(position_upper_scene, 0.0f, 0.0f);



//bush 4











// First Wavy Circle
GLfloat qzOrigin = 0.0f * 0.7f - 0.1f;  // 0.0f - 0.1f = -0.1f
GLfloat pxOrigin = 0.0f * 0.7f + 0.8f;  // 0.0f + 0.8f = 0.8f
GLfloat kjBaseSize = 0.15f * 0.7f;  // 0.105f
GLfloat mnWaveHeight = 0.035f;  // maximum wave height
GLfloat opWaveCycles = 18.0f;  // controls number of waves
GLfloat rsCircleConst = 2.0f * 3.14159265359f;  // 2 * PI
int tuVertexCount = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat vwViewRatio = 1200.0f / 800.0f;
GLfloat xySizeX, xySizeY;

glColor3f(0.16f, 0.38f, 0.01f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(qzOrigin, pxOrigin);  // center of the wavy circle
    for (int ab = 0; ab <= tuVertexCount; ab++) {
        GLfloat cdAngle = ab * rsCircleConst / tuVertexCount;
        // Combine sine functions for irregular wave sizes
        GLfloat efWaveA = (sinf(opWaveCycles * cdAngle) + 1.0f) / 2.0f;  // primary wave
        GLfloat ghWaveB = (sinf(opWaveCycles * 1.618f * cdAngle + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat ijAmpMix = 0.55f * efWaveA + 0.45f * ghWaveB;  // weighted combination
        GLfloat klSize = kjBaseSize + mnWaveHeight * ijAmpMix;  // radius with uneven waves
        xySizeX = klSize / vwViewRatio;  // adjust x for aspect ratio
        xySizeY = klSize;  // y remains unscaled
        glVertex2f(
            qzOrigin + xySizeX * cosf(cdAngle),
            pxOrigin + xySizeY * sinf(cdAngle)
        );
    }
glEnd();

// Second Wavy Circle
GLfloat mnPoint = (-0.02f * 0.7f) - 0.1f;  // -0.014f - 0.1f = -0.114f
GLfloat opPoint = (0.03f * 0.7f) + 0.8f;   // 0.021f + 0.8f = 0.821f
GLfloat pqCoreSize = 0.13f * 0.7f;  // 0.091f
GLfloat rsWavePeak = 0.035f;  // maximum wave height
GLfloat tuWaveFreq = 14.0f;  // controls number of waves
GLfloat vwFullCycle = 2.0f * 3.14159265359f;  // 2 * PI
int xyEdgeCount = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat abDisplayScale = 1200.0f / 800.0f;
GLfloat cdDimX, cdDimY;

glColor3f(0.3f, 0.52f, 0.07f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(mnPoint, opPoint);  // center of the wavy circle
    for (int ef = 0; ef <= xyEdgeCount; ef++) {
        GLfloat ghTheta = ef * vwFullCycle / xyEdgeCount;
        // Combine sine functions for irregular wave sizes
        GLfloat ijWaveC = (sinf(tuWaveFreq * ghTheta) + 1.0f) / 2.0f;  // primary wave
        GLfloat klWaveD = (sinf(tuWaveFreq * 1.618f * ghTheta + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat mnWaveBlend = 0.55f * ijWaveC + 0.45f * klWaveD;  // weighted combination
        GLfloat opDim = pqCoreSize + rsWavePeak * mnWaveBlend;  // radius with uneven waves
        cdDimX = opDim / abDisplayScale;  // adjust x for aspect ratio
        cdDimY = opDim;  // y remains unscaled
        glVertex2f(
            mnPoint + cdDimX * cosf(ghTheta),
            opPoint + cdDimY * sinf(ghTheta)
        );
    }
glEnd();

// Third Wavy Circle
GLfloat rsSource = (-0.02f * 0.7f) - 0.1f;  // -0.014f - 0.1f = -0.114f
GLfloat tuSource = (0.04f * 0.7f) + 0.8f;   // 0.028f + 0.8f = 0.828f
GLfloat vwMainSize = 0.08f * 0.7f;  // 0.056f
GLfloat xyWaveMax = 0.035f;  // maximum wave height
GLfloat abWavePulse = 14.0f;  // controls number of waves
GLfloat cdFullTurn = 2.0f * 3.14159265359f;  // 2 * PI
int efPointCount = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/1000 = 1.2)
GLfloat ghScreenAdjust = 1200.0f / 1000.0f;
GLfloat ijWidthX, ijWidthY;

glColor3f(0.55f, 0.72f, 0.25f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rsSource, tuSource);  // center of the wavy circle
    for (int kl = 0; kl <= efPointCount; kl++) {
        GLfloat mnPhi = kl * cdFullTurn / efPointCount;
        // Combine sine functions for irregular wave sizes
        GLfloat opWaveE = (sinf(abWavePulse * mnPhi) + 1.0f) / 2.0f;  // primary wave
        GLfloat pqWaveF = (sinf(abWavePulse * 1.618f * mnPhi + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat rsWaveMix = 0.55f * opWaveE + 0.45f * pqWaveF;  // weighted combination
        GLfloat tuWidth = vwMainSize + xyWaveMax * rsWaveMix;  // radius with uneven waves
        ijWidthX = tuWidth / ghScreenAdjust;  // adjust x for aspect ratio
        ijWidthY = tuWidth;  // y remains unscaled
        glVertex2f(
            rsSource + ijWidthX * cosf(mnPhi),
            tuSource + ijWidthY * sinf(mnPhi)
        );
    }
glEnd();

// Pebbles
GLfloat klLoopConst = 2.0f * 3.14159265359f;  // 2 * PI
int mnSegmentNum = 100;  // number of segments for smooth rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat opRenderScale = 1200.0f / 800.0f;
GLfloat pqSpanX, pqSpanY;

// Pebble 1
GLfloat rsPosX1 = ((0.2f / 8.0f) * 0.7f - 0.02f) - 0.1f;   // 0.0175f - 0.02f - 0.1f = -0.1025f
GLfloat tuPosY1 = ((0.4f / 8.0f) * 0.7f + 0.02f) + 0.8f;   // 0.035f + 0.02f + 0.8f = 0.855f
GLfloat vwBaseX1 = 0.12f / 8.0f * 0.7f;  // 0.0105f
GLfloat xyBaseY1 = 0.08f / 8.0f * 0.7f;  // 0.007f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rsPosX1, tuPosY1);  // center
    for (int ab = 0; ab <= mnSegmentNum; ab++) {
        GLfloat cdAngle1 = ab * klLoopConst / mnSegmentNum;
        pqSpanX = vwBaseX1 / opRenderScale;  // adjust x
        pqSpanY = xyBaseY1;  // y unscaled
        glVertex2f(rsPosX1 + pqSpanX * cosf(cdAngle1), tuPosY1 + pqSpanY * sinf(cdAngle1));
    }
glEnd();

// Pebble 2
GLfloat efPosX2 = ((-0.2f / 8.0f) * 0.7f - 0.02f) - 0.1f;   // -0.0175f - 0.02f - 0.1f = -0.1375f
GLfloat ghPosY2 = ((0.3f / 8.0f) * 0.7f + 0.02f) + 0.8f;   // 0.02625f + 0.02f + 0.8f = 0.84825f
GLfloat ijBaseX2 = 0.1f / 8.0f * 0.7f;    // 0.00875f
GLfloat klBaseY2 = 0.08f / 8.0f * 0.7f;   // 0.007f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(efPosX2, ghPosY2);  // center
    for (int mn = 0; mn <= mnSegmentNum; mn++) {
        GLfloat opAngle2 = mn * klLoopConst / mnSegmentNum;
        pqSpanX = ijBaseX2 / opRenderScale;  // adjust x
        pqSpanY = klBaseY2;  // y unscaled
        glVertex2f(efPosX2 + pqSpanX * cosf(opAngle2), ghPosY2 + pqSpanY * sinf(opAngle2));
    }
glEnd();

// Pebble 3
GLfloat rsPosX3 = ((0.4f / 8.0f) * 0.7f - 0.02f) - 0.1f;    // 0.035f - 0.02f - 0.1f = -0.085f
GLfloat tuPosY3 = ((0.1f / 8.0f) * 0.7f + 0.02f) + 0.8f;    // 0.00875f + 0.02f + 0.8f = 0.82875f
GLfloat vwBaseX3 = 0.08f / 8.0f * 0.7f;   // 0.007f
GLfloat xyBaseY3 = 0.1f / 8.0f * 0.7f;    // 0.00875f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rsPosX3, tuPosY3);  // center
    for (int ab = 0; ab <= mnSegmentNum; ab++) {
        GLfloat cdAngle3 = ab * klLoopConst / mnSegmentNum;
        pqSpanX = vwBaseX3 / opRenderScale;  // adjust x
        pqSpanY = xyBaseY3;  // y unscaled
        glVertex2f(rsPosX3 + pqSpanX * cosf(cdAngle3), tuPosY3 + pqSpanY * sinf(cdAngle3));
    }
glEnd();

// Pebble 4
GLfloat efPosX4 = ((-0.0f / 8.0f) * 0.7f - 0.02f) - 0.1f;   // 0.0f - 0.02f - 0.1f = -0.12f
GLfloat ghPosY4 = ((-0.2f / 8.0f) * 0.7f + 0.02f) + 0.8f;   // -0.0175f + 0.02f + 0.8f = 0.8025f
GLfloat ijBaseX4 = 0.14f / 8.0f * 0.7f;   // 0.01225f
GLfloat klBaseY4 = 0.1f / 8.0f * 0.7f;    // 0.00875f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(efPosX4, ghPosY4);  // center
    for (int mn = 0; mn <= mnSegmentNum; mn++) {
        GLfloat opAngle4 = mn * klLoopConst / mnSegmentNum;
        pqSpanX = ijBaseX4 / opRenderScale;  // adjust x
        pqSpanY = klBaseY4;  // y unscaled
        glVertex2f(efPosX4 + pqSpanX * cosf(opAngle4), ghPosY4 + pqSpanY * sinf(opAngle4));
    }
glEnd();

// Pebble 5
GLfloat rsPosX5 = ((0.3f / 8.0f) * 0.7f - 0.02f) - 0.1f;    // 0.02625f - 0.02f - 0.1f = -0.09375f
GLfloat tuPosY5 = ((-0.3f / 8.0f) * 0.7f + 0.02f) + 0.8f;   // -0.02625f + 0.02f + 0.8f = 0.79375f
GLfloat vwBaseX5 = 0.07f / 8.0f * 0.7f;   // 0.006125f
GLfloat xyBaseY5 = 0.05f / 8.0f * 0.7f;   // 0.004375f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rsPosX5, tuPosY5);  // center
    for (int ab = 0; ab <= mnSegmentNum; ab++) {
        GLfloat cdAngle5 = ab * klLoopConst / mnSegmentNum;
        pqSpanX = vwBaseX5 / opRenderScale;  // adjust x
        pqSpanY = xyBaseY5;  // y unscaled
        glVertex2f(rsPosX5 + pqSpanX * cosf(cdAngle5), tuPosY5 + pqSpanY * sinf(cdAngle5));
    }
glEnd();

// Pebble 6
GLfloat efPosX6 = ((-0.3f / 8.0f) * 0.7f - 0.02f) - 0.1f;    // -0.02625f - 0.02f - 0.1f = -0.14625f
GLfloat ghPosY6 = ((-0.05f / 8.0f) * 0.7f + 0.02f) + 0.8f;   // -0.004375f + 0.02f + 0.8f = 0.815625f
GLfloat ijBaseX6 = 0.09f / 8.0f * 0.7f;   // 0.007875f
GLfloat klBaseY6 = 0.07f / 8.0f * 0.7f;   // 0.006125f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(efPosX6, ghPosY6);  // center
    for (int mn = 0; mn <= mnSegmentNum; mn++) {
        GLfloat opAngle6 = mn * klLoopConst / mnSegmentNum;
        pqSpanX = ijBaseX6 / opRenderScale;  // adjust x
        pqSpanY = klBaseY6;  // y unscaled
        glVertex2f(efPosX6 + pqSpanX * cosf(opAngle6), ghPosY6 + pqSpanY * sinf(opAngle6));
    }
glEnd();

// Pebble 7
GLfloat rsPosX7 = ((-0.4f / 8.0f) * 0.7f - 0.02f) - 0.1f;    // -0.035f - 0.02f - 0.1f = -0.155f
GLfloat tuPosY7 = ((0.5f / 8.0f) * 0.7f + 0.02f) + 0.8f;    // 0.04375f + 0.02f + 0.8f = 0.86375f
GLfloat vwBaseX7 = 0.06f / 8.0f * 0.7f;   // 0.00525f
GLfloat xyBaseY7 = 0.06f / 8.0f * 0.7f;   // 0.00525f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rsPosX7, tuPosY7);  // center
    for (int ab = 0; ab <= mnSegmentNum; ab++) {
        GLfloat cdAngle7 = ab * klLoopConst / mnSegmentNum;
        pqSpanX = vwBaseX7 / opRenderScale;  // adjust x
        pqSpanY = xyBaseY7;  // y unscaled
        glVertex2f(rsPosX7 + pqSpanX * cosf(cdAngle7), tuPosY7 + pqSpanY * sinf(cdAngle7));
    }
glEnd();

// Pebble 8
GLfloat efPosX8 = ((-0.1f / 8.0f) * 0.7f - 0.02f) - 0.1f;    // -0.00875f - 0.02f - 0.1f = -0.12875f
GLfloat ghPosY8 = ((0.65f / 8.0f) * 0.7f + 0.02f) + 0.8f;   // 0.056875f + 0.02f + 0.8f = 0.876875f
GLfloat ijBaseX8 = 0.07f / 8.0f * 0.7f;   // 0.006125f
GLfloat klBaseY8 = 0.06f / 8.0f * 0.7f;   // 0.00525f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(efPosX8, ghPosY8);  // center
    for (int mn = 0; mn <= mnSegmentNum; mn++) {
        GLfloat opAngle8 = mn * klLoopConst / mnSegmentNum;
        pqSpanX = ijBaseX8 / opRenderScale;  // adjust x
        pqSpanY = klBaseY8;  // y unscaled
        glVertex2f(efPosX8 + pqSpanX * cosf(opAngle8), ghPosY8 + pqSpanY * sinf(opAngle8));
    }
glEnd();




glPopMatrix();








glPushMatrix();
glTranslatef(position_upper_scene, 0.0f, 0.0f);



//bush 5






// First Wavy Circle
GLfloat zkPoint = 0.0f * 0.5f * 1.1f + 0.8f;  // 0.0f + 0.8f = 0.8f
GLfloat fjPoint = 0.0f * 0.5f * 1.1f + 0.8f;  // 0.0f + 0.8f = 0.8f
GLfloat bnRadius = 0.15f * 0.5f * 1.1f;  // 0.0825f
GLfloat wtHeight = 0.035f * 1.1f;  // 0.0385f
GLfloat qsFreq = 18.0f;  // controls number of waves
GLfloat hyCycle = 2.0f * 3.14159265359f;  // 2 * PI
int lpSegments = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat xdRatio = 1200.0f / 800.0f;
GLfloat cvWidth, nmHeight;

glColor3f(0.16f, 0.38f, 0.01f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(zkPoint, fjPoint);  // center of the wavy circle
    for (int qr = 0; qr <= lpSegments; qr++) {
        GLfloat tuAngle = qr * hyCycle / lpSegments;
        // Combine sine functions for irregular wave sizes
        GLfloat yiWave = (sinf(qsFreq * tuAngle) + 1.0f) / 2.0f;  // primary wave
        GLfloat poWave = (sinf(qsFreq * 1.618f * tuAngle + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat asMix = 0.55f * yiWave + 0.45f * poWave;  // weighted combination
        GLfloat dfSize = bnRadius + wtHeight * asMix;  // radius with uneven waves
        cvWidth = dfSize / xdRatio;  // adjust x for aspect ratio
        nmHeight = dfSize;  // y remains unscaled
        glVertex2f(
            zkPoint + cvWidth * cosf(tuAngle),
            fjPoint + nmHeight * sinf(tuAngle)
        );
    }
glEnd();

// Second Wavy Circle
GLfloat ghSpot = (-0.02f * 0.5f * 1.1f) + 0.8f;  // -0.011f + 0.8f = 0.789f
GLfloat jkSpot = (0.03f * 0.5f * 1.1f) + 0.8f;   // 0.0165f + 0.8f = 0.8165f
GLfloat zxMidSize = 0.13f * 0.5f * 1.1f;  // 0.0715f
GLfloat cvPeak = 0.035f * 1.1f;  // 0.0385f
GLfloat bnRate = 14.0f;  // controls number of waves
GLfloat mtCycle = 2.0f * 3.14159265359f;  // 2 * PI
int qzCount = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat weProp = 1200.0f / 800.0f;
GLfloat rtWidth2, yiHeight2;

glColor3f(0.3f, 0.52f, 0.07f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(ghSpot, jkSpot);  // center of the wavy circle
    for (int po = 0; po <= qzCount; po++) {
        GLfloat asAngle = po * mtCycle / qzCount;
        // Combine sine functions for irregular wave sizes
        GLfloat dfWave = (sinf(bnRate * asAngle) + 1.0f) / 2.0f;  // primary wave
        GLfloat ghWave = (sinf(bnRate * 1.618f * asAngle + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat jkMix = 0.55f * dfWave + 0.45f * ghWave;  // weighted combination
        GLfloat zxSize = zxMidSize + cvPeak * jkMix;  // radius with uneven waves
        rtWidth2 = zxSize / weProp;  // adjust x for aspect ratio
        yiHeight2 = zxSize;  // y remains unscaled
        glVertex2f(
            ghSpot + rtWidth2 * cosf(asAngle),
            jkSpot + yiHeight2 * sinf(asAngle)
        );
    }
glEnd();

// Third Wavy Circle
GLfloat cvCore = (-0.02f * 0.5f * 1.1f) + 0.8f;  // -0.011f + 0.8f = 0.789f
GLfloat bnCore = (0.04f * 0.5f * 1.1f) + 0.8f;   // 0.022f + 0.8f = 0.822f
GLfloat mtBaseRad = 0.08f * 0.5f * 1.1f;  // 0.044f
GLfloat qzWaveSize = 0.035f * 1.1f;  // 0.0385f
GLfloat wePulse = 14.0f;  // controls number of waves
GLfloat rtCycle = 2.0f * 3.14159265359f;  // 2 * PI
int yiTotal = 120;  // number of segments for smoother rendering

// Adjust for aspect ratio (1200/1000 = 1.2)
GLfloat asScale = 1200.0f / 1000.0f;
GLfloat dfWidth3, ghHeight3;

glColor3f(0.55f, 0.72f, 0.25f);  // original color
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cvCore, bnCore);  // center of the wavy circle
    for (int jk = 0; jk <= yiTotal; jk++) {
        GLfloat zxAngle = jk * rtCycle / yiTotal;
        // Combine sine functions for irregular wave sizes
        GLfloat mtWave = (sinf(wePulse * zxAngle) + 1.0f) / 2.0f;  // primary wave
        GLfloat qzWave = (sinf(wePulse * 1.618f * zxAngle + 0.5f) + 1.0f) / 2.0f;  // secondary wave with golden ratio frequency
        // Blend for uneven amplitudes (mimics small, big, big, small, small)
        GLfloat weMix = 0.55f * mtWave + 0.45f * qzWave;  // weighted combination
        GLfloat rtSize = mtBaseRad + qzWaveSize * weMix;  // radius with uneven waves
        dfWidth3 = rtSize / asScale;  // adjust x for aspect ratio
        ghHeight3 = rtSize;  // y remains unscaled
        glVertex2f(
            cvCore + dfWidth3 * cosf(zxAngle),
            bnCore + ghHeight3 * sinf(zxAngle)
        );
    }
glEnd();

// Pebbles
GLfloat jkConst = 2.0f * 3.14159265359f;  // 2 * PI
int zxAmount = 100;  // number of segments for smooth rendering

// Adjust for aspect ratio (1200/800 = 1.5)
GLfloat mtAdjust = 1200.0f / 800.0f;
GLfloat qzSpanX, weSpanY;

// Pebble 1
GLfloat rtPosX1 = ((0.2f / 8.0f) * 0.5f * 1.1f) + 0.8f;   // 0.01375f + 0.8f = 0.81375f
GLfloat yiPosY1 = ((0.4f / 8.0f) * 0.5f * 1.1f + 0.02f * 1.1f) + 0.8f;   // 0.0275f + 0.022f + 0.8f = 0.8495f
GLfloat asDimX1 = 0.12f / 8.0f * 0.5f * 1.1f;  // 0.00825f
GLfloat dfDimY1 = 0.08f / 8.0f * 0.5f * 1.1f;  // 0.0055f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rtPosX1, yiPosY1);  // center
    for (int gh = 0; gh <= zxAmount; gh++) {
        GLfloat jkAngle1 = gh * jkConst / zxAmount;
        qzSpanX = asDimX1 / mtAdjust;  // adjust x
        weSpanY = dfDimY1;  // y unscaled
        glVertex2f(rtPosX1 + qzSpanX * cosf(jkAngle1), yiPosY1 + weSpanY * sinf(jkAngle1));
    }
glEnd();

// Pebble 2
GLfloat rtPosX2 = ((-0.2f / 8.0f) * 0.5f * 1.1f - 0.02f * 1.1f) + 0.8f;   // -0.01375f - 0.022f + 0.8f = 0.76425f
GLfloat yiPosY2 = ((0.3f / 8.0f) * 0.5f * 1.1f + 0.02f * 1.1f) + 0.8f;   // 0.020625f + 0.022f + 0.8f = 0.842625f
GLfloat asDimX2 = 0.1f / 8.0f * 0.5f * 1.1f;    // 0.006875f
GLfloat dfDimY2 = 0.08f / 8.0f * 0.5f * 1.1f;   // 0.0055f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rtPosX2, yiPosY2);  // center
    for (int jk = 0; jk <= zxAmount; jk++) {
        GLfloat zxAngle2 = jk * jkConst / zxAmount;
        qzSpanX = asDimX2 / mtAdjust;  // adjust x
        weSpanY = dfDimY2;  // y unscaled
        glVertex2f(rtPosX2 + qzSpanX * cosf(zxAngle2), yiPosY2 + weSpanY * sinf(zxAngle2));
    }
glEnd();

// Pebble 3
GLfloat rtPosX3 = ((0.4f / 8.0f) * 0.5f * 1.1f - 0.02f * 1.1f) + 0.8f;    // 0.0275f - 0.022f + 0.8f = 0.8055f
GLfloat yiPosY3 = ((0.1f / 8.0f) * 0.5f * 1.1f + 0.02f * 1.1f) + 0.8f;    // 0.006875f + 0.022f + 0.8f = 0.828875f
GLfloat asDimX3 = 0.08f / 8.0f * 0.5f * 1.1f;   // 0.0055f
GLfloat dfDimY3 = 0.1f / 8.0f * 0.5f * 1.1f;    // 0.006875f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rtPosX3, yiPosY3);  // center
    for (int jk = 0; jk <= zxAmount; jk++) {
        GLfloat zxAngle3 = jk * jkConst / zxAmount;
        qzSpanX = asDimX3 / mtAdjust;  // adjust x
        weSpanY = dfDimY3;  // y unscaled
        glVertex2f(rtPosX3 + qzSpanX * cosf(zxAngle3), yiPosY3 + weSpanY * sinf(zxAngle3));
    }
glEnd();

// Pebble 4
GLfloat rtPosX4 = ((-0.0f / 8.0f) * 0.5f * 1.1f - 0.02f * 1.1f) + 0.8f;   // 0.0f - 0.022f + 0.8f = 0.778f
GLfloat yiPosY4 = ((-0.2f / 8.0f) * 0.5f * 1.1f + 0.02f * 1.1f) + 0.8f;   // -0.01375f + 0.022f + 0.8f = 0.80825f
GLfloat asDimX4 = 0.14f / 8.0f * 0.5f * 1.1f;   // 0.009625f
GLfloat dfDimY4 = 0.1f / 8.0f * 0.5f * 1.1f;    // 0.006875f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rtPosX4, yiPosY4);  // center
    for (int jk = 0; jk <= zxAmount; jk++) {
        GLfloat zxAngle4 = jk * jkConst / zxAmount;
        qzSpanX = asDimX4 / mtAdjust;  // adjust x
        weSpanY = dfDimY4;  // y unscaled
        glVertex2f(rtPosX4 + qzSpanX * cosf(zxAngle4), yiPosY4 + weSpanY * sinf(zxAngle4));
    }
glEnd();

// Pebble 5
GLfloat rtPosX5 = ((0.3f / 8.0f) * 0.5f * 1.1f - 0.02f * 1.1f) + 0.8f;    // 0.020625f - 0.022f + 0.8f = 0.798625f
GLfloat yiPosY5 = ((-0.3f / 8.0f) * 0.5f * 1.1f + 0.02f * 1.1f) + 0.8f;   // -0.020625f + 0.022f + 0.8f = 0.801375f
GLfloat asDimX5 = 0.07f / 8.0f * 0.5f * 1.1f;   // 0.0048125f
GLfloat dfDimY5 = 0.05f / 8.0f * 0.5f * 1.1f;   // 0.0034375f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rtPosX5, yiPosY5);  // center
    for (int jk = 0; jk <= zxAmount; jk++) {
        GLfloat zxAngle5 = jk * jkConst / zxAmount;
        qzSpanX = asDimX5 / mtAdjust;  // adjust x
        weSpanY = dfDimY5;  // y unscaled
        glVertex2f(rtPosX5 + qzSpanX * cosf(zxAngle5), yiPosY5 + weSpanY * sinf(zxAngle5));
    }
glEnd();

// Pebble 6
GLfloat rtPosX6 = ((-0.3f / 8.0f) * 0.5f * 1.1f - 0.02f * 1.1f) + 0.8f;    // -0.020625f - 0.022f + 0.8f = 0.757375f
GLfloat yiPosY6 = ((-0.05f / 8.0f) * 0.5f * 1.1f + 0.02f * 1.1f) + 0.8f;   // -0.0034375f + 0.022f + 0.8f = 0.8185625f
GLfloat asDimX6 = 0.09f / 8.0f * 0.5f * 1.1f;   // 0.0061875f
GLfloat dfDimY6 = 0.07f / 8.0f * 0.5f * 1.1f;   // 0.0048125f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rtPosX6, yiPosY6);  // center
    for (int jk = 0; jk <= zxAmount; jk++) {
        GLfloat zxAngle6 = jk * jkConst / zxAmount;
        qzSpanX = asDimX6 / mtAdjust;  // adjust x
        weSpanY = dfDimY6;  // y unscaled
        glVertex2f(rtPosX6 + qzSpanX * cosf(zxAngle6), yiPosY6 + weSpanY * sinf(zxAngle6));
    }
glEnd();

// Pebble 7
GLfloat rtPosX7 = ((-0.4f / 8.0f) * 0.5f * 1.1f - 0.02f * 1.1f) + 0.8f;    // -0.0275f - 0.022f + 0.8f = 0.7505f
GLfloat yiPosY7 = ((0.5f / 8.0f) * 0.5f * 1.1f + 0.02f * 1.1f) + 0.8f;    // 0.034375f + 0.022f + 0.8f = 0.856375f
GLfloat asDimX7 = 0.06f / 8.0f * 0.5f * 1.1f;   // 0.004125f
GLfloat dfDimY7 = 0.06f / 8.0f * 0.5f * 1.1f;   // 0.004125f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rtPosX7, yiPosY7);  // center
    for (int jk = 0; jk <= zxAmount; jk++) {
        GLfloat zxAngle7 = jk * jkConst / zxAmount;
        qzSpanX = asDimX7 / mtAdjust;  // adjust x
        weSpanY = dfDimY7;  // y unscaled
        glVertex2f(rtPosX7 + qzSpanX * cosf(zxAngle7), yiPosY7 + weSpanY * sinf(zxAngle7));
    }
glEnd();

// Pebble 8
GLfloat rtPosX8 = ((-0.1f / 8.0f) * 0.5f * 1.1f - 0.02f * 1.1f) + 0.8f;    // -0.006875f - 0.022f + 0.8f = 0.771125f
GLfloat yiPosY8 = ((0.65f / 8.0f) * 0.5f * 1.1f + 0.02f * 1.1f) + 0.8f;   // 0.0446875f + 0.022f + 0.8f = 0.8666875f
GLfloat asDimX8 = 0.07f / 8.0f * 0.5f * 1.1f;   // 0.0048125f
GLfloat dfDimY8 = 0.06f / 8.0f * 0.5f * 1.1f;   // 0.004125f
glColor3f(0.8f, 0.92f, 0.45f);  // light yellowish-green
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rtPosX8, yiPosY8);  // center
    for (int jk = 0; jk <= zxAmount; jk++) {
        GLfloat zxAngle8 = jk * jkConst / zxAmount;
        qzSpanX = asDimX8 / mtAdjust;  // adjust x
        weSpanY = dfDimY8;  // y unscaled
        glVertex2f(rtPosX8 + qzSpanX * cosf(zxAngle8), yiPosY8 + weSpanY * sinf(zxAngle8));
    }
glEnd();








glPopMatrix();


















glColor3f(1.0f, 0.0f, 0.0f);
    char buffer[50];

    if (!game_over) {
        sprintf(buffer, "Score: %d", Scoreer);
    } else {
        sprintf(buffer, "Your Score: %d", Scoreer);
    }
 sprintf(high_score_buffer, "High Score: %d", highScore);
     glRasterPos2f(-0.95f, 0.85f);
    for (int i = 0; high_score_buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, high_score_buffer[i]);

    drawText( buffer, 0.7f, 0.9f);  // Adjust position as needed

    glutSwapBuffers();


    // Display game over message
    if (game_over) {
        glColor3f(1.0f, 0.0f, 0.0f);
        drawText("Game Over! Press 'X' to Exit.", -0.2f, 0.0f);
    }




    glFlush(); // Render now
}

void timer(int value) {
    if (!game_over) {
        Scoreer++;
        }

        else {
        saveHighScore(); // ✅ Save new high score if it's higher
    }
    if (game_over && !sound_stopped)
    {
        stop_sound();
        sound_stopped = true;
    }
        glutPostRedisplay();
        glutTimerFunc(1000, timer, 0);  // Repeat after 1 second

}




void SpecialInput(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            if (car_y_offset + 0.3f <= 0.400f) {
                car_y_offset += 0.3f;
                glutPostRedisplay();
            }
            break;
        case GLUT_KEY_DOWN:
            if (car_y_offset - 0.3f >= -0.600f) {
                car_y_offset -= 0.3f;
                glutPostRedisplay();
            }
            break;
    }
}
void handleCombinedKeypress(unsigned char key, int x, int y)
{

    if (key == 'x' || key == 'X')
    {
        exit(0);
    }
}








void play() {
    loadHighScore();
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(50, 1);
    glutCreateWindow("F1 Car Game");
    glutDisplayFunc(display);
  sound();
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(handleCombinedKeypress);
    glutTimerFunc(100, update, 0);
    glutTimerFunc(100, timer, 0);

    glutMainLoop();

}




}

namespace AirStrike{





#define PI 3.14159265358979323846
#define BULLET_MAX 10

#define MAX_EXPLOSIONS 10
#define CLOUD_COUNT 6

    float explosionX[MAX_EXPLOSIONS];
    float explosionY[MAX_EXPLOSIONS];
    int explosionFrame[MAX_EXPLOSIONS];
    bool explosionActive[MAX_EXPLOSIONS];
    int highScore=0;
    int score = 0;
    GLfloat cloudOffsetX = 0.0f;
    GLfloat forwardPlaneX = 0.0f;
    float centerTextX = -0.18f;

    bool gameOver = false;

    // Bullet states
    const int MAX_BULLETS = 10;
    float bulletX[MAX_BULLETS];
    float bulletY[MAX_BULLETS];
    bool bulletActive[MAX_BULLETS];

    // Reverse plane states (existing)
    float reversePlaneX[6] = { -0.6f, 0.0f, 0.6f, 0.3f, -0.3f ,-0.7f};
    float reversePlaneY[6] = { 1.2f, 1.2f, 1.2f, 3.0f, 5.0f ,1.2f};


     ///-------For Cloud----Array///
    float cloudX[CLOUD_COUNT]     = { -0.9f,  0.2f, -0.7f,  0.4f,  0.8f, -0.95f };
    float cloudY[CLOUD_COUNT]     = { -0.5f,  0.8f,  0.7f, -0.5f,  0.3f,  0.2f };
    float cloudScale[CLOUD_COUNT] = {  1.0f,  0.7f,  1.2f,  0.9f,  0.9f,  0.9f };


    // --------- Fixed the center at (0,0) ----------
    void getSceneCenter(float* centerX, float *centerY) {
        *centerX = 0.0f;
        *centerY = 0.0f;
    }


    // --------- TEXT RENDERING  ----------
    void renderBitmapString(float x, float y, float z, void *font, char *string) {
        char *c;
        glRasterPos3f(x, y, z);
        for (c = string; *c != '\0'; c++) {
            glutBitmapCharacter(font, *c);
        }
    }

    // --------- Circle Drawing ----------
    void drawCircle(float x, float y, float radius, int segments) {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= segments; i++) {
            float angle = 2 * PI * i / segments;
            glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
        }
        glEnd();
    }


    // --------- Cloud Drwaing----------
    void drawCloud(float x, float y, float scale) {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glScalef(scale, scale, 0.0f);

        int segments = 100;
        glColor3f(1.0f, 1.0f, 1.0f);

        drawCircle(0.00f,  0.00f, 0.07f, segments);
        drawCircle(0.07f,  0.05f, 0.10f, segments);
        drawCircle(0.15f,  0.08f, 0.13f, segments);
        drawCircle(0.28f,  0.05f, 0.09f, segments);
        drawCircle(0.38f,  0.02f, 0.07f, segments);
        drawCircle(0.12f, -0.04f, 0.09f, segments);
        drawCircle(0.28f, -0.03f, 0.08f, segments);

        glPopMatrix();
    }


    // ------------ Forward Plane---------//
    void ForwardPlane(float x, float y) {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);

        glBegin(GL_QUADS);

        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex2f(+0.016f, +0.059f);
        glVertex2f(-0.016f, +0.059f);
        glVertex2f(-0.010f, +0.1f);
        glVertex2f(+0.010f, +0.1f);

        glColor3f(0.25f, 0.25f, 0.25f);
        glVertex2f(-0.016f, +0.059f);
        glVertex2f(+0.016f, +0.059f);
        glVertex2f(+0.016f, -0.059f);
        glVertex2f(-0.016f, -0.059f);

        glColor3f(0.35f, 0.42f, 0.40f);
        glVertex2f(-0.015f, +0.02f);
        glVertex2f(-0.015f, +0.07f);
        glVertex2f(-0.07f , +0.04f);
        glVertex2f(-0.07f , -0.01f);

        glVertex2f(+0.015f, +0.02f);
        glVertex2f(+0.015f, +0.07f);
        glVertex2f(+0.07f , +0.04f);
        glVertex2f(+0.07f , -0.01f);

        glColor3f(0.44f, 0.50f, 0.56f);
        glVertex2f(-0.09f , 0.00f);
        glVertex2f(-0.09f , -0.02f);
        glVertex2f(-0.015f, 0.00f);
        glVertex2f(-0.015f, +0.045f);

        glVertex2f(+0.09f , 0.00f);
        glVertex2f(+0.09f , -0.02f);
        glVertex2f(+0.015f, 0.00f);
        glVertex2f(+0.015f, +0.045f);

        glColor3f(0.35f, 0.42f, 0.40f);
        glVertex2f(-0.015f, -0.06f);
        glVertex2f(-0.015f, -0.04f);
        glVertex2f(-0.05f , -0.08f);
        glVertex2f(-0.05f , -0.12f);

        glVertex2f(+0.015f, -0.06f);
        glVertex2f(+0.015f, -0.04f);
        glVertex2f(+0.05f , -0.08f);
        glVertex2f(+0.05f , -0.12f);

        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex2f(-0.016f, -0.06f);
        glVertex2f(+0.016f, -0.06f);
        glVertex2f(+0.026f, -0.08f);
        glVertex2f(-0.026f, -0.08f);

        glColor3f(1.0f, 0.27f, 0.0f);
        glVertex2f(-0.011f, -0.09f);
        glVertex2f(+0.011f, -0.09f);
        glVertex2f(+0.011f, -0.11f);
        glVertex2f(-0.011f, -0.11f);

        glEnd();

        glColor3f(0.8f, 0.8f, 0.8f);
        glBegin(GL_TRIANGLES);
            glVertex2f(+0.011f, +0.10f);
            glVertex2f(-0.011f, +0.10f);
            glVertex2f(0.0f, +0.18f);
        glEnd();

        glPopMatrix();
    }


      //----------Reverse Plane-------------//
    void ReversePlane(float x, float y) {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glScalef(0.7f, 0.7f, 0.0f);

        glBegin(GL_QUADS);

        glColor3f(0.0f, 0.0f, 0.502f);
        glVertex2f(-0.016f, -0.059f);
        glVertex2f(+0.016f, -0.059f);
        glVertex2f(+0.016f, +0.059f);
        glVertex2f(-0.016f, +0.059f);

        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex2f(+0.016f, -0.059f);
        glVertex2f(-0.016f, -0.059f);
        glVertex2f(-0.012f, -0.1f);
        glVertex2f(+0.012f, -0.1f);

        glColor3f(0.47f, 0.53f, 0.60f);
        glVertex2f(-0.015f, +0.03f);
        glVertex2f(-0.015f, -0.02f);
        glVertex2f(-0.07f, +0.01f);
        glVertex2f(-0.07f, +0.06f);

        glVertex2f(+0.015f, +0.03f);
        glVertex2f(+0.015f, -0.02f);
        glVertex2f(+0.07f, +0.01f);
        glVertex2f(+0.07f, +0.06f);

        glColor3f(0.961f, 0.871f, 0.702f);
        glVertex2f(-0.09f, +0.05f);
        glVertex2f(-0.09f, +0.07f);
        glVertex2f(-0.015f, +0.05f);
        glVertex2f(-0.015f, +0.005f);

        glVertex2f(+0.09f, +0.05f);
        glVertex2f(+0.09f, +0.07f);
        glVertex2f(+0.015f, +0.05f);
        glVertex2f(+0.015f, +0.005f);

        glColor3f(0.47f, 0.53f, 0.60f);
        glVertex2f(-0.015f, +0.06f);
        glVertex2f(-0.015f, +0.04f);
        glVertex2f(-0.05f, +0.08f);
        glVertex2f(-0.05f, +0.12f);

        glVertex2f(+0.015f, +0.06f);
        glVertex2f(+0.015f, +0.04f);
        glVertex2f(+0.05f, +0.08f);
        glVertex2f(+0.05f, +0.12f);

        glColor3f(0.25f, 0.25f, 0.25f);
        glVertex2f(-0.016f, +0.06f);
        glVertex2f(+0.016f, +0.06f);
        glVertex2f(+0.026f, +0.08f);
        glVertex2f(-0.026f, +0.08f);

        glColor3f(1.0f, 0.27f, 0.0f);
        glVertex2f(-0.011f, +0.09f);
        glVertex2f(+0.011f, +0.09f);
        glVertex2f(+0.011f, +0.11f);
        glVertex2f(-0.011f, +0.11f);

        glEnd();

        glColor3f(0.5f, 0.5f, 0.0f);
        glBegin(GL_TRIANGLES);
            glVertex2f(-0.011f, -0.1f);
            glVertex2f(+0.011f, -0.1f);
            glVertex2f(0.0f, -0.18f);
        glEnd();

        glPopMatrix();
    }



        ///   ----- score card------///
        void drawScoreText() {
                glColor3f(0.0f, 0.6f, 0.2f);
                glBegin(GL_QUADS);
                glVertex2f(-1.0f, 1.0f);
                glVertex2f(-0.6f, 1.0f);
                glVertex2f(-0.6f, 0.94f);
                glVertex2f(-1.0f, 0.94f);
                glEnd();

            glColor3f(1.0f, 1.0f, 1.0f);
            char scoreText[50];
            sprintf(scoreText, "Score: %d", score);
            renderBitmapString(-0.95f, 0.955f, 0.0f, GLUT_BITMAP_HELVETICA_18, scoreText);

            // === High Score Box ===
            glColor3f(0.2f, 0.4f, 0.8f);
            glBegin(GL_QUADS);
                glVertex2f(-1.0f, 0.93f);
                glVertex2f(-0.6f, 0.93f);
                glVertex2f(-0.6f, 0.87f);
                glVertex2f(-1.0f, 0.87f);
            glEnd();

            glColor3f(1.0f, 1.0f, 1.0f); // White text
            char highScoreText[50];
            sprintf(highScoreText, "High Score: %d", highScore);
            renderBitmapString(-0.95f, 0.885f, 0.0f, GLUT_BITMAP_HELVETICA_18, highScoreText);

            // === Optional Game Over Text ===
            if (gameOver) {
                glColor3f(1.0f, 0.0f, 0.0f);
                renderBitmapString(-0.25f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, (char*)"GAME OVER");
            }
        }


           /// -----move cloud----///
        void updateCloud(int value) {
            if (gameOver) return;

            cloudOffsetX += 0.001f;
            if (cloudOffsetX > 2.2f) {
                cloudOffsetX = -2.2f;
            }
            glutPostRedisplay();
            glutTimerFunc(16, updateCloud, 0);
        }

   ///---move Reverse Plane---///
           int reverseTimer = 0;

        void updateReversePlanes(int value) {
            if (gameOver) return;
            for (int i = 0; i < 6; i++) {
                reversePlaneY[i] -= 0.001f + (i * 0.0002f);
                if (reversePlaneY[i] < -1.2f)
                    reversePlaneY[i] = 1.2f + (rand() % 30) / 10.0f;
            }

            glutPostRedisplay();
            glutTimerFunc(5, updateReversePlanes, 0);
        }





          ///----Hight Score---///
    void loadHighScore() {
            std::ifstream inFile("C:\\Users\\LENOVO\\Documents\\Airshoot.txt");
            if (inFile.is_open()) {
                inFile >> highScore;
                std::cout << "Loaded high score: " << highScore << std::endl;
                inFile.close();
            } else {
                std::cout << "Could not open highScore.txt. Setting high score to 0.\n";
                highScore = 0;
            }
        }

    void saveHighScore() {
            std::ofstream outFile("C:\\Users\\LENOVO\\Documents\\Airshoot.txt");
            if (outFile.is_open()) {
                outFile << highScore;
                std::cout << "Saved high score: " << highScore << std::endl;
                outFile.close();
            } else {
                std::cout << "ERROR: Could not write to highScore.txt!\n";
            }
        }


          ///---sound--//
    void sound() {
            PlaySound("Shooting.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP);
        }


  void checkCollision() {
    if (gameOver) return;

    for (int i = 0; i < 6; i++) {
        float px = reversePlaneX[i];
        float py = reversePlaneY[i];
        float fx = forwardPlaneX;
        float fy = -0.7f;

        if (fabs(px - fx) < 0.14f && fabs(py - fy) < 0.12f) {
         gameOver = true;

      if (score > highScore) {
        highScore = score;
        saveHighScore();
      }

      return;
      }

        for (int j = 0; j < MAX_BULLETS; j++) {
            if (bulletActive[j]) {
                float bx = bulletX[j];
                float by = bulletY[j];

            if (fabs(bx - px) < 0.05f && fabs(by - py) < 0.1f) {
                    // Hit!
                  // Trigger explosion
        for (int k = 0; k < MAX_EXPLOSIONS; k++) {
            if (!explosionActive[k]) {
                explosionX[k] = px;
                explosionY[k] = py;
                explosionFrame[k] = 0;
                explosionActive[k] = true;
                break;
            }
        }

        // Reset plane and bullet
        reversePlaneY[i] = 1.2f + (float)(rand() % 30) / 10.0f;
        bulletActive[j] = false;
        score += 10;
                        }
                    }
                }
    }
}







             ///bullet ///
    void updateBullets(int value) {
                if (gameOver) return;

                for (int i = 0; i < MAX_BULLETS; i++) {
                    if (bulletActive[i]) {
                        bulletY[i] += 0.02f;
                        if (bulletY[i] > 1.2f)
                            bulletActive[i] = false;
                    }
                }

                checkCollision();
                glutPostRedisplay();
                glutTimerFunc(16, updateBullets, 0);
            }

      ///----Animation--- for Bullet---//

    void drawBullets() {
                glColor3f(1.0f, 0.0f, 0.0f);
                glBegin(GL_LINES);
                for (int i = 0; i < BULLET_MAX; i++) {
                    if (bulletActive[i]) {
                        glVertex2f(bulletX[i], bulletY[i]);
                        glVertex2f(bulletX[i], bulletY[i] + 0.03f);
                    }
                }

                glEnd();

            }








          ///---animation---///
    void drawExplosion(float x, float y, int frame) {
            glPushMatrix();
            glTranslatef(x, y, 0.0f);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            int segments = 20;
            float baseRadius = 0.02f + 0.002f * frame;  // Expands with frame
            float alpha = 1.0f - frame / 15.0f;         // Fades out

            glColor4f(1.0f, 0.4f, 0.0f, alpha);
            drawCircle(0.0f, 0.0f, baseRadius, segments);

            glColor4f(1.0f, 1.0f, 0.0f, alpha * 0.6f);
            drawCircle(0.0f, 0.0f, baseRadius * 0.6f, segments);

            glDisable(GL_BLEND);
            glPopMatrix();
        }


    void updateExplosions(int value) {
                for (int i = 0; i < MAX_EXPLOSIONS; i++) {
                    if (explosionActive[i]) {
                        explosionFrame[i]++;
                        if (explosionFrame[i] > 15) {
                            explosionActive[i] = false;
                        }
                    }
                }

                glutPostRedisplay();
                glutTimerFunc(50, updateExplosions, 0);
            }

          ///---show games.
    void showGameOverScreen() {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1.0f, 0.2f, 0.2f);
            glLineWidth(2.0f);
            glBegin(GL_LINE_LOOP);
            glVertex2f(-0.4f, 0.4f);
            glVertex2f( 0.4f, 0.4f);
            glVertex2f( 0.4f,-0.4f);
            glVertex2f(-0.4f,-0.4f);
            glEnd();



           // Title
            glColor3f(0.8f, 0.2f, 0.2f);
            renderBitmapString(centerTextX, 0.20f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, (char*)"GAME OVER");


            char scoreText[50];
            sprintf(scoreText, "Your Score: %d", score);
            glColor3f(1.0f, 1.0f, 1.0f);
            renderBitmapString(centerTextX+0.03f, 0.05f, 0.0f, GLUT_BITMAP_HELVETICA_18, scoreText);

            char highScoreText[50];
            sprintf(highScoreText, "High Score: %d", highScore);
            renderBitmapString(centerTextX+0.03f, -0.05f, 0.0f, GLUT_BITMAP_HELVETICA_18, highScoreText);


            glColor3f(0.0f, 1.0f, 0.0f);
            renderBitmapString(centerTextX-0.05, -0.20f, 0.0f, GLUT_BITMAP_HELVETICA_18, (char*)"Press D to restart the game");

            // Main menu instruction
            glColor3f(0.5f, 0.8f, 1.0f);
            renderBitmapString(centerTextX-0.1, -0.30f, 0.0f, GLUT_BITMAP_HELVETICA_18, (char*)"Press M to return to Main Menu");



            glFlush();
        }



          /// ---- keyBoard----///
    void specialKey(int key, int x, int y) {
            if (gameOver) return;

            if (key == GLUT_KEY_LEFT && forwardPlaneX > -0.95f)
                forwardPlaneX -= 0.05f;
            if (key == GLUT_KEY_RIGHT && forwardPlaneX < 0.95f)
                forwardPlaneX += 0.05f;

            glutPostRedisplay();
        }









    void keyboard(unsigned char key, int x, int y) {
            if (gameOver && (key == 'd' || key == 'D')) {
                score = 0;
                gameOver = false;
                forwardPlaneX = 0.0f;

                for (int i = 0; i < MAX_BULLETS; i++) {
                    bulletActive[i] = false;
                }

                for (int i = 0; i < 6; i++) {
                    reversePlaneY[i] = 1.2f + (rand() % 30) / 10.0f;
                }

                for (int i = 0; i < MAX_EXPLOSIONS; i++) {
                    explosionActive[i] = false;
                    explosionFrame[i] = 0;
                }

                glutTimerFunc(0, updateCloud, 0);
                glutTimerFunc(0, updateReversePlanes, 0);
                glutTimerFunc(0, updateBullets, 0);
                glutTimerFunc(0, updateExplosions, 0);

                glutPostRedisplay();
                return;
            }
            if ((gameOver || !gameOver) && (key == 'm' || key == 'M')) {
//                gameOver = false;
//                glutPostRedisplay();
//                return;
                    exit(0);


            }

            if (key == 32) {
                for (int i = 0; i < MAX_BULLETS; i++) {
                    if (!bulletActive[i]) {
                        bulletX[i] = forwardPlaneX;
                        bulletY[i] = -0.53f;
                        bulletActive[i] = true;
                        sound();
                        break;
                    }
                }
            }

            glutPostRedisplay();
        }





        // --------- DISPLAY FUNCTION ----------
    void display() {

            if (gameOver) {
                showGameOverScreen();
                return;
            }
            glClearColor(0.4f, 0.7f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            float centerX, centerY;
            getSceneCenter(&centerX, &centerY);
            for (int i = 0; i < CLOUD_COUNT; i++) {
            drawCloud(centerX + cloudX[i] + cloudOffsetX, centerY + cloudY[i], cloudScale[i]);
           }

            drawScoreText();
             ///---reverse Plane Update---///
             for (int i = 0; i < 6; i++) {
             ReversePlane(reversePlaneX[i], reversePlaneY[i]);
             }
             ///----main plane----///
             ForwardPlane(forwardPlaneX, -0.7f);

             drawBullets();
            for (int i = 0; i < MAX_EXPLOSIONS; i++) {
            if (explosionActive[i]) {
                drawExplosion(explosionX[i], explosionY[i], explosionFrame[i]);
              }
          }
            glFlush();
        }





    void play() {


        loadHighScore();

        glutInitWindowSize(900, 600);
        glutInitWindowPosition(50, 1);
        glutCreateWindow("Air Strike");
        //glutPositionWindow(450, 150);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glutDisplayFunc(display);
        /// --- timer for cloud----///
        glutTimerFunc(0, updateCloud, 0);
        /// ---for reverse    Plane ---///
        glutTimerFunc(0, updateReversePlanes, 0);
        ///for main plane//
        for (int i = 0; i < BULLET_MAX; i++) {
        bulletActive[i] = false;
        }

        ///-animation--//
        for (int i = 0; i < MAX_EXPLOSIONS; i++) {
        explosionActive[i] = false;
        explosionFrame[i] = 0;
    }


        glutKeyboardFunc(keyboard);
        glutSpecialFunc(specialKey);
        glutTimerFunc(0, updateBullets, 0); /// Bullet animation
        glutTimerFunc(0, updateExplosions, 0);///animation
        glutMainLoop();




    }



}


namespace BirdHunt{



            GLfloat radiusL1 =0.1f;
            GLfloat radiusL2 =0.06f;
            int triangleAmount = 1000;

            GLfloat speed = 0.05f;
            # define PI 3.14159265358979323846
            GLfloat twicePi = 2.0f * PI;

            // Game variables
            GLfloat birdPosition[3] = {0.0f, -0.6f, -1.2f}; // Translation positions for birds
            GLfloat birdY[3] = {0.375f, 0.1f, 0.6f}; // 3 birds at different heights
            GLfloat birdSpeed[3] = {0.003f, 0.002f, 0.0035f}; // Different speeds for variety
            int birdVisible[3] = {1, 1, 1}; // All birds visible initially

            GLfloat cloudPosition[3] = {0.0f, 0.6f, 1.2f}; // Translation positions for clouds
            GLfloat cloudY[3] = {0.75f, 0.6f, 0.9f}; // Different Y positions for clouds
            GLfloat cloudSpeed[3] = {0.001f, 0.0008f, 0.0012f}; // Different cloud speeds

            GLfloat crosshairX = 0.7f;
            GLfloat crosshairY = 0.375f;
            int score = 0;
            int highScore = 0;
            int missCount = 0;
            bool gameOver = false;
            char scoreText[50];
            char highScoreText[50];
            char debugText[100];
            char gameOverText[100];
            char missText[50];

            // Game states
            enum GameState {
                PLAYING,
                GAME_OVER
            };
            GameState currentState = PLAYING;

            void loadHighScore() {


                std::ifstream file("C:\\Users\\LENOVO\\Documents\\testfile.txt"); //E drive e file read write er permission nai ty ei location dewa
                if (file.is_open()) {
                    file >> highScore;
                    file.close();
                    printf("High score loaded: %d\n", highScore);
                } else {
                    highScore = 0;
                    printf("No highscore.txt found, creating new file with score 0\n");
                    // Create the file with initial score of 0
                    std::ofstream newFile("C:\\Users\\LENOVO\\Documents\\testfile.txt");
                    if (newFile.is_open()) {
                        newFile << "0";
                        newFile.close();
                        printf("Created highscore.txt successfully\n");
                    } else {
                        printf("Error: Cannot create highscore.txt file\n");
                    }
                }
            }

            void saveHighScore() {
                if (score > highScore) {
                    highScore = score;


                    std::ofstream file("C:\\Users\\LENOVO\\Documents\\testfile.txt");
                    if (file.is_open()) {
                        file << highScore;
                        file.close();
                        printf("High score saved: %d\n", highScore);
                    } else {
                        printf("Error: Cannot save high score to file\n");
                    }
                }
            }

            void sound()
            {
                PlaySound("g.wav", NULL, SND_ASYNC|SND_FILENAME);
            }

            void resetGame() {
                // Reset bird positions
                birdPosition[0] = 0.0f;
                birdPosition[1] = -0.6f;
                birdPosition[2] = -1.2f;

                // Reset cloud positions
                cloudPosition[0] = 0.0f;
                cloudPosition[1] = 0.6f;
                cloudPosition[2] = 1.2f;

                // Reset game variables
                score = 0;
                missCount = 0;
                gameOver = false;
                currentState = PLAYING;

                // Make all birds visible
                for(int i = 0; i < 3; i++) {
                    birdVisible[i] = 1;
                    birdY[i] = -0.2f + (rand() % 80) * 0.01f; // Random height
                }
            }

            void update(int value) {
                if (currentState == PLAYING) {
                    // Update birds using translation positions
                    for(int i = 0; i < 3; i++) {
                        if(birdVisible[i]) {
                            birdPosition[i] += birdSpeed[i];
                            if(birdPosition[i] > 2.4f) { // Bird flew off screen
                                birdPosition[i] = -1.2f - (i * 0.6f); // Reset to left
                                birdY[i] = -0.2f + (rand() % 80) * 0.01f; // Random height
                            }
                        }
                    }

                    // Update clouds using translation positions
                    for(int i = 0; i < 3; i++) {
                        cloudPosition[i] += cloudSpeed[i];
                        if(cloudPosition[i] > 2.6f) {
                            cloudPosition[i] = -1.3f; // Reset to left side
                        }
                    }
                }

                glutPostRedisplay();
                glutTimerFunc(16, update, 0); // ~60 FPS
            }

            void mouseMotion(int x, int y) {
                if (currentState == PLAYING) {
                    // Convert screen coordinates to OpenGL coordinates
                    crosshairX = (float)(x - 450) / 450.0f; // 450 is half of window width (900)
                    crosshairY = (float)(300 - y) / 300.0f; // 300 is half of window height (600)

                    // Clamp crosshair to screen bounds
                    if(crosshairX > 1.0f) crosshairX = 1.0f;
                    if(crosshairX < -1.0f) crosshairX = -1.0f;
                    if(crosshairY > 1.0f) crosshairY = 1.0f;
                    if(crosshairY < -1.0f) crosshairY = -1.0f;

                    glutPostRedisplay();
                }
            }

            void mouseClick(int button, int state, int x, int y) {
                if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && currentState == PLAYING) {
                    sound(); // Play gunshot sound

                    bool hitBird = false;

                    // Check collision between crosshair and each bird
                    for(int i = 0; i < 3; i++) {
                        if(birdVisible[i]) {
                            // Calculate bird center position (with translation)
                            float birdCenterX = -1.2f + birdPosition[i] + 0.15f; // Base position + translation + center offset
                            float birdCenterY = birdY[i];

                            float distance = sqrt(pow(crosshairX - birdCenterX, 2) + pow(crosshairY - birdCenterY, 2));

                            if(distance < 0.25f) { // Hit tolerance
                                score++;
                                hitBird = true;
                                birdVisible[i] = 0; // Make bird disappear

                                // Respawn bird immediately at left side
                                birdPosition[i] = -1.2f - (i * 0.6f);
                                birdY[i] = -0.2f + (rand() % 80) * 0.01f; // Random height
                                birdVisible[i] = 1;
                                break; // Only hit one bird per shot
                            }
                        }
                    }

                    // If no bird was hit, increment miss counter
                    if (!hitBird) {
                        missCount++;
                        if (missCount >= 2) {
                            currentState = GAME_OVER;
                            saveHighScore();
                        }
                    }

                    glutPostRedisplay();
                }
            }

            void keyboard(unsigned char key, int x, int y) {
                if (currentState == GAME_OVER) {
                    if (key == 'r' || key == 'R') {
                        // Resume/Restart game
                        resetGame();
                    } else if (key == 'q' || key == 'Q') {
                        // Quit game
                        exit(0);
                    }
                }
                glutPostRedisplay();
            }

            void renderBitmapString(float x, float y, float z, void *font, char *string)
            {
                char *c;
                glRasterPos3f(x, y,z);
                for (c=string; *c != '\0'; c++)
                {
                    glutBitmapCharacter(font, *c);
                }
            }

            void display()
            {
                glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                glLoadIdentity();

                /**........................................ Sky Area ...........................................**/
                // Sky background solid blue area separation
                glColor3f(0.2f, 0.6f, 0.9f);
                glBegin(GL_QUADS);
                glVertex2f(-1.0f, -0.4275f);
                glVertex2f(1.0f, -0.4275f);
                glVertex2f(1.0f, 1.0f);
                glVertex2f(-1.0f, 1.0f);
                glEnd();

                /**........................................ Forest Area...........................................**/
                glColor3f(0.2f, 0.5f, 0.2f);//green forest area separation
                glBegin(GL_QUADS);
                glVertex2f(-1.0f, -1.0f);
                glVertex2f(1.0f, -1.0f);
                glVertex2f(1.0f, -0.4275f);
                glVertex2f(-1.0f, -0.4275f);
                glEnd();
               /**....................................... Multiple Trees Drawing ..........................................**/

                 /**....................................... Tree Drawing ..........................................**/

                  /**.......................................  first Tree ..........................................**/
            glLoadIdentity();
             glPushMatrix();
            //middle circle


                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.8f, -0.7125f);


                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.8f + (radiusL1 * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (radiusL1 * sin(i * twicePi / triangleAmount)) );
                }

                glEnd();


              //left circle


                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.9f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.9f + (0.06f * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (0.06f * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                //right side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.7f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.7f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                 //top side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.8f, -0.57f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.8f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.57f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();

                  //left upper side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.86f, -0.627f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.86f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.627f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                  //right  upper side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.74f, -0.627f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.74f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.627f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();





                //==========================================tree wood body drawing=========================

                // Tree wood portion

                glColor3f(0.4f, 0.2f, 0.0f);//wood color
                glBegin(GL_QUADS);
                glVertex2f(-.84, -0.9975);
                glVertex2f(-0.76,-0.9975);
                glVertex2f(-0.76,-0.81225);
                glVertex2f(-.84,-0.81225);
                glEnd();

               /**....................................... Second Tree  ..........................................**/



            //middle circle
            glTranslatef(0.42f, 0.0f, 0.0f);

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.8f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.8f + (radiusL1 * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (radiusL1 * sin(i * twicePi / triangleAmount)) );
                }

                glEnd();


              //left circle


                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.9f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.9f + (0.06f * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (0.06f * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                //right side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.7f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.7f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                 //top side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.8f, -0.57f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.8f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.57f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();

                  //left upper side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.86f, -0.627f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.86f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.627f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                  //right  upper side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.74f, -0.627f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.74f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.627f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();





                //==========================================tree wood body drawing=========================


                glColor3f(0.4f, 0.2f, 0.0f);//wood color
                glBegin(GL_QUADS);
                glVertex2f(-.84, -0.9975);
                glVertex2f(-0.76,-0.9975);
                glVertex2f(-0.76,-0.81225);
                glVertex2f(-.84,-0.81225);
                glEnd();


                 /**....................................... 3rd Tree  ..........................................**/



            //middle circle
            glTranslatef(0.32f, 0.0f, 0.0f);


                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.8f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.8f + (radiusL1 * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (radiusL1 * sin(i * twicePi / triangleAmount)) );
                }

                glEnd();


              //left circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.9f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.9f + (0.06f * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (0.06f * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                //right side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.7f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.7f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                 //top side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.8f, -0.57f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.8f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.57f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();

                  //left upper side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.86f, -0.627f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.86f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.627f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                  //right  upper side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.74f, -0.627f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.74f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.627f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();





                //==========================================tree wood body drawing=========================


                glColor3f(0.4f, 0.2f, 0.0f);//wood color
                glBegin(GL_QUADS);
                glVertex2f(-.84, -0.9975);
                glVertex2f(-0.76,-0.9975);
                glVertex2f(-0.76,-0.81225);
                glVertex2f(-.84,-0.81225);
                glEnd();


                 /**....................................... 4rth Tree  ..........................................**/




            //middle circle
            glTranslatef(0.32f, 0.0f, 0.0f);

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.8f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.8f + (radiusL1 * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (radiusL1 * sin(i * twicePi / triangleAmount)) );
                }

                glEnd();


              //left circle


                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.9f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.9f + (0.06f * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (0.06f * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                //right side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.7f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.7f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                 //top side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.8f, -0.57f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.8f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.57f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();

                  //left upper side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.86f, -0.627f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.86f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.627f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                  //right  upper side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.74f, -0.627f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.74f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.627f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();





                //==========================================tree wood body drawing=========================


                glColor3f(0.4f, 0.2f, 0.0f);//wood color
                glBegin(GL_QUADS);
                glVertex2f(-.84, -0.9975);
                glVertex2f(-0.76,-0.9975);
                glVertex2f(-0.76,-0.81225);
                glVertex2f(-.84,-0.81225);
                glEnd();



                 /**....................................... 5th Tree  ..........................................**/



            //middle circle
            glTranslatef(0.42f, 0.0f, 0.0f);


                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.8f, -0.7125f);


                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.8f + (radiusL1 * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (radiusL1 * sin(i * twicePi / triangleAmount)) );
                }

                glEnd();


              //left circle


                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.9f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.9f + (0.06f * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (0.06f * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                //right side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.7f, -0.7125f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.7f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.7125f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                 //top side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.8f, -0.57f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.8f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.57f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();

                  //left upper side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.86f, -0.627f);

                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.86f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.627f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();


                  //right  upper side circle

                glColor3f(0.0f, 0.6f, 0.0f);//green tree
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-0.74f, -0.627f);
                //int triangleAmount = 1000;
                //GLfloat twicePi = 2.0f * PI;
                for(int i = 0; i <= triangleAmount; i++)
                {
                    glVertex2f( -0.74f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                -0.627f + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                }
                glEnd();





                //==========================================tree wood body drawing=========================

                glColor3f(0.4f, 0.2f, 0.0f);//wood color
                glBegin(GL_QUADS);
                glVertex2f(-.84, -0.9975);
                glVertex2f(-0.76,-0.9975);
                glVertex2f(-0.76,-0.81225);
                glVertex2f(-.84,-0.81225);
                glEnd();
                glPopMatrix();





               /**....................................... Cloud Drawing with glTranslatef ..........................................**/

                // Multiple Moving Clouds using glTranslatef
                for(int cloudIndex = 0; cloudIndex < 3; cloudIndex++) {
                    glPushMatrix();
                    glTranslatef(cloudPosition[cloudIndex], 0.0f, 0.0f);

                    //middle cloud
                    glColor3f(1.0f, 0.95f, 0.8f);//white
                    glBegin(GL_TRIANGLE_FAN);
                    glVertex2f(-0.7f, cloudY[cloudIndex]); //center of the circle
                    for(int i = 0; i <= triangleAmount; i++)
                    {
                        glVertex2f( -0.7f + (radiusL1 * cos(i *  twicePi / triangleAmount)),
                                    cloudY[cloudIndex] + (radiusL1 * sin(i * twicePi / triangleAmount)) );
                    }
                    glEnd();

                    //left side of cloud
                    glColor3f(1.0f, 0.95f, 0.8f);//white
                    glBegin(GL_TRIANGLE_FAN);
                    glVertex2f(-0.8f, cloudY[cloudIndex]); //center of the circle
                    for(int i = 0; i <= triangleAmount; i++)
                    {
                        glVertex2f( -0.8f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                    cloudY[cloudIndex] + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                    }
                    glEnd();

                    //right side of cloud
                    glColor3f(1.0f, 0.95f, 0.8f);//white
                    glBegin(GL_TRIANGLE_FAN);
                    glVertex2f(-0.6f, cloudY[cloudIndex]); //center of the circle
                    for(int i = 0; i <= triangleAmount; i++)
                    {
                        glVertex2f( -0.6f + (radiusL2 * cos(i *  twicePi / triangleAmount)),
                                    cloudY[cloudIndex] + (radiusL2 * sin(i * twicePi / triangleAmount)) );
                    }
                    glEnd();

                    glPopMatrix();
                }

                /**.................................... Multiple Birds Drawing with glTranslatef .......................................**/

                for(int birdIndex = 0; birdIndex < 3; birdIndex++) {
                    if(birdVisible[birdIndex]) {
                        glPushMatrix();
                        glTranslatef(birdPosition[birdIndex], 0.0f, 0.0f);

                        //left side body
                        glColor3f(1.0f, 0.5f, 0.0f);//orange color
                        glBegin(GL_TRIANGLES);
                        glVertex2f(-1.02f, birdY[birdIndex] - 0.15f);
                        glVertex2f(-0.9f, birdY[birdIndex] - 0.075f);
                        glVertex2f(-1.1f, birdY[birdIndex] + 0.025f);
                        glEnd();

                        //middle body
                        glColor3f(1.0f, 0.0f, 0.0f);//red color
                        glBegin(GL_TRIANGLES);
                        glVertex2f(-1.2f, birdY[birdIndex] - 0.25f);
                        glVertex2f(-0.9f, birdY[birdIndex] - 0.075f);
                        glVertex2f(-0.9f, birdY[birdIndex] + 0.075f);
                        glEnd();

                        //right side body
                        glColor3f(1.0f, 0.5f, 0.0f);//orange color
                        glBegin(GL_TRIANGLES);
                        glVertex2f(-1.02f, birdY[birdIndex] - 0.15f);
                        glVertex2f(-0.9f, birdY[birdIndex] - 0.075f);
                        glVertex2f(-1.06f, birdY[birdIndex] + 0.125f);
                        glEnd();

                        //face
                        glColor3f(1.0f, 0.5f, 0.0f);//orange color
                        glBegin(GL_TRIANGLES);
                        glVertex2f(-0.9f, birdY[birdIndex] + 0.025f);
                        glVertex2f(-0.82f, birdY[birdIndex] + 0.025f);
                        glVertex2f(-0.9f, birdY[birdIndex] + 0.075f);
                        glEnd();

                        //eye ball
                        glColor3f(0.0f, 0.0f, 0.0f);//black
                        glBegin(GL_TRIANGLE_FAN);
                        glVertex2f(-0.9f, birdY[birdIndex] + 0.05f); //center of the circle
                        for(int i = 0; i <= triangleAmount; i++)
                        {
                            glVertex2f( -0.9f + (0.01f * cos(i *  twicePi / triangleAmount)),
                                        (birdY[birdIndex] + 0.05f) + (0.01f * sin(i * twicePi / triangleAmount)) );
                        }
                        glEnd();

                        glPopMatrix();
                    }
                }

                /**.................................... CrossCircle Drawing .......................................**/

                if (currentState == PLAYING) {
                    glColor3f(0.0f, 0.0f, 0.0f);//black
                    glLineWidth(2);

                    // Horizontal line
                    glBegin(GL_LINES);
                    glVertex2f(crosshairX - 0.1f, crosshairY);
                    glVertex2f(crosshairX + 0.1f, crosshairY);
                    glEnd();

                    // Vertical line
                    glBegin(GL_LINES);
                    glVertex2f(crosshairX, crosshairY - 0.1f);
                    glVertex2f(crosshairX, crosshairY + 0.1f);
                    glEnd();

                    glBegin(GL_LINE_LOOP);
                    glVertex2f(crosshairX, crosshairY); //center of the circle
                    for(int i = 0; i <= triangleAmount; i++)
                    {
                        glVertex2f( crosshairX + (0.1f * cos(i *  twicePi / triangleAmount)),
                                    crosshairY + (0.1f * sin(i * twicePi / triangleAmount)) );
                    }
                    glEnd();
                }

                // Display UI text
                sprintf(scoreText, "Score: %d", score);
                sprintf(highScoreText, "High Score: %d", highScore);
                sprintf(missText, "Misses: %d/2", missCount);

                glColor3f(0.0f, 0.0f, 0.0f);
                renderBitmapString(-0.9f, 0.9f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, scoreText);
                renderBitmapString(-0.9f, 0.8f, 0.0f, GLUT_BITMAP_HELVETICA_18, highScoreText);
                renderBitmapString(-0.9f, 0.7f, 0.0f, GLUT_BITMAP_HELVETICA_18, missText);

                // Game Over screen
                if (currentState == GAME_OVER) {
                    // Semi-transparent overlay
                    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBegin(GL_QUADS);
                    glVertex2f(-1.0f, -1.0f);
                    glVertex2f(1.0f, -1.0f);
                    glVertex2f(1.0f, 1.0f);
                    glVertex2f(-1.0f, 1.0f);
                    glEnd();
                    glDisable(GL_BLEND);

                    // Game Over text
                    glColor3f(1.0f, 0.0f, 0.0f);
                    renderBitmapString(-0.3f, 0.2f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER!");

                    sprintf(gameOverText, "Final Score: %d", score);
                    glColor3f(1.0f, 1.0f, 1.0f);
                    renderBitmapString(-0.25f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, gameOverText);

                    if (score > highScore) {
                        glColor3f(1.0f, 1.0f, 0.0f);
                        renderBitmapString(-0.3f, -0.1f, 0.0f, GLUT_BITMAP_HELVETICA_18, "NEW HIGH SCORE!");
                    }

                    glColor3f(1.0f, 1.0f, 1.0f);
                    renderBitmapString(-0.4f, -0.3f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Press 'R' to Resume");
                    renderBitmapString(-0.4f, -0.4f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Press 'Q' to Quit");
                }

                glFlush();  // Render now
            }


            //===============================================menubar




            void play()
            {
                // Load high score at startup
                loadHighScore();
                glutInitWindowSize(900, 600);   // Set the window's initial width & height
                glutInitWindowPosition(50, 1);  // Set the window's initial position according to the monitor
                glutCreateWindow("Bird Hunt by Mahir"); // Create a window with the given title
                glutDisplayFunc(display); // Register display callback handler for window re-paint
                glutPassiveMotionFunc(mouseMotion); // Register mouse motion callback
                glutMouseFunc(mouseClick); // Register mouse click callback
                glutKeyboardFunc(keyboard); // Register keyboard callback
                glutTimerFunc(16, update, 0); // Start animation timer
                glutMainLoop();           // Enter the event-processing loop

            }



}


namespace MenuBar{

void renderBitmapString(float x, float y, float z, void *font, char *string)
{
    char *c;
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}


void keyboard(unsigned char key, int x, int y) {

        if (key == '3' || key == '#') {
                BirdHunt::play();
           //go to level3 game
        } else if (key == 'X' || key == 'x') {
            //exit game
            exit(0);
        }else if (key == '2' || key == '@') {
            //go to Level2 game
            AirStrike::play();
        }else if (key == '1' || key == '!') {
            //go to Level2 game
            CarObstacle::play();
        }else if (key == '4' || key == '$') {
            //go to higscore
            HighScores::play();
        }

    //glutPostRedisplay();
}
void display() {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Set background color to dark blue
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

    // Game Title Header
    glColor3f(1.0f, 0.8f, 0.0f); // Golden yellow
    renderBitmapString(-0.5f, 0.8f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "                 GAME MENU");

    // Subtitle
    glColor3f(0.8f, 0.8f, 0.8f); // Light gray
    renderBitmapString(-0.4f, 0.7f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Car Obstacle | Space Shooting | Bird Hunting");

    // Decorative separator
    glColor3f(0.5f, 0.5f, 0.7f); // Light blue
    renderBitmapString(-0.7f, 0.6f, 0.0f, GLUT_BITMAP_HELVETICA_10, "                                  ================================================================");

    // Menu Options Header
    glColor3f(0.0f, 1.0f, 0.5f); // Bright green
    renderBitmapString(-0.25f, 0.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, "MAIN MENU");

    // Menu Options
    glColor3f(1.0f, 1.0f, 1.0f); // White
    renderBitmapString(-0.4f, 0.35f, 0.0f, GLUT_BITMAP_HELVETICA_18, "1. Level 1 (Press 1)");

    glColor3f(1.0f, 1.0f, 1.0f); // White
    renderBitmapString(-0.4f, 0.25f, 0.0f, GLUT_BITMAP_HELVETICA_18, "2. Level 2 (Press 2)");

    glColor3f(1.0f, 1.0f, 1.0f); // White
    renderBitmapString(-0.4f, 0.15f, 0.0f, GLUT_BITMAP_HELVETICA_18, "3. Level (Press 3)");

    glColor3f(1.0f, 1.0f, 1.0f); // White
    renderBitmapString(-0.4f, 0.05f, 0.0f, GLUT_BITMAP_HELVETICA_18, "4. HighScores (Press 4)");



    // Decorative separator
    glColor3f(0.5f, 0.5f, 0.7f); // Light blue
    renderBitmapString(-0.7f, -0.3f, 0.0f, GLUT_BITMAP_HELVETICA_10, "=======================================================================================================");

    // Controls Information
    glColor3f(0.8f, 0.8f, 0.0f); // Yellow
    renderBitmapString(-0.6f, -0.4f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Instructions:");

    glColor3f(0.7f, 0.7f, 0.7f); // Light gray
    renderBitmapString(-0.6f, -0.48f, 0.0f, GLUT_BITMAP_HELVETICA_10, "Press X to EXIT");
    renderBitmapString(-0.6f, -0.54f, 0.0f, GLUT_BITMAP_HELVETICA_10, "Please exit each level Rexecute the program for lavel change");
    renderBitmapString(-0.6f, -0.6f, 0.0f, GLUT_BITMAP_HELVETICA_10, "Level 1 is Carobstacle, Level-2 is AirShoot, Level-3 is BirdHunt");

    // Footer
    glColor3f(0.5f, 0.5f, 0.5f); // Gray
    renderBitmapString(-0.3f, -0.75f, 0.0f, GLUT_BITMAP_HELVETICA_10, "Group-04 | Section-J | AIUB");

    glFlush(); // Render now
}

   void play()
    {
        glutInitWindowSize(900, 600); // Set the window's initial width & height
        glutInitWindowPosition(50, 1);  // Set the window's initial position according to the monitor
        glutCreateWindow("Game Menu"); // Create a window with the given title
        glutDisplayFunc(display); // Register display callback handler for window re-paint

        glutKeyboardFunc(keyboard); // Register keyboard callback
        glutMainLoop(); // Enter the event-processing loop

    }
}

namespace Cover{

        void renderBitmapString(float x, float y, float z, void *font, char *string)
{
    char *c;
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void keyboard(unsigned char key, int x, int y) {

        if (key == 'n' || key == 'N') {
                MenuBar::play();
           //go to level1 game
        } else if (key == 'X' || key == 'x') {
            //go to Level2 game
            exit(0);
        }

    //glutPostRedisplay();
}

void displayCover() {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Set background color to dark blue (matching menu)
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

    // University Header
    glColor3f(1.0f, 0.8f, 0.0f); // Golden yellow (matching menu title)
    renderBitmapString(-0.85f, 0.9f, 0.0f, GLUT_BITMAP_HELVETICA_18, "American International University-Bangladesh");

    // Course Information
    glColor3f(0.8f, 0.8f, 0.8f); // Light gray (matching menu subtitle)
    renderBitmapString(-0.85f, 0.82f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Computer Graphics, Section-J, Group-04");

    // Project Title
    glColor3f(0.0f, 1.0f, 0.5f); // Bright green (matching menu header)
    renderBitmapString(-0.85f, 0.7f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Project: Car Obstacle, Space Shooting, Bird Hunting");

    // Separator line
    glColor3f(0.5f, 0.5f, 0.7f); // Light blue (matching menu separators)
    renderBitmapString(-0.85f, 0.62f, 0.0f, GLUT_BITMAP_HELVETICA_10, "================================================================================");

    // Submitted By Header
    glColor3f(0.8f, 0.8f, 0.0f); // Yellow (matching menu controls header)
    renderBitmapString(-0.85f, 0.55f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Submitted By:");

    // Table Headers
    glColor3f(0.7f, 0.7f, 0.7f); // Light gray (matching menu controls text)
    renderBitmapString(-0.8f, 0.47f, 0.0f, GLUT_BITMAP_HELVETICA_12, "SL   Name                                                ID                     Contribution");
    renderBitmapString(-0.8f, 0.43f, 0.0f, GLUT_BITMAP_HELVETICA_10, "---- ------------------------------- ----------------- -----------------");

    // Student Information
    glColor3f(1.0f, 1.0f, 1.0f); // White (matching menu options)
    renderBitmapString(-0.8f, 0.37f, 0.0f, GLUT_BITMAP_HELVETICA_12, "17   Rezwan Ahmed Prottoy                   22-49034-3              100%");
    renderBitmapString(-0.8f, 0.31f, 0.0f, GLUT_BITMAP_HELVETICA_12, "19   Md Parvez Mia                             22-49155-3               100%");
    renderBitmapString(-0.8f, 0.25f, 0.0f, GLUT_BITMAP_HELVETICA_12, "20   Sajid Hasan Mahir                         22-49485-3               100%");
    renderBitmapString(-0.8f, 0.19f, 0.0f, GLUT_BITMAP_HELVETICA_12, "35   Avijit Sarker                                23-51032-1                100%");
    renderBitmapString(-0.8f, 0.13f, 0.0f, GLUT_BITMAP_HELVETICA_12, "34   Abdullah Al Nayeem                   23-51028-1               100%");

    // Separator line
    glColor3f(0.5f, 0.5f, 0.7f); // Light blue (matching menu separators)
    renderBitmapString(-0.85f, 0.05f, 0.0f, GLUT_BITMAP_HELVETICA_10, "================================================================================");

    // Submitted To Header
    glColor3f(0.8f, 0.8f, 0.0f); // Yellow (matching menu controls header)
    renderBitmapString(-0.85f, -0.03f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Submitted to:");

    // Professor Information
    glColor3f(1.0f, 0.8f, 0.0f); // Golden yellow (matching menu title)
    renderBitmapString(-0.8f, -0.12f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Mahfujur Rahman");
    renderBitmapString(-0.8f, -0.21f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Assistant Professor");

    glColor3f(0.8f, 0.8f, 0.8f); // Light gray (matching menu subtitle)
    renderBitmapString(-0.8f, -0.29f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Department of Computer Science");
    renderBitmapString(-0.8f, -0.36f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Faculty of Science and Technology");
    renderBitmapString(-0.8f, -0.43f, 0.0f, GLUT_BITMAP_HELVETICA_12, "American International University-Bangladesh (AIUB)");

    // Separator line
    glColor3f(0.5f, 0.5f, 0.7f); // Light blue (matching menu separators)
    renderBitmapString(-0.85f, -0.53f, 0.0f, GLUT_BITMAP_HELVETICA_10, "================================================================================");

    // Instructions
    glColor3f(1.0f, 0.0f, 0.0f); // Red (matching menu arrows)
    renderBitmapString(-0.85f, -0.65f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Press \"N\" for Menubar");

    glFlush(); // Render now
}
    void play()
    {
    glutInitWindowSize(900, 600); // Set the window's initial width & height
    glutInitWindowPosition(50, 1);  // Set the window's initial position according to the monitor
    glutCreateWindow("Computer Graphics Project Cover"); // Create a window with the given title
    glutDisplayFunc(displayCover); // Register display callback handler for window re-paint
    glutKeyboardFunc(keyboard);
    glutMainLoop(); // Enter the event-processing loop

    }

}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    Cover::play();

}
