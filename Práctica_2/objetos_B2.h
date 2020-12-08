//**************************************************************************
// Práctica 2 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

#include "file_ply_stl.hpp"


const float AXIS_SIZE=5000;
typedef enum{ PUNTOS, ARISTAS, AJEDREZ, SOLIDO, MULTICOLOR } _modo;
typedef enum{ EJE_X, EJE_Y, EJE_Z } _eje_de_rotacion;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D {
	public:

		_triangulos3D();
		void draw_aristas(float r, float g, float b, int grosor);
		void draw_solido(float r, float g, float b);
		void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
		void draw_multicolor();
		void _genera_colores();

		vector<_vertex3i> caras;
		vector<_vertex3f> colores;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};


//*************************************************************************
// clase rombo
//*************************************************************************

class _rombo: public _triangulos3D
{
public:

	_rombo(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
static vector<_vertex3f> parametros_para_perfiles(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void regenerar_con_nuevas_opciones(_eje_de_rotacion eje_de_rotacion);
void parametros(vector<_vertex3f> perfil, int num);
void giro_en_eje_y(vector<_vertex3f> &perfil, int num, int num_aux);
void giro_en_eje_x(vector<_vertex3f> &perfil, int num, int num_aux);
void giro_en_eje_z(vector<_vertex3f> &perfil, int num, int num_aux);
void genera_tapas(int c, int num, int num_aux);

vector<_vertex3f> perfil_eje_y; 
vector<_vertex3f> perfil_eje_x; 
vector<_vertex3f> perfil_eje_z; 
_eje_de_rotacion eje_de_rotacion;

int num;
};

//************************************************************************
// objeto por revolución : Cilindro
//************************************************************************

class _cilindro: public _rotacion
{
	public:
		_cilindro(_eje_de_rotacion eje);
};

//************************************************************************
// objeto por revolución : Cono
//************************************************************************

class _cono: public _rotacion
{
	public:
		_cono(_eje_de_rotacion eje);
};

//************************************************************************
// objeto por revolución : Cono
//************************************************************************

class _esfera: public _rotacion
{
	public:
		_esfera(_eje_de_rotacion eje);
	void lee_perfil(char *archivo);
	void genera_perfil(int num);

	vector<_vertex3f> perfil_semiesfera; 
};