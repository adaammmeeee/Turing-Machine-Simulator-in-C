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

struct mt 
{
    BANDEAU etat_bande;
    char* etat_courant;
    char* etat_accepte;
    char* etat_init;
    int position_tete_lecture;
    char *nom;
    T* tab_transitions;
    int nb_transitions;
};
typedef struct mt * MT;



void init(BANDEAU b);
MT init_machine(char * nomfic, char* entree);
int ajout_elem(BANDEAU b, char elem);
void ignore_commentaire(FILE * f);
void libere_machine(MT ma_machine);
int test_transition(FILE * f, int * nombre_de_ligne, char * alphabet);
T* recup_transition(FILE * f, int nb_transitions);
void libere_bandeau(BANDEAU b);
int calcul_pas(MT ma_machine, CARREAU tete_lecture);
void affiche_bandeau(BANDEAU b);
void affiche_transition(T *tab_transition, int nb_transitions);


