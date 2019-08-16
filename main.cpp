#include <windows.h>
#include <MMSystem.h>
#include <glut.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#define ENV_SIZE 20

using namespace std;

///Initial Variable
int TIME = 0;
int msl = 0;
int planeColied = 0;
int planeLife = 20;

///Scoreboard Variable
int hitCount = 0;

float zoom = 4;
float rotX=0, rotY=0, rotZ=0;
float tX=0, tY=0, tZ=-8;
float tZ1=-20, tZ2=-40, tZ3=-60, tZ4=-80, tZ5=-100, tZ6=-120, tZ7=-140, tZ8=-160;
float astPosX[10] = {2, -1, 5, -3, 4, -1, 4, 6, -3};
float astPosY[10] = {1, 4, 2, 2, 5, 3, 1, 2, 3};
float speed = 0.00;
float stablePlane = 0.2;
float msSpd=0.00;
float msX, msY, msZ;
float plnX, plnY;


double angle;


bool missiles[6]  = {true, true, true, true, true, true};
bool isMslhit[10] = {true, true, true, true, true, true, true, true, true, true};
bool envRotation = false;
bool start = false;
bool misPos = true, appearMsl = false;
bool mslTriggered = false;
bool isPlanehit = false;

char snum[5];

void resize(int width, int height){
    const float ar = (float)width / (float)height;

    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 1000.0);
    /*void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
               GLdouble near, GLdouble far)*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawAxes(){
    glColor3f(5.0, 5.0, 5.0);
    glBegin(GL_LINES);{
        //X axes
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(0.5, 9.5, 0);
        glVertex3f(-0.5, 9.5, 0);

        //Y axes
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(0, 10, 0);
        glVertex3f(0, 9, 0);

        //Z axes
        /*glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0, 0, 1000);
        glVertex3f(0, 0, -1000);*/
    }
    glEnd();

}

void developerAxes(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        //X axes
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(1000, 0.0, 0.0);
        glVertex3f(-1000, 0.0, 0.0);

        //Y axes
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0, 1000, 0);
        glVertex3f(0, -1000, 0);

        //Z axes
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0, 0, 1000);
        glVertex3f(0, 0, -1000);
    }
    glEnd();


}


