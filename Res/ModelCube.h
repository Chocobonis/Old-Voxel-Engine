void mcCube(int map[100][255][100],int px,int py,int pz,float x,float y,float s){
	glBegin(GL_QUADS); 
	 if(map[px][py+1][pz] == 0){
	 	glTexCoord2d(x+0.0,y+0.0);glVertex3f( s, s,-s);
     	glTexCoord2d(x+0.0,y+0.16);glVertex3f(-s, s,-s);
     	glTexCoord2d(x+0.16,y+0.16);glVertex3f(-s, s, s);
     	glTexCoord2d(x+0.16,y+0.0);glVertex3f( s, s, s);
	 }
	 if(map[px][py-1][pz] == 0){
     	glTexCoord2d(x+0.32,y+0.0);glVertex3f( s, -s,  s);
     	glTexCoord2d(x+0.32,y+0.16);glVertex3f(-s, -s,  s);
     	glTexCoord2d(x+0.48,y+0.16);glVertex3f(-s, -s, -s);
     	glTexCoord2d(x+0.48,y+0.0);glVertex3f( s, -s, -s);
	 }
     if(map[px][py][pz+1] == 0){
	 	glTexCoord2d(x+0.16,y+0.0);glVertex3f( s,  s, s);
     	glTexCoord2d(x+0.16,y+0.16);glVertex3f(-s,  s, s);
     	glTexCoord2d(x+0.32,y+0.16);glVertex3f(-s, -s, s);
     	glTexCoord2d(x+0.32,y+0.0);glVertex3f( s, -s, s);
	 }
	 if(map[px][py][pz-1] == 0){
     	glTexCoord2d(x+0.32,y+0.0);glVertex3f( s, -s, -s);
     	glTexCoord2d(x+0.32,y+0.16);glVertex3f(-s, -s, -s);
     	glTexCoord2d(x+0.16,y+0.16);glVertex3f(-s,  s, -s);
     	glTexCoord2d(x+0.16,y+0.0);glVertex3f( s,  s, -s);
	 }
	 if(map[px-1][py][pz] == 0){
     	glTexCoord2d(x+0.16,y+0.0);glVertex3f(-s,  s,  s);
     	glTexCoord2d(x+0.16,y+0.16);glVertex3f(-s,  s, -s);
     	glTexCoord2d(x+0.32,y+0.16);glVertex3f(-s, -s, -s);
     	glTexCoord2d(x+0.32,y+0.0);glVertex3f(-s, -s,  s);
	 }
	 if(map[px+1][py][pz] == 0){
     	glTexCoord2d(x+0.16,y+0.0);glVertex3f(s,  s, -s);
     	glTexCoord2d(x+0.16,y+0.16);glVertex3f(s,  s,  s);
     	glTexCoord2d(x+0.32,y+0.16);glVertex3f(s, -s,  s);
     	glTexCoord2d(x+0.32,y+0.0);glVertex3f(s, -s, -s);
 	 }
   glEnd();
}

void mcDebug(int map[100][255][100],int sx,int sy,int sz){
	for(int z = sz; z < sz+16 ; z++){
		for(int y = sy; y < sy+16; y++){
			for(int x = sx; x < sx+16; x++){
				switch(map[x][y][z]){
					case -1:glPushMatrix();glTranslatef(x,y,z);glutWireCube(1);glPopMatrix();break;
					case 1:glPushMatrix();glTranslatef(x,y,z);mcCube(map,x,y,z,0,0.833f,0.5f);glPopMatrix();break;
					case 2:glPushMatrix();glTranslatef(x,y,z);mcCube(map,x,y,z,0,0.333f,0.5f);glPopMatrix();break;
					case 3:glPushMatrix();glTranslatef(x,y,z);mcCube(map,x,y,z,0,0.166f,0.5f);glPopMatrix();break;
					case 4:glPushMatrix();glTranslatef(x,y,z);mcCube(map,x,y,z,0,0.000f,0.5f);glPopMatrix();break;
					case 5:glPushMatrix();glTranslatef(x,y,z);mcCube(map,x,y,z,0.5f,  0,0.5f);glPopMatrix();break;
					case 6:glPushMatrix();glTranslatef(x,y,z);mcCube(map,x,y,z,0,0.500f,0.5f);glPopMatrix();break;
					case 12:glPushMatrix();glTranslatef(x,y,z);glRotatef(180,0,0,1);glScalef(0.1,0.1,0.1);playerModel(0,0);glPopMatrix();break;
				}
			}
		}
	}
}
void PrefabCopy(int prf[6][6][6][6],int map[100][255][100],int _x,int _y,int _z,int model){
	for(int z = 0; z < 6; z++){
		for(int y = 0; y < 6; y++){
			for(int x = 0; x < 6; x++){
				if(prf[model][x][y][z] != 0){
					map[x+_x][y+_y][z+_z] = prf[model][x][y][z];
				}
			}
		}
	}
}

void mcGenMap(int map[100][255][100], int prf[6][6][6][6],int seed){
	int found,rndx,rndm,rnd,rnd2,pty = 0,gpf;
	for(int z = 0; z < 100; z++){
		rndx= roundf(rand()%99+1);
			rndm = roundf(rand()%2) +52;
			rnd  = roundf(rand()%2) +52;
			rnd2 = roundf(rand()%2) +52;
		std::cout<<"["<<z<<"] points: x0 = "<<rnd<<" tmid = "<<rndm<<" xmid = "<<rndx<<" x100 = "<<rnd2<<std::endl;
		map[0][rnd][z]     = 1;
		map[rndx][rndm][z] = 1;
		map[1][rnd2][z]    = 1;
		for(int x = 0; x < rndx; x++){
			found = rnd+((x-0)*((rndm-rnd)/(rndx-0)));
			map[x][found][z] = 1;
			for(int i = 0; i < found; i++){
				map[x][i][z] = 2;
			} 
		}
		for(int x = rndx; x < 100; x++){
			found = rndm+((x-rndx)*((rnd2-rndm)/(100-rndx)));
			map[x][found][z] = 1;
			for(int i = 0; i < found; i++){
				map[x][i][z] = 2;
			} 
		}
	}
	// generate prefabs for the world
	for(int z = 0; z < 100; z++){
		for(int x = 0; x < 100; x++){
			gpf = roundf(rand()%seed);
			std::cout<<"gen tree?: "<<gpf<<" X:"<<x<<" Z:"<<z<<std::endl;
			if(gpf == 1){
				pty = 0;
				while(map[x][pty][z] != 0){
					pty++;
				}
				if(x+6 > 100||x-6 < 0||z+6 > 100||z-6 < 0){
					std::cout<<"cant plant a tree here\n";
				}else{
					PrefabCopy(prf,map,x,pty,z,0);
				}
			}
		}
	}
}
