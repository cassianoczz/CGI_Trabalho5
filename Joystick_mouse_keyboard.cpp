#include<bits/stdc++.h>
#include <unistd.h>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "common/shader.hpp"
// Include AntTweakBar
#include "AntTweakBarCode/AntTweakBar/include/AntTweakBar.h"
GLFWwindow* window;
using namespace glm;

#define NUM_SHAPES 3
typedef enum { SHAPE_TEAPOT=1, SHAPE_TORUS, SHAPE_CONE } Shape;
Shape g_CurrentShape = SHAPE_TORUS;
const GLint WIDTH = 1280, HEIGHT = 768;
const GLfloat R = 0.0f, G = 0.0f, B = 0.3f, A = 0.0f;

bool selecionamm = false;
bool selecionahulk = false;
bool selecionaanime = false;

double zoommm = 1.0f;
double zoomhulk = 1.0f;

double xposMouse, yposMouse, Person, present;
int widthWindow, heightWindow;

const float mp = 3.1415926/180.0;
const float uqp = 3.1415926/90.0;

float XT=0,YT=0,GRAUS=0,XE=1,YE=1,TANXS=0, TANYS=0, E=1, XTM=0,YTM=0,GRAUSM=0,XEM=1,YEM=1,TANXSM=0, TANYSM=0, EM=1.0;
GLuint colorbuffer, vertexbuffer, MatrixIDXT, MatrixIDYT, MatrixIDGRAUS, MatrixIDXE, MatrixIDYE, MatrixIDTANXS, MatrixIDTANYS, MatrixIDE, MatrixIDXTM, 
MatrixIDYTM, MatrixIDGRAUSM, MatrixIDXEM, MatrixIDYEM, MatrixIDTANXSM, MatrixIDTANYSM, MatrixIDEM,programID, intPerson;

char * instrucoes = strdup ( "Primeiramente Selecione o personagem na Barra da esquerda clicando no desejado" ) ;
char * instrucoes2 = strdup ( "Para animacao clique na opcao correspondente na Barra da esquerda." ) ;
char * instrucoes3 = strdup ( "Para selecionar os personagens nas configuracoes de Origem pressione a tecla R " ) ;
char * itranslacao = strdup ( "Clique o botão direito do mouse, e arraste para transladar " ) ;
char * irotacao = strdup ( "Horario: Seta pra cima + Seta pra direita, Anti Horario: Seta pra cima + Seta pra esquerda" ) ;
char * iescalanuniforme = strdup ( "Pra Y: Seta pra cima + Seta pra Baixo, Para X: Seta pra Esquerda + Seta pra Direita" ) ;
char * iescalauniforme = strdup ( "Pra aumentar: Seta pra Cima, Pra diminuir: Seta Pra Baixo" ) ;
char * ishearx = strdup ( "Para X: Shift + Seta Esquerda (AntiHorario), Shift + Seta Direita (Horario)" ) ;
char * isheary = strdup ( "Para Y: Shift + Seta pra Baixo (Diminui), Shift + Seta pra Cima (Cresce)" ) ;


GLfloat cabelo_mm[] = { 
//Parte SUPERIOR		
	-0.082f, 0.73f,//base e
	 0.082f,0.73f, //base d
	-0.082,0.78f, 
	 0.082f,0.73f, //base d
	-0.082f,0.78f, // altura e
	 0.082f,0.78f,//a d
//G lado e
	-0.082f,0.73f,//altura e
	-0.082f,0.47f,//b e
	-0.06f,0.47f,//b d
	-0.082f,0.73f,//altura e
	-0.06f,0.47f,//b d
	-0.06f,0.73f,//a d
//G Baixo C
	-0.06f,0.51f,//a d
	-0.06f, 0.47f,//b 
	-0.03f,0.47f,//b d
	-0.06f,0.51f,//a d
	-0.03f,0.47f,//b d
	-0.03f,0.51f,//a e
//G lado d
	0.082f,0.73f,//altura e
	0.082f,0.47f,//b e
	0.06f,0.47f,//b d		
	0.082f,0.73f,//altura e
	0.06f,0.47f,//b d
	0.06f,0.73f,//a d
//G Baixo C d
	0.06f,0.51f,//a d
	0.06f, 0.47f,//b e
	0.03f,0.47f,//b d
	0.06f,0.51f,//a d
	0.03f,0.47f,//b d
	0.03f,0.51f,//a e
};

