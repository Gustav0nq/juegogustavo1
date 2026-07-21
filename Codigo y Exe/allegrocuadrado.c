//Librerias
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>   

//Modularización de los .h
#include "struct.h"
#include "define.h"
#include "funciones.h"


int main()
{
    int ANCHO = 0;
    int ALTO = 0;
    int ganador = 0;

    if (!INICIARALLEGRO())
    {   
        return 1;
    }

    ALLEGRO_DISPLAY *display = crear_pantalla_completa(&ANCHO, &ALTO);

    if (display == NULL)
    {
        return 1;
    }

    ALLEGRO_EVENT_QUEUE *cola = al_create_event_queue();

    if (cola == NULL)
    {
        printf("No se pudo crear la cola de eventos\n");
        al_destroy_display(display);
        return 1;
    }

    ALLEGRO_BITMAP *spritesPersonajes[CANT_TIPOS_PERSONAJES][CANT_ANIMACIONES][MAX_FRAMES_ANIMACION] = {NULL};
    int cantidadFrames[CANT_TIPOS_PERSONAJES][CANT_ANIMACIONES] = {0};

    /* PERSONAJE 1: MONO */
    spritesPersonajes[PERSONAJE_MONO][ANIM_IDLE][0] = cargar_imagen("assets/imgs/personajemono/mono1.png");
    cantidadFrames[PERSONAJE_MONO][ANIM_IDLE] = 1;

    spritesPersonajes[PERSONAJE_MONO][ANIM_CAMINAR][0] = cargar_imagen("assets/imgs/personajemono/mono2.png");
    spritesPersonajes[PERSONAJE_MONO][ANIM_CAMINAR][1] = cargar_imagen("assets/imgs/personajemono/mono3.png");
    cantidadFrames[PERSONAJE_MONO][ANIM_CAMINAR] = 2;

    spritesPersonajes[PERSONAJE_MONO][ANIM_CORRER][0] = cargar_imagen("assets/imgs/personajemono/mono4.png");
    spritesPersonajes[PERSONAJE_MONO][ANIM_CORRER][1] = cargar_imagen("assets/imgs/personajemono/mono5.png");
    cantidadFrames[PERSONAJE_MONO][ANIM_CORRER] = 2;

    spritesPersonajes[PERSONAJE_MONO][ANIM_SALTAR][0] = cargar_imagen("assets/imgs/personajemono/mono6.png");
    cantidadFrames[PERSONAJE_MONO][ANIM_SALTAR] = 1;

    spritesPersonajes[PERSONAJE_MONO][ANIM_AGACHADO][0] = cargar_imagen("assets/imgs/personajemono/mono7.png");
    cantidadFrames[PERSONAJE_MONO][ANIM_AGACHADO] = 1;

    spritesPersonajes[PERSONAJE_MONO][ANIM_GOLPE][0] = cargar_imagen("assets/imgs/personajemono/mono8.png");
    cantidadFrames[PERSONAJE_MONO][ANIM_GOLPE] = 1;

    
    /* PERSONAJE 2: T-REX */
    spritesPersonajes[PERSONAJE_TREX][ANIM_IDLE][0] = cargar_imagen("assets/imgs/personajetrex/trex1.png");
    cantidadFrames[PERSONAJE_TREX][ANIM_IDLE] = 1;

    spritesPersonajes[PERSONAJE_TREX][ANIM_CAMINAR][0] = cargar_imagen("assets/imgs/personajetrex/trex2.png");
    spritesPersonajes[PERSONAJE_TREX][ANIM_CAMINAR][1] = cargar_imagen("assets/imgs/personajetrex/trex3.png");   
    cantidadFrames[PERSONAJE_TREX][ANIM_CAMINAR] = 2;

    spritesPersonajes[PERSONAJE_TREX][ANIM_CORRER][0] = cargar_imagen("assets/imgs/personajetrex/trex5.png");
    spritesPersonajes[PERSONAJE_TREX][ANIM_CORRER][1] = cargar_imagen("assets/imgs/personajetrex/trex4.png");
    cantidadFrames[PERSONAJE_TREX][ANIM_CORRER] = 2;

    spritesPersonajes[PERSONAJE_TREX][ANIM_SALTAR][0] = cargar_imagen("assets/imgs/personajetrex/trex6.png");
    cantidadFrames[PERSONAJE_TREX][ANIM_SALTAR] = 1;

    spritesPersonajes[PERSONAJE_TREX][ANIM_AGACHADO][0] = cargar_imagen("assets/imgs/personajetrex/trex7.png");
    cantidadFrames[PERSONAJE_TREX][ANIM_AGACHADO] = 1;

    spritesPersonajes[PERSONAJE_TREX][ANIM_GOLPE][0] = cargar_imagen("assets/imgs/personajetrex/trex8.png");
    cantidadFrames[PERSONAJE_TREX][ANIM_GOLPE] = 1;



    if (spritesPersonajes[PERSONAJE_MONO][ANIM_IDLE][0] == NULL ||
    spritesPersonajes[PERSONAJE_TREX][ANIM_IDLE][0] == NULL)
    {
        printf("Error cargando sprites de personajes\n");
        al_destroy_event_queue(cola);
        al_destroy_display(display);
        return 1;
    }

    ALLEGRO_BITMAP *fondo = al_load_bitmap("assets/imgs/fondolava1.png");

    if (fondo == NULL)
    {
        printf("No se pudo cargar la imagen assets/imgs/fondolava1.png\n");
        al_destroy_event_queue(cola);
        al_destroy_display(display);
        return 1;
    }

    ALLEGRO_BITMAP *tilePiso35 = cargar_imagen("assets/imgs/carpetatile/tiles/Tile_35.png");
    ALLEGRO_BITMAP *tilePiso02 = cargar_imagen("assets/imgs/carpetatile/tiles/Tile_02.png");
    ALLEGRO_BITMAP *tileLavaquema = cargar_imagen("assets/imgs/tileslava/lava_animada_1.png");
    ALLEGRO_BITMAP *tilepinchos = cargar_imagen("assets/imgs/pinchos/pinchos.png");
    ALLEGRO_BITMAP *tilebotiquin = cargar_imagen("assets/imgs/botiquin/botiquin.png");
    ALLEGRO_BITMAP *tilecaja = cargar_imagen("assets/imgs/cajas/caja1.png");

    if (tilePiso35 == NULL || tilePiso02 == NULL || tileLavaquema == NULL || tilepinchos == NULL || tilebotiquin == NULL || tilecaja == NULL)
    {
        return 1;
    }

    ALLEGRO_FONT *fuente = al_load_ttf_font("assets/fuentes/fuentemenu.ttf", 100, 0);  
    ALLEGRO_FONT *fuenteVida = al_load_ttf_font("assets/fuentes/fuentemenu.ttf", 26, 0); 
    ALLEGRO_FONT *fuenteganador = al_load_ttf_font("assets/fuentes/fuentemenu.ttf", 180,0);

    if (fuente == NULL || fuenteVida == NULL || fuenteganador == NULL)
    {   
        printf("No se pudo crear la fuente\n");
        al_destroy_bitmap(fondo);
        al_destroy_event_queue(cola);
        al_destroy_display(display);
        return 1;
    }


    char mapa[MAPA_FILAS][MAPA_COLUMNAS];

    if (!cargar_mapa("assets/mapas/mapa1.txt", mapa))
    {
        printf("No se pudo cargar el mapa\n");
        return 1;
    }

    // 4. Registrar eventos de la ventana
    al_register_event_source(cola, al_get_display_event_source(display));
    al_register_event_source(cola, al_get_keyboard_event_source());

    int cerrar = 0;
    
    Pantalla pantallaActual = PANTALLA_MENU;

    int opcionMenu = 0;
    int totalOpciones = 3;

    Mono monos[CANT_MONOS];
    inicializar_monos_sobre_piso(monos, mapa);
    Proyectil proyectiles[MAX_PROYECTILES]= {0};
    
    int mostrarRectangulo = 0;  
    int monoActivo = PRIMER_MONO;
    int trexActivo = PRIMER_TREX;

    int tecla_izquierda_mono = 0;
    int tecla_derecha_mono = 0;
    int salto_mono = 0;

    int tecla_izquierda_trex = 0;
    int tecla_derecha_trex = 0;
    int salto_trex = 0;
    // 5. Ciclo principal del programa
while (cerrar == 0)
{
    ALLEGRO_EVENT evento;

    while (al_get_next_event(cola, &evento))
{
    if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        cerrar = 1;
    }

    if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            if (pantallaActual == PANTALLA_MENU)
            {
                cerrar = 1;
            }
            else
            {
                pantallaActual = PANTALLA_MENU;
            }
        }
        else if (pantallaActual == PANTALLA_MENU)
        {
            if (evento.keyboard.keycode == ALLEGRO_KEY_UP)
            {
                opcionMenu--;

                if (opcionMenu < 0)
                {
                    opcionMenu = totalOpciones - 1;
                }
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
                opcionMenu++;

                if (opcionMenu >= totalOpciones)
                {
                    opcionMenu = 0;
                }
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                if (opcionMenu == 0)
                {
                    pantallaActual = PANTALLA_JUEGO;
                }
                else if (opcionMenu == 1)
                {
                    pantallaActual = PANTALLA_AJUSTES;
                }
                else if (opcionMenu == 2)
                {
                    pantallaActual = PANTALLA_RANKING;
                }
            }
        }
        else if (pantallaActual == PANTALLA_JUEGO)
        {
            if (evento.keyboard.keycode == ALLEGRO_KEY_UP)
            {
                salto_mono = 1;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT)
            {
                tecla_izquierda_mono = 1;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT)
            {
                tecla_derecha_mono = 1;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_MINUS ||
                     evento.keyboard.keycode == ALLEGRO_KEY_PAD_MINUS)
            {
                monoActivo++;

                if (monoActivo > ULTIMO_MONO)
                {
                    monoActivo = PRIMER_MONO;
                }
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_W)
            {
                salto_trex = 1;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_A)
            {
                tecla_izquierda_trex = 1;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_D)
            {
                tecla_derecha_trex = 1;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_TAB)
            {
                trexActivo++;

                if (trexActivo > ULTIMO_TREX)
                {
                    trexActivo = PRIMER_TREX;
                }
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
            disparar_arma(proyectiles,&monos[monoActivo],monoActivo);
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_E)
            {
            disparar_arma(proyectiles,&monos[trexActivo],trexActivo);
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_H)
            {
                mostrarRectangulo = !mostrarRectangulo;
            }
        }
    }

    if (evento.type == ALLEGRO_EVENT_KEY_UP)
    {
        if (pantallaActual == PANTALLA_JUEGO)
        {
            if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT)
            {
                tecla_izquierda_mono = 0;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT)
            {
                tecla_derecha_mono = 0;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_A)
            {
                tecla_izquierda_trex = 0;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_D)
            {
                tecla_derecha_trex = 0;
            }
        }
    }
}
   
    if (pantallaActual == PANTALLA_JUEGO)
{
    for (int i = 0; i < CANT_MONOS; i++)
    {
        if (monos[i].vida > 0)
        {
            int esMonoActivo = 0;
            int esTrexActivo = 0;

            int saltoPersonaje = 0;
            int izquierdaPersonaje = 0;
            int derechaPersonaje = 0;

            if (i == monoActivo)
            {
                esMonoActivo = 1;
            }

            if (i == trexActivo)
            {
                esTrexActivo = 1;
            }

            if (esMonoActivo == 1)
            {
                saltoPersonaje = salto_mono;
                izquierdaPersonaje = tecla_izquierda_mono;
                derechaPersonaje = tecla_derecha_mono;
            }

            if (esTrexActivo == 1)
            {
                saltoPersonaje = salto_trex;
                izquierdaPersonaje = tecla_izquierda_trex;
                derechaPersonaje = tecla_derecha_trex;
            }

            mover_mono(
                &monos[i],
                saltoPersonaje,
                izquierdaPersonaje,
                derechaPersonaje,
                mapa
            );

            limitar_mono_pantalla(&monos[i], ANCHO, ALTO);

            aplicar_daño_pinchos(&monos[i], mapa);
            aplicar_tile_muerte(&monos[i], mapa);

            if (esMonoActivo == 1 || esTrexActivo == 1)
            {
                aplicar_curacion_botiquin(&monos[i], mapa);
            }

            actualizar_animacion_mono(
                &monos[i],
                izquierdaPersonaje,
                derechaPersonaje,
                0,
                0,
                cantidadFrames
            );
        }
    }
    actualizar_proyectiles(proyectiles, monos, ANCHO);
    ganador=revisar_ganador(monos);
    salto_mono = 0;
    salto_trex = 0;
}
    
    al_clear_to_color(al_map_rgb(0, 0, 0)); 
    dibujar_fondo(fondo, ANCHO, ALTO);

    if (pantallaActual == PANTALLA_MENU)
    {
        dibujar_menu(fuente, ANCHO, opcionMenu);
    }
    else if (pantallaActual == PANTALLA_JUEGO)
    {
        dibujar_mapa(mapa, tilePiso35, tilePiso02, tileLavaquema, tilepinchos, tilebotiquin, tilecaja);
        dibujar_monos(spritesPersonajes, cantidadFrames, monos);
        dibujar_proyectiles(proyectiles);
        for (int fila = 0; fila < MAPA_FILAS; fila++)
        {
            for (int columna = 0; columna < MAPA_COLUMNAS; columna++)
            {
                if (mapa[fila][columna] == '$')
                {
                al_draw_scaled_bitmap(
                tilepinchos,
                0,
                0,
                al_get_bitmap_width(tilepinchos),
                al_get_bitmap_height(tilepinchos),
                columna * TAM_TILE,
                fila * TAM_TILE,
                TAM_TILE,
                TAM_TILE,
                0
                );
                }
            }
        }
        dibujar_vidas_monos(monos, fuenteVida, ANCHO);
        if (mostrarRectangulo == 1 && monos[monoActivo].vida > 0)
        {
            dibujar_hitbox_mono(monos[monoActivo]);
        }
    }
    else if (pantallaActual == PANTALLA_AJUSTES)
    {
        al_draw_text(fuente, al_map_rgb(255, 255, 255), ANCHO/ 2, 300, ALLEGRO_ALIGN_CENTER, "PANTALLA DE AJUSTES");
        al_draw_text(fuente, al_map_rgb(180, 180, 180), ANCHO / 2, 360, ALLEGRO_ALIGN_CENTER, "Presiona ESC para volver");
    }
    else if (pantallaActual == PANTALLA_RANKING)
    {
        al_draw_text(fuente, al_map_rgb(255, 255, 255), ANCHO / 2, 300, ALLEGRO_ALIGN_CENTER, "PANTALLA DE RANKING");
        al_draw_text(fuente, al_map_rgb(180, 180, 180), ANCHO / 2, 360, ALLEGRO_ALIGN_CENTER, "Presiona ESC para volver");
    }

    dibujar_ganador(ganador, fuenteganador, ANCHO, ALTO);
    al_flip_display();

    al_rest(0.01);
}   
    al_destroy_font(fuenteVida);
    al_destroy_font(fuente);
    al_destroy_font(fuenteganador);
    al_destroy_bitmap(tilePiso35);
    al_destroy_bitmap(tilePiso02);
    al_destroy_bitmap(tileLavaquema);
    al_destroy_bitmap(tilepinchos);
    al_destroy_bitmap(tilebotiquin);
    al_destroy_bitmap(tilecaja);
    al_destroy_bitmap(fondo);
    for (int tipo = 0; tipo < CANT_TIPOS_PERSONAJES; tipo++)
    {
        for (int anim = 0; anim < CANT_ANIMACIONES; anim++)
        {
            for (int frame = 0; frame < MAX_FRAMES_ANIMACION; frame++)
            {
                if (spritesPersonajes[tipo][anim][frame] != NULL)
                {
                    al_destroy_bitmap(spritesPersonajes[tipo][anim][frame]);
                }
            }
        }
    }
    al_destroy_event_queue(cola);
    al_destroy_display(display);
    
    return 0;
}