#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void escucharCancion(char ArchivoPlaylist[], char ArchivoCancion[], int idUsuario, int idCancion);
int obtenerUltimoIdPlaylist(char ArchivoPlaylist[]);
void cancionesRecomendadas(char ArchivoPlaylist[], char ArchivoCancion[], int idUsuario);
int estaEnPlaylist(char ArchivoPlaylist[], int idUsuario, int idCancion);
int cargarCanciones(char archivoCancion[], stCancion canciones[]);
void ordenarPorTitulo(stCancion canciones[], int numCanciones);
void ordenarPorGenero(stCancion canciones[], int numCanciones);
void mostrarCanciones(stCancion canciones[], int numCanciones);
void listarCanciones(char archivoCancion[]);
int cargarUsuarios(char archivo[], stUsuario usuarios[]);
void ordenarPorNombreUsuario(stUsuario usuarios[], int numUsuarios);
void mostrarUsuarios(stUsuario usuarios[], int numUsuarios);
void listarUsuarios(char archivo[]);
void mostrarPlaylist(char archivoPlaylist[], char archivoCancion[], int idUsuario);
void mostrarCancionesPlaylist(stPlaylist playlist[], stCancion canciones[], int numPlaylist, int numCanciones);
int cargarPlaylist(char archivoPlaylist[], stPlaylist playlist[], int idUsuario);
int cargarArregloPlaylistConCanciones(char archivo[], stCancion canciones[]);
void ordenarPorTituloPlaylist(stCancion canciones[], int numCanciones);
void ordenarPorGeneroPlaylist(stCancion canciones[], int numCanciones);
#endif // MENU_H_INCLUDED
