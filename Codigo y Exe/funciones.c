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
void dibujar_mapa(char mapa[MAPA_FILAS][MAPA_COLUMNAS],ALLEGRO_BITMAP *tilePiso,ALLEGRO_BITMAP *tileLava, ALLEGRO_BITMAP *tileLavaquema, ALLEGRO_BITMAP *tilepinchos, ALLEGRO_BITMAP *tilebotiquin, ALLEGRO_BITMAP *tilecaja)
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
            if(mapa[fila][columna] == '%')
            {
                al_draw_scaled_bitmap(tileLavaquema,
                    0, 0,
                    al_get_bitmap_width(tileLavaquema),
                    al_get_bitmap_height(tileLavaquema),
                    x,
                    y,
                    TAM_TILE,
                    TAM_TILE,
                    0
                );
            }
            if(mapa[fila][columna] == '$')
            {
                al_draw_scaled_bitmap(tilepinchos,
                    0, 0,
                    al_get_bitmap_width(tilepinchos),
                    al_get_bitmap_height(tilepinchos),
                    x,
                    y,
                    TAM_TILE,
                    TAM_TILE,
                    0
                );
            }
            if(mapa[fila][columna] == '*')
            {
                al_draw_scaled_bitmap(tilebotiquin,
                    0, 0,
                    al_get_bitmap_width(tilebotiquin),
                    al_get_bitmap_height(tilebotiquin),
                    x,
                    y,
                    TAM_TILE,
                    TAM_TILE,
                    0
                );
            }
            if(mapa[fila][columna] == 'C')
            {
                al_draw_scaled_bitmap(tilecaja,
                    0, 0,
                    al_get_bitmap_width(tilecaja),
                    al_get_bitmap_height(tilecaja),
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
void dibujar_monos(
    ALLEGRO_BITMAP *spritesPersonajes[CANT_TIPOS_PERSONAJES][CANT_ANIMACIONES][MAX_FRAMES_ANIMACION],
    int cantidadFrames[CANT_TIPOS_PERSONAJES][CANT_ANIMACIONES],
    Mono monos[]
)
{

    for(int i = 0; i < CANT_MONOS; i++)
    {   
        if (monos[i].vida <= 0)
        {
            continue;
        }

        int tipo = monos[i].tipoPersonaje;
        int animacion = monos[i].animacionActual;
        int frame = monos[i].frameActual;

        if (tipo < 0 || tipo >= CANT_TIPOS_PERSONAJES)
        {
            continue;
        }

        if (animacion < 0 || animacion >= CANT_ANIMACIONES)
        {
            continue;
        }

        if (cantidadFrames[tipo][animacion] <= 0)
        {
            continue;
        }

        if (frame >= cantidadFrames[tipo][animacion])
        {
            frame = 0;
        }

        ALLEGRO_BITMAP *spriteActual = spritesPersonajes[tipo][animacion][frame];

        if (spriteActual == NULL)
        {
            continue;
        }

        int direccion = 0;

        if (monos[i].mirandoDerecha == 0)
        {
            direccion = ALLEGRO_FLIP_HORIZONTAL;
        }

        al_draw_scaled_bitmap(
            spriteActual,
            0, 0,
            al_get_bitmap_width(spriteActual),
            al_get_bitmap_height(spriteActual),
            monos[i].x,
            monos[i].y,
            monos[i].ancho,
            monos[i].alto,
            direccion
        );
    }
}

void cambiar_animacion_mono(Mono *mono, int nuevaAnimacion)
{
    if (mono->animacionActual != nuevaAnimacion)
    {
        mono->animacionActual = nuevaAnimacion;
        mono->frameActual = 0;
        mono->contadorAnimacion = 0;
    }
}

void actualizar_animacion_mono(
    Mono *mono,
    int izquierda,
    int derecha,
    int abajo,
    int golpe,
    int cantidadFrames[CANT_TIPOS_PERSONAJES][CANT_ANIMACIONES]
)
{
    if (derecha == 1)
    {
        mono->mirandoDerecha = 1;
    }

    if (izquierda == 1)
    {
        mono->mirandoDerecha = 0;
    }

    if (golpe == 1)
    {
        cambiar_animacion_mono(mono, ANIM_GOLPE);
    }
    else if (mono->enSuelo == 0)
    {
        cambiar_animacion_mono(mono, ANIM_SALTAR);
    }
    else if (abajo == 1)
    {
        cambiar_animacion_mono(mono, ANIM_AGACHADO);
    }
    else if (izquierda == 1 || derecha == 1)
    {
        cambiar_animacion_mono(mono, ANIM_CAMINAR);
    }
    else
    {
        cambiar_animacion_mono(mono, ANIM_IDLE);
    }

    mono->contadorAnimacion++;

    if (mono->contadorAnimacion >= 8)
    {
        mono->contadorAnimacion = 0;
        mono->frameActual++;

        int tipo = mono->tipoPersonaje;
        int animacion = mono->animacionActual;
        int cantidad = cantidadFrames[tipo][animacion];

        if (cantidad <= 0)
        {
            mono->frameActual = 0;
            return;
        }

        if (mono->frameActual >= cantidad)
        {
            mono->frameActual = 0;
        }
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

        monos[i].velocidadY = 0;
        monos[i].enSuelo = 1;

        monos[i].vida = VIDA_MAXIMA_MONO;
        monos[i].cooldownDaño = 0;
        monos[i].armaActual.tipo = arma_pistola;
        monos[i].armaActual.daño = dañoarma1;
        monos[i].armaActual.municion = municionarma1;
        monos[i].armaActual.tiemporecarga = tiemporecargaarma1;
        monos[i].armaActual.velocidadproyectil = velocidadarma1;

        
        if (i < CANT_MONOS/2)
        {
            monos[i].tipoPersonaje = PERSONAJE_MONO;
        }
        else
        {
            monos[i].tipoPersonaje = PERSONAJE_TREX;
        }   

        /* Datos iniciales de animación */
        monos[i].animacionActual = ANIM_IDLE;
        monos[i].frameActual = 0;
        monos[i].contadorAnimacion = 0;
        monos[i].mirandoDerecha = 1;

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
    if (bloque == '#' || bloque == '~' || bloque == '%' || bloque == '*' || bloque == 'C')
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


//mover mono
// Mueve el mono usando una hitbox más pequeña que el sprite.
// La imagen del mono sigue midiendo 72x64,
// pero las colisiones usan HITBOX_MONO_ANCHO x HITBOX_MONO_ALTO.
void mover_mono(Mono *mono, int salto, int izquierda, int derecha, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    float nuevaX = mono->x;

    if (izquierda == 1)
    {
        nuevaX = mono->x - mono->velocidad;
    }

    if (derecha == 1)
    {
        nuevaX = mono->x + mono->velocidad;
    }

    // Posición real de la hitbox
    float hitboxX = nuevaX + HITBOX_MONO_OFFSET_X;
    float hitboxY = mono->y + HITBOX_MONO_OFFSET_Y;

    // Colisión horizontal usando la hitbox roja
    if (!mono_colisiona_con_mapa(
            mapa,
            hitboxX,
            hitboxY,
            HITBOX_MONO_ANCHO,
            HITBOX_MONO_ALTO
        ))
    {
        mono->x = nuevaX;
    }

    // Salto
    if (salto == 1 && mono->enSuelo == 1)
    {
        mono->velocidadY = velocidad_salto;
        mono->enSuelo = 0;
    }

    // Gravedad
    mono->velocidadY += gravedad;

    if (mono->velocidadY > velocidad_caida)
    {
        mono->velocidadY = velocidad_caida;
    }

    float nuevaY = mono->y + mono->velocidadY;

    hitboxX = mono->x + HITBOX_MONO_OFFSET_X;
    hitboxY = nuevaY + HITBOX_MONO_OFFSET_Y;

    // Colisión vertical usando la hitbox roja
    if (!mono_colisiona_con_mapa(
            mapa,
            hitboxX,
            hitboxY,
            HITBOX_MONO_ANCHO,
            HITBOX_MONO_ALTO
        ))
    {
        mono->y = nuevaY;
        mono->enSuelo = 0;
    }
    else
    {
        // Si venía cayendo, lo dejamos justo arriba del piso
        if (mono->velocidadY > 0)
        {
            while (!mono_colisiona_con_mapa(
                        mapa,
                        mono->x + HITBOX_MONO_OFFSET_X,
                        mono->y + 1 + HITBOX_MONO_OFFSET_Y,
                        HITBOX_MONO_ANCHO,
                        HITBOX_MONO_ALTO
                    ))
            {
                mono->y += 1;
            }

            mono->enSuelo = 1;
        }

        // Si venía subiendo, lo dejamos justo debajo del bloque
        if (mono->velocidadY < 0)
        {
            while (!mono_colisiona_con_mapa(
                        mapa,
                        mono->x + HITBOX_MONO_OFFSET_X,
                        mono->y - 1 + HITBOX_MONO_OFFSET_Y,
                        HITBOX_MONO_ANCHO,
                        HITBOX_MONO_ALTO
                    ))
            {
                mono->y -= 1;
            }
        }

        mono->velocidadY = 0;
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

//funcion hitbox
// Dibuja la hitbox real que se ocupa para chocar con el mapa.
// Verde = tamaño completo del sprite.
// Rojo = hitbox real usada para colisiones.
void dibujar_hitbox_mono(Mono mono)
{
    float hitboxX = mono.x + HITBOX_MONO_OFFSET_X;
    float hitboxY = mono.y + HITBOX_MONO_OFFSET_Y;

    // Rectángulo verde: tamaño completo del sprite
    al_draw_rectangle(
        mono.x,
        mono.y,
        mono.x + mono.ancho,
        mono.y + mono.alto,
        al_map_rgb(0, 255, 0),
        1
    );

    // Rectángulo rojo: hitbox real
    al_draw_rectangle(
        hitboxX,
        hitboxY,
        hitboxX + HITBOX_MONO_ANCHO,
        hitboxY + HITBOX_MONO_ALTO,
        al_map_rgb(255, 0, 0),
        3
    );
}

void dibujar_vidas_monos(Mono monos[], ALLEGRO_FONT *fuenteVida, int ANCHO)
{
    int contadorMonos = 0;
    int contadorTrex = 0;

    for (int i = 0; i < CANT_MONOS; i++)
    {
        int vidaActual = monos[i].vida;

        if (vidaActual < 0)
        {
            vidaActual = 0;
        }

        if (vidaActual > VIDA_MAXIMA_MONO)
        {
            vidaActual = VIDA_MAXIMA_MONO;
        }

        float porcentajeVida = (float)vidaActual / VIDA_MAXIMA_MONO;
        float anchoVida = VIDA_BARRA_ANCHO * porcentajeVida;

        float x;
        float y;

        const char *nombrePersonaje;
        int numeroPersonaje;

        if (monos[i].tipoPersonaje == PERSONAJE_MONO)
        {
            nombrePersonaje = "MONO";
            numeroPersonaje = contadorMonos + 1;

            x = 40;
            y = 35 + contadorMonos * 60;

            contadorMonos++;
        }
        else
        {
            nombrePersonaje = "T-REX";
            numeroPersonaje = contadorTrex + 1;

            x = ANCHO - VIDA_BARRA_ANCHO - 40;
            y = 35 + contadorTrex * 60;

            contadorTrex++;
        }

        ALLEGRO_COLOR colorBarra = al_map_rgb(0, 220, 0);

        if (porcentajeVida <= 0.60)
        {
            colorBarra = al_map_rgb(255, 180, 0);
        }

        if (porcentajeVida <= 0.30)
        {
            colorBarra = al_map_rgb(220, 0, 0);
        }

        al_draw_filled_rectangle(
            x - 4,
            y - 4,
            x + VIDA_BARRA_ANCHO + 4,
            y + VIDA_BARRA_ALTO + 4,
            al_map_rgb(20, 20, 20)
        );

        al_draw_filled_rectangle(
            x,
            y,
            x + VIDA_BARRA_ANCHO,
            y + VIDA_BARRA_ALTO,
            al_map_rgb(80, 0, 0)
        );

        al_draw_filled_rectangle(
            x,
            y,
            x + anchoVida,
            y + VIDA_BARRA_ALTO,
            colorBarra
        );

        al_draw_rectangle(
            x,
            y,
            x + VIDA_BARRA_ANCHO,
            y + VIDA_BARRA_ALTO,
            al_map_rgb(255, 255, 255),
            2
        );

        al_draw_textf(
        fuenteVida,
        al_map_rgb(255, 255, 255),
        x,
        y + VIDA_BARRA_ALTO + 6,
        0,
        "%s %d VIDA %d",
        nombrePersonaje,
        numeroPersonaje,
        vidaActual
        );
    }
}

int mono_toca_tile(char mapa[MAPA_FILAS][MAPA_COLUMNAS], float x, float y, float ancho, float alto, char tileBuscado)
{
    int columnaIzquierda = x / TAM_TILE;
    int columnaDerecha = (x + ancho - 1) / TAM_TILE;
    int filaArriba = y / TAM_TILE;
    int filaAbajo = (y + alto - 1) / TAM_TILE;

    if (columnaDerecha < 0 || columnaIzquierda >= MAPA_COLUMNAS ||
        filaAbajo < 0 || filaArriba >= MAPA_FILAS)
    {
        return 0;
    }

    if (columnaIzquierda < 0)
    {
        columnaIzquierda = 0;
    }

    if (columnaDerecha >= MAPA_COLUMNAS)
    {
        columnaDerecha = MAPA_COLUMNAS - 1;
    }

    if (filaArriba < 0)
    {
        filaArriba = 0;
    }

    if (filaAbajo >= MAPA_FILAS)
    {
        filaAbajo = MAPA_FILAS - 1;
    }

    for (int fila = filaArriba; fila <= filaAbajo; fila++)
    {
        for (int columna = columnaIzquierda; columna <= columnaDerecha; columna++)
        {
            if (mapa[fila][columna] == tileBuscado)
            {
                return 1;
            }
        }
    }

    return 0;
}


void aplicar_daño_pinchos(Mono *mono, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    if (mono->cooldownDaño > 0)
    {
        mono->cooldownDaño--;
    }

    float hitboxX = mono->x + HITBOX_MONO_OFFSET_X;
    float hitboxY = mono->y + HITBOX_MONO_OFFSET_Y;

    if (mono_toca_tile(
            mapa,
            hitboxX,
            hitboxY,
            HITBOX_MONO_ANCHO,
            HITBOX_MONO_ALTO + 2,
            '$'
        ))
    {
        if (mono->cooldownDaño == 0)
        {
            mono->vida -= DAÑO_PINCHOS;

            if (mono->vida < 0)
            {
                mono->vida = 0;
            }

            mono->cooldownDaño = COOLDOWN_DAÑO_PINCHOS;
        }
    }
}

void aplicar_tile_muerte(Mono *mono, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    float hitboxX = mono ->x +
    HITBOX_MONO_OFFSET_X;
    float hitboxY = mono ->y +
    HITBOX_MONO_OFFSET_Y;
    if(mono_toca_tile(
            mapa,
            hitboxX,
            hitboxY,
            HITBOX_MONO_ANCHO,
            HITBOX_MONO_ALTO + 4,
            '%'
            )
        )
    {
        mono->vida = 0;
    }
}


void aplicar_curacion_botiquin(Mono *mono, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    float hitboxX = mono->x + HITBOX_MONO_OFFSET_X;
    float hitboxY = mono->y + HITBOX_MONO_OFFSET_Y;

    int columnaIzquierda = (hitboxX -8)/ TAM_TILE;
    int columnaDerecha = (hitboxX + HITBOX_MONO_ANCHO +8 - 1) / TAM_TILE;
    int filaArriba = hitboxY / TAM_TILE;
    int filaAbajo = (hitboxY + HITBOX_MONO_ALTO - 1) / TAM_TILE;

    if (columnaIzquierda < 0)
    {
        columnaIzquierda = 0;
    }

    if (columnaDerecha >= MAPA_COLUMNAS)
    {
        columnaDerecha = MAPA_COLUMNAS - 1;
    }

    if (filaArriba < 0)
    {
        filaArriba = 0;
    }

    if (filaAbajo >= MAPA_FILAS)
    {
        filaAbajo = MAPA_FILAS - 1;
    }

    for (int fila = filaArriba; fila <= filaAbajo; fila++)
    {
        for (int columna = columnaIzquierda; columna <= columnaDerecha; columna++)
        {
            if (mapa[fila][columna] == '*')
            {
                if (mono->vida < VIDA_MAXIMA_MONO)
                {
                    mono->vida += CURACION_BOTIQUIN;

                    if (mono->vida > VIDA_MAXIMA_MONO)
                    {
                        mono->vida = VIDA_MAXIMA_MONO;
                    }

                    mapa[fila][columna] = '.';
                }

                return;
            }
        }
    }
}

void disparar_arma(Proyectil proyectiles[],Mono *personaje,int indicePersonaje)
{
    if (personaje->vida <= 0)
    {
        return;
    }

    if (personaje->armaActual.tipo == arma_sin)
    {
        return;
    }

    if (personaje->armaActual.municion <= 0)
    {
        return;
    }

    for (int i = 0; i < MAX_PROYECTILES; i++)
    {
        if (proyectiles[i].activa == 0)
        {
            proyectiles[i].activa = 1;

            proyectiles[i].ancho = PROYECTIL_ANCHO;
            proyectiles[i].alto = PROYECTIL_ALTO;

            proyectiles[i].daño =
                personaje->armaActual.daño;

            proyectiles[i].personajequedispara =
                indicePersonaje;

            proyectiles[i].personajedañado = -1;

            proyectiles[i].y = personaje->y + HITBOX_MONO_OFFSET_Y + HITBOX_MONO_ALTO / 2 - PROYECTIL_ALTO / 2;

            if (personaje->mirandoDerecha == 1)
            {

                proyectiles[i].x =
                    personaje->x +
                    HITBOX_MONO_OFFSET_X +
                    HITBOX_MONO_ANCHO;

                proyectiles[i].velocidadX =
                    personaje->armaActual.velocidadproyectil;
            }
            else
            {
                proyectiles[i].x = personaje->x + HITBOX_MONO_OFFSET_X - PROYECTIL_ANCHO;

                proyectiles[i].velocidadX =-personaje->armaActual.velocidadproyectil;
            }

            personaje->armaActual.municion--;

            return;
        }
    }
}

void actualizar_proyectiles(
    Proyectil proyectiles[], Mono monos[],
    int anchoPantalla
)
{
    int i=0;
    int j=0;

    for (i = 0; i < MAX_PROYECTILES; i++)
    {
        if (proyectiles[i].activa == 1)
        {
            proyectiles[i].x +=
                proyectiles[i].velocidadX;

            if (proyectiles[i].x > anchoPantalla ||
                proyectiles[i].x +
                proyectiles[i].ancho < 0)
            {
                proyectiles[i].activa = 0;
                continue;
            }
            for(j=0 ;j<CANT_MONOS; j++)
            {
                int indiceDisparador =  proyectiles[i].personajequedispara;

                /*personaje que dispara se guarda en la variable indiceDisparador, revisa q no puede hacerse daño el mismo*/
                
                if(j==indiceDisparador)
                {
                    continue;
                }

                if(monos[j].vida<=0)
                {
                    continue;
                }

                if (indiceDisparador >= 0 && indiceDisparador < CANT_MONOS && monos[j].tipoPersonaje == monos[indiceDisparador].tipoPersonaje)
                {
                    continue;
                }

                float hitboxX = monos[j].x + HITBOX_MONO_OFFSET_X;
                float hitboxY = monos[j].y + HITBOX_MONO_OFFSET_Y;

                int hayColision =
                    proyectiles[i].x <
                    hitboxX + HITBOX_MONO_ANCHO &&

                    proyectiles[i].x +
                    proyectiles[i].ancho >
                    hitboxX &&

                    proyectiles[i].y <
                    hitboxY + HITBOX_MONO_ALTO &&

                    proyectiles[i].y +
                    proyectiles[i].alto >
                    hitboxY;

                

                if(hayColision == 1 )
                {
                    monos[j].vida = monos[j].vida - proyectiles[i].daño;

                     if (monos[j].vida < 0)
                    {
                        monos[j].vida = 0;
                    }

                    proyectiles[i].personajedañado = j;

                    proyectiles[i].activa = 0;

                    break;

                }
            }
        }
    }
}

void dibujar_proyectiles(
    Proyectil proyectiles[]
)
{
    for (int i = 0; i < MAX_PROYECTILES; i++)
    {
        if (proyectiles[i].activa == 1)
        {
            al_draw_filled_rectangle(
                proyectiles[i].x,
                proyectiles[i].y,

                proyectiles[i].x +
                proyectiles[i].ancho,

                proyectiles[i].y +
                proyectiles[i].alto,

                al_map_rgb(255, 220, 0)
            );
        }
    }
}

int revisar_ganador(Mono monos[])
{
    int i=0;
    int j=0;
    int monosVivos = 0;
    int trexVivos = 0;

    for (i = 0; i < CANT_MONOS; i++)
    {
        if (monos[i].vida > 0)
        {
            if (monos[i].tipoPersonaje == PERSONAJE_MONO)
            {
                monosVivos++;
            }
            else if (monos[i].tipoPersonaje == PERSONAJE_TREX)
            {
                trexVivos++;
            }
        }
    }

    if (trexVivos == 0 && monosVivos > 0)
    {
        return 1;
    }
    if (monosVivos == 0 && trexVivos > 0)
    {
        return 2;   
    }
    return 0;
}


void dibujar_ganador(int ganador, ALLEGRO_FONT *fuente, int ANCHO,int ALTO)
{
    if (ganador == 1)
    {
        al_draw_text(
            fuente,
            al_map_rgb(255, 255, 255),
            ANCHO / 2,
            (ALTO) / 2,
            ALLEGRO_ALIGN_CENTER,
            "GANADOR EQUIPO MONOS"
        );
    }
    else if(ganador == 2 )
    {
        al_draw_text(
            fuente,
            al_map_rgb(255, 255, 255),
            ANCHO / 2,
            (ALTO) / 2,
            ALLEGRO_ALIGN_CENTER,
            "GANADOR EQUIPO T-REX"
        );

    }
}