///Weapons Modeling Functions
void missileWings(){
    glPushMatrix();{
            glTranslated(0,0,0.8);
            glScaled(0.1, 0.5, 0.3);
            glRotated(90, 0,1,0);
            glColor3f(1.0,1.0,1.0);
            //Right Wing
            glPushMatrix();{
                glTranslated(0.4, 0.0, 1.5);
                glRotated(-30, 0,1,0);
                glScaled(0.7,0.1,3);
                glRotated(10, 0,1,0);
                glutSolidCube(1);
            }glPopMatrix();
            //Left Wing
            glPushMatrix();{
                glTranslated(0.4, 0, -1.5);
                glRotated(30, 0,1,0);
                glScaled(0.7, 0.1, 3);
                glRotated(-10,0,1,0);
                glutSolidCube(1);
            }glPopMatrix();
        }glPopMatrix();

}
void missile(){
    glPushMatrix();{
        ///Main Body + Head
        glPushMatrix();{
            glRotated(180, 1,0,0);
            ///Main Body
            glPushMatrix();{
                glColor3f(1.0, 1.0, 1.0);
                glTranslated(0,0,0);
                glScaled(0.8,0.8,-10);
                glutSolidTorus(0.1, 0.1, 30, 30);
            }glPopMatrix();

            ///Head
            glPushMatrix();{
                glColor3f(1.0, 0.0, 0.0);
                glTranslated(0,0,0.8);
                glutSolidCone(0.14, 1, 30, 30);
            }glPopMatrix();
        }glPopMatrix();

        ///Back Wings
        glPushMatrix();{
            missileWings();
            glRotated(90, 0,0,1);
            missileWings();
        }glPopMatrix();


    }glPopMatrix();
}
void plane(){
    const double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    double a = t*90.0;

    glPushMatrix();
        glColor3d(0.5, 1, 0);
        glTranslated(0,0,0);
        glScaled(3,0.4,0.5);
        glutSolidSphere(1,30,30);
    glPopMatrix();

    glColor3d(1,0,0);
    glPushMatrix();
        glTranslated(1.7, 0.1, 0);
        glScaled(1.5, 0.7, 0.8);
        glRotated(40, 0,1,0);
        glutSolidSphere(0.45, 30, 30);
    glPopMatrix();

    ///front Wing
    ///Right
    glPushMatrix();{
        glColor3d(0.8,1,0);
        glPushMatrix();{
            glTranslated(0,0,1.2);
            glRotated(-50,0,1,0);
            glScaled(0.7,0.1,3);
            glRotated(25,0,1,0);
            glutSolidCube(1);
        }glPopMatrix();

        //Missiles
        glPushMatrix();{
            glTranslated(-0.3, -0.15, 1.6);
            glRotated(-90, 0,1,0);
            glScaled(0.8, 0.8, 0.8);
            //glutSolidTorus(0.5, 0.5, 50, 50);
            if(missiles[0]){
                missile();
            }
        }glPopMatrix();
        glPushMatrix();{
            glTranslated(-0.2, -0.15, 1.2);
            glRotated(-90, 0,1,0);
            glScaled(0.8, 0.8, 0.8);
            //glutSolidTorus(0.5, 0.5, 50, 50);
            if(missiles[2]){
                missile();
            }
        }glPopMatrix();
        glPushMatrix();{
            glTranslated(-0.1, -0.15, 0.8);
            glRotated(-90, 0,1,0);
            glScaled(0.8, 0.8, 0.8);
            //glutSolidTorus(0.5, 0.5, 50, 50);
            if(missiles[4]){
                missile();
            }
        }glPopMatrix();


        ///Left Wing
        glColor3d(0.8,1,0);
        glPushMatrix();{
            glTranslated(0,0,-1.2);
            glRotated(50,0,1,0);
            glScaled(0.7,0.1,3);
            glRotated(-25,0,1,0);
            glutSolidCube(1);
        }glPopMatrix();

        //Missiles
        glPushMatrix();{
            glTranslated(-0.3, -0.15, -1.6);
            glRotated(-90, 0,1,0);
            glScaled(0.8, 0.8, 0.8);
            //glutSolidTorus(0.5, 0.5, 50, 50);
            if(missiles[1]){
                missile();
            }
        }glPopMatrix();
        glPushMatrix();{
            glTranslated(-0.2, -0.15, -1.2);
            glRotated(-90, 0,1,0);
            glScaled(0.8, 0.8, 0.8);
            //glutSolidTorus(0.5, 0.5, 50, 50);
            if(missiles[3]){
                missile();
            }
        }glPopMatrix();
        glPushMatrix();{
            glTranslated(-0.1, -0.15, -0.8);
            glRotated(-90, 0,1,0);
            glScaled(0.8, 0.8, 0.8);
            //glutSolidTorus(0.5, 0.5, 50, 50);
            if(missiles[5]){
                missile();
            }
        }glPopMatrix();
    }glPopMatrix();

    ///Back Wing

    glPushMatrix();
        glTranslated(-2.8,0,0);
        glScaled(0.8, 0.5, 0.3);

        ///Right Wing
        glColor3d(0.8, 1,0);
        glPushMatrix();
            glTranslated(0.4, 0, 1.5);
            glRotated(-30, 0,1,0);
            glScaled(0.7, 0.1, 3);
            glRotated(10,0,1,0);
            glutSolidCube(1);
        glPopMatrix();

        ///Left Wing
        glPushMatrix();
            glTranslated(0.4, 0, -1.5);
            glRotated(30, 0,1,0);
            glScaled(0.7, 0.1, 3);
            glRotated(-10,0,1,0);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();

    ///Radar
    glColor3d(0.8, 1, 0);
    glPushMatrix();
        glTranslated(-2.7, 0.5, 0);
        glRotated(45, 0,0,1);
        glScaled(0.8, 2, 0.1);
        glRotated(-20, 0,0,1);
        glutSolidCube(0.5);
    glPopMatrix();
}
void gunFire(){

}

