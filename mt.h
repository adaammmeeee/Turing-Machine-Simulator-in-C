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
    char* etat_courant;
    char* etat_accepte;
    char* etat_init;
    int position_tete_lecture;
    char *nom;
} MT;

typedef struct transition
{
    char etat_lu;
    int caractere_lu;
    char nouvelle_etat;
    int nouveau_caractere;
    char direction;
} T;

void init(BANDEAU b);
MT init_ruban(char * nomfic, char* entree);
int ajout_elem(BANDEAU b, char elem);
void ignore_commentaire(FILE * f);
void libere_machine(MT ma_machine);
int recupere_transition(FILE * f, int * nombre_de_ligne);