#ifndef PLAYLIST_H_INCLUDED
#define PLAYLIST_H_INCLUDED

typedef struct
{
    int idPlaylist;
    int idUsuario;
    int idCancion;
} stPlaylist;

typedef struct
{
    int idUsuario;
    char nombreUsuario[50];
    int idCancion;
    char nombreCancion[100];
} stCancionesEscuchadas;

void cargarPlaylistArchivo(char ArchivoPlaylist[]);

#endif // PLAYLIST_H_INCLUDED
