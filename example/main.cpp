/*
  Simple Demo for GLSL
  www.lighthouse3d.com
  
  tweaked a bit by andy
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "GL/glew.h"
#include <gl\glaux.h>

#ifdef __linux__
#include <GL/glut.h>
#endif

#ifdef __APPLE__
#include <glut.h>
#endif

#ifdef _WIN32

#include "gl/glut.h"
#endif

#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include <math.h>

GLuint texNumNormal;

float mouseWindowX = 0.0;
float mouseWindowY = 0.0;

int windowWidth =500;
int windowHeight = 500;

static float default_time;
static float moveright=0;
static float moveup=0;
static float angle;
static float shake_tail;
static float shake;
static float far1;
static float ang;
static float zrotate;
static float star_body;

//----------------	readfile *.vs  *.fs	-------------------//

char *textFileRead(char *fn)
{
	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {
      
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	
	if (content == NULL)
	   {
	   fprintf(stderr, "ERROR: could not load in file %s\n", fn);
	   exit(1);
	   }
	return content;
}           



GLuint p;

float lpos[4] = {1.0, 0.5, 1.0, 0.0};

void changeSize(int w, int h) {

	glViewport(0, 0, w, h);
	
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	
	float ratio = 1.0* w / h;
	
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
  //  glViewport(0, 0, 500,500);

    windowWidth = w;
    windowHeight = h;
    
	// Set the correct perspective.
	gluPerspective(70, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

////////////////////////////////////////////////////////////////////////////////

void printShaderLog(GLuint prog)
{
    GLint infoLogLength = 0;
    GLsizei charsWritten  = 0;
    GLchar *infoLog;

    glGetShaderiv(prog, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        infoLog = (char *) malloc(infoLogLength);
        glGetShaderInfoLog(prog, infoLogLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}

void printProgramLog(GLuint shad)
{
    GLint infoLogLength = 0;
    GLsizei charsWritten  = 0;
    GLchar *infoLog;

    glGetProgramiv(shad, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        infoLog = (char *) malloc(infoLogLength);
        glGetProgramInfoLog(shad, infoLogLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}

//-------idle

void idle(void){

  default_time = glutGet(GLUT_ELAPSED_TIME) / 500.0;
  shake = sin(default_time*10)*0.1;
  glutPostRedisplay();
}
//------------------------------------------------------------------------//
void fish(void)
{
		glBegin(GL_TRIANGLES);

		 glTexCoord2f(0.0, 0.0);
		 glVertex3f( -4.0f, 0.0f,  0.0f);
		 

         glVertex3f( 0.0f, -1.0f, 1.0f);
         glTexCoord2f(1.0, 0.0);

		 glVertex3f( 0.0f, 1.0f,  1.0f);
         glTexCoord2f(0.0, 1.0);

		 glVertex3f( 0.0f, -1.0f,  1.0f);
         glTexCoord2f(0.0, 1.0);

         glVertex3f( 4.0f, 0.0f,  0.0f);
         glTexCoord2f(1.0, 1.0);

         glVertex3f( 0.0f, 1.0f,  1.0f);
         glTexCoord2f(0.0, 1.0);

		 
		 
		 
		 glVertex3f( -4.0f, 0.0f,  0.0f);
		 glTexCoord2f(0.0, 0.0);

         glVertex3f( 0.0f, 1.0f, 1.0f);
         glTexCoord2f(1.0, 0.0);

		 glVertex3f( 0.0f, 1.0f,  -1.0f);
         glTexCoord2f(0.0, 1.0);

		 glVertex3f( 0.0f, 1.0f, 1.0f);
         glTexCoord2f(1.0, 0.0);

         glVertex3f( 4.0f, 0.0f,  0.0f);
         glTexCoord2f(1.0, 1.0);

         glVertex3f( 0.0f, 1.0f,  -1.0f);
         glTexCoord2f(0.0, 1.0);	
	 
		 
		 
		 glVertex3f( -4.0f, 0.0f,  0.0f);
		 glTexCoord2f(0.0, 0.0);

         glVertex3f( 0.0f, 1.0f, -1.0f);
         glTexCoord2f(1.0, 0.0);

		 glVertex3f( 0.0f, -1.0f,  -1.0f);
         glTexCoord2f(0.0, 1.0);

		 glVertex3f( 0.0f, 1.0f, -1.0f);
         glTexCoord2f(1.0, 0.0);

         glVertex3f( 4.0f, 0.0f,  -0.0f);
         glTexCoord2f(1.0, 1.0);

         glVertex3f( 0.0f, -1.0f,  -1.0f);
         glTexCoord2f(0.0, 1.0);	
		 
		 
		 
		 glVertex3f( -4.0f, 0.0f,  0.0f);
		 glTexCoord2f(0.0, 0.0);

         glVertex3f( 0.0f, -1.0f, -1.0f);
         glTexCoord2f(1.0, 0.0);

		 glVertex3f( 0.0f, -1.0f,  1.0f);
         glTexCoord2f(0.0, 1.0);

		 glVertex3f( 0.0f, -1.0f, -1.0f);
         glTexCoord2f(1.0, 0.0);

         glVertex3f( 4.0f, 0.0f,  0.0f);
         glTexCoord2f(1.0, 1.0);

         glVertex3f( 0.0f, -1.0f,  1.0f);
         glTexCoord2f(0.0, 1.0);



		 
	glEnd();


	glBegin(GL_TRIANGLES);

		glVertex3f( 6.0f, -1.0f,  0.0f);
        glTexCoord2f(0.0, 0.0);

		glVertex3f( 6.0f, 1.0f,  0.0f);
        glTexCoord2f(0.0, 1.0);

		glVertex3f( 4.0f, 0.0f,  0.0f);
        glTexCoord2f(1.0, 1.0);	 
		 
	glEnd();
	//--------------------hand-----------------------

	glBegin(GL_TRIANGLES);

		glVertex3f( 0.0f, 1.0f,  0.0f);
        glTexCoord2f(0.0, 1.0);

		glVertex3f( 3.5f, 3.0f,  0.0f);
        glTexCoord2f(0.0, 1.0);

		glVertex3f( 2.0f, 1.5f,  0.0f);
        glTexCoord2f(1.0, 1.0);	 

		glVertex3f( 0.0f, -1.0f,  0.0f);
        glTexCoord2f(0.0, 1.0);

		glVertex3f( 3.5f, -3.0f,  0.0f);
        glTexCoord2f(0.0, 1.0);

		glVertex3f( 2.0f, -1.5f,  0.0f);
        glTexCoord2f(1.0, 1.0);	
		 
	glEnd();
}
/*
void tail(void)
{
	glBegin(GL_TRIANGLES);
		 glVertex3f( 0.0f, 0.0f,  0.0f);
         glTexCoord2f(1.0, 1.0);

		 glVertex3f( -2.0f, 0.0f,  1.0f);
         glTexCoord2f(0.0, 1.0);

		 glVertex3f( -2.0f, 0.0f,  -1.0f);
         glTexCoord2f(0.0, 0.0);
	glEnd();
}

*/

