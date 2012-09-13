#include "main.h"

/*Fonction d'affichage :*/

//Fonction qui affiche une barre pour le volume :
void afficher_volume (SDL_Surface *ecran, int volume, SDL_Surface *barre_vol, SDL_Rect *pos_vol, int *larg, int *haut)
{
    SDL_Surface *bouton = NULL ;
    SDL_Rect pos_bout ;

    //On crée la barre du volume :
    barre_vol = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 3, 32, 0, 0, 0, 0) ;
    SDL_FillRect(barre_vol, NULL, SDL_MapRGB(barre_vol->format, COUL_BOUT)) ;
    pos_vol->x = ecran->w - barre_vol->w - 10 ;
    pos_vol->y = ecran->h - barre_vol->h - 10 ;
    *larg = barre_vol->w ;


    //Puis le bouton qui indique le niveau du volume :
    bouton = SDL_CreateRGBSurface(SDL_HWSURFACE, 5, 9, 32, 0, 0, 0, 0) ;
    SDL_FillRect(bouton, NULL, SDL_MapRGB(bouton->format, 16, 158, 235)) ;
    pos_bout.x = pos_vol->x + volume*barre_vol->w/255 ;
    pos_bout.y = pos_vol->y - bouton->h/2 + barre_vol->h/2 ;
    *haut = bouton->h ;

    //On blitte tout ça :
    SDL_BlitSurface(barre_vol, NULL, ecran, pos_vol) ;
    SDL_BlitSurface(bouton, NULL, ecran, &pos_bout) ;

    SDL_FreeSurface(bouton) ;
    SDL_FreeSurface(barre_vol) ;
}

//Fonction qui affiche une barre pour la balance :
void afficher_balance (SDL_Surface *ecran, int balance, SDL_Surface *barre_bal, SDL_Rect *pos_bal, int *larg, int *haut)
{
    SDL_Surface *bouton = NULL, *milieu= NULL ;
    SDL_Rect pos_bout, pos_mil ;

    //On crée la barre de la balance :
    barre_bal = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 3, 32, 0, 0, 0, 0) ;
    SDL_FillRect(barre_bal, NULL, SDL_MapRGB(barre_bal->format, COUL_BOUT)) ;
    pos_bal->x = 10 ;
    pos_bal->y = ecran->h - barre_bal->h - 10 ;
    *larg = barre_bal->w ;

    //Puis le bouton qui indique le niveau de la balance :
    bouton = SDL_CreateRGBSurface(SDL_HWSURFACE, 5, 9, 32, 0, 0, 0, 0) ;
    SDL_FillRect(bouton, NULL, SDL_MapRGB(bouton->format, 16, 158, 235)) ;
    pos_bout.x = pos_bal->x + balance*barre_bal->w/255 - bouton->w/2 ;
    pos_bout.y = pos_bal->y - bouton->h/2 + barre_bal->h/2 ;
    *haut = bouton->h ;

    //On crée une petite barre pour indique le milieu :
    milieu = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 11, 32, 0, 0, 0, 0) ;
    SDL_FillRect(milieu, NULL, SDL_MapRGB(milieu->format, NOIR)) ;
    pos_mil.x = pos_bal->x + barre_bal->w/2 ;
    pos_mil.y = pos_bal->y - milieu->h/2 + barre_bal->h/2 ;

    SDL_BlitSurface(barre_bal, NULL, ecran, pos_bal) ;
    SDL_BlitSurface(bouton, NULL, ecran, &pos_bout) ;
    SDL_BlitSurface(milieu, NULL, ecran, &pos_mil) ;

    SDL_FreeSurface(bouton) ;
    SDL_FreeSurface(barre_bal) ;
    SDL_FreeSurface(milieu) ;
}

//Fonction qui affiche le niveau des haut-parleurs gauche et droit :
void afficher_stereo (SDL_Surface *ecran, int channel, int volume)
{
    float g = 0, d = 0 ;
    SDL_Surface *gauche = NULL, *droite = NULL ;
    SDL_Rect pos_g, pos_d ;

    //On récupére le volume sonore à gauche et à droite :
    FSOUND_GetCurrentLevels(channel, &g, &d) ;
    if (volume!=0)
    {
        g /= volume ;
        d /= volume ;
    }
    gauche = SDL_CreateRGBSurface(SDL_HWSURFACE, 20000*g, 5, 32, 0, 0, 0, 0) ;
    droite = SDL_CreateRGBSurface(SDL_HWSURFACE, 20000*d, 5, 32, 0, 0, 0, 0) ;
    SDL_FillRect(gauche, NULL, SDL_MapRGB(gauche->format, 0, 0, 0)) ;
    SDL_FillRect(droite, NULL, SDL_MapRGB(droite->format, 0, 0, 0)) ;
    pos_g.x = 10 ;
    pos_g.y = 10 ;
    pos_d.x = ecran->w - pos_g.x - droite->w ;
    pos_d.y = pos_g.y ;

    //On blitte le tout...
    SDL_BlitSurface(gauche, NULL, ecran, &pos_g) ;
    SDL_BlitSurface(droite, NULL, ecran, &pos_d) ;

    SDL_FreeSurface(gauche) ;
    SDL_FreeSurface(droite) ;
}
