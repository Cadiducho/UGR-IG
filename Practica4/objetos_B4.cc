//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B4.h"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor) {
    //**** usando vertex_array ****
    glPointSize(grosor);
    glColor3f(r,g,b);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
    glDrawArrays(GL_POINTS,0,vertices.size()); 

    /*int i;
    glPointSize(grosor);
    glColor3f(r,g,b);
    glBegin(GL_POINTS);
    for (i=0;i<vertices.size();i++){
        glVertex3fv((GLfloat *) &vertices[i]);
        }
    glEnd();*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
    b_normales_caras = false;
    b_normales_vertices = false;
    ambiente_difusa._0 = 1;
    ambiente_difusa._1 = 0.4;
    ambiente_difusa._2 = 0.3;
    especular._0 = 0.5;
    especular._1 = 0.5;
    especular._2 = 0.5;
    brillo = 1;
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor) {
    //**** usando vertex_array ****
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glLineWidth(grosor);
    glColor3f(r,g,b);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
    glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

    /*int i;
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glLineWidth(grosor);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);
    for (i=0;i<caras.size();i++){
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
        }
    glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b) {
    int i;

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);
    for (i=0;i<caras.size();i++) {
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
    glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2) {
    int i;
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
    for (i=0;i<caras.size();i++) {
        if (i%2==0) {
            glColor3f(r1,g1,b1);
        } else {
            glColor3f(r2,g2,b2);
        }

        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
    glEnd();
}

//*************************************************************************
// dibujar con iluminacion plana y sin suavizado
//*************************************************************************

void _triangulos3D::draw_iluminacion_plana()
{
    int i;

    if(b_normales_caras == false) calcular_normales_caras();
    if(b_normales_vertices == false) calcular_normales_vertices();

    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, (GLfloat *) &especular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, (GLfloat *) &brillo);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBegin(GL_TRIANGLES);
        for (unsigned int i=0 ; i < caras.size() ; i++){
            glNormal3fv((GLfloat*) &normales_caras[i]);
            glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
            glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
            glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
        }
        glEnd();
        glDisable(GL_LIGHTING);
}

//*************************************************************************
// dibujar con iluminacion suavizada
//*************************************************************************

void _triangulos3D::draw_iluminacion_suave() {
    int i;

    if (b_normales_caras == false) calcular_normales_caras();
    if (b_normales_vertices == false) calcular_normales_vertices();

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, (GLfloat *) &especular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, (GLfloat *) &brillo);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBegin(GL_TRIANGLES);
        for (unsigned int i=0 ; i < caras.size() ; i++){
            glNormal3fv((GLfloat*) &normales_vertices[caras[i]._0]);
            glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glNormal3fv((GLfloat*) &normales_vertices[caras[i]._1]);
            glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glNormal3fv((GLfloat*) &normales_vertices[caras[i]._2]);
            glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
        }
        glEnd();
        glDisable(GL_LIGHTING);
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor) {
    switch (modo){
        case POINTS:draw_puntos(r1, g1, b1, grosor);break;
        case EDGES:draw_aristas(r1, g1, b1, grosor);break;
        case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
        case SOLID:draw_solido(r1, g1, b1);break;
        case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana();
	    case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave();
    }
}

//*************************************************************************
// calculo de normales (caras)
//*************************************************************************

void _triangulos3D::calcular_normales_caras() {
	normales_caras.resize(caras.size());
	_vertex3f a1, a2;

	for (unsigned long i=0; i<caras.size(); i++) {
		//obtener 2 vectores en el triángulo y calcular el producto vectorial
		_vertex3f
		a1=vertices[caras[i]._1]-vertices[caras[i]._0],
		a2=vertices[caras[i]._2]-vertices[caras[i]._0],
		n=a1.cross_product(a2);
		//modulo
		float m=sqrt(n.x*n.x*+n.y*n.y+n.z*n.z);
		//normalizacion
		normales_caras[i]=_vertex3f(n.x/m, n.y/m, n.z/m);

	}
	
	b_normales_caras=true;
}


//*************************************************************************
// calculo de normales (vertices)
//*************************************************************************

void _triangulos3D::calcular_normales_vertices() {
    //modulo
    float m=vertices.size();

	if (b_normales_vertices == false) {

		//si las normales de las caras no estan creadas crearlas
		if (b_normales_caras==false) calcular_normales_caras();

		normales_vertices.resize(vertices.size());

		for (unsigned long i=0; i<caras.size(); i++) {
			normales_vertices[caras[i]._0] += normales_caras[i];
			normales_vertices[caras[i]._1] += normales_caras[i];
			normales_vertices[caras[i]._2] += normales_caras[i];
		}

		for (unsigned long i=0; i<vertices.size(); i++) {
			normales_vertices[i] = (normales_vertices[i].normalize());
		}

		b_normales_vertices=true;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam) {
    //vertices
    vertices.resize(8);
    vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
    vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
    vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
    vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
    vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
    vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
    vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
    vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

    // triangulos
    caras.resize(12);
    caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
    caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
    caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
    caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
    caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
    caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
    caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
    caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
    caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
    caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
    caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
    caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;  
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
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() {
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



int _objeto_ply::parametros(char *archivo) {
    int n_ver,n_car;

    vector<float> ver_ply ;
    vector<int>   car_ply ;
    
    _file_ply::read(archivo, ver_ply, car_ply );

    n_ver=ver_ply.size()/3;
    n_car=car_ply.size()/3;

    printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

    //if (n_ver<3 || n_car<1){
    //	printf("Error %d %d\n",__FILE__,__LINE__);
    //	exit(-1);
    //	}

    vertices.resize(n_ver);
    caras.resize(n_car);

    _vertex3f ver_aux;
    _vertex3i car_aux;

    for (int i=0;i<n_ver;i++) {
        ver_aux.x=ver_ply[i*3];
        ver_aux.y=ver_ply[i*3+1];
        ver_aux.z=ver_ply[i*3+2];
        vertices[i]=ver_aux;
    }

    for (int i=0;i<n_car;i++) {
        car_aux.x=car_ply[i*3];
        car_aux.y=car_ply[i*3+1];
        car_aux.z=car_ply[i*3+2];
        caras[i]=car_aux;
    }

    return(0);
}

//************************************************************************
// esfera
//************************************************************************

_esfera::_esfera(){
int perfiles = 6;
int puntos = 6;
float radio = 2.0;
int i,j;
vector<_vertex3f> perfil;
_vertex3f vertice_aux;
_vertex3i cara_aux;
vertices.clear();
// tratamiento de los vértices
for (j=0; j<perfiles; j++){
      vertice_aux.x=radio*cos( (3*M_PI)/2 + M_PI*(1+j)/(1.0+perfiles));
      vertice_aux.y=radio*sin( (3*M_PI)/2 + M_PI*(1+j)/(1.0+perfiles));
      vertice_aux.z=0.0;
	  perfil.push_back(vertice_aux);
  }

for (j=0; j<perfiles; j++)
  {for (i=0; i<puntos; i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*perfiles))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*perfiles));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*perfiles))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*perfiles));
      vertice_aux.y=perfil[i].y;

      vertices.push_back(vertice_aux);
     }
  }

// tratamiento de las caras
for(j=0; j<perfiles; j++)
{for (i=0;i<puntos-1; i++)
     {
/**/
		cara_aux._0=i + ((j+1)%perfiles)*puntos;
		cara_aux._1=i + 1 + ((j+1)%perfiles)*puntos;
		cara_aux._2=i + 1 + j*puntos;
		caras.push_back(cara_aux);

		cara_aux._0=i + 1 + j*puntos;
		cara_aux._1=i + j*puntos;
		cara_aux._2=i + ((j+1)%perfiles)*puntos;
		caras.push_back(cara_aux);
}
}

 // tapa inferior
	vertice_aux.x=0.0;  //Creamos un nuevo punto en mitad del eje, a la misma altura del primer punto del perfil
	vertice_aux.y=-radio;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<perfiles; j++) //Y creamos caras que unen los radio inferiores del perfil con nuestro nuevo punto central
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=j*perfiles;
		cara_aux._2=((j+1)%puntos)*perfiles;
		caras.push_back(cara_aux);
	}

 // tapa superior
	vertice_aux.x=0.0;
	vertice_aux.y=radio;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<perfiles; j++)
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=puntos-1+j*perfiles;
		cara_aux._2=puntos-1+((j+1)%puntos)*perfiles;
		caras.push_back(cara_aux);
	}
}