void star(void)
{
	glBegin(GL_TRIANGLES);
		 glVertex3f( 0.0f, 3.0f,  5.0f);
         glTexCoord2f(0.5, 1.0);

		 glVertex3f( -1.0f, 1.0f,  5.0f);
         glTexCoord2f(0.4, 0.6);

		 glVertex3f( 1.0f, 1.0f,  5.0f);
         glTexCoord2f(0.6, 0.6);


		 glVertex3f( -1.0f, 1.0f,  5.0f);
         glTexCoord2f(0.4, 0.6);

		 glVertex3f( -3.0f, 1.0f,  5.0f);
         glTexCoord2f(0.0, 0.6);

		 glVertex3f( -1.0f, -1.0f,  5.0f);
         glTexCoord2f(0.4, 0.4);


		 glVertex3f( -1.0f, -1.0f,  5.0f);
         glTexCoord2f(0.4, 0.4);

		 glVertex3f( -2.0f, -3.0f,  5.0f);
         glTexCoord2f(0.2, 0.0);

		 glVertex3f( 0.0f, -1.5f,  5.0f);
         glTexCoord2f(0.5, 0.4);


		 glVertex3f( 1.0f, 1.0f,  5.0f);
         glTexCoord2f(0.6, 0.6);

		 glVertex3f( 3.0f, 1.0f,  5.0f);
         glTexCoord2f(1.0, 0.6);

		 glVertex3f( 1.0f, -1.0f,  5.0f);
         glTexCoord2f(0.6, 0.4);


		 glVertex3f( 1.0f, -1.0f,  5.0f);
         glTexCoord2f(0.6, 0.4);

		 glVertex3f( 2.0f, -3.0f,  5.0f);
         glTexCoord2f(0.8, 0.0);

		 glVertex3f( 0.0f, -1.5f,  5.0f);
         glTexCoord2f(0.5, 0.4);
	glEnd();

	glBegin(GL_POLYGON);
		 glVertex3f( -1.0f, 1.0f,  5.0f);
         glTexCoord2f(0.4, 0.6);
		 glVertex3f( 1.0f, 1.0f,  5.0f);
         glTexCoord2f(0.6, 0.6);
		 glVertex3f( -1.0f, -1.0f,  5.0f);
         glTexCoord2f(0.4, 0.4);
		 glVertex3f( 0.0f, -1.5f,  5.0f);
         glTexCoord2f(0.5, 0.4);
		 glVertex3f( 1.0f, -1.0f,  5.0f);
         glTexCoord2f(0.6, 0.4);

	glEnd();
}
//------------------------------------------------------------------------//

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glViewport(0, 0, 250,250);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*
	gluLookAt(	4,0,50,
				0,0,1,
				1,0,0);   //視線的座標及方向
