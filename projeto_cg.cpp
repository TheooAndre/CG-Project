
//----------------------------------------CHANGE ALL x64 FILES 64 TO x86 tut do microsoft sdk

#include <windows.h>			// printf
#include <stdio.h>				// printf
#include <fstream>				// printf

#include <string>
#include <fstream>

#include <errno.h>
#include <GL\glew.h>			// openGL
#include <GL\freeGlut.h>		// openGL

#pragma comment(lib,"glew32d.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159

#include "RgbImage.h"
//================================================================================
//===========================================================Variaveis e constantes

GLfloat tam = 1.0;

GLint    msec = 100;					//.. definicao do timer (actualizacao)

//materiais
void initMaterials(int material);
char Materiais[18][30] = {
	"Esmerald",  "Jade",  "obsidian",    "Pearl",        "Ruby",
	"Turquoise", "Brass", "Bronze",      "Chrome",       "Copper",
	"Gold",      "Silver","blackPlastic","cyankPlastic", "greenPlastic",
	"redPlastic", "whitePlastic","yellowPlastic" };


static GLfloat vertices[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
		-tam,  tam,  tam,	// 0 
		-tam,   tam,  -tam,	// 1 
		-tam,   -tam, -tam,	// 2 
		-tam,  -tam, tam,	// 3 

	//…………………………………………………… Direita
		 tam,  tam,  -tam,	// 4 
		 tam,   tam,  tam,	// 5
		 tam,   -tam, tam,	// 6
		 tam,  -tam, -tam,	// 7

	//……………………………………………………… (Cima
		-tam,  tam,  tam,	//8
		-tam,  tam, -tam,	// 9 
		 tam,  tam, -tam,	// 10 
		 tam,  tam,  tam,	// 11 

	//……………………………………………………Baixo
		tam,  -tam,  tam,	// 12 
		-tam,   -tam,  tam,	// 13 
		-tam,   -tam, -tam,	// 14 
		tam,  -tam, -tam,	// 15 

	//……………………………………………………Frente
		tam,  tam,  tam,	// 16 
		-tam,   tam,  tam,	// 17 
		-tam,   -tam, tam,	// 18 
		tam,  -tam, tam,	// 19 

   //……………………………………………………Back
		tam,  -tam,  -tam,	// 20 
		-tam,   -tam,  -tam,// 21
		-tam,   tam, -tam,	// 22 
		tam,  tam, -tam,	// 23 
};

static GLfloat normais[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,


	  //…………………………………………………………………………………………………… x=tam (Direita)

	   1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,



		//…………………………………………………………………………………………………… y=tam (Cima)
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,


	   //…………………………………………………………………………………………………… baixo

		0.0, -1.0, 0.0,
	   0.0, -1.0, 0.0,
	   0.0, -1.0, 0.0,
	   0.0, -1.0, 0.0,

	   //…………………………………………………………………………………………………… frente
		0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,

	   //…………………………………………………………………………………………………… back
		0.0, 0.0, -1.0,
	   0.0, 0.0, -1.0,
	   0.0, 0.0, -1.0,
	   0.0, 0.0, -1.0,
};
//------------------------------------------------------------ Cores
static GLfloat cor[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda) - BROWN
	  0.0,  0.0, 1.0,	// 0 
	  0.0,  0.0, 1.0,	// 1 
	  0.0,  0.0, 1.0,	// 2 
	  0.0,  0.0, 1.0,	// 3 

	  0.0,  0.0, 1.0,	// 0 
	  0.0,  0.0, 1.0,	// 1 
	  0.0,  0.0, 1.0,	// 2 
	   0.0,  0.0, 1.0,	// 3 
	//…………………………………………………………………………………………………… x=2*tam (Direita) - BROWN
	  0.0,  0.0, 1.0,	// 4 
	   0.0,  0.0, 1.0,	// 5 
	  0.0,  0.0, 1.0,	// 6 
	  0.0,  0.0, 1.0,	// 7 

	  0.0,  0.0, 1.0,	// 0 
	  0.0,  0.0, 1.0,	// 1 
	   0.0,  0.0, 1.0,	// 2 
	   0.0,  0.0, 1.0,	// 3 
	//…………………………………………………………………………………………………… y=tam (Cima) - BROWN
	  0.0,  0.0, 1.0,	// 0 
	  0.0,  0.0, 1.0,	// 1 
	  0.0,  0.0, 1.0,	// 2 
	  0.0,  0.0, 1.0,	// 3 

	  0.0,  0.0, 1.0,	// 8 
	  0.0,  0.0, 1.0,	// 9 
	  0.0,  0.0, 1.0,	// 10 
	  0.0,  0.0, 1.0,	// 11 
};

