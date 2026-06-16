#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "define.h"
#include "struct.h"
#include "funciones.h"  

//Funcion dibujar fondo

void dibujar_fondo(ALLEGRO_BITMAP *fondo, int ANCHO, int ALTO)
{
    al_draw_scaled_bitmap(
    fondo,
    0, 0,
    al_get_bitmap_width(fondo),
    al_get_bitmap_height(fondo),
    0, 0,
    ANCHO,
    ALTO,
    0);
}


//Funcion pantalla completa

ALLEGRO_DISPLAY *crear_pantalla_completa(int *ANCHO, int *ALTO)
{
    ALLEGRO_MONITOR_INFO info;

    if (!al_get_monitor_info(0, &info))
    {
        printf("No se pudo obtener informacion del monitor\n");
        return NULL;
    }

    *ANCHO = info.x2 - info.x1;
    *ALTO = info.y2 - info.y1;

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    ALLEGRO_DISPLAY *display = al_create_display(*ANCHO, *ALTO);

    if (display == NULL)
    {
        printf("No se pudo crear la pantalla completa\n");
        return NULL;
    }

    *ANCHO = al_get_display_width(display);
    *ALTO = al_get_display_height(display);

    return display;
}   


//Funcion iniciar allegro

int INICIARALLEGRO(void)
{
        if(!al_init())
    {
        printf("No se pudo iniciar Allegro\n");
        return 0;
    }

    if (!al_install_keyboard())
    {
    printf("No se pudo instalar el teclado\n");
    return 0;
    }

    al_init_primitives_addon();
    al_init_font_addon();

    if (!al_init_ttf_addon())
    {
        printf("No se pudo iniciar el addon de fuentes TTF\n");
        return 0;
    }

    if (!al_init_image_addon())
    {
        printf("No se pudo iniciar el addon de imagenes\n");
        return 0;
    }
    return 1;
}




ALLEGRO_BITMAP *cargar_imagen(const char *ruta)
{
    ALLEGRO_BITMAP *imagen = al_load_bitmap(ruta);

    if (imagen == NULL)
    {
        printf("No se pudo cargar la imagen: %s\n", ruta);
        return NULL;
    }

    return imagen;
}

int cargar_mapa(const char *ruta, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    FILE *archivo = fopen(ruta, "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el mapa: %s\n", ruta);
        return 0;
    }

    int fila;
    int columna;
    int caracter;

    for (fila = 0; fila < MAPA_FILAS; fila++)
    {
        for (columna = 0; columna < MAPA_COLUMNAS; columna++)
        {
            caracter = fgetc(archivo);

            while (caracter == '\n' || caracter == '\r')
            {
                caracter = fgetc(archivo);
            }

            if (caracter == EOF)
            {
                printf("Error: el mapa tiene menos caracteres de los esperados\n");
                fclose(archivo);
                return 0;
            }

            mapa[fila][columna] = caracter;
        }
    }

    fclose(archivo);
    return 1;
}


//Funcion Inserta tiles
void dibujar_mapa(char mapa[MAPA_FILAS][MAPA_COLUMNAS],ALLEGRO_BITMAP *tilePiso,ALLEGRO_BITMAP *tileLava)
{
    int fila;
    int columna;

    for (fila = 0; fila < MAPA_FILAS; fila++)
    {
        for (columna = 0; columna < MAPA_COLUMNAS; columna++)
        {
            int x = columna * TAM_TILE;
            int y = fila * TAM_TILE;

            if (mapa[fila][columna] == '#')
            {
                al_draw_scaled_bitmap(
                    tilePiso,
                    0, 0,
                    al_get_bitmap_width(tilePiso),
                    al_get_bitmap_height(tilePiso),
                    x,
                    y,
                    TAM_TILE,
                    TAM_TILE,
                    0
                );
            }

            if (mapa[fila][columna] == '~')
            {
                al_draw_scaled_bitmap(
                    tileLava,
                    0, 0,
                    al_get_bitmap_width(tileLava),
                    al_get_bitmap_height(tileLava),
                    x,
                    y,
                    TAM_TILE,
                    TAM_TILE,
                    0
                );
            }
        }
    }
}


//función menú

