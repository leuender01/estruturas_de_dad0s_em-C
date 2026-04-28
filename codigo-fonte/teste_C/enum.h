#ifndef DATA
#define DATA
enum MES
{
    JANEIRO,
    FEVEREIRO,
    MARÇO,
    ABRIL,
    MAIO,
    JUNHO,
    JULHO,
    AGOSTO,
    SETEMBRO,
    OUTUBRO,
    NOVEMBRO,
    DEZEMBRO
};

enum SEMANA{
    DOMINGO,
    SEGUNDA,
    TERÇA,
    QUARTA,
    QUINTA,
    SEXTA,
    SABADO,
};


extern const char *SEMANA[];
extern const char *MES[];
void exibir(void);

#endif