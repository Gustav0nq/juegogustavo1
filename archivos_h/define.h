#ifndef definiciones_h
#define definiciones_h

//definiciones
#define CANT_MONOS 8
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

#define VIDA_MAXIMA_MONO 200
#define VIDA_BARRA_ANCHO 260
#define VIDA_BARRA_ALTO 22


#define DAÑO_PINCHOS 10
#define COOLDOWN_DAÑO_PINCHOS 30

#define CURACION_BOTIQUIN 50

#define PRIMER_MONO 0
#define ULTIMO_MONO 3

#define PRIMER_TREX 4
#define ULTIMO_TREX 7

//DEFINICIONES ARMAS
#define municionarma1 10
#define dañoarma1 80    
#define velocidadarma1 12
#define tiemporecargaarma1 0


#define MAX_PROYECTILES 2
#define PROYECTIL_ANCHO 12
#define PROYECTIL_ALTO 6

//DAÑO_PINCHOS = quita 10 de vida
//COOLDOWN_DAÑO_PINCHOS = espera 30 frames antes de volver a quitar vida

#endif
