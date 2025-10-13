
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GAMES 50000
#define MAX_LINE 30000
#define MAX_FIELD 15000

typedef struct
{
    int id;
    char nome[500];
    char data[20];
    long donos;
    float preco;
    char idiomas[4000];
    int meta;
    double user;
    int conquistas;
    char pubs[2000];
    char devs[2000];
    char cats[3000];
    char gens[2000];
    char tags[8000];
} Jogo;

void meu_strcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i = i + 1;
    }
    dest[i] = '\0';
}

int meu_strlen(const char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len = len + 1;
    }
    return len;
}

void meu_strcat(char *dest, const char *src)
{
    int dest_len = meu_strlen(dest);
    int i = 0;
    while (src[i] != '\0')
    {
        dest[dest_len + i] = src[i];
        i = i + 1;
    }
    dest[dest_len + i] = '\0';
}

int eh_digito(char c)
{
    return (c >= '0' && c <= '9');
}

void trim(char *str)
{
    int inicio = 0;
    while (str[inicio] == ' ' || str[inicio] == '\t')
    {
        inicio = inicio + 1;
    }

    int fim = meu_strlen(str) - 1;
    while (fim >= inicio && (str[fim] == ' ' || str[fim] == '\t' || str[fim] == '\n' || str[fim] == '\r'))
    {
        fim = fim - 1;
    }

    int i = 0;
    while (inicio <= fim)
    {
        str[i] = str[inicio];
        i = i + 1;
        inicio = inicio + 1;
    }
    str[i] = '\0';
}

void remover_aspas_externas(char *str)
{
    trim(str);
    int len = meu_strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
    {
        int i = 0;
        while (i < len - 2)
        {
            str[i] = str[i + 1];
            i = i + 1;
        }
        str[len - 2] = '\0';
    }
}

int extrair_inteiro(const char *str)
{
    char num[100];
    int idx = 0;
    int i = 0;
    while (str[i] != '\0' && idx < 99)
    {
        if (eh_digito(str[i]))
        {
            num[idx] = str[i];
            idx = idx + 1;
        }
        i = i + 1;
    }
    num[idx] = '\0';
    return (idx > 0) ? atoi(num) : -1;
}

long extrair_longo(const char *str)
{
    char num[100];
    int idx = 0;
    int i = 0;
    while (str[i] != '\0' && idx < 99)
    {
        if (eh_digito(str[i]))
        {
            num[idx] = str[i];
            idx = idx + 1;
        }
        i = i + 1;
    }
    num[idx] = '\0';
    return (idx > 0) ? atol(num) : 0;
}

float extrair_preco(const char *str)
{
    float result = 0.0;
    if (strstr(str, "Free") == NULL && strstr(str, "free") == NULL)
    {
        char num[100];
        int idx = 0;
        int i = 0;
        while (str[i] != '\0' && idx < 99)
        {
            if (eh_digito(str[i]) || str[i] == '.')
            {
                num[idx] = str[i];
                idx = idx + 1;
            }
            i = i + 1;
        }
        num[idx] = '\0';
        if (idx > 0)
        {
            result = atof(num);
        }
        else
        {
            result = 0.0;
        }
    }
    else
    {
        result = 0.0;
    }
    return result;
}

double extrair_user(const char *str)
{
    double result = -1.0;
    if (!(str[0] == '\0' || strstr(str, "tbd") != NULL))
    {
        char num[100];
        int idx = 0;
        int i = 0;
        while (str[i] != '\0' && idx < 99)
        {
            if (eh_digito(str[i]) || str[i] == '.' || str[i] == ',')
            {
                num[idx] = (str[i] == ',') ? '.' : str[i];
                idx = idx + 1;
            }
            i = i + 1;
        }
        num[idx] = '\0';
        if (idx > 0)
        {
            result = atof(num);
        }
        else
        {
            result = -1.0;
        }
    }
    return result;
}

