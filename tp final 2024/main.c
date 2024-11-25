#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "canciones.h"
#include "usuario.h"
#include "playlist.h"
#include "menu.h"
///ARREGLODELISTAS
int alta(stCelda ADL[],int validos,stUsuario A,stCancion C);
int pasarArchivoToADL(char ArchivoUsuario[],stCelda ADL[]);
void mostrarADL(stCelda ADL [],int validos);
void cargarArchivoDecanciones(char ArchivoCancion []);
void cargarArchivoDeUsuario( char ArchivoUsuario[]);
int pasarArchivoPlaylistToADL(char Archivoplaylist[], stCelda ADL[], int validos, nodoArbolCancion *arbol);
void mostrarADL(stCelda ADL [],int validos);
int pasarArchivoCancionesToADL(char archivoCanciones[], stCelda ADL[], int validos);
int usuarioEscuchaCancion(int idUsuario, int idCancion);
void limpiarArregloDeListas(stCelda ADL[], int validos);
void persistirCancionesEscuchadas(stCelda ADL[], char ArchivoCancionesEscuchadas[], int validos);
void mostrarArchiEscuchadas(char ArchivoCancionesEscuchadas[]);
int contarUsuariosActivos(char ArchivoUsuario[]);

int main()
{

    menu();
    return 0;
}

int alta(stCelda ADL[],int validos,stUsuario A,stCancion C)
{
    nodoListaCancion* aux=crearNodo(C);
    int pos=buscarPosUsuario(ADL,A.idUsuario,validos);
    if(pos==-1)
    {
        A=cargarUsuarioADL(A.idUsuario);
        validos=agregarUsuario(ADL,A,validos);
        pos=validos-1;
    }
    ADL[pos].listaCanciones=AgregarEnOrdenPorNombreCancion(ADL[pos].listaCanciones,aux);
    return validos;
}

int contarUsuariosActivos(char ArchivoUsuario[])
{
    FILE* archi = fopen("usuario.dat", "rb");
    int cantidad = 0;

    if(archi)
    {
        stUsuario usuario;
        while (fread(&usuario, sizeof(stUsuario), 1, archi) > 0)
        {
            if (usuario.eliminado == 0)
            {
                cantidad++;
            }
        }

        fclose(archi);
    }
    return cantidad;
}





int pasarArchivoToADL(char ArchivoUsuario[], stCelda ADL[])
{
    FILE* archi = fopen(ArchivoUsuario, "rb");
    if (!archi)
    {
        printf("ERROR: No se pudo abrir el archivo de usuarios.\n");
        return 0;
    }

    stUsuario A;
    int validos = 0;
    while (fread(&A, sizeof(stUsuario), 1, archi) > 0)
    {
        if (A.eliminado == 0)
        {
            ADL[validos].A = A;
            ADL[validos].listaCanciones = iniclista();
            validos++;
        }
    }

    fclose(archi);
    return validos;
}

int pasarArchivoPlaylistToADL(char Archivoplaylist[], stCelda ADL[], int validos, nodoArbolCancion *arbol)
{
    FILE * archi = fopen(Archivoplaylist, "rb");
    if (archi == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo de playlists\n");
        return validos;
    }
    stPlaylist playlist;
    while (fread(&playlist, sizeof(stPlaylist), 1, archi) > 0)
    {
        int pos = buscarPosUsuario(ADL, playlist.idUsuario, validos);
        if (pos != -1)
        {
            nodoArbolCancion * cancionBuscada = buscarCancion(arbol, playlist.idCancion);
            if (cancionBuscada != NULL)
            {
                nodoListaCancion * nuevoNodo = crearNodo(cancionBuscada->dato);
                ADL[pos].listaCanciones = AgregarEnOrdenPorNombreCancion(ADL[pos].listaCanciones, nuevoNodo);
            }
        }
    }

    fclose(archi);
    return validos;
}

int pasarArchivoCancionesToADL(char archivoCanciones[], stCelda ADL[], int validos)
{
    FILE *archi = fopen(archivoCanciones, "rb");
    if (!archi)
    {
        printf("Error al abrir el archivo %s \n", archivoCanciones);
        return validos;
    }

    stCancion cancion;
    while (fread(&cancion, sizeof(stCancion), 1, archi) > 0)
    {
        for (int i = 0; i < validos; i++)
        {

            if (usuarioEscuchaCancion(ADL[i].A.idUsuario, cancion.idCancion))
            {
                nodoListaCancion *nuevoNodo = crearNodo(cancion);
                ADL[i].listaCanciones = AgregarEnOrdenPorNombreCancion(ADL[i].listaCanciones, nuevoNodo);
            }
        }
    }

    fclose(archi);
    return validos;
}

int usuarioEscuchaCancion(int idUsuario, int idCancion)
{
    FILE *archi = fopen("playlist.dat", "rb");
    if (archi == NULL)
    {
        return 0;
    }

    stPlaylist playlist;
    while (fread(&playlist, sizeof(stPlaylist), 1, archi) > 0)
    {

        if (playlist.idUsuario == idUsuario && playlist.idCancion == idCancion)
        {
            fclose(archi);
            return 1;
        }
    }

    fclose(archi);
    return 0;
}