void dibujar_menu(ALLEGRO_FONT *fuente, int ANCHO, int opcionMenu)
{
    al_draw_text(
        fuente,
        al_map_rgb(255, 255, 255),
        ANCHO / 2,
        150,
        ALLEGRO_ALIGN_CENTER,
        "WAR OF MONKEYS"
    );

    al_draw_text(
        fuente,
        opcionMenu == 0 ? al_map_rgb(255    , 128, 0) : al_map_rgb(200, 200, 200),
        ANCHO / 2,
        320,
        ALLEGRO_ALIGN_CENTER,
        "JUGAR"
    );

    al_draw_text(
        fuente,
        opcionMenu == 1 ? al_map_rgb(255, 128, 0) : al_map_rgb(200, 200, 200),
        ANCHO / 2,
        520,
        ALLEGRO_ALIGN_CENTER,
        "AJUSTES"
    );

    al_draw_text(
        fuente,
        opcionMenu == 2 ? al_map_rgb(255, 128, 0) : al_map_rgb(200, 200, 200),
        ANCHO / 2,
        720,
        ALLEGRO_ALIGN_CENTER,
        "RANKING"
    );

    al_draw_text(
        fuente,
        al_map_rgb(255, 255, 255),
        ANCHO / 2,
        880,
        ALLEGRO_ALIGN_CENTER,
        "Usa flechas y ENTER"
    );
}


//dibujar monos
void dibujar_monos(ALLEGRO_BITMAP *personaje, Mono monos[])
{
    for(int i = 0; i < CANT_MONOS; i++)
    {
        al_draw_scaled_bitmap(personaje, 0, 0, al_get_bitmap_width(personaje), al_get_bitmap_height(personaje),
            monos[i].x,
            monos[i].y,
            monos[i].ancho,
            monos[i].alto,
            0
        );
    }
}

//inicializar monos

    void inicializar_monos_sobre_piso(Mono monos[], char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    srand(time(0));

    for (int i = 0; i < CANT_MONOS; i++)
    {
        monos[i].ancho = anchomono;
        monos[i].alto = altomono;
        monos[i].velocidad = velocidadmono;
        monos[i].vida = 200;

        int encontrado = 0;

        while (encontrado == 0)
        {
            int columna = rand() % MAPA_COLUMNAS;

            for (int fila = 1; fila < MAPA_FILAS; fila++)
            {
                if (mapa[fila][columna] == '#' && mapa[fila - 1][columna] == '.')
                {
                    monos[i].x = columna * TAM_TILE;
                    monos[i].y = fila * TAM_TILE - monos[i].alto;

                    encontrado = 1;
                    break;
                }
            }
        }
    }
}

//detectar bloque
int es_tile_solido(char bloque)
{
    if (bloque == '#' || bloque == '~')
    {
        return 1;
    }

    return 0;
}

int mono_colisiona_con_mapa(char mapa[MAPA_FILAS][MAPA_COLUMNAS], float x, float y, float ancho, float alto)
{
    int columnaIzquierda = x / TAM_TILE;
    int columnaDerecha = (x + ancho - 1) / TAM_TILE;
    int filaArriba = y / TAM_TILE;
    int filaAbajo = (y + alto - 1) / TAM_TILE;

    if (columnaIzquierda < 0 || columnaDerecha >= MAPA_COLUMNAS ||
        filaArriba < 0 || filaAbajo >= MAPA_FILAS)
    {
        return 1;
    }

    for (int fila = filaArriba; fila <= filaAbajo; fila++)
    {
        for (int columna = columnaIzquierda; columna <= columnaDerecha; columna++)
        {
            if (es_tile_solido(mapa[fila][columna]))
            {
                return 1;
            }
        }
    }

    return 0;
}


void mover_mono(Mono *mono, int arriba, int abajo, int izquierda, int derecha, int *mostrarRectangulo, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    float nuevaX = mono->x;
    float nuevaY = mono->y;

    if (izquierda == 1)
    {
        nuevaX = mono->x - mono->velocidad;
        *mostrarRectangulo = 0;
    }

    if (derecha == 1)
    {
        nuevaX = mono->x + mono->velocidad;
        *mostrarRectangulo = 0;
    }

    if (!mono_colisiona_con_mapa(mapa, nuevaX, mono->y, mono->ancho, mono->alto))
    {
        mono->x = nuevaX;
    }

    if (arriba == 1)
    {
        nuevaY = mono->y - mono->velocidad;
        *mostrarRectangulo = 0;
    }

    if (abajo == 1)
    {
        nuevaY = mono->y + mono->velocidad;
        *mostrarRectangulo = 0;
    }

    if (!mono_colisiona_con_mapa(mapa, mono->x, nuevaY, mono->ancho, mono->alto))
    {
        mono->y = nuevaY;
    }
}

//limitar monos
void limitar_mono_pantalla(Mono *mono, int anchoPantalla, int altoPantalla)
{
    if (mono->x < 0)
    {
        mono->x = 0;
    }

    if (mono->y < 0)
    {
        mono->y = 0;
    }

    if (mono->x + mono->ancho > anchoPantalla)
    {
        mono->x = anchoPantalla - mono->ancho;
    }

    if (mono->y + mono->alto > altoPantalla)
    {
        mono->y = altoPantalla - mono->alto;
    }
}