void formatar_data(char *dest, const char *src)
{
    char temp[100];
    char out[20];
    out[0] = '\0';
    meu_strcpy(temp, src);
    trim(temp);

    int apenas_numeros = 1;
    int i = 0;
    while (temp[i] != '\0')
    {
        if (eh_digito(temp[i]) == 0)
        {
            apenas_numeros = 0;
        }
        i = i + 1;
    }

    if (apenas_numeros && meu_strlen(temp) == 4)
    {
        snprintf(out, sizeof(out), "01/01/%s", temp);
    }
    else
    {
        char *meses[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        char *nums[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};

        int m = 0;
        while (m < 12)
        {
            if (strstr(temp, meses[m]) != NULL)
            {
                char dia[5] = "01";
                char ano[10] = "";

                char *pos = strstr(temp, meses[m]);
                char *p = pos - 1;

                while (p >= temp && (*p == ' ' || *p == ','))
                {
                    p = p - 1;
                }

                char *fim_dia = p;
                while (p >= temp && eh_digito(*p))
                {
                    p = p - 1;
                }
                char *ini_dia = p + 1;

                if (ini_dia <= fim_dia)
                {
                    int tam = fim_dia - ini_dia + 1;
                    if (tam == 1)
                    {
                        dia[0] = '0';
                        dia[1] = *ini_dia;
                        dia[2] = '\0';
                    }
                    else if (tam >= 2)
                    {
                        dia[0] = ini_dia[0];
                        dia[1] = ini_dia[1];
                        dia[2] = '\0';
                    }
                }

                p = pos + meu_strlen(meses[m]);
                while (*p != '\0' && (eh_digito(*p) == 0))
                {
                    p = p + 1;
                }

                int ai = 0;
                while (*p != '\0' && eh_digito(*p) && ai < 4)
                {
                    ano[ai] = *p;
                    ai = ai + 1;
                    p = p + 1;
                }
                ano[ai] = '\0';

                snprintf(out, sizeof(out), "%s/%s/%s", dia, nums[m], ano);
                break;
            }
            m = m + 1;
        }
    }

    if (out[0] == '\0')
    {
        meu_strcpy(dest, "01/01/0000");
    }
    else
    {
        meu_strcpy(dest, out);
    }
}

void processar_lista(char *dest, const char *src)
{
    dest[0] = '[';
    dest[1] = '\0';
    char temp[MAX_FIELD];
    meu_strcpy(temp, src);
    trim(temp);

    char *ini = strchr(temp, '[');
    char *fim = strrchr(temp, ']');
    char *start;
    int tam;

    if (ini == NULL || fim == NULL || fim <= ini)
    {
        start = temp;
        tam = meu_strlen(temp);
    }
    else
    {
        start = ini + 1;
        tam = fim - start;
    }

    int i = 0;
    int em_aspas = 0;
    int primeiro = 1;
    char item[MAX_FIELD];
    int item_i = 0;

    while (i <= tam)
    {
        char c = (i < tam) ? start[i] : ',';

        if (c == '\'' || c == '"')
        {
            em_aspas = 1 - em_aspas;
            i = i + 1;
        }
        else if (c == ',' && em_aspas == 0)
        {
            item[item_i] = '\0';
            trim(item);

            char clean[MAX_FIELD];
            int ci = 0;
            int k = 0;
            while (item[k] != '\0')
            {
                if (item[k] != '\'' && item[k] != '"')
                {
                    clean[ci++] = item[k];
                }
                k = k + 1;
            }
            clean[ci] = '\0';

            if (meu_strlen(clean) > 0)
            {
                if (primeiro == 0)
                {
                    meu_strcat(dest, ", ");
                }
                meu_strcat(dest, clean);
                primeiro = 0;
            }

            item_i = 0;
            i = i + 1;
        }
        else
        {
            item[item_i] = c;
            item_i = item_i + 1;
            i = i + 1;
        }
    }

    meu_strcat(dest, "]");
}

int separar_campos(char *linha, char campos[][MAX_FIELD])
{
    int campo = 0;
    int pos = 0;
    int i = 0;
    int em_aspas = 0;

    while (linha[i] != '\0' && campo < 20)
    {
        if (linha[i] == '"')
        {
            em_aspas = 1 - em_aspas;
            i = i + 1;
        }
        else if (linha[i] == ',' && em_aspas == 0)
        {
            campos[campo][pos] = '\0';
            campo = campo + 1;
            pos = 0;
            i = i + 1;
        }
        else
        {
            campos[campo][pos] = linha[i];
            pos = pos + 1;
            i = i + 1;
        }
    }
    campos[campo][pos] = '\0';

    return campo + 1;
}

void criar_jogo(Jogo *j, char campos[][MAX_FIELD], int n)
{
    j->id = (n > 0) ? extrair_inteiro(campos[0]) : -1;

    if (n > 1)
    {
        remover_aspas_externas(campos[1]);
        meu_strcpy(j->nome, campos[1]);
    }
    else
    {
        j->nome[0] = '\0';
    }

    if (n > 2)
    {
        remover_aspas_externas(campos[2]);
        formatar_data(j->data, campos[2]);
    }
    else
    {
        meu_strcpy(j->data, "01/01/0000");
    }

    j->donos = (n > 3) ? extrair_longo(campos[3]) : 0;
    j->preco = (n > 4) ? extrair_preco(campos[4]) : 0.0;

    if (n > 5)
    {
        remover_aspas_externas(campos[5]);
        processar_lista(j->idiomas, campos[5]);
    }
    else
    {
        meu_strcpy(j->idiomas, "[]");
    }

    j->meta = (n > 6) ? extrair_inteiro(campos[6]) : -1;
    j->user = (n > 7) ? extrair_user(campos[7]) : -1.0;
    j->conquistas = (n > 8) ? extrair_inteiro(campos[8]) : 0;

    if (n > 9)
    {
        remover_aspas_externas(campos[9]);
        processar_lista(j->pubs, campos[9]);
    }
    else
    {
        meu_strcpy(j->pubs, "[]");
    }

    if (n > 10)
    {
        remover_aspas_externas(campos[10]);
        processar_lista(j->devs, campos[10]);
    }
    else
    {
        meu_strcpy(j->devs, "[]");
    }

    if (n > 11)
    {
        remover_aspas_externas(campos[11]);
        processar_lista(j->cats, campos[11]);
    }
    else
    {
        meu_strcpy(j->cats, "[]");
    }

    if (n > 12)
    {
        remover_aspas_externas(campos[12]);
        processar_lista(j->gens, campos[12]);
    }
    else
    {
        meu_strcpy(j->gens, "[]");
    }

    if (n > 13)
    {
        remover_aspas_externas(campos[13]);
        processar_lista(j->tags, campos[13]);
    }
    else
    {
        meu_strcpy(j->tags, "[]");
    }
}

int ler_arquivo(const char *caminho, Jogo *jogos)
{
    int result = 0;
    FILE *f = fopen(caminho, "r");
    if (f == NULL)
    {
        result = 0;
        goto end_ler;
    }

    char linha[MAX_LINE];
    int total = 0;

    if (fgets(linha, MAX_LINE, f) != NULL)
    {
        while (fgets(linha, MAX_LINE, f) != NULL && total < MAX_GAMES)
        {
            int len = meu_strlen(linha);
            if (len > 0 && linha[len - 1] == '\n')
            {
                linha[len - 1] = '\0';
            }
            if (len > 1 && linha[len - 2] == '\r')
            {
                linha[len - 2] = '\0';
            }

            char campos[20][MAX_FIELD];
            int ncampos = separar_campos(linha, campos);

            if (ncampos > 0)
            {
                criar_jogo(&jogos[total], campos, ncampos);
                if (jogos[total].id != -1)
                {
                    total = total + 1;
                }
            }
        }
    }

    fclose(f);
    result = total;

end_ler:
    return result;
}

void imprimir(Jogo *j)
{
    printf("=> %d ## %s ## %s ## %ld ## %.2f ## %s ## %d ## %.1f ## %d ## %s ## %s ## %s ## %s ## %s ##\n",
           j->id, j->nome, j->data, j->donos, j->preco, j->idiomas,
           j->meta, j->user, j->conquistas, j->pubs, j->devs,
           j->cats, j->gens, j->tags);
}

int main()
{
    int exit_code = 0;
    Jogo *jogos = (Jogo *)malloc(MAX_GAMES * sizeof(Jogo));
    if (jogos == NULL)
    {
        exit_code = 1;
        goto end_main;
    }

    int total = ler_arquivo("/tmp/games.csv", jogos);

    char entrada[100];
    int finished = 0;
    while (!finished && fgets(entrada, 100, stdin) != NULL)
    {
        trim(entrada);

        if (strcmp(entrada, "FIM") == 0)
        {
            finished = 1;
            break;
        }

        int id = atoi(entrada);
        int i = 0;
        while (i < total)
        {
            if (jogos[i].id == id)
            {
                imprimir(&jogos[i]);
                i = total;
            }
            i = i + 1;
        }
    }

    free(jogos);

end_main:
    return exit_code;
}