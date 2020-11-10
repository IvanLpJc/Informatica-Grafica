//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


void _triangulos3D::_genera_colores(){

	colores.resize(caras.size());
	for (int i = 0 ; i < caras.size(); i++) {
		colores[i].r = drand48() * 1.0;
		colores[i].g = drand48() * 1.0;
		colores[i].b = drand48() * 1.0;
	}
}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for( int i=0 ; i < caras.size() ; i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i=0;i<caras.size();i++){
		if (i%2==0) glColor3f(r2,g2,b2);
		else glColor3f(r1,g1,b1);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido multicolor
//*************************************************************************

void _triangulos3D::draw_multicolor() {
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i=0;i<caras.size();i++){
		glColor3f(colores[i].r, colores[i].g, colores[i].b);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	switch (modo){
		case PUNTOS:
			draw_puntos(r1, g1, b1, grosor);
			break;
		case ARISTAS:
			draw_aristas(r1, g1, b1, grosor);
			break;
		case AJEDREZ:
			draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);
			break;
		case SOLIDO:
			draw_solido(r1, g1, b1);
			break;
		case MULTICOLOR:
			draw_multicolor();
			break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam) {
	//vertices
	vertices.resize(8);
	vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
	vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;

	vertices[4].x=-tam;vertices[4].y=tam*2;vertices[4].z=tam;
	vertices[5].x=tam;vertices[5].y=tam*2;vertices[5].z=tam;
	vertices[6].x=tam;vertices[6].y=tam*2;vertices[6].z=-tam;
	vertices[7].x=-tam;vertices[7].y=tam*2;vertices[7].z=-tam;

	// triangulos
	caras.resize(12);
	caras[0]._0=0;caras[0]._1=3;caras[0]._2=1;
	caras[1]._0=3;caras[1]._1=2;caras[1]._2=1;

	caras[2]._0=0;caras[2]._1=1;caras[2]._2=4;
	caras[3]._0=1;caras[3]._1=5;caras[3]._2=4;

	caras[4]._0=1;caras[4]._1=2;caras[4]._2=5;
	caras[5]._0=2;caras[5]._1=6;caras[5]._2=5;

	caras[6]._0=2;caras[6]._1=3;caras[6]._2=6;
	caras[7]._0=3;caras[7]._1=7;caras[7]._2=6;

	caras[8]._0=3;caras[8]._1=0;caras[8]._2=7;
	caras[9]._0=0;caras[9]._1=4;caras[9]._2=7;

	caras[10]._0=4;caras[10]._1=5;caras[10]._2=7;
	caras[11]._0=5;caras[11]._1=6;caras[11]._2=7;

	_genera_colores() ;
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al) {

	//vertices 
	vertices.resize(5); 
	vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
	vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
	vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

	caras.resize(6);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
	caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
	caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
	caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
	caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
	caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

	_genera_colores();
}

//*************************************************************************
// clase rombo
//*************************************************************************

_rombo::_rombo(float tam, float al){

	//vertices
	//puntos finales
	vertices.resize(6);
	vertices[0].x=0;vertices[0].y=0;vertices[0].z=0;
	vertices[1].x=0;vertices[1].y=al*2;vertices[1].z=0;
	//centro
	vertices[2].x=-tam;vertices[2].y=al;vertices[2].z=tam;
	vertices[3].x=tam;vertices[3].y=al;vertices[3].z=tam;
	vertices[4].x=tam;vertices[4].y=al;vertices[4].z=-tam;
	vertices[5].x=-tam;vertices[5].y=al;vertices[5].z=-tam;


	///caras

	caras.resize(8);
	caras[0]._0=2;caras[0]._1=3;caras[0]._2=1; //frontal superior
	caras[1]._0=0;caras[1]._1=3;caras[1]._2=2; //frontal inferior
	
	
	caras[2]._0=3;caras[2]._1=4;caras[2]._2=1; //derecha superior
	caras[3]._0=0;caras[3]._1=3;caras[3]._2=4; //derecha inferior

	caras[4]._0=5;caras[4]._1=1;caras[4]._2=4; //trasera superior
	caras[5]._0=0;caras[5]._1=5;caras[5]._2=4; //trasera inferior
	
	caras[6]._0=2;caras[6]._1=1;caras[6]._2=5; //izquierda superior
	caras[7]._0=0;caras[7]._1=2;caras[7]._2=5; //izquierda inferior

	_genera_colores() ;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);
vertices.resize(n_ver);
caras.resize(n_car);

int j = 0;
for (int i = 0; i < ver_ply.size();)
{
	vertices[j].x = ver_ply[i++];
	vertices[j].y = ver_ply[i++];
	vertices[j].z = ver_ply[i++];
	j++;
}

j = 0;

for (int i = 0; i < car_ply.size();)
{
	caras[j]._0 = car_ply[i++];
	caras[j]._1 = car_ply[i++];
	caras[j]._2 = car_ply[i++];
	j++;
}

_genera_colores();

return(0);
}
//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num+2);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras 
caras.resize((num_aux-1)*2*num+2*num);

