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
int cargarPlaylist(char archivoPlaylist[], stPlaylist playlist[], int idUsuario);
int cargarCancionesPlaylist(char archivoCancion[], stCancion canciones[]);
void ordenarPorTituloP(stCancion canciones[], int numCanciones);
void ordenarPorGeneroP(stCancion canciones[], int numCanciones);
void mostrarCancionesPlaylist(stPlaylist playlist[], stCancion canciones[], int numPlaylist, int numCanciones);
void mostrarPlaylist(char archivoPlaylist[], char archivoCancion[], int idUsuario);
int seleccionarCriterioOrdenamiento();
int pasarArchivoPlaylistToADL(char Archivoplaylist[], stCelda ADL[], int validos, nodoArbolCancion *arbol);
int pasarArchivoCancionesToADL(char archivoCanciones[], stCelda ADL[], int validos);
int usuarioEscuchaCancion(int idUsuario, int idCancion);
void limpiarArregloDeListas(stCelda ADL[], int validos);
void persistirCancionesEscuchadas(stCelda ADL[], char ArchivoCancionesEscuchadas[], int validos);
void mostrarArchiEscuchadas(char ArchivoCancionesEscuchadas[]);
void mostrarADL(stCelda ADL[], int validos);
int alta(stCelda ADL[],int validos,stUsuario A,stCancion C);
int contarUsuariosActivos(char ArchivoUsuario[]);
int pasarArchivoToADL(char ArchivoUsuario[], stCelda ADL[]);
#endif // MENU_H_INCLUDED
