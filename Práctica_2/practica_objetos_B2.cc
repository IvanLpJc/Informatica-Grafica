//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B2.h"


using namespace std;

// tipos
typedef enum { CUBO, PIRAMIDE, ROMBO, OBJETO_PLY, CILINDRO, CONO, ESFERA } _tipo_objeto;
_tipo_objeto tipo_objeto=CUBO;
_eje_de_rotacion eje_de_rotacion=EJE_Y;
_tapas tapa_sup=TAPA_CERRADA, tapa_inf=TAPA_CERRADA;
_modo   modo=PUNTOS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_piramide piramide(0.85,1.3);
_cubo cubo(0.5);
_rombo rombo(0.5, 0.5);
_objeto_ply  ply; 
_cilindro cilindro(tapa_sup, tapa_inf, EJE_Y);
_cono cono(tapa_sup, tapa_inf, EJE_Y);
_esfera esfera(tapa_sup, tapa_inf, EJE_Y);

float r = 0, g = 0.5, b = 0.25;
float r2 = 1, g2 = 0.75, b2 = 0.5;
int grosor = 4 ;

int pasos = 20 ;

// _objeto_ply *ply1;


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (tipo_objeto) {
	case CUBO: 
		cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
		break;
	case PIRAMIDE: 
		piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
		break;
	case ROMBO: 
		rombo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
		break;
    case OBJETO_PLY: 
		ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);
		break;
    case CILINDRO:
		cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
		break;
	case CONO:
		cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
	case ESFERA:
		esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
	}

}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{

clean_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}

static bool han_cambiado_opciones(_tapas prev_tapas_inf, _tapas prev_tapas_sup, _eje_de_rotacion prev_eje){
	if(prev_tapas_inf != tapa_inf || prev_tapas_sup != tapa_sup || eje_de_rotacion != prev_eje){
		return true;
	}

	return false;
}

//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
	_tapas prev_tapa_inf = tapa_inf ;
	_tapas prev_tapa_sup = tapa_sup ;
	_eje_de_rotacion _prev_eje = eje_de_rotacion;

	switch (toupper(Tecla1)) {
		case 'Q':
			exit(0);
		case 'P':
			modo=PUNTOS;
			break;
		case 'L':
			modo=ARISTAS;
			break;
		case 'F':
			modo=SOLIDO;
			break;
		case 'C':
			modo=AJEDREZ;
			break;
		case 'M':
			modo=MULTICOLOR;
			break;
		case '1':
			tipo_objeto=PIRAMIDE;
			break;
		case '2':
			tipo_objeto=CUBO;
			break;
		case '3':
			tipo_objeto=ROMBO;
			break;
		case '4':
			tipo_objeto=OBJETO_PLY;
			break;	
		case '5':
			tipo_objeto=CILINDRO;
			break;
		case '6':
			tipo_objeto=CONO;
			break;
		case '7':
			tipo_objeto=ESFERA;
			break;
		case 'T':
			tapa_sup=TAPA_ABIERTA;
			break;
		case 'R':
			tapa_sup=TAPA_CERRADA;
			break;
		case 'E':
			tapa_inf=TAPA_CERRADA;
			break;
		case 'W':
			tapa_inf=TAPA_ABIERTA;
			break;
		case 'X':
			eje_de_rotacion=EJE_X;
			break;
		case 'Y':
			eje_de_rotacion=EJE_Y;
			break;
		case 'Z':
			eje_de_rotacion=EJE_Z;
			break;
	}
	
	if( han_cambiado_opciones(prev_tapa_inf, prev_tapa_sup, _prev_eje)){
		cilindro.regenerar_con_nuevas_opciones( tapa_inf, tapa_sup, eje_de_rotacion);
		cono.regenerar_con_nuevas_opciones(tapa_inf, tapa_sup, eje_de_rotacion);
	}
	
	glutPostRedisplay();

}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);



}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{


// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);
//esfera.lee_perfil(argv[2]);
esfera.genera_perfil(pasos);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
