void mcCreateWindow(int wdth, int hght, int pos,char *name){
	glutInitWindowSize(wdth,hght);
	glutInitWindowPosition(pos,pos);
	glutCreateWindow(name);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);
}

void stand(){
	usleep(33);
	glutPostRedisplay();
}

void mcFog(float strt , float end ,float dens){
	GLuint filter;
	GLfloat FogColor[4] = {0.8,0.8,1.0,1.0};
	glClearColor(0.8,0.8,1.0,0);
	glFogi(GL_FOG_MODE , GL_LINEAR);
	glFogfv(GL_FOG_COLOR , FogColor);
	glFogf(GL_FOG_DENSITY , dens );
	glHint(GL_FOG_HINT , GL_DONT_CARE);
	glFogf(GL_FOG_START , strt );
	glFogf(GL_FOG_END , end);
	glEnable(GL_FOG);
}

void keybd(unsigned char key, int x, int y){
	switch(key){
		case 'f':exit(1);break;
		case 'a':dir = dir-15;steve.setRotation(dir);break;
		case 'd':dir = dir+15;steve.setRotation(dir);break;
		case 'w':steve.moveForward();steve.coliderSpw(world);break;
		case ' ':steve.setPosition(rx,ry+2,rz);break;
		case 'e':steve.setViewSpot('u');break;
		case 'q':steve.setViewSpot('d');break;
		case 'x':steve.rayCast(world,4,'b',cb);break;
		case 'z':steve.rayCast(world,4,'p',cb);break;
		case 'i':steve.damage(world);break;
		case 'k':steve.regen();break;
		case '1':cb = 1;break;case '2':cb = 2;break;case '3':cb = 3;break;case '4':cb = 4;break;case '5':cb = 5;break;case '6':cb = 6;break;
		default:std::cout<<"rot: "<<dir<<" X:"<<rx<<"Z: "<<rz<<std::endl;break;
	}
}

int createTexture(int bpp,int width,int height,const void *data){
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
        gluBuild2DMipmaps( GL_TEXTURE_2D, bpp, width ,height,GL_RGBA, GL_UNSIGNED_BYTE,data );
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void glInitialize(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glClearColor(0.7,0.7,1.0,0.0);
	glLoadIdentity();
	gluPerspective(60,1,0.1,50);
        glGenTextures(1,&mc_tex);
        glBindTexture(GL_TEXTURE_2D,mc_tex);
        createTexture(Mc_Textures.bytes_per_pixel,Mc_Textures.width,Mc_Textures.height,Mc_Textures.pixel_data);
}
