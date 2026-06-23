#ifndef struct_h
#define struct_h

typedef enum {
    PERSONAJE_MONO,
    PERSONAJE_DOS
} TipoPersonaje;

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
}Mono;

//estructura pantallas
typedef enum {
    PANTALLA_MENU,
    PANTALLA_JUEGO,
    PANTALLA_AJUSTES,
    PANTALLA_RANKING
} Pantalla;
#endif