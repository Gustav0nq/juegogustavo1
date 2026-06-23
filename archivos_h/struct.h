#ifndef struct_h
#define struct_h

typedef enum {
    PERSONAJE_MONO,
    PERSONAJE_DOS
} TipoPersonaje;

typedef enum {
    ANIM_IDLE,
    ANIM_CAMINAR,
    ANIM_CORRER,
    ANIM_SALTAR,
    ANIM_AGACHADO,
    ANIM_GOLPE,
    CANT_ANIMACIONES
} Animacion;

//estructura monos
typedef struct{
    float x;
    float y;
    float ancho;
    float alto;
    float velocidad;

    float velocidadY;
    int enSuelo;

    int vida;

    int tipoPersonaje;

    int animacionActual;
    int frameActual;    
    int contadorAnimacion;
    int mirandoDerecha;
    }Mono;

//estructura pantallas
typedef enum {
    PANTALLA_MENU,
    PANTALLA_JUEGO,
    PANTALLA_AJUSTES,
    PANTALLA_RANKING
} Pantalla;
#endif