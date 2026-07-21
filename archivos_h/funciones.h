#ifndef funciones_h
#define funciones_h

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_font.h>

#include "define.h"
#include "struct.h"

int INICIARALLEGRO(void);

ALLEGRO_DISPLAY *crear_pantalla_completa(int *ANCHO, int *ALTO);

ALLEGRO_BITMAP *cargar_imagen(const char *ruta);

int cargar_mapa(const char *ruta, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

void dibujar_mapa(char mapa[MAPA_FILAS][MAPA_COLUMNAS],ALLEGRO_BITMAP *tilePiso,ALLEGRO_BITMAP *tileLava, ALLEGRO_BITMAP *tileLavaquema, ALLEGRO_BITMAP *tilepinchos, ALLEGRO_BITMAP *tilebotiquin, ALLEGRO_BITMAP *tilecaja);

void dibujar_fondo(ALLEGRO_BITMAP *fondo, int ANCHO, int ALTO);

void dibujar_menu(ALLEGRO_FONT *fuente, int ANCHO, int opcionMenu);

void dibujar_monos(
    ALLEGRO_BITMAP *spritesPersonajes[CANT_TIPOS_PERSONAJES][CANT_ANIMACIONES][MAX_FRAMES_ANIMACION],
    int cantidadFrames[CANT_TIPOS_PERSONAJES][CANT_ANIMACIONES],
    Mono monos[]
);

void cambiar_animacion_mono(Mono *mono, int nuevaAnimacion);

void actualizar_animacion_mono(
    Mono *mono,
    int izquierda,
    int derecha,
    int abajo,
    int golpe,
    int cantidadFrames[CANT_TIPOS_PERSONAJES][CANT_ANIMACIONES]
);


//funcion hitbox
void dibujar_hitbox_mono(Mono mono);

void inicializar_monos_sobre_piso(Mono monos[], char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

int es_tile_solido(char bloque);

int mono_colisiona_con_mapa(char mapa[MAPA_FILAS][MAPA_COLUMNAS], float x, float y, float ancho, float alto);

void mover_mono(Mono *mono, int salto, int izquierda, int derecha, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

void limitar_mono_pantalla(Mono *mono, int anchoPantalla, int altoPantalla);

int mono_toca_tile(char mapa[MAPA_FILAS][MAPA_COLUMNAS], float x, float y, float ancho, float alto, char tileBuscado);

void aplicar_daño_pinchos(Mono *mono, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

void dibujar_vidas_monos(Mono monos[], ALLEGRO_FONT *fuenteVida, int ANCHO);

void aplicar_tile_muerte(Mono *mono, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

void aplicar_curacion_botiquin(Mono *mono, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

void disparar_arma(Proyectil proyectiles[], Mono *personaje, int indicePersonaje);

void actualizar_proyectiles(Proyectil proyectiles[], Mono monos[], int anchoPantalla);

void dibujar_proyectiles(Proyectil proyectiles[]);

int revisar_ganador(Mono monos[]);

void dibujar_ganador(int ganador, ALLEGRO_FONT *fuente, int ANCHO, int ALTO);

#endif