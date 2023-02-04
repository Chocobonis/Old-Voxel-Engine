void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	mcFog(4,9,10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	steve.setCamera();
	steve.setGravity(world);
	rx = steve.getPosition(1);
	ry = steve.getPosition(2);
	rz = steve.getPosition(3);
	dir = steve.getRotation(1);
	mcDebug(world,rx-8,ry-8,rz-8);
	steve.drawGui();
	glFlush();
	glutSwapBuffers();
}
