class Player{
	private:
		int   px = 0,py = 0,pz = 0;
		float xt = 0,yt = 0,zt = 0;int c;
		int   view = 0,dir = 0,health = 5,spc = 5;
		int   invetory[5];
	public:
	 Player(int,int,int); // player constructor
	 void setPosition(int,int,int); // set position x y z
	 void setViewSpot(char); // set rotation top-down
	 void setRotation(int); // set rotation left-right
	 int  getPosition(int); //get where player is
	 int  getRotation(int); //get where player is looking
	 void setCamera(); // draw player on game
	 void coliderSpw(int map[100][255][100]); // move player always at the top
	 void moveForward(); // go to the front
	 void damage(int map[100][255][100]); // damage player
	 void setGravity(int map[100][255][100]); // move player down
	 void drawHand();
	 void drawGui();
	 void regen(); // heal player
	 void rayCast(int map[100][255][100],int,char,int); // place or break block
};

Player::Player(int _x, int _y, int _z){ // just the constructor
	px = _x;
	py = _y;
	pz = _z;
}

void Player::setPosition(int _x, int _y, int _z){
	px = _x; // set x position to
	py = _y; // set y position to
	pz = _z; // set z position to
}

void Player::setRotation(int angle){
	dir = angle; // set view angle
	if(dir >= 360){
		dir = 0;
	}else if(dir < 0||dir == -1){
		dir = 315;
	}
}

void Player::setViewSpot(char d){
	switch(d){
		case 'u':if(view <  5){view++;}break;
		case 'd':if(view > -5){view--;}break;
	}
}

int Player::getRotation(int rt){
	switch(rt){
		case 1:return dir;break; // get which angle player is looking at
		case 2:return view;break; // get what layer player is looking at
	}
}

int Player::getPosition(int pos){
	switch(pos){
		case 1:return px;break; // get x position from player
		case 2:return py;break; // get y position from player
		case 3:return pz;break; // get z position from player
	}
}

void Player::setCamera(){
	xt = px-sin((dir * 3.14159)/180);
	yt = py+view;
	zt = pz+cos((dir * 3.14159)/180);
	gluLookAt(px,py,pz,xt,yt,zt,0,1,0);
}

void Player::moveForward(){
	// line
	 if(dir == 0){  pz++;} // front
	 if(dir == 180){pz--;} // back
	 if(dir == 90){ px--;} // left
	 if(dir == 270){px++;} // right
	// diagonal
	 if(dir > 0  && dir <   90){pz++;px--;}
	 if(dir > 90  && dir < 180){pz--;px--;}
	 if(dir > 180 && dir < 270){pz--;px++;}
	 if(dir > 270 && dir < 360){pz++;px++;}
}
void Player::coliderSpw(int map[100][255][100]){
	while(map[px][py-1][pz] != 0||map[px][py][pz] != 0){
		py++;
	}
}

void Player::setGravity(int map[100][255][100]){
	if(map[px][py-2][pz] == 0){
		py--;
		usleep(100000);
		c++;
		std::cout<<"fall: "<<c<<"\n";
	}
	if(map[px][py-2][pz] != 0){
		if(c >= 4){
		 damage(map);
		}
		c = 0;
	}
}

void Player::drawHand(){
	glPushMatrix();
	 glTranslatef(px-sin(dir),py-0.5,pz+cos(dir));
	 glRotatef(0,-dir,0,1);
	 glScalef(0.05,0.05,0.05);
	 mcArm(0,0);
	glPopMatrix();
}

void Player::rayCast(int map[100][255][100],int _dst,char act,int brick){
	int cx,cz,oldx,oldz;
	for(int d = 1; d < _dst; d++){
		cx = px-(roundf(sin((dir*3.14159)/180)))*d;
		cz = pz+(roundf(cos((dir*3.14159)/180)))*d;
		if(map[cx][py+view][cz] != 0){
			if(act == 'b'){
				map[cx][py+view][cz] = 0;
			}
			if(act == 'p'){
				map[oldx][py+view][oldz] = brick;
			}
			break;
		}else{
			if(act == 'b' && d == _dst-1){
				map[cx][py+view][cz] = 0;
			}
			if(act == 'p' && d == _dst-1){
				map[cx][py+view][cz] = brick;
			}
		}
	    oldx = cx;oldz = cz;
	}
}

void Player::drawGui(){
	float x = 0.333333f,y = 0.833f;
	float x1 = 0.333333f,y1 = 0.666f;
	float x2 = 0.333333f,y2 = 0.500f;
	float fx = 0.5,fy = -0.5;
	int resh;
	glPushMatrix();
	 	glTranslatef(px,py,pz);
	 	glRotatef(dir,0,-dir,1);
	 	resh = spc-health;
	 	for(int i = 0; i < health;i++){
		 glBegin(GL_QUADS);
		  glTexCoord2d(x+0.32,y+0.0); glVertex3f(fx+0.05, fy-0.05, 1.3);
     	  glTexCoord2d(x+0.32,y+0.16);glVertex3f(fx-0.05, fy-0.05, 1.3);
     	  glTexCoord2d(x+0.16,y+0.16);glVertex3f(fx-0.05, fy+0.05, 1.3);
     	  glTexCoord2d(x+0.16,y+0.0); glVertex3f(fx+0.05, fy+0.05, 1.3);
     	 glEnd();
     	fx-=0.1;
		}
		for(int i = 0; i < resh;i++){
		 glBegin(GL_QUADS);
		  glTexCoord2d(x1+0.32,y1+0.0); glVertex3f(fx+0.05, fy-0.05, 1.3);
     	  glTexCoord2d(x1+0.32,y1+0.16);glVertex3f(fx-0.05, fy-0.05, 1.3);
     	  glTexCoord2d(x1+0.16,y1+0.16);glVertex3f(fx-0.05, fy+0.05, 1.3);
     	  glTexCoord2d(x1+0.16,y1+0.0); glVertex3f(fx+0.05, fy+0.05, 1.3);
     	 glEnd();
     	fx-=0.1;
		}
		fx = 0.5;fy = -0.629;
		for(int i = 0; i < 5; i++){
		 glBegin(GL_QUADS);
		  glTexCoord2d(x2+0.32,y2+0.0); glVertex3f(fx+0.08, fy-0.08, 1.3);
     	  glTexCoord2d(x2+0.32,y2+0.16);glVertex3f(fx-0.08, fy-0.08, 1.3);
     	  glTexCoord2d(x2+0.16,y2+0.16);glVertex3f(fx-0.08, fy+0.08, 1.3);
     	  glTexCoord2d(x2+0.16,y2+0.0); glVertex3f(fx+0.08, fy+0.08, 1.3);
     	 glEnd();
     	fx-=0.152;
		}
	glPopMatrix();
}

void Player::damage(int map[100][255][100]){
	health--;
	if(health <= 0){
		map[px][py-1][pz] = 12;
		px = 50;
		pz = 50;
		coliderSpw(map);
		health = 5;
	}
}

void Player::regen(){
	health++;
	if(health > 5){
		health = 5;
	}
}