//Added Texturas
static GLfloat arrayTexture[] = {
0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1,  0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1
};

GLint   frenteVisivel = 0;
static GLuint     cima[] = { 8,11,10,9 };       // regra da mao direita
static GLuint     esquerda[] = { 0, 1, 2, 3 };
static GLuint     direita[] = { 4, 7, 6, 5 };
static GLuint     baixo[] = { 12, 15, 14, 13 };

static GLuint     frente[] = { 16, 17, 18, 19 };
static GLuint     back[] = { 20, 23, 22, 21 };


//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 800, hScreen = 600;			//.. janela (pixeis)
GLfloat		xC = 20.0, yC = 20.0, zC = 20.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao), 3.0, rVisao * sin(aVisao) };
GLfloat  angZoom = 90;
GLfloat  incZoom = 3;

GLfloat xPosition = 0.0, yPosition = 2.0, zPosition = 0.0, zPosJ = 0.0, angle = 0, new_angle = 0, mesaY = 0.1, mesaX = 0, mesaZ = 0, zPosJ2 = 0.0, rot_orient = 1.0;
GLint gav_um = 1, limite = 1, gav_dois = 1, door = 0, hand_1 = 0, hand_2 = 0;

GLint   Dia = 1;     //:::   'D'
GLfloat intensidadeDia = 0.7;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia,intensidadeDia, 1.0 };   //

//---------------------------------------------------- TETO
GLint   ligaTeto = 1;         //:::   'T'
GLfloat intensidadeT = 0.8;  //:::   'I'
GLint   luzR = 1;              //:::   'R'
GLint   luzG = 1;             //:::   'G'
GLint   luzB = 1;             //:::   'B'
GLfloat localPos[4] = { 0, 0.0, 0, 1.0 };   // no teto e é uma luz pontual pois tem w 1.0 se fosse direcional era 0
GLfloat localCorAmb[4] = { (GLfloat)luzR * intensidadeT,(GLfloat)luzG * intensidadeT,(GLfloat)luzB * intensidadeT, 1.0 };
GLfloat localCorDif[4] = { (GLfloat)luzR * intensidadeT,(GLfloat)luzG * intensidadeT,(GLfloat)luzB * intensidadeT, 1.0 };
GLfloat localCorEsp[4] = { (GLfloat)luzR * intensidadeT,(GLfloat)luzG * intensidadeT,(GLfloat)luzB * intensidadeT, 1.0 };


GLint   ligaFoco = 1;
GLfloat focoCutoff = 4.0;
GLfloat focoExponent = 10.0;
GLfloat focoPini[4] = { 0, 1, 1, 1.0 };
GLfloat focoPfim[4] = { 0, 1, 0, 1.0 };
GLfloat focoDir[4] = { focoPfim[0] - focoPini[0], focoPfim[1] - focoPini[1], focoPfim[2] - focoPini[2], 0.0 };
GLint   focoLuzR = 1;             //:::   'R'
GLint   focoLuzG = 1;             //:::   'G'
GLint   focoLuzB = 1;             //:::   'B'
GLfloat focoCorAmb[4] = { (GLfloat)focoLuzR,(GLfloat)focoLuzG,(GLfloat)focoLuzB, 0.0 };
GLfloat focoCorDif[4] = { (GLfloat)focoLuzR,(GLfloat)focoLuzG,(GLfloat)focoLuzB, 0.0 };
GLfloat focoCorEsp[4] = { (GLfloat)focoLuzR,(GLfloat)focoLuzG,(GLfloat)focoLuzB, 0.0 };

