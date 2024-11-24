#ifndef CANCIONES_H_INCLUDED
#define CANCIONES_H_INCLUDED

typedef struct
{
    int idCancion;
    char titulo[30];
    char artista[20];
    int duracion;
    char album[20];
    int anio;
    char genero[20];
    char comentario[100];
    int eliminado;  // indica 1 o 0 si la canción fue eliminada
} stCancion;

typedef struct
{
    stCancion dato;
    struct nodoListaCancion * siguiente;
} nodoListaCancion;
typedef struct
{
    stCancion dato;
    struct nodoArbolCancion * izq;
    struct nodoArbolCancion * der;
} nodoArbolCancion;


void mostrarUnaCancion(stCancion A);
void mostrarLista(nodoListaCancion* lista);
void preorder(nodoArbolCancion* arbol);
void inorder(nodoArbolCancion * arbol);
void postorder(nodoArbolCancion* arbol);
void cargarUnaCancionArchivo(char ArchivoCancion[],stCancion C);
nodoListaCancion* iniclista();
nodoListaCancion* crearNodo(stCancion dato);
nodoListaCancion* AgregarAlPrincipio(nodoListaCancion* lista,nodoListaCancion* nuevo);
void AgregarAlFinal(nodoListaCancion** lista,nodoListaCancion* nuevo);
nodoListaCancion* AgregarEnOrdenPorNombreCancion(nodoListaCancion* lista,nodoListaCancion* nuevo);
nodoListaCancion* borrarNodoPorIdCancion(nodoListaCancion* lista,int IdCancionAborrar);

nodoArbolCancion * inicarbol();
nodoArbolCancion * crearnodoArbol(stCancion dato);
nodoArbolCancion * insertarNodoArbol (nodoArbolCancion * arbol, nodoArbolCancion * nuevo);
nodoArbolCancion * buscarCancion(nodoArbolCancion* arbol, int idcancionAbuscar);
nodoListaCancion* buscarEnlistaPorIdCancion(nodoListaCancion* lista,int IdCancion);
nodoArbolCancion* cargarArbolcancionConArchivo(nodoArbolCancion* arbol,char ArchivoCancion[]);
stCancion cargarUnaCancion();
int buscarCancionPorID(char ArchivoCancion[], int dato);
void MostrarArchivoCanciones(char ArchivoCancion[], stCancion C);
void modificarDatosCancion(char ArchivoCancion[], int dato) ;
void pasarArchiToArbolCanciones(char ArchivoCancion[],nodoArbolCancion** arbol);

#endif // CANCIONES_H_INCLUDED