///Environment
void environment(){
    glColor3f(0.0,0.5, 0.1);

    glPushMatrix();{
        glTranslated(0,0,0);
        glScaled(ENV_SIZE*2, 0.3, ENV_SIZE*2);
        glutSolidCube(1);
    }glPopMatrix();

    ///Asteroied or Stars
    /*glColor3f(1,1,0);
    glPushMatrix();{
        glTranslated(astPosX[n], astPosY[n], 0);
        glScaled(0.3,0.3,0.3);
        glutSolidDodecahedron();
    }glPopMatrix();*/
}
void stars(int n){
    glColor3f(1,1,0);
    glPushMatrix();{
        glTranslated(astPosX[n], astPosY[n], 0);
        glScaled(0.5,0.5,0.5);
        glutSolidDodecahedron();
    }glPopMatrix();
}


///Scoreboard Functions

void drawScoreboard(){
    glPushMatrix();{
        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();{
           glTranslatef(-4.0, 13.5, 0.0);
           glScalef(2.0, 3.0, 1.0);
            glBegin(GL_POLYGON);{
                glVertex2f(-8.0, -0.3);
                glVertex2f(-8.0, 0.0);
                glVertex2f(-1.0, 0.0);
                //glVertex2f(0.0, -0.5);
                glVertex2f(-2.0, -0.3);
            }glEnd();

        }glPopMatrix();

    }glPopMatrix();
}

///Writing Functions
void drawStrokeText(char* str, int x, int y, int z){
    char *c;
    glPushMatrix();{
        glColor3f(10.0, 10.0, 0.0);
        glTranslatef(x, y+8, z);
        glScaled(0.004f, 0.004f, z);

        for(c=str; *c != '\0'; c++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
        }
    }glPopMatrix();
}
void drawStrokechar(char c, float x, float y, float z){
    glPushMatrix();{
        glColor3f(10.0, 10.0, 0.0);
        glTranslated(x, y+8, z);
        glScaled(0.004f, 0.004f, z);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    }glPopMatrix();
}

