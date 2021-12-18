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

typedef struct transition
{
    char* etat_lu;
    char caractere_lu;
    char* nouvel_etat;
    char nouveau_caractere;
    char direction;
} T;

struct elem_transition
{
    T ma_transition;
    struct elem_transition *prec;
    struct elem_transition *suiv;
};
typedef struct elem_transition* TRANSI;

struct liste_transition
{
    TRANSI premier;
    TRANSI dernier;
};
typedef struct liste_transition * LISTE_TRANSI;


struct mt 
{
    BANDEAU etat_bande;
    char* etat_courant;
    char* etat_accepte;
    char* etat_init;
    int position_tete_lecture;
    char *nom;
    LISTE_TRANSI liste_transitions;
    int nb_transitions;
};
typedef struct mt * MT;



void init(BANDEAU b);
MT init_machine(char * nomfic, char* entree);
int ajout_elem(BANDEAU b, char elem);
void libere_machine(MT ma_machine);
int test_transition(FILE * f, int * nombre_de_ligne, char * alphabet);
LISTE_TRANSI recup_transition(FILE *F);
void libere_bandeau(BANDEAU b);
int calcul_pas(MT ma_machine, CARREAU tete_lecture);
void affiche_bandeau(BANDEAU b);
void affiche_transition(MT ma_machine);
int ajout_transition(LISTE_TRANSI liste_transition, T ma_transition);
void init_liste_transi(LISTE_TRANSI liste_transition);
int bi_inf_vers_semi_inf(char * nomfic);
void libere_liste_transi(LISTE_TRANSI liste_transition);