int c = 0 ;
for(j = 0; j <num-1 ; j++){
	caras[c]._0 = j*2 ;
	caras[c]._1 = j*2 + 1 ;
	caras[c]._2 = (j+1)*2+1 ;
	c++;
	caras[c]._0 = (j+1)*2+1 ;
	caras[c]._1 = (j+1)*2 ;
	caras[c]._2 = j*2 ;
	c++;
}

for(int i = 0; i<num_aux-1; i++){
	caras[c]._0 = (num-1) * num_aux + i;
	caras[c]._1 = i;
	caras[c]._2 = (num-1) * num_aux + (i+1);
	c++;
	caras[c]._0 = i;
	caras[c]._1 = i+1;
	caras[c]._2 = (num-1) * num_aux + (i+1);
    c++;
}
// tapa inferior
if (fabs(perfil[0].x)>0.0)
{
	vertices[num_aux*num].x = 0.0 ;
	vertices[num_aux*num].y = perfil[0].y ;
	vertices[num_aux*num].z = 0.0 ;

	for(j=0 ; j < num-1 ; j++){
		caras[c]._0 = num_aux*num; 
		caras[c]._1 = j*2 ;
		caras[c]._2 = (j+1)*2;
		c++;
	}

	caras[c]._0 = vertices.size()-2;
	caras[c]._1 = (num-1) * num_aux ;
	caras[c]._2 = 0;
	c++;
}
 
 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
{
	vertices[num_aux*num+1].x = 0.0 ;
	vertices[num_aux*num+1].y = perfil[num_aux-1].y ;
	vertices[num_aux*num+1].z = 0.0 ;

	for(j=0 ; j < num-1 ; j++){
		caras[c]._0 = num_aux*num+1; 
		caras[c]._1 = j*2+1 ;
		caras[c]._2 = (j+1)*2+1;
		c++;
	}

	caras[c]._0 = vertices.size()-1;
	caras[c]._1 = (num-1) * num_aux + (num_aux-1);
	caras[c]._2 = num_aux - 1 ;
	c++;
}

  _genera_colores();
}

//************************************************************************
// objeto por revolucion: Cilindro
//************************************************************************

_cilindro::_cilindro(){
	_vertex3f aux;
	aux.x=1.0; aux.y=0.0; aux.z=0.0;
	perfil.push_back(aux);
	aux.x=1.0; aux.y=1.0; aux.z=0.0;
	perfil.push_back(aux);
	parametros(perfil, 20);
}

//************************************************************************
// objeto por revolucion: Cono
//************************************************************************

_cono::_cono(){
	_vertex3f aux;
	aux.x=0.0; aux.y=1.0; aux.z=0.0;
	perfil.push_back(aux);
	aux.x=1.0; aux.y=0.0; aux.z=0.0;
	perfil.push_back(aux);
	parametros(perfil, 20);
}