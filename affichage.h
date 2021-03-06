#ifndef AFFICHAGEH
#define AFFICHAGEH

#define COUL_FOND I, I, I
#define COUL_BOUT J, J, J
#define NOIR 0, 0, 0
#define I 218
#define J 60

//Prototype des fonctions :
void afficher_volume (SDL_Surface *ecran, int volume, SDL_Surface *barre_vol, SDL_Rect *pos_vol, int *larg, int *haut) ;
void afficher_balance (SDL_Surface *ecran, int balance, SDL_Surface *barre_bal, SDL_Rect *pos_bal, int *larg, int *haut) ;
void afficher_stereo (SDL_Surface *ecran, int channel, int volume) ;

#endif
