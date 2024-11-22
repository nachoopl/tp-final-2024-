#ifndef PLAYLIST_H_INCLUDED
#define PLAYLIST_H_INCLUDED

typedef struct
{
    int idPlaylist;
    int idUsuario;
    int idCancion;
} stPlaylist;

void cargarPlaylistArchivo(char ArchivoPlaylist[]);

#endif // PLAYLIST_H_INCLUDED
