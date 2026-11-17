// Textura.cpp - Isabel H. Manssour
// Um programa OpenGL que exemplifica a visualização
// de objetos 3D com mapeamento de textura.
// Este código está baseado nos exemplos disponíveis no livro
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.

#define STB_IMAGE_IMPLEMENTATION
#include <GL/glut.h>
#include <stdio.h>
#include "stb_image.h"

// Variáveis globais
double angle, fAspect;
float rotX, rotY, obsZ; 
int luz;
int idTexture[10];
//int width, height;


// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
{
	//Define os parâmetros através de vetores RGBA - o último valor deve ser sempre 1.0f
		float luzAmbiente[]={0.2f, 0.2f, 0.2f, 1.0f}; 
		float luzDifusa[]={1.0f, 1.0f, 1.0f, 1.0f};  
		float luzEspecular[]={1.0f, 1.0f, 1.0f, 1.0f};
		float posicaoLuz[]={40.0f, 60.0f, 0.0f, 1.0f}; // último parâmetro: 0-direcional, 1-pontual/posicional 

		float posicaoLuz2[]={-40.0f, 60.0f, 0.0f, 1.0f};
		float luzEspecular2[]={1.0f, 1.0f, 1.0f, 0.0f};
		float luzDifusa2[]={1.0f, 1.0f, 1.0f, 1.0f};
		
		//Ativa o uso da luz ambiente 
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

		//Define os parâmetros da luz de número 0
		glLightfv(GL_LIGHT0,GL_AMBIENT, luzAmbiente); 
		glLightfv(GL_LIGHT0,GL_DIFFUSE, luzDifusa );
		glLightfv(GL_LIGHT0,GL_SPECULAR, luzEspecular);
		glLightfv(GL_LIGHT0,GL_POSITION, posicaoLuz ); 	
		
		//Define os parâmetros da luz de número 1
		glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente); 
		glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa2 );
		glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular2);
		glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz2); 
		
		// Brilho do material
		float especularidade[]={1.0f, 1.0f, 1.0f, 1.0f};
		int especMaterial = 60;

		// Define a reflectância do material 
		glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
		// Define a concentração do brilho
		glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
}

// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Especifica posição do observador e do alvo
	glTranslatef(0,0,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();
    // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle, fAspect, 0.2, 500);

	PosicionaObservador();
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
		
	if (luz)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
		
	EspecificaParametrosVisualizacao(); 
	DefineIluminacao();
		
	glLineWidth(2);

		
	// Desenha uma esfera azul
	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
		glTranslatef(30.0f, 0.0f, 0.0f);
		glutSolidSphere(24, 30, 30);
	glPopMatrix();
	
	// Desenha um cubo no qual a textura é aplicada
	glEnable(GL_TEXTURE_2D);	// Primeiro habilita uso de textura	  	
	glPushMatrix();
		glTranslatef(-30.0f, 0.0f, 0.0f);
		glScalef(16.0f, 16.0f, 16.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin (GL_QUADS );
		// Especifica a coordenada de textura para cada vértice
			// Face frontal
			glNormal3f(0.0f,0.0f,-1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);				
			// Face posterior
			glNormal3f(0.0f,0.0f,1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
			// Face superior
			glNormal3f(0.0f,1.0f,0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
			// Face inferior
			glNormal3f(0.0f,-1.0f,0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
			// Face lateral direita
			glNormal3f(1.0f,0.0f,0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
			// Face lateral esquerda
			glNormal3f(-1.0f,0.0f,0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);	//	Desabilita uso de textura
	glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Especifica o ângulo da projeção perspectiva  
	angle=50;   
		// Inicializa o valor para correção de aspecto   
	fAspect = 1; 
		
	// Inicializa os atributos usados para alterar a posição do 
	// observador virtual (=câmera)
	rotX = 0;
	rotY = 0;
	obsZ = 200; 
	
	luz = 1;

	int width, height, nrChannels;
	glEnable(GL_DEPTH_TEST);    
		
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
		
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);	
		
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
	  	
	// Comandos de inicialização para textura
	unsigned char *data = stbi_load("xadrez.jpg", &width, &height, &nrChannels, 0);
     
		
	// Gera identificador de textura	
	glGenTextures(1, idTexture);
		
	// Especifica qual é a textura corrente pelo identificador 
	glBindTexture(GL_TEXTURE_2D, idTexture[0]);	


	if (data)	{
	// Envio da textura para OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR,GL_UNSIGNED_BYTE, data);
	}
	else{
        printf("Failed to load texture" );
    }
	
	// Define os filtros de magnificação e minificação 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);   

	stbi_image_free(data); 

}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w,h);
	fAspect = (float)w/(float)h; 
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 40) angle -= 4;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 72) angle += 4;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Callback para gerenciar eventos do teclado para teclas especiais
void TeclasEspeciais(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:rotY--;
				break;
		case GLUT_KEY_RIGHT:rotY++;
				break;
		case GLUT_KEY_UP:rotX++;
				break;
		case GLUT_KEY_DOWN:rotX--;
				break;
		case GLUT_KEY_HOME:obsZ++;
				break;
		case GLUT_KEY_END:obsZ--;
				break;
		case GLUT_KEY_F1: if (luz) luz = 0;
		else luz = 1;
		break;		
		case GLUT_KEY_F10:// "camera reset"
				rotX=0;
				rotY=0;
				obsZ=200;
				angle=50;
				EspecificaParametrosVisualizacao();
				break;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Programa Principal
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("Visualizacao 3D com Mapeamento de Textura");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutSpecialFunc(TeclasEspeciais);
	Inicializa();
	glutMainLoop();
}
