//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);
void    asignar_colores_vertices() ;

vector<_vertex3f> vertices;
vector<_vertex3f> colores_vertices ;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void    asignar_colores_caras() ;
void    draw_solido_colores_caras() ;
void    draw_solido_colores_vertices() ;

vector<_vertex3i> caras;
vector<_vertex3f> colores_caras ;
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
// clase octaedro
//*************************************************************************
class _octaedro: public _triangulos3D
{
public:
    _octaedro(float tam = 0.5, float al = 0.75) ;
};