//CORPO_SUPERIOR
GLfloat corpo_mm[] = {
//CABEÇA
	-0.06f, 0.51f,//base esquerda
	 0.06f,0.51f,//base direita
	-0.06f,0.70f,//altura esquerda
	 0.06f, 0.70f,//altura direita
	 0.06f,0.51f,//base direita
	-0.06f,0.70f,//altura esquerda

//PESCOCO
	-0.03f, 0.47f,
	 0.03f, 0.47f,
	-0.03f, 0.51f,
	 0.03f, 0.47f,
	-0.03,0.51f,
	 0.03f,0.51f,
//OMBROS
	 0.145f,0.47f,//altura direita
	 0.145f,0.38f,//base direita
	-0.145f,0.38f,//base esquerda
	-0.145f,0.38f,//base esquerda
	 0.145f,0.47f,//altura direita
	-0.145f,0.47f,//altura esquerda
//BRACO DIREITO
	0.145f,0.38f,//altura esquerda
	0.145,0.15f, //base esquerda
	0.110f,0.38f,//base direita
	0.145,0.15f, //base esquerda
	0.110f,0.38f,//altura direita
	0.110f,0.15f,//base direita
//MAO DIREITA
	0.145f, -0.01f, //altura esquerda
	0.110f, 0.01f, //altura direita
	0.145f, -0.12f,//base esquerda
	0.110f, 0.01f, //altura direita
	0.145f, -0.12f,//base esquerda
	0.110f,-0.12f,//base direita
//BRACOS ESQUERDO
	-0.145f,0.38f,//altura esquerda
	-0.145,0.15f, //base esquerda
	-0.110f,0.38f,//base direita
	-0.145,0.15f, //base esquerda
	-0.110f,0.38f,//altura direita
	-0.110f,0.15f,//base direita
//MAO ESQUERDA
	-0.145f, -0.01f, //altura esquerda
	-0.110f, 0.01f, //altura direita
	-0.145f, -0.12f,//base esquerda
	-0.110f, 0.01f, //altura direita
	-0.145f, -0.12f,//base esquerda
	-0.110f,-0.12f,//base direita
//PERNAS
//PERNA ESQUERDA
	-0.1f, -0.12f,
	-0.03f, -0.12f,
	-0.1f, -0.42f,
	-0.03f, -0.12f,
	-0.1f, -0.42f,
	-0.03f, -0.42f,
//PERNA DIREITA
	0.1f, -0.12f,
	0.03f, -0.12f,
	0.1f, -0.42f,
	0.03f, -0.12f,
	0.1f, -0.42f,
	0.03f, -0.42f,
};

//BRACELETES
GLfloat braceletes_mm[] = {
//BRACELETE DIREITO
	0.145f,-0.01f, //base esquerda
	0.110f,0.15f,//altura direita
	0.110f,-0.01f,//base direita
	0.145f,-0.01f, //base esquerda
	0.110f,0.15f,//altura direita
	0.145f,0.15f,//altura esquerda
//BRACELETE ESQUERDO
	-0.145f,-0.01f, //base esquerda
	-0.110f,0.15f,//altura direita
	-0.110f,-0.01f,//base direita
	-0.145f,-0.01f, //base esquerda
	-0.110f,0.15f,//altura direita
	-0.145f,0.15f,//altura esquerda
};

