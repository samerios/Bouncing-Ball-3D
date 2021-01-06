
#include <GL/glut.h>
#include <stdio.h>
#include <math.H>
#include<malloc.h>

static int flagX = 0, flagZ = 0;
int rot = 0;
static float ball_x = -13.0, ball_y = 0.2, ball_z = -6.0, radius = 0.20;
float moveWest=0,moveEast=0;
float hetz1, hetz2;
static int flagWest = 0, westz = 0, eastFlag = 0;
char str[500] = "", *str2;
static long points = 0,balls=3;
FILE * file;
unsigned char *pic;
static int flagCubex = 0, flagCubez = 0;
GLfloat xl = 2.5, yl = 1.0, zl = 0.0;
static int zoom = -24,upDown=-6;

struct cub
{
	float x, y, z;
	float width, depth, height;
	float r, g, b;
};
struct cub arr[8];
struct cub arrMaklotBoaot[4];
void init_cub()//function to init all cubes
{
	for (int i = 0; i<8; i++)
	{
		arr[i].width = 0.18;
		arr[i].depth = 0.18;
		arr[i].height = 1.2;
	}
	arr[0].x = -12; arr[0].y = 0.0; arr[0].z = -6; arr[0].r = 0.0; arr[0].g = 0.222; arr[0].b = 0.7;
	arr[1].x = -8; arr[1].y = 0.0; arr[1].z = -3; arr[1].r = 0.2; arr[1].g = 0.1; arr[1].b = 0.008;
	arr[2].x = -10; arr[2].y = 0.0; arr[2].z =-2; arr[2].r = 0.34; arr[2].g = 0.6; arr[2].b = 0.43;
	arr[3].x = -11; arr[3].y = 0.0; arr[3].z = -7; arr[3].r = 0.888; arr[3].g = 0.774; arr[3].b = 0.333;
	arr[4].x = -4.2; arr[4].y = 0.0; arr[4].z = -5; arr[4].r = 0.141; arr[4].g = 0.84; arr[4].b = 0.114;
	arr[5].x = -7; arr[5].y = 0.0; arr[5].z = -6.4; arr[5].r = 0.666; arr[5].g = 0.2; arr[5].b = 0.0;
	arr[6].x = -3.5; arr[6].y = 0.0; arr[6].z = -1.5; arr[6].r = 0.7411; arr[6].g = 0.33; arr[6].b = 0.7;
	arr[7].x = -5; arr[7].y = 0.0; arr[7].z = -4; arr[7].r = 0.1111; arr[7].g = 0.1666; arr[7].b = 0.01;
}
void intit_maklot_boaot() //function to init maklot and boaot 
{
	arrMaklotBoaot[0].x = -5.0; arrMaklotBoaot[0].y = -0.4; arrMaklotBoaot[0].z = -6.0;
	arrMaklotBoaot[0].r = 0.0;	arrMaklotBoaot[0].g = 0.0;	arrMaklotBoaot[0].b = 0.0;
	arrMaklotBoaot[0].width = 0.2;	arrMaklotBoaot[0].height = 0.5;	arrMaklotBoaot[0].depth = 0.2;

	arrMaklotBoaot[1].x = -6.0; arrMaklotBoaot[1].y = -0.4; arrMaklotBoaot[1].z = -3.5;
	arrMaklotBoaot[1].r = 1.0;	arrMaklotBoaot[1].g = 0.6;	arrMaklotBoaot[1].b = 0.0;
	arrMaklotBoaot[1].width = 0.2;	arrMaklotBoaot[1].height = 0.5;	arrMaklotBoaot[1].depth = 0.2;


	for (int i = 2; i < 4; i++)
	{
		arrMaklotBoaot[i].y = 0.0; arrMaklotBoaot[i].z = -2.0;
		arrMaklotBoaot[i].width = 0.2;	arrMaklotBoaot[i].height = 0.3;	arrMaklotBoaot[i].depth = 1.0;
		arrMaklotBoaot[i].r = 0.0;	arrMaklotBoaot[i].g = 0.0;	arrMaklotBoaot[i].b = 0.0;
	}
	arrMaklotBoaot[2].x = -14.2;	arrMaklotBoaot[3].x = -0.7;
}
bool SphereRectCollision(float ballx, float bally, float ballz, float radius, cub rect)//function to check if ball damage the sides
{
	float sphereXDistance = fabs(ballx - rect.x);
	float sphereYDistance = fabs(bally - rect.y);
	float sphereZDistance = fabs(ballz - rect.z);

	if (sphereXDistance >= (rect.width + radius)) { return false; }
	if (sphereYDistance >= (rect.height + radius)) { return false; }
	if (sphereZDistance >= (rect.depth + radius)) { return false; }

	if (sphereXDistance < (rect.width)) { return true; }
	if (sphereYDistance < (rect.height)) { return true; }
	if (sphereZDistance < (rect.depth)) { return true; }

	float cornerDistance_sq = ((sphereXDistance - rect.width) * (sphereXDistance - rect.width)) +
		((sphereYDistance - rect.height) * (sphereYDistance - rect.height) +
		((sphereZDistance - rect.depth) * (sphereZDistance - rect.depth)));

	return (cornerDistance_sq < (radius * radius));
} 
void keyboard(unsigned char key, int x, int y)//Keyboard control
{
	if (key == 27) exit(1);
	if (key == 'r')
	{
		rot += 5;
		rot %= 360;
		xl += 0.5;
		yl += 0.5;
		zl += 0.5;
	}
	if (key == 'e')
	{
		rot -= 5;
		rot %= 360;
		xl -= 0.5;
		yl -= 0.5;
		zl -= 0.5;
	}
	if (key == 'q')upDown++;
	if (key == 'a')upDown--;
	if (key == '+')zoom++;
	if (key == '-')zoom--;
	if (!eastFlag)
	{
		if (key == 't'&&arrMaklotBoaot[2].z >= -7.0)
			arrMaklotBoaot[2].z -= 0.5;
		if (key == 'g'&&arrMaklotBoaot[2].z <= -1.6)
			arrMaklotBoaot[2].z += 0.5;
	}
	if (key == 'y'&&arrMaklotBoaot[3].z >=-7.0)
		arrMaklotBoaot[3].z -= 0.5;
	if (key == 'h'&&arrMaklotBoaot[3].z <= -1.6)
		arrMaklotBoaot[3].z += 0.5;
	glutPostRedisplay();
}
bool SphereTf(float ballx, float bally, float ballz, float radius, cub rect)//function to check if ball damage any cube
{
	float sphereXDistance = fabs(ballx - rect.x);
	float sphereZDistance = fabs(ballz - rect.z);

	if (sphereXDistance >= (rect.width + radius)) { return false; }
	if (sphereZDistance >= (rect.depth + radius)) { return false; }

	if (sphereXDistance < (rect.width)) { return true; }
	if (sphereZDistance < (rect.depth)) { return true; }

	float cornerDistance_sq = ((sphereXDistance - rect.width) * (sphereXDistance - rect.width)) +
		((sphereZDistance - rect.depth) * (sphereZDistance - rect.depth));

	return (cornerDistance_sq < (radius * radius));
}
void func(float x, float y, float z)//function to insert cube
{
	glBegin(GL_QUADS);
	// Front
	glNormal3f(0, 0, z);
	glVertex3f(-x, 0, z);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, 0, z);
	// Back
	glNormal3f(0, 0, -z);
	glVertex3f(-x, 0, -z);
	glVertex3f(x, 0, -z);
	glVertex3f(x, y, -z);
	glVertex3f(-x, y, -z);
	// Left side
	glNormal3f(-x, 0, 0);
	glVertex3f(-x, 0, z);
	glVertex3f(-x, y, z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, 0, -z);
	// Right side
	glNormal3f(x, 0, 0);
	glVertex3f(x, 0, z);
	glVertex3f(x, 0, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);
	glEnd();
}
void regel()//function to insert table leg
{
	glBegin(GL_QUADS);
	// Front
	glNormal3f(0, 0, 0.5);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, -2, 0.5);
	glVertex3f(0.5, -2, 0.5);
	glVertex3f(0.5, 0, 0.5);
	// Back
	glNormal3f(0, 0, -0.5);
	glVertex3f(-0.5, 0, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, -2, -0.5);
	glVertex3f(-0.5, -2, -0.5);
	// Left side
	glNormal3f(-0.5, 0, 0);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, -2, 0.5);
	glVertex3f(-0.5, -2, -0.5);
	glVertex3f(-0.5, 0, -0.5);
	// Right side
	glNormal3f(0.5, 0, 0);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, -2, -0.5);
	glVertex3f(0.5, -2, 0.5);
	glEnd();
}
void dafnot1()//function to insert 2 sides
{ 
	glBegin(GL_QUADS);
	// Front
	glNormal3f(0, 0, 0.5);
	glVertex3f(-8, 0, 0.5);
	glVertex3f(-8, 0.2, 0.5);
	glVertex3f(8, 0.2, 0.5);
	glVertex3f(8, 0, 0.5);
	// Back
	glNormal3f(0, 0, -0.5);
	glVertex3f(-8, 0, -0.5);
	glVertex3f(-8, 0.2, -0.5);
	glVertex3f(8, 0.2, -0.5);
	glVertex3f(8, 0, -0.5);
	// left side
	glNormal3f(-1, 0, 0);
	glVertex3f(-8, 0, 0.5);
	glVertex3f(-8, 0.2, 0.5);
	glVertex3f(-8, 0.2, -0.5);
	glVertex3f(-8, 0, -0.5);
	// right side
	glNormal3f(1, 0, 0);
	glVertex3f(8, 0, 0.5);
	glVertex3f(8, 0.2, 0.5);
	glVertex3f(8, 0.2, -0.5);
	glVertex3f(8, 0, -0.5);
	// up side
	glNormal3f(0, 0.2, 0);
	glVertex3f(8, 0.2, 0.5);
	glVertex3f(-8, 0.2, 0.5);
	glVertex3f(-8, 0.2, -0.5);
	glVertex3f(8, 0.2, -0.5);
	glEnd();
}
void Tfloor(float x,float y, float z)//function to create floor
{
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);
	glEnd();
}
void hetz(float x,float y,float z)//function to create arrow
{
	glBegin(GL_QUADS);
	// Front
	glNormal3f(0, 0, z);
	glVertex3f(-x, 0, z);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, 0, z);
	// left side
	glNormal3f(-x, 0, 0);
	glVertex3f(-x, 0, z);
	glVertex3f(-x, 0, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, y, z);
	// Back
	glNormal3f(0, 0, -z);
	glVertex3f(-x, 0, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, 0, -z);
	// right side
	glNormal3f(x, 0, 0);
	glVertex3f(x, 0, z);
	glVertex3f(x, 0, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);
	// up side
	glNormal3f(0, y, 0);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, -z);
	glVertex3f(-x, y, -z);
	glEnd(); 
}
void updateCubePossision()//function to update cube possision (move)
{
	if (!flagCubex)
	{
		for (int j = 4; j < 8; j++)
		{
			arr[j].x += 0.01;
			if (arr[j].x > -2)
				flagCubex = 1;
		}
		for (int j = 0; j < 4; j++)
		{
			arr[j].x -= 0.01;
			if (arr[j].x > -2)
				flagCubex = 0;
		}
	}
	if (flagCubex)
	{
		for (int j = 4; j < 8; j++)
		{
			arr[j].x -= 0.01;
			if (arr[j].x<-13.5)
				flagCubex = 0;
		}
		for (int j = 0; j < 4; j++)
		{
			arr[j].x += 0.01;
			if (arr[j].x<-13.5)
				flagCubex = 1;
		}
	}
	if (!flagCubez)
	{
		for (int j = 4; j < 8; j++)
		{
			arr[j].z += 0.01;
			if (arr[j].z>-1.5)
				flagCubez = 1;
		}
		for (int j = 0; j < 4; j++)
		{
			arr[j].z -= 0.01;
			if (arr[j].z>-1.5)
				flagCubez = 0;
		}
	}
	if (flagCubez)
	{
		for (int j = 4; j < 8; j++)
		{
			arr[j].z -= 0.01;
			if (arr[j].z<-7.5)
				flagCubez = 0;
		}
		for (int j = 0; j < 4; j++)
		{
			arr[j].z += 0.01;
			if (arr[j].z<-7.5)
				flagCubez = 1;
		}
	}
}
void updateBall()//function to update ball possision (move) 
{
	if (balls != 0)
	{
		if (!flagX)
		{
			ball_x += 0.05;
			if (ball_x > -1)
			{
				points -= 5;
				flagX = 1;
			}
			else if (ball_x == 0) balls -= 5;
			for (int i = 0; i < 8; i++)
			{
				if (SphereRectCollision(ball_x, ball_y, ball_z, radius, arr[i]) == true)
					flagX = 1;
			}
			if (SphereRectCollision(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[3]) == true)
				flagX = 1;
			if (SphereTf(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[0]) == true)
			{
				points -= 10;
				balls--;
				ball_x = -13.0; ball_y = 0.2; ball_z = -6.0;
				flagX = 1;
			}
			if (SphereTf(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[1]) == true)
			{
				points += 10;
				flagX = 1;
			}
		}
		if (flagX)
		{
			ball_x -= 0.05;
			if (ball_x < -14.5)
			{
				points -= 5;
				flagX = 0;
			}
			else if (ball_x == -15) balls -= 5;

			for (int i = 0; i < 8; i++)
			{
				if (SphereRectCollision(ball_x, ball_y, ball_z, radius, arr[i]) == true)
					flagX = 0;
			}
			if (SphereRectCollision(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[2]) == true)
				flagX = 0;
			if (SphereTf(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[0]) == true)
			{
				points -= 10;
				balls--;
				ball_x = -13.0; ball_y = 0.2; ball_z = -6.0;
				flagX = 0;
			}
			if (SphereTf(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[1]) == true)
			{
				points += 10;
				flagX = 0;
			}
		}
		if (!flagZ)
		{
			ball_z += 0.05;
			if (ball_z > -0.5)
				flagZ = 1;
			else if (ball_z == 0) balls -= 5;

			for (int i = 0; i < 8; i++)
			{
				if (SphereRectCollision(ball_x, ball_y, ball_z, radius, arr[i]) == true)
					flagZ = 1;
			}
			for (int i = 2; i < 4; i++)
			{
				if (SphereRectCollision(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[i]) == true)
					flagZ = 1;
			}
			if (SphereTf(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[0]) == true)
			{
				points -= 10;
				balls--;
				ball_x = -13.0; ball_y = 0.2; ball_z = -6.0;
				flagZ = 1;
			}
			if (SphereTf(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[1]) == true)
			{
				points += 10;
				flagZ = 1;
			}
		}
		if (flagZ)
		{
			ball_z -= 0.05;
			if (ball_z < -8.5)
				flagZ = 0;
			else if (ball_z == -9) balls -= 5;

			for (int i = 0; i < 8; i++)
			{
				if (SphereRectCollision(ball_x, ball_y, ball_z, radius, arr[i]) == true)
					flagZ = 0;
			}
			for (int i = 2; i < 4; i++)
			{
				if (SphereRectCollision(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[i]) == true)
					flagZ = 0;
			}
			if (SphereTf(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[0]) == true)
			{
				points -= 10;
				balls--;
				ball_x = -13.0; ball_y = 0.2; ball_z = -6.0;
				flagZ = 0;
			}
			if (SphereTf(ball_x, ball_y, ball_z, radius, arrMaklotBoaot[1]) == true)
			{
				points += 10;
				flagZ = 0;
			}
		}
		updateCubePossision();
	}
	else if(balls==0)//if there are not balls exit game
	{
		exit(1);
	}
}
void setPic()//function to create 2 sides with picture
{	
	glBegin(GL_QUADS);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3d(-0.5, 0, 0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3d(-0.5, 0.2, 0.5);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3d(0.5, 0.2, 0.5);
	glTexCoord3d(0.0, 1.0, 1.0); glVertex3d(0.5, 0, 0.5);
	glEnd();
	pic = (unsigned char*)malloc(256 * 256 * 3);
	fopen_s(&file, "flower.bmp", "rb");
	fread(pic, 256 * 256 * 3, 1, file);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 256, 256, GL_BGR_EXT, GL_UNSIGNED_BYTE, pic);
	fclose(file);
	free(pic);

	glBegin(GL_QUADS);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3d(-0.5, 0, 0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3d(-0.5, 0, -8);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3d(-0.5, 0.2, -8);
	glTexCoord3d(0.0, 1.0, 1.0); glVertex3d(-0.5, 0.2, 0.5);
	glEnd();
	pic = (unsigned char*)malloc(256 * 256 * 3);
	fopen_s(&file, "flower.bmp", "rb");
	fread(pic, 256 * 256 * 3, 1, file);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 256, 256, GL_BGR_EXT, GL_UNSIGNED_BYTE, pic);
	fclose(file);
	free(pic);

	glBegin(GL_QUADS);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3d(-0.5, 0, -8);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3d(-0.5, 0.2, -8);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3d(0.5, 0.2, -8);
	glTexCoord3d(0.0, 1.0, 1.0); glVertex3d(0.5, 0, -8);
	glEnd();
	pic = (unsigned char*)malloc(256 * 256 * 3);
	fopen_s(&file, "flower.bmp", "rb");
	fread(pic, 256 * 256 * 3, 1, file);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 256, 256, GL_BGR_EXT, GL_UNSIGNED_BYTE, pic);
	fclose(file);
	free(pic);

	glBegin(GL_QUADS);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3d(0.5, 0, 0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3d(0.5, 0, -8);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3d(0.5, 0.2, -8);
	glTexCoord3d(0.0, 1.0, 1.0); glVertex3d(0.5, 0.2, 0.5);
	glEnd();
	pic = (unsigned char*)malloc(256 * 256 * 3);
	fopen_s(&file, "flower.bmp", "rb");
	fread(pic, 256 * 256 * 3, 1, file);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 256, 256, GL_BGR_EXT, GL_UNSIGNED_BYTE, pic);
	fclose(file);
	free(pic);

	glBegin(GL_QUADS);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3d(-0.5, 0.2, 0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3d(0.5, 0.2, 0.5);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3d(0.5, 0.2, -8);
	glTexCoord3d(0.0, 1.0, 1.0); glVertex3d(-0.5, 0.2, -8);
	glEnd();
	pic = (unsigned char*)malloc(256 * 256 * 3);
	fopen_s(&file, "flower.bmp", "rb");
	fread(pic, 256 * 256 * 3, 1, file);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 256, 256, GL_BGR_EXT, GL_UNSIGNED_BYTE, pic);
	fclose(file);
	free(pic);
}
void draw()//draw control
{
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, upDown, zoom);
	glRotatef(rot, 0, 1, 0);
	
	// Create light components
	GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5, 0.5, 0.5, 1.0f };
	GLfloat mat_shininess[] = { 128.0 };
	//x,y,z,light
	GLfloat position[] = { xl, yl, zl, 1.0f };
    // Assign created components to GL_LIGHT1
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
	glMaterialfv(GL_MAX_LIGHTS, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);

	//table floor 
	glColor3f(0.4, 0.4, 0.4);
	Tfloor(8,0,5);

	//table legs
	glTranslatef(-7.5, 0, -4.5);
	glColor3f(1.0, 0.0, 0.0);
	regel();
	glTranslatef(15, 0, 9);
	regel();
	glTranslatef(-15, 0, 0);
	regel();
	glTranslatef(15, 0, -9);
	regel();
	
	//table 2 sides no picture
	glTranslatef(-7.5, 0, 9);
	dafnot1();
	glTranslatef(0, 0, -9);
	dafnot1();

	//all cubes
	glTranslatef(7.5, 0, 9);
	for (int i = 0; i<8; i++)
	{
		glTranslatef(arr[i].x, arr[i].y, arr[i].z);
		glTranslatef(0, 0, 0);
		glColor3f(arr[i].r, arr[i].g, arr[i].b);
		func(arr[i].width, arr[i].height, arr[i].depth);
		glTranslatef(-arr[i].x, -arr[i].y, -arr[i].z);
	}
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(ball_x, ball_y, ball_z);
	glutSolidSphere(radius, 32, 32);
	glTranslatef(-ball_x, -ball_y, -ball_z);
	
	//maklot and boaot 
	for (int i = 2; i < 4; i++)
	{
		glTranslatef(arrMaklotBoaot[i].x, arrMaklotBoaot[i].y, arrMaklotBoaot[i].z);
		glTranslatef(0, 0, 0);
		glColor3f(arrMaklotBoaot[i].r, arrMaklotBoaot[i].g, arrMaklotBoaot[i].b);
		hetz(arrMaklotBoaot[i].width, arrMaklotBoaot[i].height, arrMaklotBoaot[i].depth);
		glTranslatef(-arrMaklotBoaot[i].x, -arrMaklotBoaot[i].y, -arrMaklotBoaot[i].z);
	}

	for (int i = 0; i < 2; i++)
	{
		glTranslatef(arrMaklotBoaot[i].x, arrMaklotBoaot[i].y, arrMaklotBoaot[i].z);
		glTranslatef(0, 0, 0);
		glColor3f(arrMaklotBoaot[i].r, arrMaklotBoaot[i].g, arrMaklotBoaot[i].b);
		Tfloor(arrMaklotBoaot[i].width, arrMaklotBoaot[i].height, arrMaklotBoaot[i].depth);
		glTranslatef(-arrMaklotBoaot[i].x, -arrMaklotBoaot[i].y, -arrMaklotBoaot[i].z);
	}

	//yellow floor
	glColor3f(0.8, 0.7, 0.6);
	glTranslatef(-7.5, 0, -4.5);
	Tfloor(9, -2, 6);

	//table 2 sides with picture
	glTranslatef(7.5, 0, 3.5);
	setPic();
	glTranslatef(-15, 0, 0);
	setPic();
	glTranslatef(9.5, 0, -3.5);

	//result and balls text
	sprintf_s(str, "\nPoints= %d  balls=%d", points, balls);
	glColor3f(1.0, 1.0, 1.0);
	str2 = str;
	glRasterPos3f(-2, 15, 0);
	do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str2); while (*(++str2));

	glutSwapBuffers();
}
void idle()//idel function
{
	updateBall();	
	draw();
}
void passiveMotionFunc(int x, int y)//passiveMotionFunc control mouse (right arrow)
{
	if (!flagWest)
	{
		if (westz > y)
			arrMaklotBoaot[3].z -= 0.5;
		if (arrMaklotBoaot[3].z < -7.0)
			flagWest = 1;
	}
	if (flagWest)
	{
		if (westz < y)
			arrMaklotBoaot[3].z += 0.5;
		if (arrMaklotBoaot[3].z > -1.6)
			flagWest = 0;
	}
	westz = y;
	updateBall();
	draw();
}
void keyPressed(int key, int x, int y) {
	if (key == GLUT_KEY_F1)//if clicked f1 then start game
		glutIdleFunc(idle);
	if (key == GLUT_KEY_RIGHT)//if clicked right key then start mouse remote right arrow
	{
		eastFlag = 1;
		glutIdleFunc(idle);
		glutPassiveMotionFunc(passiveMotionFunc);
	}
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	// Lighting parameters
	GLfloat mat_ambdif[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 0.0 };
	GLfloat mat_shininess[] = { 80.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambdif);	// set both amb and diff components
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		// set specular
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		// set shininess
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);		// set light "position", in this case direction
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);		// active material changes by glColor3f(..)
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 900);
	glutCreateWindow("Bouncing Ball 3D");
	glutDisplayFunc(draw);
	init_cub();
	intit_maklot_boaot();
	init();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyPressed);
	glutMainLoop();
}
