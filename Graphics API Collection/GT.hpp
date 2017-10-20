#pragma once
#ifndef GT_HPP
#define GT_HPP
#include "GT.hpp"
#include <iostream>
//glut

#include "PM.hpp"

//#include "glew.h"
#include "glut.h"
using namespace std;
#pragma comment(lib,"glut.lib")
#pragma comment(lib,"glut32.lib")
//#pragma comment(lib,"glew32.lib")
//#pragma comment(lib,"glew32s.lib")



#define FileName "1.bmp"
static GLint imagewidth;
static GLint imageheight;
static GLint pixellength;
static GLubyte* pixeldata;

//Picture demo
void displaypicture(void);

void read_bmp_file(int argc, char *argv[]);

//GL define
//²èºødemo

void initialize();;
static void resize(int width, int height);
static void displaychahu(void);
void Chahu(int argc, char *argv[]);

//Glew:














#endif // !GRAPHIC_TEMPLATE