//Transparência
GLint Transp = 0;


//nr do material
GLint     material = 11;

GLUquadric* quad;

//…………………………………………………………………………………………………………………………………………… Textura Quadro
void initLights(void) {
	// Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
	// Teto
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);

	//    Foco
	glLightfv(GL_LIGHT1, GL_POSITION, focoPini);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, focoDir);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, focoCutoff);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, focoExponent);
	glLightfv(GL_LIGHT1, GL_AMBIENT, focoCorAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, focoCorDif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, focoCorEsp);
}


//=================================================================== TEXTURAS

//------------------------------------------------------------ Texturas (5 texturas)
GLuint   texture[5];
RgbImage imag;



GLvoid resize(GLsizei width, GLsizei height) {
	wScreen = width;
	hScreen = height;
	glViewport(0, 0, wScreen, hScreen);
	glutPostRedisplay();
}

void initTexturas()
{
	
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("blackwood.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		(GLfloat)imag.GetNumCols(),
		(GLfloat)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());


	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("pedra.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		(GLfloat)imag.GetNumCols(),
		(GLfloat)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("mordenGreyWall.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		(GLfloat)imag.GetNumCols(),
		(GLfloat)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	imag.LoadBmpFile("post.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		(GLfloat)imag.GetNumCols(),
		(GLfloat)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	imag.LoadBmpFile("blueWall.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		(GLfloat)imag.GetNumCols(),
		(GLfloat)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}


//===============================================================================
//     SHADERS -READ, LINK, COMPILE, USAVEL
//===============================================================================
//------------------------------------------ Definição dos ficheiros dos shaders: vertices + fragmentos
char filenameV[] = "Vshader_bin1.txt";
char filenameF[] = "Fshader_bin1.txt";

GLint  uniOp;
GLint  uniDir = 0;
float  Direcao[] = { 1, 0, 0 };
float  opcao = -45;
GLint uniPosition;
GLfloat uniCount = 0;
GLint flagCount = 0;
//---------------------------------------------------------- SHADERS variaveis
char* VertexShaderSource;
char* FragmentShaderSource;
GLuint  VertexShader, FragmentShader;
GLuint  ShaderProgram;


char* readShaderFile(char* FileName);
//============================================= 1. Ler um ficheiro com um shader
char* readShaderFile(char* FileName) {
	char* DATA = NULL;
	int   flength = 0;
	FILE* filepoint;
	errno_t err;

	err = fopen_s(&filepoint, FileName, "r");
	if (!err) {
		fseek(filepoint, 0, SEEK_END);
		flength = ftell(filepoint);
		rewind(filepoint);

		DATA = (char*)malloc(sizeof(char) * (flength + 1));
		flength = fread(DATA, sizeof(char), flength, filepoint);

		DATA[flength] = '\0';
		fclose(filepoint);
		return DATA;
	}
	else {
		printf(" --------  Error while reading  %s ", FileName);
	}
}
//============================================= 2. Criar, compilar, linkar, e usar
void BuiltShader(void) {

	// GLEW_ARB_vertex_shader;
	// GLEW_ARB_fragment_shader;

	//......................................................... Criar
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	VertexShaderSource = readShaderFile(filenameV);
	FragmentShaderSource = readShaderFile(filenameF);

	const char* VS = VertexShaderSource;
	const char* FS = FragmentShaderSource;
	glShaderSource(VertexShader, 1, &VS, NULL);
	glShaderSource(FragmentShader, 1, &FS, NULL);
	free(VertexShaderSource);
	free(FragmentShaderSource);

	//......................................................... Compilar
	glCompileShaderARB(VertexShader);
	glCompileShaderARB(FragmentShader);

	//......................................................... Criar e Linkar
	ShaderProgram = glCreateProgramObjectARB();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	//......................................................... Usar
	glUseProgramObjectARB(ShaderProgram);
}

void InitShader(void) {
	//------------------------ Criar+linkar
	BuiltShader();
	uniPosition = glGetUniformLocation(ShaderProgram, "PositionNumber");
	glUniform1f(uniPosition, uniCount);

	glUniform1f(uniOp, opcao);
	glUniform3fv(uniDir, 1, Direcao);

	Direcao[0] = cos((3.14 * opcao / 180.0));
	Direcao[2] = sin((3.14 * opcao / 180.0));

	uniDir = glGetUniformLocation(ShaderProgram, "Direcao");
	glUniform3fv(uniDir, 1, Direcao);
	uniOp = glGetUniformLocation(ShaderProgram, "opcao");
	glUniform1f(uniOp, opcao);

}
//============================================= 3.Libertar os Shaders
void DeInitShader(void) {
	glDetachShader(ShaderProgram, VertexShader);
	glDetachShader(ShaderProgram, FragmentShader);
	glDeleteShader(ShaderProgram);

}
//===============================================================================
//     SHADERS -READ, LINK, COMPILE
//===============================================================================




//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
	glClearColor(WHITE);        //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖApagar
	glShadeModel(GL_SMOOTH);    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖInterpolacao de cores
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖProfundidade

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	initLights();
	initMaterials(3);
	initTexturas();

	glVertexPointer(3, GL_FLOAT, 0, vertices); //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖVertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, arrayTexture);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
void draw_meta3() {
	glPushMatrix();
	InitShader();
	glTranslatef(1.5, 1.55, 2);
	quad = gluNewQuadric();
	gluSphere(quad, 2, 100, 20);
	DeInitShader();
	glLinkProgram(NULL);
	glPopMatrix();
}


void drawChao() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	//glNormal3f(0, 1, 0);
	
	glTranslatef(0, 0.0, 0);
	//glColor4f(BLACK);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);  	 glVertex3i(-xC, 0, -xC);
	glTexCoord2f(1.0f, 0.0f); 	 glVertex3i(-xC, 0, xC);
	glTexCoord2f(1.0f, 1.0f);    glVertex3i(xC, 0, xC);
	glTexCoord2f(0.0f, 1.0f);    glVertex3i(xC, 0, -xC);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawFundoLid() {

	
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTranslatef(0.0, 2.45, 0.0 - 0.9);
	glScalef(1.8, 0.1, 0.8);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar uma das faces da mesa
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Door_Handle(){
	/*TODO */
	
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[3]);
	initMaterials(11);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();
	//initMaterials(11);
	glTranslatef(0.6+hand_2, 2.45,0.22);
	glRotatef(-new_angle, 0.0, 1.0, 0.0);
	glScalef(0.22, 0.08,0.11);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar uma das faces da mesa
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);
	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);
}

void Door_Handle2() {
	/*TODO */
	
	//glEnable(GL_COLOR_MATERIAL);
	//glColor4f(BLUE);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_Ambient);
	//
	//
	initMaterials(11);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();
	//
	glTranslatef(-0.4-hand_1, 2.45, 0.22);
	glRotatef(-new_angle, 0.0, 1.0, 0.0);
	glScalef(0.22, 0.08, 0.11);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar uma das faces da mesa
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);
	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);
}