void draw(){
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    double a = t*90.0;


    TIME = t;

    ///This code is for the plane to take it in the rotation range
    if(rotX>21)
        rotX=21;
    if(rotX<-21)
        rotX=-21;
    if(rotZ>50)
        rotZ=50;
    if(rotZ<-55)
        rotZ=-55;

    ///Draw the plane and control
    glPushMatrix();{
        glTranslated(0,1,-0.5);
        glRotated(90, 0,1,0);
        glRotated(5,  0,0,1);
        glRotated(rotX, 1,0,0);
        glRotated(rotY, 0,1,0);
        glRotated(rotZ, 0,0,1);

        glScaled(0.4, 0.4, 0.4);
        plane();
    }glPopMatrix();




    ///Environment
    glPushMatrix();{
        glTranslated(tX, tY, tZ);
        environment();
        if(isMslhit[0]){
            stars(0);
        }
    }glPopMatrix();
    glPushMatrix();{
        glTranslated(tX, tY, tZ1);
        environment();
        if(isMslhit[1]){
            stars(1);
        }
    }glPopMatrix();
    glPushMatrix();{
        glTranslated(tX, tY, tZ2);
        environment();
        if(isMslhit[2]){
            stars(2);
        }
    }glPopMatrix();
    glPushMatrix();{
        glTranslated(tX, tY, tZ3);
        environment();
        if(isMslhit[3]){
            stars(3);
        }
    }glPopMatrix();
    glPushMatrix();{
        glTranslated(tX, tY, tZ4);
        environment();
        if(isMslhit[4]){
            stars(4);
        }
    }glPopMatrix();
    glPushMatrix();{
        glTranslated(tX, tY, tZ5);
        environment();
        if(isMslhit[5]){
            stars(5);
        }
    }glPopMatrix();
    /*glPushMatrix();{
        glTranslated(tX, tY, tZ6);
        environment(6);
    }glPopMatrix();
    glPushMatrix();{
        glTranslated(tX, tY, tZ7);
        environment(7);
    }glPopMatrix();
    glPushMatrix();{
        glTranslated(tX, tY, tZ8);
        environment(8);
    }glPopMatrix();*/


    ///Draw the Missile
    if(appearMsl){
            msX = tX;
            msX*=-1;
            msY = tY;
            msY*=-1;
            if(misPos == true){
            //For Right-Wing Missile
                if(msZ >= -110){
                        glPushMatrix();{
                            //glTranslated(0.5, 0.8, -1.0);
                            glTranslated((msX/100)+0.5,(msY/100)+0.8, msZ);
                            //printf("msX: %f astPosX[0]: %f msY: %f astPosY[0]: %f msZ: %f tZ: %f\n", msX, astPosX[0],  msY, astPosY[0], msZ, tZ);
                            //glTranslated(tX, tY, msZ);
                            glRotated(5,  0,0,1);

                            glScaled(0.4, 0.4, 0.4);
                            missile();
                    }glPopMatrix();
                }else{
                    mslTriggered = false;
                }
            }else if(misPos == false){
                //For Left-Wing Missile
                if(msZ >= -110){
                        glPushMatrix();{
                            //glTranslated(-0.5, 0.8, -1.0);
                            glTranslated((msX/100)+0.5*(-1), (msY/100)+0.8, msZ);
                            glRotated(5, 0,0,1);
                            glScaled(0.4,0.4,0.4);
                            missile();
                    }glPopMatrix();
                }else{
                    mslTriggered = false;
                }
            }
        }


    //This code is for the plane to take it in the game window
    if(tX>=6.1)
        tX = 6.1;
    if(tX<=-6.1)
        tX=-6.1;
    if(tY>0.1)
        tY= 0.1;
    if(tY<-15)
        tY= -15;

    //This code is for go forwarding of the plane
    tZ+=speed;
    tZ1+=speed;
    tZ2+=speed;
    tZ3+=speed;
    tZ4+=speed;
    tZ5+=speed;
    tZ6+=speed;
    tZ7+=speed;
    tZ8+=speed;

    //Missile Speed
    msZ+=msSpd;
    msZ*=-1;
    if(msZ <= -110){
        appearMsl = false;
        msX = 0.0;
        msY = 0.0;
        msZ = 0.0;
    }

    //printf("msZ: %f\n",msZ);

    //This code is for redraw the whole environment over and over again
    if(tZ>=20){
        tZ=-110;
        isMslhit[0] = true;
    }
    if(tZ1>=20){
        tZ1=-110;
        isMslhit[1] = true;
    }
    if(tZ2>=20){
        tZ2=-110;
       isMslhit[2] = true;
    }
    if(tZ3>=20){
        tZ3=-110;
        isMslhit[3] = true;
    }
    if(tZ4>=20){
        tZ4=-110;
        isMslhit[4] = true;
    }
    if(tZ5>=20){
        tZ5=-110;
        isMslhit[5] = true;
    }
    /*if(tZ6>=20)tZ6=-110;
    if(tZ7>=20)tZ7=-110;
    if(tZ8>=20)tZ8=-110;*/


    //This code is for manage the plane rotation stable
    if(rotX>0)rotX-=stablePlane;
    if(rotX<0)rotX+=stablePlane;
    if(rotY>0)rotY-=stablePlane;
    if(rotY<0)rotY+=stablePlane;
    if(rotZ>0)rotZ-=stablePlane;
    if(rotZ<0)rotZ+=stablePlane;


    ///This code is for missile hit the astoried or not
    //printf("msX: %f msY: %f msZ: %f tZ: %f\n",msX, msY, msZ, tZ);
    //if(msX == astPosX[0] && msY == astPosY[0] && tZ >= msZ){
    if(msX >= 1.20 && msX <= 2.50 && msY >= 0.00 && msY <= 1.80){  //X= 2, Y = 1
        if(tZ >= msZ && tZ <= msZ+0.40){
            isMslhit[0] = false;
            printf("Star 0 is Hit\n");
            hitCount++;
            printf("Score: %d\n",hitCount);
        }
    }if(msX <= -0.50 && msX >= -1.50 && msY >=2.00 && msY <= 4.50){ //X= -1, Y= 4
        if(tZ1 >= msZ && tZ1 <= msZ+0.40){
            isMslhit[1] = false;
            printf("Star 1 is Hit\n");
            hitCount++;
            printf("Score: %d\n",hitCount);
        }
    }if(msX >= 3.50 && msX <= 6.00 && msY >= 1.20 && msY <= 2.50){ //X = 5, Y= 2
        if(tZ2 >= msZ && tZ2 <= msZ+0.40){
            isMslhit[2] = false;
            printf("Star 2 is Hit\n");
            hitCount++;
            printf("Score: %d\n",hitCount);
        }
    }if(msX <= -1.00 && msX >= -5.00 && msY >= 0.00 && msY <= 3.00){ //X = -3, Y = 2
        if(tZ3 > msZ && tZ3 <= msZ+0.40){
            isMslhit[3] = false;
            printf("Star 4 is Hit\n");
            hitCount++;
            printf("Score: %d\n",hitCount);
        }
    }if(msX>=2.00 && msX <= 5.00 && msY >= 3.50 && msY<=6.00){ //X = 4 Y = 5
        if(tZ4 > msZ && tZ4 <= msZ+0.40){
                isMslhit[4] = false;
                printf("Star 5 is Hit\n");
                hitCount++;
                printf("Score: %d\n",hitCount);
        }
    }if(msX>=-3.00 && msX <= 3.00 && msY>=2.00 && msY<=4.50){ //X=-1, Y= 3
        if(tZ5 > msZ && tZ5 <= msZ+0.40){
            isMslhit[5] = false;
            printf("Star 6 is Hit\n");
            hitCount++;
            printf("Score: %d\n",hitCount);
        }
    }

    ///Check if the plane collide or Not
    //printf("tX: %f tY: %f tZ: %f\n",tX, tY, tZ);
    /*plnX = tX;
    plnX*=-1;
    plnY = tY;
    plnY*=-1;
    //printf("plnX: %f plnY: %f tZ: %f\n", plnX, plnY, tZ);
    if(isPlanehit == false){
        if(plnX >= 0.20 && plnX <=3.80 && plnY<=0.70 && plnY>=-0.10 && tZ >= 0.00 && tZ <= 3.00){
            printf("Checked\n");
            isPlanehit = true;
        }
    }*/


    /*if(isPlanehit == true){
        planeLife--;
        printf("Plane Life: %d",planeLife);
        isPlanehit = false;
    }*/





   //printf("tZ: %f msZ:%f\n",tZ,msZ);

    //Increment the speed of of the Game
    speed+=0.0002;
    if(speed>=0.15){
        speed = 0.15;
        //printf("Plane speed: %f\n",speed);
    }

    //Missile Speed
    if(mslTriggered == true){
        msSpd += 0.4;
    }
    //printf("Missile Speed: %f\n",msSpd);
            /*if(msSpd >= 0.4){
                msSpd = 0.4;
            }*/
    //printf("tX: %f tY:%f tZ1:%f msX: %f msY:%f  msZ:%f\n",tX, tY, tZ1, msX, msY, msZ);

    //drawScoreboard();

}

