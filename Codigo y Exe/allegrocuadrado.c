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
    if (!INICIARALLEGRO())
    {   
        return 1;
    }

    int ANCHO = 0;
    int ALTO = 0;

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

    ALLEGRO_BITMAP *personaje = al_load_bitmap("assets/imgs/mono.png");

    if (personaje == NULL)
    {
    printf("No se pudo cargar la imagen assets/imgs/mono.png\n");
    al_destroy_event_queue(cola);
    al_destroy_display(display);
    return 1;
    }

    ALLEGRO_BITMAP *fondo = al_load_bitmap("assets/imgs/fondolava1.png");

    if (fondo == NULL)
    {
        printf("No se pudo cargar la imagen assets/imgs/fondolava1.png\n");
        al_destroy_bitmap(personaje);
        al_destroy_event_queue(cola);
        al_destroy_display(display);
        return 1;
    }

    ALLEGRO_BITMAP *tilePiso = cargar_imagen("assets/imgs/roca1.png");
    ALLEGRO_BITMAP *tileLava = cargar_imagen("assets/imgs/roca2.png");

    if (tilePiso == NULL || tileLava == NULL)
    {
        return 1;
    }

    ALLEGRO_FONT *fuente = al_load_ttf_font("assets/fuentes/fuentemenu.ttf", 100, 0);   
    if (fuente == NULL)
    {   
        printf("No se pudo crear la fuente\n");
        al_destroy_bitmap(fondo);
        al_destroy_bitmap(personaje);
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
    inicializar_monos(monos, ANCHO, ALTO);

    int monoActivo = 0;
    int mostrarRectangulo = 1;

    int tecla_arriba = 0;
    int tecla_abajo = 0;
    int tecla_izquierda = 0;
    int tecla_derecha = 0;
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
                    tecla_arriba = 1;
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN)
                {
                    tecla_abajo = 1;
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT)
                {
                    tecla_izquierda = 1;
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                {
                    tecla_derecha = 1;
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_TAB)
                {
                    monoActivo++;

                    if (monoActivo >= CANT_MONOS)
                    {
                        monoActivo = 0;
                    }

                    mostrarRectangulo = 1;
                }
            }
        }

        if (evento.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (evento.keyboard.keycode == ALLEGRO_KEY_UP)
            {
                tecla_arriba = 0;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
                tecla_abajo = 0;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT)
            {
                tecla_izquierda = 0;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT)
            {
                tecla_derecha = 0;
            }
        }
    }

    if (pantallaActual == PANTALLA_JUEGO)
    {
        mover_mono(&monos[monoActivo],tecla_arriba,tecla_abajo,tecla_izquierda,tecla_derecha,&mostrarRectangulo);
    }
    limitar_mono_pantalla(&monos[monoActivo], ANCHO, ALTO);
    al_clear_to_color(al_map_rgb(0, 0, 0)); 
    dibujar_fondo(fondo, ANCHO, ALTO);

    if (pantallaActual == PANTALLA_MENU)
    {
        dibujar_menu(fuente, ANCHO, opcionMenu);
    }
    else if (pantallaActual == PANTALLA_JUEGO)
    {
        dibujar_mapa(mapa, tilePiso, tileLava);
        dibujar_monos(personaje, monos);
        if (mostrarRectangulo == 1)
        {
            al_draw_rectangle(
            monos[monoActivo].x,
            monos[monoActivo].y,
            monos[monoActivo].x + monos[monoActivo].ancho,
            monos[monoActivo].y + monos[monoActivo].alto,
            al_map_rgb(0, 255, 0),
            3);
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

    al_flip_display();

    al_rest(0.01);
}   

    al_destroy_font(fuente);
    al_destroy_bitmap(tileLava);
    al_destroy_bitmap(tilePiso);
    al_destroy_bitmap(fondo);
    al_destroy_bitmap(personaje);
    al_destroy_event_queue(cola);
    al_destroy_display(display);
    
    return 0;
}