void drawEixos(){

	
	glPushMatrix();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(10, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 10, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 10);
	glEnd();

	glPopMatrix();

}

void drawGaveta() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	//
	glTranslatef(0.0, 0.68, zPosJ2 - 0.9);
	//glRotatef(angle, 0.0, 1.0, 0.0);
	glScalef(1.8, 0.6, 0.8);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda); // desenhar uma das faces da mesa
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawGaveta2() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	
	glTranslatef(0.0, 1.90, zPosJ - 0.9);
	//glRotatef(angle, 0.0, 1.0, 0.0);
	glScalef(1.8, 0.6, 0.8);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda); // desenhar uma das faces da mesa
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawFundo() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	
	
	glTranslatef(0.0, 2.0, -0.9);
	glRotatef(90, 1.0, 0.0, 0.0);
	glScalef(2, 1.0, 2);
	//----------------------------------------------

	
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawPortaEsq() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glColorPointer(3, GL_FLOAT, 0, cor);	// podia ser modificada a cor !
	glPushMatrix();
	
	glTranslatef(-rot_orient, yPosition, zPosition);
	glRotatef(-new_angle, 0.0, 1.0, 0.0);
	glScalef(1.0, 2.0, 0.1);
	
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar uma das faces da mesa
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


void drawPortaDir() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glColorPointer(3, GL_FLOAT, 0, cor);	 podia ser modificada a cor !
	glPushMatrix();
	
	glTranslatef(rot_orient, yPosition, zPosition);
	glRotatef(new_angle, 0.0, 1.0, 0.0);
	glScalef(1, 2, 0.1);


	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar uma das faces da mesa
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);



}