*/
	gluLookAt(	0,0,100,
				0,0,-1,
				0,1,0);   //視線的座標及方向		
	
	

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	
	//----rotate by moving mouse----//
	//glRotatef(mouseWindowX*90+90,0,1,0);
	//glRotatef(mouseWindowY*90,0,0,1);
	
    glEnable(GL_TEXTURE_2D); 
	
    glUseProgram(p);
	
   //------load uniform data
    GLint texLoc0;
	GLint Use_right;
	GLint Use_up;
	GLint Use_rotate;
    GLint Use_tail;
	GLint Use_zrotate;
	
	texLoc0 = glGetUniformLocation(p, "myTexture_wall");
    glUniform1i(texLoc0, 0);
	
	Use_right = glGetUniformLocation(p, "moveright");
	Use_up = glGetUniformLocation(p, "moveup");
	Use_rotate = glGetUniformLocation(p, "angle");
	Use_tail = glGetUniformLocation(p, "shake_tail");
	Use_zrotate = glGetUniformLocation(p, "ang");
    glUniform1f(Use_right, moveright);
	glUniform1f(Use_up, moveup);
	glUniform1f(Use_rotate, angle);
	glUniform1f(Use_tail, shake_tail);
	glUniform1f(Use_zrotate, ang);
	

	glPushMatrix();
	glTranslated(0.0,0.0, 0.0);
	//glRotated(90,0,1,0);
	//glRotated(ang,0,0,1);
	//glRotated(360*sin(time),0,1,0);
	glScalef (5 ,5, 1);
	
	fish();
	glPopMatrix();	


	glPushMatrix();
	glTranslated(0.0,50.0, 0.0);
	//glRotated(ang,1,0,0);
	//glRotated(ang,0,0,1);
	//glRotated(360*sin(time),0,1,0);
	glScalef (star_body ,star_body, star_body);
	star();
	glPopMatrix();	

	glPushMatrix();
	glTranslated(-10.0,1.0, 0.0);
	//glRotated(ang,1,0,0);
	//glRotated(ang,0,0,1);
	//glRotated(360*sin(time),0,1,0);
	glScalef (1.5 ,1.5, 1.5);
	glutSolidSphere(1,20,20);
	glPopMatrix();	

