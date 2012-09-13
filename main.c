#include "main.h"

int main (int argc, char *argv[])
{
    //      DECLARATION DES VARIABLES
    int nb_mus = 0, cont = 1, volume = 128, t = SDL_GetTicks(), duree = 0, balance = 128 ;
    int t0 = 0, t1 = SDL_GetTicks(), app_vol = 0, app_bal = 0, larg_vol = 0, haut_vol = 0 ;
    int larg_bal = 0, haut_bal = 0/*, couleur = 0*/ ;
    char *titre = NULL, *auteur = NULL, *album = NULL ;
    SDL_Surface *ecran = NULL, *barre_vol = NULL, *barre_bal = NULL ;
    SDL_Rect pos_vol, pos_bal ;
    SDL_Event event ;
    FSOUND_STREAM *musique = NULL ;


    //      INITIALISATIONS
    srand(time(NULL)) ;
    SDL_Init(SDL_INIT_VIDEO) ;
    SDL_ShowCursor(SDL_ENABLE) ;
    SDL_EnableKeyRepeat(50, 50) ;
    FSOUND_Init(44100, 32, 0) ;
    //FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(1), 1) ;

    ecran = SDL_SetVideoMode(450, 150, 32, SDL_HWSURFACE | SDL_DOUBLEBUF) ;
    LoadMusic(musique, 8, &nb_mus, titre, auteur, album) ; //On lance la lecture d'une musique.
    t0 = SDL_GetTicks() ;
    while (cont)
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, COUL_FOND)) ; //On remplis l'écran avec la couleur apropriée.
        duree = FSOUND_Stream_GetLengthMs(musique) ; //On stocke la durée de la musique en ms.
        t = FSOUND_Stream_GetTime(musique) ; //On regarde ou on en est...
        t1 = SDL_GetTicks() ;
        /*if (!(t1 - t0 > 30))
        {
            SDL_Delay(30-(t1-t0)) ;
            t0 = t1 ;
        }*/
        SDL_Delay(25) ;
        afficher_stereo(ecran, 8, volume) ;
        /*printf("Position : %d", FSOUND_Stream_GetTime(musique)) ;
        printf("\tDuree : %d\n", duree) ;*/
        FSOUND_SetVolume(8, volume) ; //On règle le volume.
        FSOUND_SetPan(8, balance) ; //On règle la balance.
        afficher_volume(ecran, volume, barre_vol, &pos_vol, &larg_vol, &haut_vol) ;
        afficher_balance(ecran, balance, barre_bal, &pos_bal, &larg_bal, &haut_bal) ;
        SDL_Flip(ecran) ;
        SDL_PollEvent(&event) ;
        switch (event.type)
        {
            case SDL_KEYDOWN : switch (event.key.keysym.sym)
                               {
                                   case SDLK_SPACE : pause(8) ; //Fonction qui met en pause.
                                                     break ;
                                   case SDLK_p : pause(8) ; //Fonction qui met en pause.
                                                 break ;
                                   case SDLK_s : //Shuffle ;
                                                 break ;
                                   case SDLK_m : FSOUND_SetMute(8, (FSOUND_GetMute(8)+1)%2) ; //Tiens un truc bizarre ici : la touche 'm'
                                                 printf("m") ; //n'est pas prise en compte mais si je met SDLK_TAB à la place
                                                 break ; //j'arrive à faire "mute"...
                                   case SDLK_UP : volume += 5*256/100 ;
                                                  break ;
                                   case SDLK_DOWN : volume -= 5*256/100 ;
                                                    break ;
                                   case SDLK_LEFT : balance -= 4 ;
                                                    break ;
                                   case SDLK_RIGHT : balance += 4 ;
                                                     break ;
                                   case SDLK_PAGEUP : (--nb_mus%11) ;
                                                      LoadMusic(musique, 8, &nb_mus, titre, auteur, album) ; //Fonction pour aller à la musique précédente.
                                                      t0 = SDL_GetTicks() ;
                                                      break ;
                                   case SDLK_PAGEDOWN : (++nb_mus%11) ;
                                                        LoadMusic(musique, 8, &nb_mus, titre, auteur, album) ; //Fonction pour aller à la musique précédente.
                                                        t0 = SDL_GetTicks() ;
                                                        break ;
                                   case SDLK_ESCAPE : cont = 0 ;
                                                      break ;
                                   default : break ;
                               }
                               SDL_Delay(150) ;
                               break ;
            case SDL_MOUSEBUTTONDOWN : switch (event.button.button)
                                       {
                                           case SDL_BUTTON_WHEELUP : volume += 5*256/100 ;
                                                                     break ;
                                           case SDL_BUTTON_WHEELDOWN : volume -= 5*256/100 ;
                                                                       break ;
                                           case SDL_BUTTON_LEFT : if(pos_vol.x<=event.button.x && event.button.x<=pos_vol.x+larg_vol && pos_vol.y-3<=event.button.y && event.button.y<=pos_vol.y-3+haut_vol)
                                                                  {
                                                                      app_vol = 1 ;
                                                                      volume = 256*(float)(event.button.x - pos_vol.x - 2)/(float)larg_vol ;
                                                                  }
                                                                  if (pos_bal.x<=event.button.x && event.button.x<=pos_bal.x+larg_bal && pos_bal.y-3<=event.button.y && event.button.y<=pos_bal.y-3+haut_bal)
                                                                  {
                                                                      app_bal = 1 ;
                                                                      balance = 256*(float)(event.button.x - pos_bal.x)/(float)larg_bal ;
                                                                  }
                                                                  break ;
                                       }
                                       break ;
            case SDL_MOUSEMOTION : if (app_vol)
                                   {
                                       volume = 256*(float)(event.button.x - pos_vol.x - 2)/(float)larg_vol ;
                                   }
                                   if (app_bal)
                                   {
                                       balance = 256*(float)(event.button.x - pos_bal.x)/(float)larg_bal ;
                                   }
                                   break ;
            case SDL_MOUSEBUTTONUP : app_bal = 0 ;
                                     app_vol = 0 ;
                                     switch (event.button.button)
                                     {
                                         default : break ;
                                     }
                                     break ;
            case SDL_QUIT : cont = 0 ;
                            break ;
        }
        if (volume < 0) {volume = 0 ;}
        if (volume > 256) {volume = 256 ;}
        if (balance < 0) {balance = 0 ;}
        if (balance > 256) {balance = 256 ;}
    }

    //      LIBERATIONS
    free(album) ;
    free(auteur) ;
    free(titre) ;
    FSOUND_Stream_Close(musique) ;
    FSOUND_Close() ;
    SDL_Quit() ;
    return EXIT_SUCCESS ;
}
