#ifndef struct_h
#define struct_h

//estructura monos
typedef struct{
    float x;
    float y;
    float ancho;
    float alto;
    float velocidad;
    int vida;
}Mono;

//estructura pantallas
typedef enum {
    PANTALLA_MENU,
    PANTALLA_JUEGO,
    PANTALLA_AJUSTES,
    PANTALLA_RANKING
} Pantalla;
#endif