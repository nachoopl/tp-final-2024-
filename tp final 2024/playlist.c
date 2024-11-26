#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "playlist.h"
int ultimoIdPlaylist(char Archivoplaylist[])
{
    FILE* archi = fopen("playlist.dat", "rb");
    stPlaylist playlist;
    int ultimoId = -1;

    if (archi)
    {
        while (fread(&playlist, sizeof(stPlaylist), 1, archi) > 0)
        {
            if (playlist.idPlaylist > ultimoId)
            {
                ultimoId = playlist.idPlaylist;
            }
        }
        fclose(archi);
    }

    return ultimoId + 1;
}


void cargarPlaylistArchivo(char Archivoplaylist[])
{
    FILE* archi = fopen("playlist.dat", "ab");
    stPlaylist nuevaPlaylist;
    char control = 's';

    if (archi)
    {
        int idPlaylist = ultimoIdPlaylist(Archivoplaylist);

        while (control == 's')
        {
            nuevaPlaylist.idPlaylist = idPlaylist;
            printf("Ingrese el id del Usuario: ");
            fflush(stdin);
            scanf("%i", &nuevaPlaylist.idUsuario);

            int buscar = buscarUsuarioPorID("usuario.dat", nuevaPlaylist.idUsuario);
            if (buscar == 1)
            {
                printf("Ingrese el id de la Cancion: ");
                fflush(stdin);
                scanf("%i", &nuevaPlaylist.idCancion);

                fwrite(&nuevaPlaylist, sizeof(stPlaylist), 1, archi);
                idPlaylist++;
            }
            else
            {
                printf("\nUsuario inexistente");
            }

            printf("\n¿Cargar otro? (s/n): ");
            fflush(stdin);
            scanf(" %c", &control);
        }
        fclose(archi);
    }
}
void mostrarArchivoPlaylist(char Archivoplaylist[],stPlaylist nuevaPlaylist)
{
    FILE* archi=fopen("playlist.dat","rb");

    {
        if(archi)
        {
            while(fread(&nuevaPlaylist,sizeof(stPlaylist),1,archi)>0)
            {



                printf("IdPlaylits: %i\n",nuevaPlaylist.idPlaylist);
                printf("IdUsuario: %i\n",nuevaPlaylist.idUsuario);
                printf("IdCancion: %i\n",nuevaPlaylist.idCancion);
                printf("-----------------------------\n");
            }
        }
        fclose(archi);
    }
}