void display(){
    const double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    double a = t*90.0;
    double gameIntro = a;

    if(!envRotation){
        a = 0;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0,10.0,20.0,    0.0, 4.0, 0.0,  0.0, 1.0, 0.0);
    //gluLookAt(0.0,10.0,10.0,    0.0, 04.0, 0.0,  0.0, 1.0, 0.0);

    if(start){  //Initially 'start is false'
        //developerAxes();
        glPushMatrix();{
            glTranslated(0.0, -1.0, 0.0);
            drawAxes();
        }glPopMatrix();
            glPushMatrix();{
                glTranslated(0,0,0);
                glScaled(zoom, zoom, zoom);
                glRotated(a, 0,1,0);
                //glRotated(angle, 0,1,0);
                draw();
            }glPopMatrix();
            glPushMatrix();{
                //glScaled(1.0, 1.0, 2.0);
                //drawScoreboard();
                drawStrokeText("Your Score: ", -17.5,5,0);
                itoa(hitCount, snum, 10);
                drawStrokeText(snum, -13, 5, 0);
                if(msl >= 6){
                    drawStrokeText("Reload...!!!", -1,0,0);
                    drawStrokeText("Press 'R'", -1,-1,0);
                }
            };glPopMatrix();


    }else{
        glPushMatrix();{
            glTranslated(0,3,0);
            glRotated(gameIntro,0,1,0);
            glScaled(1.5,1.5,1.5);
            plane();
        }glPopMatrix();
        drawStrokeText("Press 'G' for start Game...!!!!", -3, -2, 0);
    }



    glutSwapBuffers();

}