/*
	glPushMatrix();
	glTranslated(-20.0,5+far1, 0.0);
	glRotated(50,1,0,0);
	glRotated(ang,0,1,0);
	//glRotated(360*sin(time),0,1,0);
	glScalef (5 ,5, 1);
	tail();
	glPopMatrix();	
*/	
	glutSwapBuffers();
	

//glFinish();

}

//---------------KeyBoard Function-----------------------//

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 'q' || key == 'Q') 
		exit(0);
	if (key == 'd' || key == 'D')
	{
		if(angle>=3.14)
		{
			angle = 3.14;
			moveright = moveright +0.05;
			shake_tail = shake;
		}
		else
			angle = angle+0.5;
	}
	if (key == 'a' || key == 'A') 
	{
		if(angle<=-1.57)
		{
			angle = angle-0.5;
			moveup = moveup -0.05;
			shake_tail = shake;
			if(angle<=-3.14)
				angle=0;
		}
		else if(angle<=0)
		{
			angle = 0;
			moveright = moveright -0.05;
			shake_tail = shake;
		}
		else
			angle = angle-0.5;
	}
	if (key == 's' || key == 'S') 
	{
		if(angle>=1.57)
		{
			angle = 1.57;
			moveup = moveup -0.05;
			shake_tail = shake;
		}
		else
			angle = angle+0.5;
	}
	if (key == 'w' || key == 'W') 
	{
		if(angle<=-1.57)
		{
			angle = -1.57;
			moveup = moveup +0.05;
			shake_tail = shake;
		}
		else
			angle = angle-0.5;



		   if(moveright>=0.5&&moveright<=1.5)
			{
				star_body = 0;
			}
   /*
   if(moveright<=2&&moveright>=-2&&moveup<=20&&moveup>=10)
   {
		star_body = 0;
   }*/
			else
			{
				star_body = 1;
			}



	}
	if (key == 'e' || key == 'E') 
	{
		far1 = far1 -0.5;
		shake_tail = shake;
		ang = -90;
	}
	if (key == 'r' || key == 'R') 
	{
		far1 = far1 +0.5;
		shake_tail = shake;
		ang = 90;
	}
	
}

//-----------------Set Shader Code------------------------//

GLuint setShaders(char * vert, char * frag) {
    GLuint v,f, pro;
	char *vs,*fs;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead(vert);
	fs = textFileRead(frag);

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);

	printShaderLog(v);
	printShaderLog(f);

	pro = glCreateProgram();
	glAttachShader(pro,v);
	glAttachShader(pro,f);

	glLinkProgram(pro);
	printProgramLog(pro);
	
	return(pro);
}



//-----------------Mouse Fuction------------------//

void PassiveMouseMotion(int x, int y)
{
    if (x<0)
        mouseWindowX = -1;
    else if (x>windowWidth)
        mouseWindowX = 1;
    else
        mouseWindowX = 2* (x / (float) windowWidth) - 1.0;
           
    if (y<0)
        mouseWindowY = -1;
    else if (y>windowHeight)
        mouseWindowY = 1;
    else
        mouseWindowY = 2* (y / (float) windowHeight) - 1.0;
    }

//-------------------Load BMP file (texture file)----------------------------//
GLuint	texture[2];
AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

//---------------------------------------------------------------------------------------//
//----------------------------------MAIN-------------------------------------------------//
//---------------------------------------------------------------------------------------//
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(1100,100);					//window's position
	glutInitWindowSize(windowWidth, windowHeight);		//window's size
	//glutInitWindowSize(640, 480);
	glutCreateWindow("GLSL demo");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutPassiveMotionFunc(PassiveMouseMotion);
	glutIdleFunc(idle);

	glewInit();
	
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1,0.1,0.7,0.7);
	
//---texture   
    GLuint textureNum[1];
    glGenTextures(1, textureNum);
	AUX_RGBImageRec *TextureImage[1];
//-- sky


	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureNum[0]);
	glEnable(GL_TEXTURE_2D);
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	//TextureImage[0]=LoadBMP("./data/images.bmp");

	//glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	
	p = setShaders((char *) "./src/vs.vert", (char *) "./src/fs.frag");

//-- wall
	

	
	glutMainLoop();
	return 0;
}

