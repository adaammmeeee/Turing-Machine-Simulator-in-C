struct carreau
{
    char valeur;
    struct carreau *prec;
    struct carreau *suiv;
};
typedef struct carreau* CARREAU;

struct bandeau
{
    CARREAU premier;
    CARREAU dernier;
};
typedef struct bandeau * BANDEAU;

typedef struct mt
{
    BANDEAU etat_bande;
    char etat_courant;
    char etat_accepte;
    char etat_init;
    int position_tete_lecture;
    char *nom;
} MT;

void init(BANDEAU b);
int init_ruban(char * nomfic, char* entree);
int ajout_elem(BANDEAU b, char elem);