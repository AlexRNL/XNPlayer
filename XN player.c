#include "main.h"

/*Fonction du lecteur audio :*/

//Fonction qui met en pause un morceau de musique :
void pause (int channel)
{
    FSOUND_SetPaused(channel, (FSOUND_GetPaused(channel)+1)%2) ;
}

//Fonction qui charge et lis une musique :
void LoadMusic (FSOUND_STREAM *musique, int channel, int *nb_mus, char *titre, char *auteur, char *album)
{
    int nb_tag = 0, lg = 0, i = 0, type = 0 ;
    void *valeur = NULL ;
    char nom_fichier[100] = "", *nom_fenetre = NULL, *tag, nom[100] = "" ;

    FSOUND_Stream_Stop(musique) ;
    FSOUND_Stream_Close(musique) ; //On lib�re la musique.

    if (*nb_mus <= -1) *nb_mus = 10 ;
    if (*nb_mus >= 11) *nb_mus = 0 ;

    sprintf(nom_fichier, "musiques/%d.mp3", *nb_mus) ; //On �crit le nom du fichier � charger...
    musique = FSOUND_Stream_Open(nom_fichier, 0, 0, 0) ; //On lis la nouvelle.
    if (musique == NULL) //V�rification.
    {
        fprintf(stderr, "Impossible de lire : %s.", nom_fichier) ;
        exit(EXIT_FAILURE) ;
    }
    FSOUND_Stream_Play(channel, musique) ;
    FSOUND_Stream_GetNumTagFields(musique, &nb_tag) ; //Avec �a, on obtient le nombre de tags.
    printf("Tags (%d) :\n", nb_tag) ;
    for (i=0 ; i<nb_tag ; i++)
    {
        FSOUND_Stream_GetTagField(musique, i, &type, &tag, &valeur, &lg) ;
        strcpy(nom, (char*) valeur) ;
        printf("%s : %s (%d)\n", tag, nom, lg) ;
        if (!strcmp(tag, "TITLE"))
        {
            free(titre) ;
            titre = malloc(lg * sizeof(char)) ;
            sprintf(titre, "%s", nom) ;
        }
        if (!strcmp(tag, "ARTIST"))
        {
            free(auteur) ;
            auteur = malloc(lg * sizeof(char)) ;
            sprintf(auteur, "%s", nom) ;
        }
        if (!strcmp(tag, "ALBUM"))
        {
            free(album) ;
            album = malloc(lg * sizeof(char)) ;
            sprintf(album, "%s", nom) ;
        }
    }
    free(tag) ;
    free(valeur) ;
    nom_fenetre = malloc((strlen(titre)+strlen(auteur)+strlen(album)+strlen(" -  () :: XN Player")+1) * sizeof(char)) ;
    sprintf(nom_fenetre, "%s - %s (%s) :: XN Player", auteur, titre, album) ;
    SDL_WM_SetCaption(nom_fenetre, NULL) ; //On change l'ent�te de la fen�tre.

    free(nom_fenetre) ;
}
