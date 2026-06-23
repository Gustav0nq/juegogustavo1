#ifndef definiciones_h
#define definiciones_h

//definiciones
#define CANT_MONOS 2
#define CANT_TIPOS_PERSONAJES 2
#define MAX_FRAMES_ANIMACION 4
#define altomono 64
#define anchomono 72
#define velocidadmono 4


#define TAM_TILE 32
#define MAPA_FILAS 34
#define MAPA_COLUMNAS 60

#define MAX_FILAS 100
#define MAX_COLUMNAS 120


// cambios hitbox
#define HITBOX_MONO_ANCHO 40
#define HITBOX_MONO_ALTO 56
#define HITBOX_MONO_OFFSET_X ((anchomono - HITBOX_MONO_ANCHO) / 2)
#define HITBOX_MONO_OFFSET_Y (altomono - HITBOX_MONO_ALTO)

#define gravedad 0.35
#define velocidad_salto -9.5
#define velocidad_caida 12


#endif
