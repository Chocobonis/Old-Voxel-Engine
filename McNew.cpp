#include<GL/glut.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<cstdio>
#include<time.h>
#include<math.h>
#ifdef _WIN32_
#include<windows.h>
#endif
GLuint mc_tex;
#include"Res/GlobalVariables.h"
#include"Res/tiles.c"
#include"Res/Player.h"
#include"Res/Arm.h"
#include"Res/Player.c"
#include"Res/textures.c"
Player steve(50,0,50);
int rx = 0,ry = 0,rz = 0,dir = 0,cb = 1;
#include"Res/mcAuxLib.h"
#include"Res/ModelCube.h"
#include"Res/mcDisplay.h"
int sid = 10;
int main(int argc , char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	std::cout<<"type your seed(blank for default): "<<std::endl;std::cin>>sid;
	mcGenMap(world,prefabs,sid);
	steve.coliderSpw(world);
	ry = steve.getPosition(2);
	PrefabCopy(prefabs,world,47,ry-2,47,1);
	mcCreateWindow(640,480,64,"Minecraft C++ edition Infdev 0.13");
	glInitialize();
	glutDisplayFunc(display);
	glutKeyboardFunc(keybd);
	glutIdleFunc(stand);
	glutMainLoop();
//	system("pause");
	return 0;
}

