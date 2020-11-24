//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
    public:
        _puntos3D();
        void draw_puntos(float r, float g, float b, int grosor);

        vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
    public:

        _triangulos3D();
        void draw_aristas(float r, float g, float b, int grosor);
        void draw_solido(float r, float g, float b);
        void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
        void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

        vector<_vertex3i> caras;
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
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
    public:
        _objeto_ply();

        int parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
    public:
        _rotacion();
        void parametros(vector<_vertex3f> perfil1, int num1, int tapas);

        vector<_vertex3f> perfil; 
        int num;
};


//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
    public:
        _chasis();
        void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

        float altura;

    protected:
        _rotacion  rodamiento;
        _cubo  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
    public:
        _torreta();
        void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

        float altura;
        float anchura;

    protected:
        _cubo  base;
        _piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
    public:
        _tubo();
        void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

    protected:
        _rotacion tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
    public:
        _tanque();
        void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

        float giro_tubo;
        float giro_torreta;

        float giro_tubo_min;
        float giro_tubo_max;

    protected:
        _chasis  chasis;
        _torreta  torreta;
        _tubo     tubo;
};

//************************************************************************
// objeto articulado: grua/inserter
//************************************************************************
class _grua: public _triangulos3D {
    private:
        _cubo base;
        _cubo brazo;
        _cubo antebrazo;
        _piramide taladro;

        float angulo_base = 0;
        float angulo_brazo = 0;
        float angulo_antebrazo = 0;
        float angulo_taladro = 0;

        float max_brazo = 45;
        float max_antebrazo = 35;

        void drawBase(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
        void drawBrazo(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
        void drawAntebrazo(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
        void drawTaladro(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
        void drawParte(_triangulos3D& parte, _modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
    
    public:
        void draw(_modo modo);

        void mueveBase(float angulo);
        void mueveBrazo(float angulo);
        void mueveAntebrazo(float angulo);
        void mueveTaladro(float angulo);
};