void drawVidro() {
	if(Transp){
		glEnable(GL_BLEND);
	}
	
	//glColorPointer(3, GL_FLOAT, 0, cor);	// podia ser modificada a cor !
	glPushMatrix();
	initMaterials(5);
	glTranslatef(0.0, 3.2, -0.1);
	glRotatef(0.0, 0.0, 1.0, 0.0);
	glScalef(1.8, 0.6, 0.1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar uma das faces da mesa
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);

	glPopMatrix();
	if (Transp) {
		glDisable(GL_BLEND);
	}
}






void iluminacao() {
	if (ligaTeto)  glEnable(GL_LIGHT0);
	else             glDisable(GL_LIGHT0);
}

void iluminacaoFoco() {
	if (ligaFoco)  glEnable(GL_LIGHT1);
	else             glDisable(GL_LIGHT1);
}


void display(void) {

	//================================================================= APaga ecrã e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	//================================================================= Não modificar !!!!!!!!!!!!
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3.0 * (float)zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	//================================================================= Não modificar !!!!!!!!!!!!

	
	//…………………………………………………………………………………………………………………………………………………………Objectos
	iluminacao();
	iluminacaoFoco();
	Door_Handle();
	Door_Handle2();
	drawEixos();
	drawChao();
	drawGaveta();
	drawFundo();
	drawFundoLid();
	drawGaveta2();
	drawPortaEsq();
	drawPortaDir();
	drawVidro();
	//draw_meta3();
	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

//======================================================= EVENTOS

void updateLuz() {
	localCorAmb[0] = luzR * intensidadeT;
	localCorAmb[1] = luzG * intensidadeT;
	localCorAmb[2] = luzB * intensidadeT;
	localCorDif[0] = luzR * intensidadeT;
	localCorDif[1] = luzG * intensidadeT;
	localCorDif[2] = luzB * intensidadeT;
	localCorEsp[0] = luzR * intensidadeT;
	localCorEsp[1] = luzG * intensidadeT;
	localCorEsp[2] = luzB * intensidadeT;;
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	/*case 'f':
	case 'F':
		if (limite) {
			new_angle += 24;
			if (new_angle > 89) {
				door = 1;
				limite = 0;
			}
				
		}
		else {
			new_angle -= 24;
			if (new_angle < 0.1) {
				limite = 1;
				door = 0;
			}
				
		}



		glutPostRedisplay();
		break;
		*/

	case 'd':
	case 'D':
		Dia = !Dia;
		if (Dia) { luzGlobalCorAmb[0] = 0.7;   luzGlobalCorAmb[1] = 0.7;   luzGlobalCorAmb[2] = 0.7; }
		else { luzGlobalCorAmb[0] = 0.2;   luzGlobalCorAmb[1] = 0.2;   luzGlobalCorAmb[2] = 0.2; }
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
		glutPostRedisplay();
		break;

		//--------------------------- TETO
	case 'c':
	case 'C':
		ligaTeto = !ligaTeto;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'z':
	case 'Z':
		ligaFoco = !ligaFoco;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'b':
	case 'B':
		opcao = opcao + 10;
		glutPostRedisplay();
		break;

		//--------------------------- Iluminacaoda sala
	case 'i':
	case 'I':
		intensidadeT = intensidadeT + 0.1;
		if (intensidadeT > 1.1) intensidadeT = 0;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'v':
	case 'V':
		luzR = (luzR + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		luzG = (luzG + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		luzB = (luzB + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	
	case 'p':
	case 'P':
		Transp = !Transp;
		glutPostRedisplay();
		break;

	case 'l':
	case 'L':
		if (door) {
			if (gav_um) {
				zPosJ += 0.125;

				if (zPosJ > 1.5)
					gav_um = 0;
			}
			else {
				zPosJ -= 0.2;

				if (zPosJ < 0.1)
					gav_um = 1;
			}
			glutPostRedisplay();
			break;
		}
	case 'k':
	case 'K':
		if (door){
			if (gav_dois) {
				zPosJ2 += 0.125;

				if (zPosJ2 > 1.5)
					gav_dois= 0;
			}
			else {
				zPosJ2 -= 0.125;

				if (zPosJ2 < 0.1)
					gav_dois = 1;
			}
			glutPostRedisplay();
			break;
		}
	case 'm':
	case 'M':
		material = (material + 1) % 18;
		initMaterials(material);
		glutPostRedisplay();
	case 'o':
	case 'O':
		if (uniCount > 10) {
			flagCount = 1;
		}
		else if (uniCount < 0) {
			flagCount = 0;
		}

		if (flagCount == 0) {
			if (uniCount < 2) {
				uniCount = uniCount + 1;
			}
			else if (uniCount < 4) {
				uniCount = uniCount + 0.7;
			}
			else if (uniCount < 9) {
				uniCount = uniCount + 0.5;
			}
			else
				uniCount = uniCount + 0.2;
		}
		else {
			if (uniCount > 9) {
				uniCount = uniCount - 0.25;
			}
			else if (uniCount > 4) {
				uniCount = uniCount - 0.5;
			}
			else
				uniCount = uniCount - 1;
		}

		glutPostRedisplay();
		break;
	case 'q':
	case 'Q':
		if (!door)  {
			//mudar o angulo para ter uma media e a porta ir arrastando

			new_angle = 90;
			rot_orient = 1.9;
			zPosition = 1.0;
			
			door = 1;
		}
		else {
			hand_1 = 0;
			hand_2 = 0;
			new_angle = 0;
			rot_orient = 1.0;
			zPosition = 0.0;
			door = 0;
		}
	}
}

void teclasNotAscii(int key, int x, int y) {
	//.. observador pode andar à volda da cena  (setas esquerda / direita)
	//.. observador pode andar para cima e para baixo (setas cima / baixo )

	if (key == GLUT_KEY_UP)   obsP[1] = (obsP[1] + 0.1);
	if (key == GLUT_KEY_DOWN) obsP[1] = (obsP[1] - 0.1);
	if (key == GLUT_KEY_LEFT)  aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT) aVisao = (aVisao - 0.1);


	if (obsP[1] > yC)   obsP[1] = yC;   // limita altura
	if (obsP[1] < -yC)  obsP[1] = -yC;

	obsP[0] = rVisao * cos(aVisao);      // actualiza posicao (X,Z)
	obsP[2] = rVisao * sin(aVisao);

	glutPostRedisplay();
}
void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Etiandro António - 2017290285|    |Mover gaveta 1:'L'|    |Mover gaveta 2:'K'|   |Abrir/fechar portas:'Q'|      |Observador:'SETAS'|  ");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutTimerFunc(msec, Timer, 1);
	glutMainLoop();

	return 0;
}


