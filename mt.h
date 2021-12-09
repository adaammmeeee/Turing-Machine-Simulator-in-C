struct carreau
{
    char value;
    struct carreau *prev;
    struct carreau *next;
};
typedef struct carreau* CARREAU;

struct bandeau
{
    CARREAU first;
    CARREAU last;
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