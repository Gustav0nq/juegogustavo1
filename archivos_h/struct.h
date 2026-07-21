#ifndef struct_h
#define struct_h

typedef enum {
    PERSONAJE_MONO,
    PERSONAJE_TREX
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

typedef enum
{
    arma_sin,
    arma_pistola,
}tipodearma;

typedef struct {
    tipodearma tipo;
    int municion;
    int daño;
    float velocidadproyectil;
    int tiemporecarga;
} Arma;

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

    int cooldownDaño;

    int tipoPersonaje;

    int animacionActual;
    int frameActual;    
    int contadorAnimacion;
    int mirandoDerecha;
    Arma armaActual;
    //Cantidad proyectiles
    //   Proyectil proyectiles[MAX_PROYECTILES]; /*revisar esto,.. ya que en este caso cada mono tendria sus propios proyectiles */
}Mono;

typedef struct{
    float x;
    float y;

    float velocidadX;

    float ancho;
    float alto;

    int daño;
    int activa;
    int personajequedispara;
    int personajedañado;


} Proyectil;

//estructura pantallas
typedef enum {
    PANTALLA_MENU,
    PANTALLA_JUEGO,
    PANTALLA_AJUSTES,
    PANTALLA_RANKING
} Pantalla;

#endif