//************************************************************************
// objeto por revolucion(cilindro)
//************************************************************************

_cilindro_tapas::_cilindro_tapas()
{

}


void _cilindro_tapas::parametros(int num)
{

  // perfil cilindro(rotacion)
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x=1.0; aux.y=-1.0; aux.z=0.0;
  perfil.push_back(aux);
  aux.x=1.0; aux.y=1.0; aux.z=0.0;
  perfil.push_back(aux);


int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux; //numero de puntos que tiene el perfil

// tratamiento de los vértices

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0; j<num; j++)
  {for (i=0; i<num_aux; i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras j=perfiles i=puntos
for(j=0; j<num; j++)
{for (i=0;i<num_aux-1;i++)
     {
		cara_aux._0=i + ((j+1)%num)*num_aux;
		cara_aux._1=i + 1 + ((j+1)%num)*num_aux;
		cara_aux._2=i + 1 + j*num_aux;
		caras.push_back(cara_aux);

		cara_aux._0=i + 1 + j*num_aux;
		cara_aux._1=i + j*num_aux;
		cara_aux._2=i + ((j+1)%num)*num_aux;
		caras.push_back(cara_aux);
	}
}

 // tapa inferior
if (fabs(perfil[0].x)>0.0) //Si el objeto de revolucion empieza fuera del eje
  {
	vertice_aux.x=0.0;  //Creamos un nuevo punto en mitad del eje, a la misma altura del primer punto del perfil
	vertice_aux.y=perfil[0].y;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<num; j++) //Y creamos caras que unen los puntos inferiores del perfil con nuestro nuevo punto central
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=j*num_aux;
		cara_aux._2=((j+1)%num)*num_aux;
		caras.push_back(cara_aux);
	}
  }

 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
	vertice_aux.x=0.0;
	vertice_aux.y=perfil[num_aux-1].y;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<num; j++)
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=j*num_aux+num_aux-1;
		cara_aux._2=((j+1)%num)*num_aux+num_aux-1;
		caras.push_back(cara_aux);
	}
  }
}