//vemelho
GLfloat vermelho_mm[] = {
//pedra_tiara
	-0.02f, 0.70f, //base esquerda
	 0.02f, 0.70f,
	-0.02f, 0.73f, //altura esquerda
	 0.02f, 0.73f, //alt d
	 0.02f, 0.70f, 
	-0.02f, 0.73f, //alt e

//pedra_detalhe_peito_mm
	-0.01f, 0.36f,
	 0.01f, 0.36f,
	-0.01f, 0.38f,
	 0.01f, 0.38f,
	 0.01f, 0.36f,
	-0.01f, 0.38f,
//abdomem
	-0.09f, 0.0f,//base lado esquerdo
	 0.09f, 0.0f,//base lado direito
	-0.09f, 0.25f,//altura lado esquedo
	-0.09f, 0.25f,
	 0.09f, 0.25f,
	 0.09f, 0.00f,

//BOTA ESQUERDA
	-0.1f, -0.42f,
	-0.03f, -0.42f,
	-0.1f, -0.64f,
	-0.03f, -0.42f,
	-0.1f, -0.64f,
	-0.03f, -0.64f,
//BOTA DIREITA
	0.1f, -0.42f,
	0.03f, -0.42f,
	0.1f, -0.64f,
	0.03f, -0.42f,
	0.1f, -0.64f,
	0.03f, -0.64f,
};

GLfloat amarelo_mm[] = {
//FAIXA CABECA
	-0.06f, 0.70f,//base esquerda
	-0.02f,0.70f,
	-0.06f,0.73f,//altura esquerda
	-0.02f, 0.73f,//altura direita
	-0.02f,0.70f,
	-0.06f,0.73f,//altura esquerda

	0.06f, 0.70f,//base esquerda
	0.02f,0.70f,
	0.06f,0.73f,//altura esquerda
	0.02f, 0.73f,//altura direita
	0.02f,0.70f,
	0.06f,0.73f,//altura esquerda
//PEITO
	-0.1f, 0.36f,
	-0.01f, 0.36f,
	-0.1f, 0.38f,
	-0.01f, 0.38f,
	-0.01f, 0.36f,
	-0.1f, 0.38f,

    0.1f, 0.36f,
	0.01f, 0.36f,
	0.1f, 0.38f,
	0.01f, 0.38f,
	0.01f, 0.36f,
	0.1f, 0.38f,

	-0.1f, 0.25f, //base esquerda
	-0.1f,0.36f, //altura esquerda
	 0.1f, 0.25f, //base direita
	 0.1f, 0.25f, //base direita
	-0.1f,0.36f, //altura esquerda
	 0.1f, 0.36f,//altura direita

//Detalhes Peito
	-0.03f, 0.22f,
	 0.03f, 0.22f,
	-0.03f, 0.25f,
	 0.03f, 0.25f,
	 0.03f, 0.22f,
	-0.03f, 0.25f,

	-0.01f, 0.16f,
	 0.01f, 0.16f,
	-0.01f, 0.22f,
	 0.01f, 0.22f,
	 0.01f, 0.16f,
	-0.01f, 0.22f,

//CINTO 
	-0.1f, -0.03f,
	-0.1f, 0.00f,
	 0.1f, 0.00f,
	 0.1f, 0.00f,	
	-0.1f, -0.03f,
	 0.1f, -0.03f,

//CABO LAÇO e
	-0.145f,-0.06f,// altura e
	-0.175f,-0.09f,//base d
	-0.175f,-0.06f,// base e
	-0.145,-0.06f,// altura e
	-0.175f,-0.09f,//base d
	-0.145f,-0.09f,// base d
//CABO LAÇO d
	-0.08f,-0.06f,// altura e
	-0.110f,-0.09f,//base d
	-0.110f,-0.06f,// base e
	-0.08f,-0.06f,// altura e
	-0.110f,-0.09f,//base d
	-0.08f,-0.09f,// base d
};

//LAÇO MULHER MARAVILHA
GLfloat laco_mm[] = {
	-0.175f,-0.075f,
	-0.3f,-0.075f,
	-0.3f, -0.35f,
	-0.175f, -0.35f,
	-0.175f, -0.12f,
	-0.28f, -0.12f,
	-0.28f, -0.30f,
	-0.195f, -0.30f,
	-0.195f, -0.15f,
	-0.26f, -0.15f,
};