void keyBoard(unsigned char key, int x, int y){
    float frac = 0.2;
    float rotFrac = 1;

    switch(key){
        case 'a':
            tX+=frac;
            rotX-=rotFrac*3;
            rotY+=rotFrac/2;
            break;
        case 'd':
            tX-=frac;
            rotX+=rotFrac*3;
            rotY-=rotFrac/2;
            break;
        case 's':
            tY+=frac;
            rotZ-=rotFrac;
            break;
        case 'w':
            tY-=frac;
            rotZ+=rotFrac;
            break;
        case 'g':
            start = true;
            break;
        case 'm':
            start = false;
            break;
        case 'f':
            //sndPlaySound("fire_2.wav", SND_ASYNC);
            mslTriggered = true;
            msSpd = 0.0;
            msZ = 0.0;
            missiles[msl] = false;
            msl++;
            if(msl <= 6){
                if(msl%2==0){
                    misPos = false;
                }else{
                    misPos = true;
                }
                appearMsl = true;
            }else{
                appearMsl = false;
            }
            break;
        case 'r':
            msl = 0;
            for(int i=0; i<6; i++){
                missiles[i] = true;
            }
            appearMsl = true;
            break;
        case 't':
            envRotation = true;
            break;
        case 'u':
            envRotation = false;
            break;

        default:

            break;
    }
}

void specialKeyListener(int key, int x, int y){
    float frac = 0.2;
    float rotFrac = 1;
    switch(key){
        case GLUT_KEY_UP:
            tY-=frac;
            rotZ+=rotFrac;
            break;

        case GLUT_KEY_DOWN:
            tY+=frac;
            rotZ-=rotFrac;
            break;
        case GLUT_KEY_RIGHT:
            tX-=frac;
            rotX+=rotFrac*3;
            rotY-=rotFrac/2;
            break;
        case GLUT_KEY_LEFT:
            tX+=frac;
            rotX-=rotFrac*3;
            rotY+=rotFrac/2;
            break;

        default:

            break;
    }
}

void animate(){
    glutPostRedisplay();
}

const GLfloat light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat light_deffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[]  = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[]  = {2.0f, 5.0f, 5.0f, 0.0f};

const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_deffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shiness[] = {100.0f};

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1366, 720);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    glutCreateWindow("Air Strike");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(keyBoard);
    glutSpecialFunc(specialKeyListener);

    sndPlaySound("falcon.wav", SND_ASYNC | SND_LOOP);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);


    glutMainLoop();

    return EXIT_SUCCESS;
}