//************************************************************************
// clase cono
//************************************************************************

_cono::_cono() {
	_rotacion();
}


void _cono::parametros(int num, float altura, float radio) {
//perfil cono


int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;

// tratamiento de los vértices
vertices.resize(num);
for (j=0; j<num; j++){
      vertice_aux.x=radio*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-radio*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=0.0;
      vertices[j]=vertice_aux;
  }


	// tapa inferior
	vertice_aux.x=0.0;  //Creamos un nuevo punto en mitad del eje, a la misma altura del primer punto del perfil
	vertice_aux.y=0.0;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<num; j++) //Y creamos caras que unen los puntos inferiores del perfil con nuestro nuevo punto central
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=j;
		cara_aux._2=(j+1)%num;
		caras.push_back(cara_aux);
	}

	// tapa superior
	vertice_aux.x=0.0;
	vertice_aux.y=altura;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<num; j++)
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=j;
		cara_aux._2=(j+1)%num;
		caras.push_back(cara_aux);
	}
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion() {

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa) {
    int i,j;
    _vertex3f vertice_aux;
    _vertex3i cara_aux;
    int num_aux;

    // tratamiento de los vértice

    num_aux=perfil.size();
    vertices.resize(num_aux*num);
    for (j=0;j<num;j++) {
        for (i=0;i<num_aux;i++) {
            vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                            perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
            vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                            perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
            vertice_aux.y=perfil[i].y;
            vertices[i+j*num_aux]=vertice_aux;
        }
    }

    // tratamiento de las caras 

    for (j=0;j<num;j++) {
        for (i=0;i<num_aux-1;i++) {
            cara_aux._0=i+((j+1)%num)*num_aux;
            cara_aux._1=i+1+((j+1)%num)*num_aux;
            cara_aux._2=i+1+j*num_aux;
            caras.push_back(cara_aux);
            
            cara_aux._0=i+1+j*num_aux;
            cara_aux._1=i+j*num_aux;
            cara_aux._2=i+((j+1)%num)*num_aux;
            caras.push_back(cara_aux);
        }
    }
        
    // tapa inferior
    if (fabs(perfil[0].x)>0.0 && tapa==1) {

    }
    
    // tapa superior
    if (fabs(perfil[num_aux-1].x)>0.0 && tapa==1) {

    }
}

//************************************************************************
// objeto articulado: tanque
//************************************************************************

_chasis::_chasis() {
    // perfil para un cilindro
    vector<_vertex3f> perfil;
    _vertex3f aux;
    aux.x=0.107;aux.y=-0.5;aux.z=0.0;
    perfil.push_back(aux);
    aux.x=0.107;aux.y=0.5;aux.z=0.0;
    perfil.push_back(aux);
    rodamiento.parametros(perfil,12,1);
    altura=0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor) {
    glPushMatrix();
    glScalef(1.0,0.22,0.95);
    base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0,1,0,0);
    rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25,0.0,0.0);
    glRotatef(90.0,1,0,0);
    rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,0.0,0.0);
    glRotatef(90.0,1,0,0);
    rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25,0.0,0.0);
    glRotatef(90.0,1,0,0);
    rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5,0.0,0.0);
    glRotatef(90.0,1,0,0);
    rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
}

//************************************************************************