// SAIA MUL MAR
GLfloat saia_mm[] = {
	-0.1f, -0.06f,
	-0.1f, -0.03f,
	 0.1f, -0.06f,
	 0.1f, -0.06f,
	 0.1f, -0.03f,
	-0.1f, -0.03f,
	-0.08f, -0.09f,
	-0.08f, -0.06f,
	 0.1f, -0.06f,
	-0.08f, -0.09f,
	 0.1f, -0.06f,
	 0.1f, -0.09f,
	-0.1f, -0.12f,
	-0.1f, -0.09f,
	 0.1f, -0.12f,
	 0.1f, -0.12f,
	 0.1f, -0.09f,
	-0.1f, -0.09f,
};

//CALÇÃO DO HULK
GLfloat calcao_hulk[] = {
	0.9f, -0.5f,
	0.85f, -0.5f,
	0.85f,  -0.6f,	
	0.9f, -0.7f,
	0.85f, -0.7f,
	0.85f,  -0.6f,	
	0.9f, -0.7f,
	0.85f,  -0.6f,
	0.9f, -0.5f,
	0.825f, -0.5f,
	0.775f, -0.5f,
	0.775f,  -0.6f,	
	0.825f, -0.7f,
	0.775f, -0.7f,
	0.775f,  -0.6f,	
	0.825f, -0.7f,
	0.775f,  -0.6f,
	0.825f, -0.5f,
	0.825f, -0.5f,
	0.825f, -0.566f,
	0.850f, -0.5f,
	0.825f, -0.566f,
	0.850f, -0.5f,
	0.850f, -0.566f,
};


//PARTES VERDES HULK
GLfloat corpo_hulk[] = {
	//PERNA DIREITA HULK			 
	0.9f, -0.7f,
	0.85f, -0.7f,
	0.85f,  -0.8f,	
	0.9f, -0.9f,
	0.85f, -0.9f,
	0.85f,  -0.8f,	
	0.9f, -0.9f,
	0.85f,  -0.8f,
	0.9f, -0.7f,

//PERNA ESQUERDA HULK
	0.825f, -0.7f,
	0.775f, -0.7f,
	0.775f,  -0.8f,	
	0.825f, -0.9f,
	0.775f, -0.9f,
	0.775f,  -0.8f,	
	0.825f, -0.9f,
	0.775f,  -0.8f,
	0.825f, -0.7f,

	0.775f, -0.5f,
	0.775f, -0.25f,
	0.9f, -0.25f,	
	0.775f, -0.5f,
	0.9f, -0.25f,
	0.9f, -0.5f,

//MUSCULOS PESCOÇO
	0.795f,-0.25f,
	0.775f, -0.25f,
	0.795f,-0.222f,
	0.88f,-0.25f,
	0.9f, -0.25f,
	0.88f,-0.222f,
//CABEÇA HULK
	0.795f,-0.15f,
	0.88f,-0.15f,
	0.795f,-0.25f,
	0.88f,-0.15f,
	0.795f,-0.25f,
	0.88f,-0.25f,

//BRAÇO ESQUERDO HULK
	0.775f, -0.25f,
	0.735f, -0.25f,
	0.775f, -0.33f,
	0.765f, -0.33f,
	0.735f, -0.25f,
	0.775f, -0.33f,
	0.765f, -0.33f,
	0.735f, -0.25f,
	0.735f, -0.566f,
	0.735f, -0.566f,
	0.765f, -0.33f,
	0.765f, -0.566f,

//BRACO DIREITO HULK
	0.9f, -0.25f,
	0.9f, -0.33f,
	0.94f, -0.25f,
	0.9f, -0.33f,
	0.91f, -0.33f,
	0.94f, -0.25f,
	0.94f, -0.25f,
	0.91f, -0.33f,
	0.94f, -0.566f,
	0.94f, -0.566f,
	0.91f, -0.33f,
	0.91f, -0.566f,
};
	
//CABELO HULK
GLfloat cabelo_hulk[] = {
	0.795f,-0.12f,
	0.88f,-0.12f,
	0.795f,-0.15f,
	0.88f,-0.12f,
	0.795f,-0.15f,
	0.88f,-0.15f,
};