void limpiarArregloDeListas(stCelda ADL[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        nodoListaCancion * aux = ADL[i].listaCanciones;
        while(aux != NULL)
        {
            nodoListaCancion * aBorrar = aux;
            aux = aux->siguiente;
            free(aBorrar);
        }
        ADL[i].listaCanciones = iniclista();
    }
}

void persistirCancionesEscuchadas(stCelda ADL[], char ArchivoCancionesEscuchadas[], int validos)
{
    FILE *archi = fopen("escuchadas.dat", "ab");

    if (archi == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo %s\n", ArchivoCancionesEscuchadas);
        return;
    }

    for (int i = 0; i < validos; i++)
    {
        nodoListaCancion *aux = ADL[i].listaCanciones;

        while (aux != NULL)
        {
            stCancionesEscuchadas cancionesEscuchadas;
            cancionesEscuchadas.idUsuario = ADL[i].A.idUsuario;
            strcpy(cancionesEscuchadas.nombreUsuario, ADL[i].A.nombreUsuario);

            cancionesEscuchadas.idCancion = aux->dato.idCancion;
            strcpy(cancionesEscuchadas.nombreCancion, aux->dato.titulo);

            fwrite(&cancionesEscuchadas, sizeof(stCancionesEscuchadas), 1, archi);
            aux = aux->siguiente;
        }
    }

    fclose(archi);

}

void mostrarArchiEscuchadas(char ArchivoCancionesEscuchadas[])
{
    FILE *archi = fopen("escuchadas.dat", "rb");

    if (archi == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo %s\n", ArchivoCancionesEscuchadas);
        return;
    }

    stCancionesEscuchadas cancionesEscuchadas;
    printf("\nArchivo datos de canciones escuchadas:\n");
    printf("---------------------------------\n");

    while (fread(&cancionesEscuchadas, sizeof(stCancionesEscuchadas), 1, archi) > 0)
    {
        printf("ID Usuario: %d\n", cancionesEscuchadas.idUsuario);
        printf("Nombre Usuario: %s\n", cancionesEscuchadas.nombreUsuario);
        printf("ID Cancion: %d\n", cancionesEscuchadas.idCancion);
        printf("Nombre Cancion: %s\n", cancionesEscuchadas.nombreCancion);
        printf("-----------------------------\n");
    }

    fclose(archi);

}


void mostrarADL(stCelda ADL[], int validos)
{
    for (int i = 0; i < validos; i++)
    {
        printf("\nID Usuario: %i", ADL[i].A.idUsuario);
        printf("\nNombre de Usuario: %s", ADL[i].A.nombreUsuario);

        if (ADL[i].listaCanciones == NULL)
        {
            printf("\nSin canciones.\n");
        }
        else
        {
            printf("\nCanciones:\n");
            nodoListaCancion *aux = ADL[i].listaCanciones;
            while (aux != NULL)
            {
                printf("  - ID Cancion: %i, Titulo: %s\n", aux->dato.idCancion, aux->dato.titulo);
                aux = aux->siguiente;
            }
        }
        printf("------------------------------------\n");
    }
}

void cargarArchivoDecanciones(char ArchivoCancion [])
{
    FILE* archi=fopen("cancion.dat","ab");
    char control='s';
    stCancion C;
    if(archi)
    {
        while(control=='s')
        {
            C=cargarUnaCancion();
            fwrite(&C,sizeof(stCancion),1,archi);
            printf("cargar mas?(s)\n");
            fflush(stdin);
            scanf("%c",&control);
        }
    }
    fclose(archi);
}

void cargarArchivoDeUsuario( char ArchivoUsuario[])
{
    FILE* archi=fopen("usuario.dat","ab");
    char control='s';
    stUsuario A;
    if(archi)
    {
        while(control=='s')
        {
            A=cargarUnusuario();
            fwrite(&A,sizeof(stUsuario),1,archi);
            printf("cargar mas?(s)\n");
            fflush(stdin);
            scanf(" %c",&control);
        }
    }
    fclose(archi);
}



/*nodoA* encontrarMinimo(nodoA* A)
{
    while (A->izq != NULL)
    {
        A = A->izq;
    }
    return A;
}

nodoA* eliminarNodo(nodoA* A, int valorAEliminar)
{
    if (A == NULL)
        return NULL;

    /// Buscar el nodo que se desea eliminar en el sub�rbol izquierdo o derecho
    if (valorAEliminar < A->dato)
        A->izq = eliminarNodo(A->izq, valorAEliminar);

    else if (valorAEliminar > A->dato)
        A->der = eliminarNodo(A->der, valorAEliminar);

    else
    {
        /// el nodo a eliminar ha sido encontrado (NO FUE NI MENOR NI MAYOR)
        /// Caso 1: Nodo sin hijos o un solo hijo (los mas sencillos)
        if (A->izq == NULL)
        {
            nodoA* temp = A->der;
            free(A);
            return temp;
        }
        else if (A->der == NULL)
        {
            nodoA* temp = A->izq;
            free(A);
            return temp;
        }

        /// Caso 2: Nodo con dos hijos
        /// Encontrar el sucesor inmediato (nodo m�s a la izquierda en el sub�rbol derecho)
        nodoA* temp = encontrarMinimo(A->der);///funcion complementaria...

        /// Copiar el valor del sucesor inmediato al nodo actual
        A->dato = temp->dato;

        /// Eliminar el sucesor inmediato
        A->der = eliminarNodo(A->der, temp->dato);
    }

    return A;
}*/