_torreta::_torreta() {
    altura=0.18;
    anchura=0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor) {
    glPushMatrix();
    glScalef(0.65,0.18,0.6);
    base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.325,0,0);
    glRotatef(90.0,0,0,1);
    glScalef(0.18,0.16,0.6);
    parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
}

//************************************************************************

_tubo::_tubo() {
    // perfil para un cilindro
    vector<_vertex3f> perfil;
    _vertex3f aux;
    aux.x=0.04;aux.y=-0.4;aux.z=0.0;
    perfil.push_back(aux);
    aux.x=0.04;aux.y=0.4;aux.z=0.0;
    perfil.push_back(aux);
    tubo_abierto.parametros(perfil,12,0);
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor) {
    glPushMatrix();
    glTranslatef(0.4,0,0);
    glRotatef(90.0,0,0,1);
    tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
}


//************************************************************************

_tanque::_tanque() {
    giro_tubo=2.0;
    giro_torreta=0.0;
    giro_tubo_min=-9;
    giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor) {
    glPushMatrix();
    chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

    glRotatef(giro_torreta,0,1,0);
    glPushMatrix();
    glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
    torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
    glRotatef(giro_tubo,0,0,1);
    tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
    glPopMatrix();

};


//************************************************************************
// objeto articulado: grua
//************************************************************************

void _grua::mueveBase(float angulo) {
    this->angulo_base = fmod((this->angulo_base + angulo), 360.0);
}

bool _grua::mueveBrazo(float angulo) {
    float nuevoAngulo = fmod((this->angulo_brazo + angulo), 360.0);
    if (max_brazo > nuevoAngulo && (-max_brazo) < nuevoAngulo) {
        this->angulo_brazo = nuevoAngulo;
        return true;
    }
    return false;
}

bool _grua::mueveAntebrazo(float angulo) {
    float nuevoAngulo = fmod((this->angulo_antebrazo + angulo), 360.0);
    if (max_antebrazo > nuevoAngulo && (-max_antebrazo) < nuevoAngulo) {
        this->angulo_antebrazo =  nuevoAngulo;
        return true;
    }
    return false;
}

void _grua::mueveTaladro(float angulo) {
  this->angulo_taladro = fmod((this->angulo_taladro + angulo), 360.0);
}

void _grua::drawBase(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor) {
    glPushMatrix();
    glScalef(0.5, 3, 0.5);
    glTranslatef(0, 0, 0);
    drawParte(this->base, modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
}

void _grua::drawBrazo(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor) {
    glPushMatrix();
    glTranslatef(-0.25, -0.25, -0.5);
    glScalef(5, 0.5, 0.5);
    drawParte(this->brazo, modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
}

void _grua::drawAntebrazo(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor) {
    glPushMatrix();
    glTranslatef(-0.25, -0.25, -0.5);
    glScalef(3, 0.5, 0.5);
    drawParte(this->antebrazo, modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
}

void _grua::drawTaladro(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor) {
    glPushMatrix();
    glRotatef(270, 0, 0, 1);
    glRotatef(this->angulo_taladro, 0, 1, 0);
    glScalef(0.75, 0.75, 0.75);
    glTranslatef(0.25, -2, -0.10);
    drawParte(this->taladro, modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
}


void _grua::draw(_modo modo) {
    // Base
    glPushMatrix();
    glRotatef(this->angulo_base, 0, 1, 0);
    drawBase(modo, 0.9, 0.66, 0, 0.8, 0.7, 0, 2);

    {
        // Brazo
        glPushMatrix();
        glTranslatef(0.25, 2, 0.5);
        glRotatef(this->angulo_brazo, 0, 0, 1);
        drawBrazo(modo, 0.95, 0.7, 0, 0.9, 0.65, 0, 2);
        {
            // Antebrazo
            glPushMatrix();
            glTranslatef(2.5, 0, 0.5);
            glRotatef(this->angulo_antebrazo, 0, 0, 1);
            drawAntebrazo(modo, 0.97, 0.5, 0, 0.85, 0.7, 0, 2);
            glTranslatef(2.75, 0, -0.25);

            drawTaladro(modo, 1, 1, 0, 0.5, 1, 0, 2);
            glPopMatrix();
        }
        
        glPopMatrix();
    }
    glPopMatrix();

}

void _grua::drawParte(_triangulos3D& parte, _modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor) {
    switch (modo) {
        case POINTS: parte.draw_puntos(r1, g1, b1, grosor); break;
        case EDGES: parte.draw_aristas(r1, g1, b1, grosor); break;
        case SOLID_CHESS: parte.draw_solido_ajedrez(r1, g1, b1, r2, g2, b2); break;
        case SOLID: parte.draw_solido(r1, g1, b1); break;
  }
}