void adicionaBarras(){
	// Initialize the GUI
	TwInit(TW_OPENGL_CORE, NULL);
	TwWindowSize(WIDTH, HEIGHT-50);//Alterar tamanho da Janela

	TwBar * bar = TwNewBar("Barra de Controle");
	TwBar * bar2 = TwNewBar("Barra de Informacoes");

	TwSetParam(bar, NULL, "position", TW_PARAM_CSTRING, 1, "15 15");
	TwSetParam(bar, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");
    TwDefine(" Nessa Bara voce realiza a selecao dos personagens e a animação' "); // Message added to the help bar.
    TwAddVarRW(bar, "Select MM", TW_TYPE_BOOL8 , &selecionamm, NULL);
    TwAddVarRW(bar, "Select HULK", TW_TYPE_BOOL8 , &selecionahulk, NULL);
    TwAddVarRW(bar, "Escalar Uniforme MM", TW_TYPE_DOUBLE, &zoommm, 
        " label='Escalar Unif MM' min=0 max=20 step=0.001  help='Mostra qual a escala atual do personagem' ");

    TwAddVarRW(bar, "Escalar Uniforme Hulk", TW_TYPE_DOUBLE, &zoomhulk, 
        " label='Escalar Unif Hulk' min=0 max=20 step=0.001  help='Mostra qual a escala atual do personagem' ");

    TwAddVarRW(bar, "ANIMAR", TW_TYPE_BOOL8 , &selecionaanime, NULL);

	TwDefine(" Nessa Bara voce realiza a selecao dos personagens e a animação' "); // Message added to the help bar.
    TwSetParam(bar2, NULL, "position", TW_PARAM_CSTRING, 1, "1050 15");
	TwSetParam(bar2, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");
    TwAddVarRW(bar2, "1. ", TW_TYPE_CDSTRING , &instrucoes, NULL);
    TwAddVarRW(bar2, "2. ", TW_TYPE_CDSTRING , &instrucoes2, NULL);
    TwAddVarRW(bar2, "3. ", TW_TYPE_CDSTRING , &instrucoes3, NULL);
    TwAddVarRW(bar2, "Translacao:", TW_TYPE_CDSTRING , &itranslacao, NULL);
    TwAddVarRW(bar2, "Rotacao:", TW_TYPE_CDSTRING , &irotacao, NULL);
    TwAddVarRW(bar2, "Escala Nao Unif:", TW_TYPE_CDSTRING , &iescalanuniforme, NULL);
    TwAddVarRW(bar2, "Escala Unif:", TW_TYPE_CDSTRING , &iescalauniforme, NULL);
    TwAddVarRW(bar2, "Shear X:", TW_TYPE_CDSTRING , &ishearx, NULL);
    TwAddVarRW(bar2, "Shear Y:", TW_TYPE_CDSTRING , &isheary, NULL);
}


void shaderLoadCreat(){
	programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
	intPerson = glGetUniformLocation(programID, "Person");// PASSA A LOCALIZACAO DA VARIAVEL DA ESCOLHA DO PERSONAGEM PRO VERTEX SHADER
	MatrixIDXTM = glGetUniformLocation(programID, "XTM");
	MatrixIDYTM = glGetUniformLocation(programID, "YTM");
	MatrixIDGRAUSM = glGetUniformLocation(programID, "GRAUSM");
	MatrixIDXEM = glGetUniformLocation(programID, "XEM");
	MatrixIDYEM = glGetUniformLocation(programID, "YEM");
	MatrixIDTANXSM = glGetUniformLocation(programID, "TANXSM");
	MatrixIDTANYSM = glGetUniformLocation(programID, "TANYSM");
	MatrixIDEM = glGetUniformLocation(programID, "EM");
	MatrixIDXT = glGetUniformLocation(programID, "XT");
	MatrixIDYT = glGetUniformLocation(programID, "YT");
	MatrixIDGRAUS = glGetUniformLocation(programID, "GRAUS");
	MatrixIDXE = glGetUniformLocation(programID, "XE");
	MatrixIDYE = glGetUniformLocation(programID, "YE");
	MatrixIDTANXS = glGetUniformLocation(programID, "TANXS");
	MatrixIDTANYS = glGetUniformLocation(programID, "TANYS");
	MatrixIDE = glGetUniformLocation(programID, "E");
}

GLfloat *colorir(int tam, float R, float G, float B){
	int i;
	//alocação dinâmica
	GLfloat *color_core = (GLfloat *)malloc((int)((tam/sizeof(GLfloat))+(tam/sizeof(GLfloat))/2)*sizeof(GLfloat));

		for(i=0;i<(tam/sizeof(GLfloat))+(tam/ sizeof(GLfloat))/2;i+=3){
		color_core[i] = R;
		color_core[i+1] = G;
		color_core[i+2] = B; 
	}	
	return color_core;
}


void sendTransfMM(){
	glUniform1f(MatrixIDXTM, XTM);
	glUniform1f(MatrixIDYTM, YTM);
	glUniform1f(MatrixIDGRAUSM, GRAUSM*mp);
	glUniform1f(MatrixIDEM, EM);
	glUniform1f(MatrixIDTANXSM, TANXSM*uqp);
	glUniform1f(MatrixIDTANYSM, TANYSM*uqp);
	glUniform1f(MatrixIDXEM, XEM);
	glUniform1f(MatrixIDYEM, YEM);
}

void sendTransfHulk(){
	glUniform1f(MatrixIDXT, XT);
	glUniform1f(MatrixIDYT, YT);
	glUniform1f(MatrixIDGRAUS, GRAUS*mp);
	glUniform1f(MatrixIDE, E);
	glUniform1f(MatrixIDTANXS, TANXS*uqp);
	glUniform1f(MatrixIDTANYS, TANYS*uqp);
	glUniform1f(MatrixIDXE, XE);
	glUniform1f(MatrixIDYE, YE);
}
void DrawObjects(int intPerson){
	GLvoid *aux;
	sendTransfHulk();
	sendTransfMM();

	glUniform1i(intPerson, 1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	aux= colorir(sizeof(cabelo_mm), 0.0, 0.0, 0.0);
	glBufferData(GL_ARRAY_BUFFER, ((sizeof(cabelo_mm)/sizeof(GLfloat))+(sizeof(cabelo_mm)/ sizeof(GLfloat))/2)* sizeof(GLfloat), aux, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cabelo_mm), cabelo_mm, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(cabelo_mm));
	free(aux);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	aux= colorir(sizeof(corpo_mm), 0.9568,  0.6431,  0.3764);
	glBufferData(GL_ARRAY_BUFFER, ((sizeof(corpo_mm)/sizeof(GLfloat))+(sizeof(corpo_mm)/ sizeof(GLfloat))/2)* sizeof(GLfloat), aux, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(corpo_mm), corpo_mm, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(corpo_mm));
	free(aux);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	aux= colorir(sizeof(braceletes_mm), 0.8627f,  0.8627,  0.8627);
	glBufferData(GL_ARRAY_BUFFER, ((sizeof(braceletes_mm)/sizeof(GLfloat))+(sizeof(braceletes_mm)/ sizeof(GLfloat))/2)* sizeof(GLfloat), aux, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(braceletes_mm), braceletes_mm, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(braceletes_mm));
	free(aux);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	aux= colorir(sizeof(vermelho_mm), 1.0,  0.0,  0.0);
	glBufferData(GL_ARRAY_BUFFER, ((sizeof(vermelho_mm)/sizeof(GLfloat))+(sizeof(vermelho_mm)/ sizeof(GLfloat))/2)* sizeof(GLfloat), aux, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vermelho_mm), vermelho_mm, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vermelho_mm));
	free(aux);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	aux= colorir(sizeof(amarelo_mm), 1.0,  1.0,  0.0);
	glBufferData(GL_ARRAY_BUFFER, ((sizeof(amarelo_mm)/sizeof(GLfloat))+(sizeof(amarelo_mm)/ sizeof(GLfloat))/2)* sizeof(GLfloat), aux, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(amarelo_mm), amarelo_mm, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(amarelo_mm));
	free(aux);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	aux= colorir(sizeof(laco_mm), 1.0,  1.0,  0.0);
	glBufferData(GL_ARRAY_BUFFER, ((sizeof(laco_mm)/sizeof(GLfloat))+(sizeof(laco_mm)/ sizeof(GLfloat))/2)* sizeof(GLfloat), aux, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(laco_mm), laco_mm, GL_STATIC_DRAW);
	glDrawArrays(GL_LINE_STRIP, 0, sizeof(laco_mm)/8);
	free(aux);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	aux= colorir(sizeof(saia_mm), 0.0,  0.5,  1.0);
	glBufferData(GL_ARRAY_BUFFER, ((sizeof(saia_mm)/sizeof(GLfloat))+(sizeof(saia_mm)/ sizeof(GLfloat))/2)* sizeof(GLfloat), aux, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(saia_mm), saia_mm, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(saia_mm));
	free(aux);

	glUniform1i(intPerson, 2);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	aux= colorir(sizeof(corpo_hulk), 0.0, 0.3921, 0.0);
	glBufferData(GL_ARRAY_BUFFER, ((sizeof(corpo_hulk)/sizeof(GLfloat))+(sizeof(corpo_hulk)/ sizeof(GLfloat))/2)* sizeof(GLfloat), aux, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(corpo_hulk), corpo_hulk, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(corpo_hulk));
	free(aux);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	aux = colorir(sizeof(calcao_hulk), 0.58039,  0.0,  0.8274);
	glBufferData(GL_ARRAY_BUFFER, ((sizeof(calcao_hulk)/sizeof(GLfloat))+(sizeof(calcao_hulk)/ sizeof(GLfloat))/2)* sizeof(GLfloat), aux, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(calcao_hulk), calcao_hulk, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(calcao_hulk));
	free(aux);

	aux = colorir(sizeof(cabelo_hulk), 0.0,  0.0,  0.0);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, ((sizeof(cabelo_hulk)/sizeof(GLfloat))+(sizeof(cabelo_hulk)/ sizeof(GLfloat))/2)* sizeof(GLfloat), aux, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cabelo_hulk), cabelo_hulk, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(cabelo_hulk));
	free(aux);
}

void MouseKeyboardMovimentObject(){
	int botao;
	glfwGetCursorPos(window, &xposMouse, &yposMouse);
	glfwGetWindowSize(window,&widthWindow, &heightWindow);
	double horizontal = double(xposMouse * 2 - widthWindow)/double(widthWindow);
	double vertical = double(heightWindow - yposMouse * 2)/double(heightWindow);
	present = glfwJoystickPresent(GLFW_JOYSTICK_1);	//VERIFICA SE O JOYSTICK ESTÁ CONECTADO

	if(present == 1){	// SE O JOYSTIC ESTÁ PRESENTE, A TRANSLAÇÃO DA MULHER MARAVILHA É PELO JOYSTIC, SENÃO, PELO MOUSE
	const unsigned char *estadobotao = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &botao);

	if (estadobotao[0] == GLFW_PRESS) 	//BUTTON_UP
	{		
		YTM += 0.01;
	}
	
	if (estadobotao[2] == GLFW_PRESS) 	//BUTTON_DOWN
	{		
		YTM += -0.01;
	}
	
	if (estadobotao[1] == GLFW_PRESS) 	//BUTTON_RIGHT
	{		
		XTM += 0.01;
	}
	
	if (estadobotao[3] == GLFW_PRESS) 	//BUTTON_LEFT
	{		
		XTM += -0.01;
	}
	}
	else {
		if (selecionamm && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{	
		XTM = horizontal;
		YTM = vertical-0.2;
	}
	}

	if (selecionahulk && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		XT = horizontal-0.84;
		YT = vertical+0.35;
	}

	if (selecionahulk && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{		
		GRAUS += 1;
	}

	if (selecionamm	&& glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{		
		GRAUSM += 1;
	}

	if (selecionahulk && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{		
		GRAUS += -1;
	}

	if (selecionamm	&& glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{		
		GRAUSM += -1;
	}

	if (selecionahulk && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{		
		YE += 0.001;
	}

	if (selecionamm && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{		
		YEM += 0.001;
	}

	if (selecionahulk && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{		
		XE += 0.001;
	}

	if (selecionamm && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{		
		XEM += 0.001;
	}

	if (selecionahulk 	&& glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{		
		E += 0.001;
	}

	if (selecionamm 	&& glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{		
		EM += 0.001;
	}

	if (selecionahulk 	&& glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{		
		E -= 0.001;
	}

	if (selecionamm 	&& glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{		
		EM -= 0.001;
	}

	if (selecionaanime)
	{	
		E +=-0.001;
		EM +=-0.001;
		GRAUSM+= 6.0;
		GRAUS+= -6.0;
	}

	if (selecionahulk && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{	
		TANXS += 0.1;
	}

	if (selecionamm && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{	
		TANXSM += 0.1;
	}

	if (selecionahulk && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{	
		TANXS += -0.1;
	}

	if (selecionamm && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{	
		TANXSM += -0.1;
	}


	if (selecionahulk && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{	
		TANYS += 0.1;
	}

	if (selecionamm && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{	
		TANYSM += 0.1;
	}

	if (selecionahulk && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{	
		TANYS += -0.1;
	}

	if (selecionamm && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{	
		TANYSM += -0.1;
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{	
		XT=0;YT=0;GRAUS=0;XE=1;YE=1;TANXS=0;TANYS=0;E=1; XTM=0;YTM=0;GRAUSM=0;XEM=1;YEM=1;TANXSM=0;TANYSM=0; EM=0.6, zoommm = 1, zoomhulk = 1;
	}
}

int initWindow(){
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( WIDTH, HEIGHT, "Heros", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	// Aplica o contexto atual da máquina de estados para Janela Atual
	glfwMakeContextCurrent(window);

	glewExperimental = true; // Necessário para core profile
	//deve ativar antes da chamada glewInit()
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	
	
	adicionaBarras();

	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW); // - Directly redirect GLFW mouse button events to AntTweakBar
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW);          // - Directly redirect GLFW mouse position events to AntTweakBar
	glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW);    // - Directly redirect GLFW mouse wheel events to AntTweakBar
	glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW);                         // - Directly redirect GLFW key events to AntTweakBar
	glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW);                      // - Directly redirect GLFW char events to AntTweakBar
 
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);//Alterado
    
    // Set the mouse at the center of the screen
    glfwPollEvents();

	glClearColor(R, G, B, A);

	//  Mostra o fragmento que estiver mais próximo da câmera Z-Buffer
	glDepthFunc(GL_LESS);
	return 1;
}

void configLayout(GLuint vertexbuffer, GLuint colorbuffer){
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
}


void destroyWindows(GLuint vertexbuffer, GLuint colorbuffer, GLuint VertexArrayID, GLuint programID){
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
	TwTerminate();
	glfwTerminate();
}




int main( void ){
	initWindow();
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	//variaveis para o vertexshaders
	shaderLoadCreat();

	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &colorbuffer);
	sendTransfMM();
	sendTransfHulk();

	do{	
		// Limpa a Tela
		glClear( GL_COLOR_BUFFER_BIT );
		// Para definir os Shaders
		glUseProgram(programID);
		// Primeiro buffer de atributo: vértices
		configLayout(vertexbuffer, colorbuffer);
		MouseKeyboardMovimentObject();

		if(selecionahulk){
			E = zoomhulk;
			E = zoomhulk;
		}

		if(selecionamm){
			EM = zoommm;
			EM = zoommm;
		}

		DrawObjects(intPerson);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);	
	 	TwDraw();
	 	glfwSwapBuffers(window);
	 	glfwPollEvents();
}
	while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
		destroyWindows(vertexbuffer, colorbuffer, VertexArrayID, programID);
	return 0;
}
