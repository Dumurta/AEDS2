

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MATRICULA "884985"

typedef struct
{
    int id;
    char name[256];
    char releaseDate[16];
    int estimatedOwners;
    float price;
    char supportedLanguages[1024];
    int metacriticScore;
    float userScore;
    int achievements;
    char publishers[1024];
    char developers[1024];
    char categories[1024];
    char genres[1024];
    char tags[2048];
} Game;

static int str_len(const char *s)
{
    int n = 0;
    if (s == NULL)
        return 0;
    while (s[n] != '\0')
    {
        n++;
    }
    return n;
}

static int str_cmp(const char *a, const char *b)
{
    unsigned char ca, cb;
    if (a == NULL && b == NULL)
        return 0;
    if (a == NULL)
        return -1;
    if (b == NULL)
        return 1;
    while (1)
    {
        ca = (unsigned char)*a;
        cb = (unsigned char)*b;
        if (ca != cb)
            return (int)ca - (int)cb;
        if (ca == '\0')
            return 0;
        a++;
        b++;
    }
}
static void str_copy(char *dst, const char *src)
{
    int i = 0;
    if (dst != NULL && src != NULL)
    {
        while (src[i] != '\0')
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
}

static void str_copy_n(char *dst, const char *src, int n)
{
    int i = 0;
    if (dst != NULL && src != NULL && n > 0)
    {
        while (i < n - 1 && src[i] != '\0')
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
}

static void str_trim_copy(char *out, const char *src, int outcap)
{
    int i = 0, j = 0, start = 0, end = 0, n = 0, k = 0;
    if (outcap > 0)
    {
        out[0] = '\0';
        if (src != NULL)
        {
            n = (int)str_len(src);
            start = 0;
            while (start < n && src[start] == ' ')
                start++;
            end = n - 1;
            while (end >= start && src[end] == ' ')
                end--;
            if (end >= start)
            {
                i = start;
                j = 0;
                while (i <= end && j < outcap - 1)
                {
                    out[j++] = src[i++];
                }
                out[j] = '\0';

                k = 0;
                j = 0;
                while (out[k] != '\0')
                {
                    if (out[k] == ' ' && out[k + 1] == ' ')
                    {
                        k++;
                    }
                    else
                    {
                        out[j++] = out[k++];
                    }
                }
                out[j] = '\0';
            }
        }
    }
}

static void strip_newline(char *s)
{
    int n = 0, i = 0;
    if (s != NULL)
    {
        n = (int)str_len(s);
        if (n > 0)
        {
            i = n - 1;
            while (i >= 0 && (s[i] == '\n' || s[i] == '\r'))
            {
                s[i] = '\0';
                i--;
            }
        }
    }
}

static int parse_int_digits(const char *s, int defv)
{
    int i = 0, n = 0, any = 0, val = 0, r = defv, ch = 0;
    if (s != NULL)
    {
        n = (int)str_len(s);
        i = 0;
        while (i < n)
        {
            ch = (int)(unsigned char)s[i];
            if (ch >= '0' && ch <= '9')
            {
                val = val * 10 + (ch - '0');
                any = 1;
            }
            i++;
        }
        if (any == 1)
            r = val;
    }
    return r;
}

static float parse_float_basic(const char *s, float defv)
{
    float r = defv;
    int i = 0, n = 0, sign = 1, any = 0;
    long whole = 0;
    float frac = 0.0f, base = 0.1f;

    if (s != NULL)
    {
        n = (int)str_len(s);
        if (n > 0 && s[0] == '-')
        {
            sign = -1;
            i = 1;
        }
        else
        {
            i = 0;
        }

        while (i < n && s[i] >= '0' && s[i] <= '9')
        {
            whole = whole * 10 + (s[i] - '0');
            i++;
            any = 1;
        }
        if (i < n && (s[i] == '.' || s[i] == ','))
        {
            i++;
            while (i < n && s[i] >= '0' && s[i] <= '9')
            {
                frac += (s[i] - '0') * base;
                base *= 0.1f;
                i++;
                any = 1;
            }
        }
        if (any == 1 && i == n)
        {
            r = (float)sign * (whole + frac);
        }
    }
    return r;
}

static int str_ieq(const char *a, const char *b)
{
    int r = 0, i = 0, na = 0, nb = 0, same = 1;
    if (a != NULL && b != NULL)
    {
        na = (int)str_len(a);
        nb = (int)str_len(b);
        if (na == nb)
        {
            i = 0;
            while (i < na)
            {
                char x = a[i], y = b[i];
                if (x >= 'A' && x <= 'Z')
                    x = (char)(x + 32);
                if (y >= 'A' && y <= 'Z')
                    y = (char)(y + 32);
                if (x != y)
                {
                    same = 0;
                    i = na;
                }
                else
                {
                    i++;
                }
            }
            r = same;
        }
        else
        {
            r = 0;
        }
    }
    return r;
}

static void put_char(char c)
{

    fputc((int)c, stdout);
}

static float normalize_price(const char *s)
{
    float r = 0.0f;
    char tmp[128];
    tmp[0] = '\0';
    str_trim_copy(tmp, s, (int)sizeof(tmp));
    if (tmp[0] != '\0')
    {
        if (str_cmp(tmp, "Free to Play") == 0)
            r = 0.0f;
        else
            r = parse_float_basic(tmp, 0.0f);
    }
    else
    {
        r = 0.0f;
    }
    return r;
}

static float normalize_user_score(const char *s)
{
    float r = -1.0f;
    char tmp[64];
    tmp[0] = '\0';
    str_trim_copy(tmp, s, (int)sizeof(tmp));
    if (tmp[0] != '\0')
    {
        if (str_ieq(tmp, "tbd") == 1)
            r = -1.0f;
        else
            r = parse_float_basic(tmp, -1.0f);
    }
    else
    {
        r = -1.0f;
    }
    return r;
}

static void buf_append_char(char *dst, int cap, int *len, char c)
{
    if (*len < cap - 1)
    {
        dst[*len] = c;
        (*len)++;
        dst[*len] = '\0';
    }
}

static void normalize_list_to_csv(const char *s, char *out, int cap, int remove_single_quotes)
{
    int start = 0, end = 0, n = 0, i = 0, token_start = 0, inq = 0, len = 0, wrote = 0;

    out[0] = '\0';
    if (s != NULL)
    {
        n = (int)str_len(s);
        if (n >= 2 && s[0] == '[' && s[n - 1] == ']')
        {
            start = 1;
            end = n - 2;
        }
        else
        {
            start = 0;
            end = n - 1;
        }

        token_start = start;
        i = start;
        inq = 0;
        len = 0;
        wrote = 0;
        while (i <= end)
        {
            char c = s[i];
            if (c == '\'')
            {
                if (inq == 1)
                    inq = 0;
                else
                    inq = 1;
            }
            if (c == ',' && inq == 0)
            {
                int a = token_start, b = i - 1;
                char tok[4096];
                int j = 0, k = 0;

                while (a <= b && s[a] == ' ')
                    a++;
                while (b >= a && s[b] == ' ')
                    b--;

                j = a;
                k = 0;
                while (j <= b && k < (int)sizeof(tok) - 1)
                {
                    char t = s[j];
                    if (t == '\'')
                    {
                        if (remove_single_quotes == 0)
                        {
                            tok[k] = t;
                            k++;
                        }
                    }
                    else
                    {
                        tok[k] = t;
                        k++;
                    }
                    j++;
                }
                tok[k] = '\0';

                if (wrote == 1)
                {
                    buf_append_char(out, cap, &len, ',');
                    buf_append_char(out, cap, &len, ' ');
                }
                j = 0;
                while (tok[j] != '\0')
                {
                    buf_append_char(out, cap, &len, tok[j]);
                    j++;
                }
                wrote = 1;
                token_start = i + 1;
            }
            i++;
        }
        {
            int a = token_start, b = end;
            char tok[4096];
            int j = 0, k = 0;
            while (a <= b && s[a] == ' ')
                a++;
            while (b >= a && s[b] == ' ')
                b--;

            j = a;
            k = 0;
            while (j <= b && k < (int)sizeof(tok) - 1)
            {
                char t = s[j];
                if (t == '\'')
                {
                    if (remove_single_quotes == 0)
                    {
                        tok[k] = t;
                        k++;
                    }
                }
                else
                {
                    tok[k] = t;
                    k++;
                }
                j++;
            }
            tok[k] = '\0';

            if (wrote == 1)
            {
                buf_append_char(out, cap, &len, ',');
                buf_append_char(out, cap, &len, ' ');
            }
            j = 0;
            while (tok[j] != '\0')
            {
                buf_append_char(out, cap, &len, tok[j]);
                j++;
            }
        }
    }
}

static void normalize_tags(const char *s, char *out, int cap) { normalize_list_to_csv(s, out, cap, 0); }
static void normalize_bracketed_list(const char *s, char *out, int cap) { normalize_list_to_csv(s, out, cap, 1); }
static void normalize_csv_plain(const char *s, char *out, int cap) { normalize_list_to_csv(s, out, cap, 1); }

/* ================================================================
   DATAS
   ================================================================ */

static int month3_to_int(const char *s)
{
    int r = 0;
    if (s != NULL && str_len(s) >= 3)
    {
        char m[4];
        m[0] = s[0];
        m[1] = s[1];
        m[2] = s[2];
        m[3] = '\0';
        if (str_cmp(m, "Jan") == 0)
            r = 1;
        else if (str_cmp(m, "Feb") == 0)
            r = 2;
        else if (str_cmp(m, "Mar") == 0)
            r = 3;
        else if (str_cmp(m, "Apr") == 0)
            r = 4;
        else if (str_cmp(m, "May") == 0)
            r = 5;
        else if (str_cmp(m, "Jun") == 0)
            r = 6;
        else if (str_cmp(m, "Jul") == 0)
            r = 7;
        else if (str_cmp(m, "Aug") == 0)
            r = 8;
        else if (str_cmp(m, "Sep") == 0)
            r = 9;
        else if (str_cmp(m, "Oct") == 0)
            r = 10;
        else if (str_cmp(m, "Nov") == 0)
            r = 11;
        else if (str_cmp(m, "Dec") == 0)
            r = 12;
        else
            r = 0;
    }
    return r;
}

static void two_digits(int v, char out2[3])
{
    out2[0] = (char)('0' + (v / 10) % 10);
    out2[1] = (char)('0' + (v % 10));
    out2[2] = '\0';
}

static int extract_year_last4(const char *s)
{
    int r = 0, i = 0;
    if (s != NULL)
    {
        i = 0;
        r = 0;
        while (s[i] != '\0')
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                int j = i, c = 0, y = 0;
                while (s[j] >= '0' && s[j] <= '9' && c < 4)
                {
                    y = y * 10 + (s[j] - '0');
                    c++;
                    j++;
                }
                if (c == 4)
                    r = y;
                i = j - 1;
            }
            i++;
        }
    }
    return r;
}

static void normalize_date(const char *raw, char out[16])
{
    int day = 1, mon = 1, year = 0, i = 0, n = 0;
    char dd[3], mm[3], tmp[64];
    out[0] = '\0';
    tmp[0] = '\0';

    str_trim_copy(tmp, raw, (int)sizeof(tmp));
    n = (int)str_len(tmp);
    if (n >= 4)
    {
        int m = month3_to_int(tmp);
        if (m >= 1 && m <= 12)
        {
            mon = m;
            i = 3;
            while (i < n && tmp[i] == ' ')
                i++;
            if (i < n && tmp[i] >= '0' && tmp[i] <= '9')
            {
                int d = 0;
                while (i < n && tmp[i] >= '0' && tmp[i] <= '9')
                {
                    d = d * 10 + (tmp[i] - '0');
                    i++;
                }
                if (d >= 1 && d <= 31)
                    day = d;
                while (i < n && (tmp[i] == ' ' || tmp[i] == ','))
                    i++;
                year = extract_year_last4(tmp + i);
            }
            else
            {
                year = extract_year_last4(tmp + i);
                day = 1;
            }
        }
        else
        {
            year = extract_year_last4(tmp);
            mon = 1;
            day = 1;
        }
    }

    if (year > 0)
    {
        two_digits(day, dd);
        two_digits(mon, mm);
        out[0] = dd[0];
        out[1] = dd[1];
        out[2] = '/';
        out[3] = mm[0];
        out[4] = mm[1];
        out[5] = '/';
        out[6] = (char)('0' + (year / 1000) % 10);
        out[7] = (char)('0' + (year / 100) % 10);
        out[8] = (char)('0' + (year / 10) % 10);
        out[9] = (char)('0' + (year % 10));
        out[10] = '\0';
    }
    else
    {
        out[0] = '\0';
    }
}

static int date_key(const char *ddmmyyyy)
{
    int r = 0;
    if (ddmmyyyy != NULL && str_len(ddmmyyyy) == 10 &&
        ddmmyyyy[2] == '/' && ddmmyyyy[5] == '/')
    {
        int d = (ddmmyyyy[0] - '0') * 10 + (ddmmyyyy[1] - '0');
        int m = (ddmmyyyy[3] - '0') * 10 + (ddmmyyyy[4] - '0');
        int y = (ddmmyyyy[6] - '0') * 1000 + (ddmmyyyy[7] - '0') * 100 + (ddmmyyyy[8] - '0') * 10 + (ddmmyyyy[9] - '0');
        r = y * 10000 + m * 100 + d;
    }
    else
    {
        r = 0;
    }
    return r;
}

static int split_csv_14(const char *line, char cols[14][4096])
{
    int r = 0, i = 0, n = 0, col = 0, inq = 0, start = 0;

    for (i = 0; i < 14; i++)
        cols[i][0] = '\0';
    if (line != NULL)
    {
        n = (int)str_len(line);
        col = 0;
        start = 0;
        inq = 0;
        i = 0;
        while (i <= n)
        {
            char c = (i < n) ? line[i] : ',';
            if (c == '"')
            {
                if (inq == 1)
                    inq = 0;
                else
                    inq = 1;
            }
            else if (c == ',' && inq == 0)
            {
                int a = start;
                int b = i - 1;
                char tmp[4096];
                char tok[4096];
                int tlen = 0, j = 0;

                while (a <= b && line[a] == ' ')
                    a++;
                while (b >= a && line[b] == ' ')
                    b--;

                j = a;
                tlen = 0;
                while (j <= b && tlen < (int)sizeof(tmp) - 1)
                {
                    if (line[j] != '\"')
                    {
                        tmp[tlen] = line[j];
                        tlen++;
                    }
                    j++;
                }
                tmp[tlen] = '\0';
                str_trim_copy(tok, tmp, (int)sizeof(tok));
                if (col < 14)
                    str_copy(cols[col], tok);
                col++;
                start = i + 1;
            }
            i++;
        }
        if (col == 14)
            r = 1;
    }
    return r;
}

static void parse_game_from_line(const char *line, Game *g)
{
    char c[14][4096];
    int ok = split_csv_14(line, c);
    if (ok == 1)
    {
        g->id = parse_int_digits(c[0], 0);
        str_copy_n(g->name, c[1], (int)sizeof(g->name));
        normalize_date(c[2], g->releaseDate);
        g->estimatedOwners = parse_int_digits(c[3], 0);
        g->price = normalize_price(c[4]);
        normalize_bracketed_list(c[5], g->supportedLanguages, (int)sizeof(g->supportedLanguages));
        g->metacriticScore = (c[6][0] == '\0') ? -1 : parse_int_digits(c[6], -1);
        g->userScore = normalize_user_score(c[7]);
        g->achievements = (c[8][0] == '\0') ? 0 : parse_int_digits(c[8], 0);
        normalize_csv_plain(c[9], g->publishers, (int)sizeof(g->publishers));
        normalize_csv_plain(c[10], g->developers, (int)sizeof(g->developers));
        normalize_bracketed_list(c[11], g->categories, (int)sizeof(g->categories));
        normalize_bracketed_list(c[12], g->genres, (int)sizeof(g->genres));
        normalize_tags(c[13], g->tags, (int)sizeof(g->tags));
    }
}

static void print_int_nz(int v)
{
    if (v == 0)
    {
        put_char('0');
    }
    else
    {
        int neg = 0, p = v, n = 0, pow10 = 1, i = 0, d = 0;
        if (v < 0)
        {
            neg = 1;
            v = -v;
        }
        p = v;
        n = 0;
        while (p > 0)
        {
            n++;
            p /= 10;
        }
        pow10 = 1;
        i = 1;
        while (i < n)
        {
            pow10 *= 10;
            i++;
        }
        if (neg)
            put_char('-');
        while (pow10 > 0)
        {
            d = v / pow10;
            put_char((char)('0' + d));
            v %= pow10;
            pow10 /= 10;
        }
    }
}

static void print_float_1(float f)
{
    int neg = 0, whole = 0, d1 = 0;
    float rest = 0.0f;
    if (f < 0.0f)
    {
        neg = 1;
        f = -f;
    }
    whole = (int)f;
    rest = f - (float)whole;
    d1 = (int)(rest * 10.0f + 0.5f);
    if (d1 == 10)
    {
        whole++;
        d1 = 0;
    }
    if (neg)
        put_char('-');
    print_int_nz(whole);
    put_char('.');
    put_char((char)('0' + d1));
}

static void print_price_auto(float p)
{
    long cents = (long)((p < 0 ? -p : p) * 100.0f + 0.5f);
    if (cents == 0)
    {
        print_float_1(p);
    }
    else
    {
        long tenths = (long)((p < 0 ? -p : p) * 10.0f + 0.5f);
        if (tenths * 10 == cents)
        {
            print_float_1(p);
        }
        else
        {
            long whole = cents / 100;
            int dec = (int)(cents % 100);
            if (p < 0)
                put_char('-');
            print_int_nz((int)whole);
            put_char('.');
            put_char((char)('0' + (dec / 10)));
            put_char((char)('0' + (dec % 10)));
        }
    }
}

static void print_bracketed(const char *csv)
{
    int i = 0;
    put_char('[');
    if (csv != NULL)
    {
        while (csv[i] != '\0')
        {
            char c = csv[i];
            if (c == ',')
            {
                put_char(',');
                put_char(' ');
                i++;
                while (csv[i] == ' ')
                {
                    i++;
                }
            }
            else
            {
                put_char(c);
                i++;
            }
        }
    }
    put_char(']');
}

static void print_game(const Game *g)
{
    fputs("=> ", stdout);
    print_int_nz(g->id);
    fputs(" ## ", stdout);
    fputs(g->name, stdout);
    fputs(" ## ", stdout);
    fputs(g->releaseDate, stdout);
    fputs(" ## ", stdout);
    print_int_nz(g->estimatedOwners);
    fputs(" ## ", stdout);
    print_price_auto(g->price);
    fputs(" ## ", stdout);
    print_bracketed(g->supportedLanguages);
    fputs(" ## ", stdout);
    if (g->metacriticScore < 0)
        fputs("-1", stdout);
    else
        print_int_nz(g->metacriticScore);
    fputs(" ## ", stdout);
    print_float_1(g->userScore);
    fputs(" ## ", stdout);
    print_int_nz(g->achievements);
    fputs(" ## ", stdout);
    print_bracketed(g->publishers);
    fputs(" ## ", stdout);
    print_bracketed(g->developers);
    fputs(" ## ", stdout);
    print_bracketed(g->categories);
    fputs(" ## ", stdout);
    print_bracketed(g->genres);
    fputs(" ## ", stdout);
    print_bracketed(g->tags);
    fputs(" ##\n", stdout);
}

typedef struct
{
    long long comparacoes;
    long long movimentacoes;
} Metrics;

static int cmp_by_release_then_id(const Game *a, const Game *b, Metrics *m)
{
    int r = 0;
    int ka = date_key(a->releaseDate);
    int kb = date_key(b->releaseDate);
    m->comparacoes = m->comparacoes + 1;
    if (ka < kb)
        r = -1;
    else if (ka > kb)
        r = 1;
    else
    {
        m->comparacoes = m->comparacoes + 1;
        if (a->id < b->id)
            r = -1;
        else if (a->id > b->id)
            r = 1;
        else
            r = 0;
    }
    return r;
}

static void swap_game(Game *a, Game *b, Metrics *m)
{
    Game tmp = *a;
    *a = *b;
    *b = tmp;
    m->movimentacoes = m->movimentacoes + 3;
}

static int partition_lomuto(Game *v, int lo, int hi, Metrics *m)
{
    int p = hi;
    Game pivot = v[p];
    int i = lo - 1;
    int j = lo;

    while (j <= hi - 1)
    {
        int c = cmp_by_release_then_id(&v[j], &pivot, m);
        if (c <= 0)
        {
            i = i + 1;
            if (i != j)
                swap_game(&v[i], &v[j], m);
        }
        j = j + 1;
    }
    if (i + 1 != hi)
        swap_game(&v[i + 1], &v[hi], m);
    return i + 1;
}

static void quicksort_by_release(Game *v, int lo, int hi, Metrics *m)
{
    int do_sort = 0;
    if (lo < hi)
        do_sort = 1;
    if (do_sort == 1)
    {
        int p = partition_lomuto(v, lo, hi, m);
        if (p - 1 > lo)
            quicksort_by_release(v, lo, p - 1, m);
        if (p + 1 < hi)
            quicksort_by_release(v, p + 1, hi, m);
    }
}

static int extract_last_int_token(const char *s)
{
    int n = 0, i = 0, j = 0;
    long val = 0, place = 1;
    int r = -1;
    if (s != NULL)
    {
        n = (int)str_len(s);
        i = n - 1;
        while (i >= 0 && r == -1)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                val = 0;
                place = 1;
                j = i;
                while (j >= 0 && s[j] >= '0' && s[j] <= '9')
                {
                    val = val + (long)(s[j] - '0') * place;
                    place = place * 10;
                    j = j - 1;
                }
                if (val > 2147483647L)
                    val = 2147483647L;
                r = (int)val;
            }
            i = i - 1;
        }
    }
    return r;
}

int main(int argc, char **argv)
{
    int retcode = 0;
    FILE *fp = NULL;
    char path[512];
    char line[131072];

    Game *arr = NULL;
    int arr_cap = 0, arr_len = 0;

    Game *sel = NULL;
    int sel_cap = 0, sel_len = 0;

    int have_error = 0;

    path[0] = '\0';
    if (argc > 1 && argv[1] && argv[1][0] != '\0')
    {
        str_copy_n(path, argv[1], (int)sizeof(path));
    }
    else
    {
        fp = fopen("/tmp/games.csv", "rb");
        if (fp != NULL)
        {
            fclose(fp);
            str_copy(path, "/tmp/games.csv");
        }
        else
        {
            str_copy(path, "games.csv");
        }
    }

    fp = fopen(path, "rb");
    if (fp == NULL)
    {
        fputs("Erro: não foi possível abrir o arquivo CSV.\n", stdout);
        have_error = 1;
        retcode = 1;
    }
    else
    {
        if (fgets(line, sizeof(line), fp) == NULL)
        {
        }
        else
        {
            arr_cap = 1024;
            arr_len = 0;
            arr = (Game *)malloc(arr_cap * sizeof(Game));
            if (arr == NULL)
            {
                have_error = 1;
                retcode = 1;
            }
            else
            {
                int reading = 1;
                while (reading == 1)
                {
                    char *ln = fgets(line, sizeof(line), fp);
                    if (ln == NULL)
                    {
                        reading = 0;
                    }
                    else
                    {
                        strip_newline(line);

                        if (arr_len >= arr_cap)
                        {
                            int newcap = arr_cap * 2;
                            Game *tmp = (Game *)realloc(arr, newcap * sizeof(Game));
                            if (tmp == NULL)
                            {
                                reading = 0;
                            }
                            else
                            {
                                arr = tmp;
                                arr_cap = newcap;
                            }
                        }
                        if (reading == 1)
                        {
                            parse_game_from_line(line, &arr[arr_len]);
                            arr_len = arr_len + 1;
                        }
                    }
                }
            }
        }
        fclose(fp);
    }

    if (have_error == 0)
    {
        sel_cap = 256;
        sel_len = 0;
        sel = (Game *)malloc(sel_cap * sizeof(Game));
        if (sel == NULL)
        {
            have_error = 1;
            retcode = 1;
        }
        else
        {
            int done = 0;
            while (done == 0)
            {
                char input[4096], token[1024];
                char *ln = fgets(input, sizeof(input), stdin);
                if (ln == NULL)
                {
                    done = 1;
                }
                else
                {
                    strip_newline(input);
                    str_trim_copy(token, input, (int)sizeof(token));
                    if (str_cmp(token, "FIM") == 0)
                    {
                        done = 1;
                    }
                    else
                    {
                        int wanted = extract_last_int_token(token);
                        if (wanted != -1)
                        {
                            int i = 0;
                            while (i < arr_len)
                            {
                                if (arr[i].id == wanted)
                                {
                                    if (sel_len >= sel_cap)
                                    {
                                        int newcap = sel_cap * 2;
                                        Game *tmp = (Game *)realloc(sel, newcap * sizeof(Game));
                                        if (tmp != NULL)
                                        {
                                            sel = tmp;
                                            sel_cap = newcap;
                                        }
                                    }
                                    if (sel_len < sel_cap)
                                    {
                                        sel[sel_len] = arr[i];
                                        sel_len = sel_len + 1;
                                    }
                                }
                                i = i + 1;
                            }
                        }
                    }
                }
            }
        }
    }

    if (have_error == 0)
    {
        Metrics mt;
        clock_t t0, t1;
        mt.comparacoes = 0;
        mt.movimentacoes = 0;

        t0 = clock();
        if (sel_len > 1)
        {
            quicksort_by_release(sel, 0, sel_len - 1, &mt);
        }
        t1 = clock();

        {
            int i = 0;
            while (i < sel_len)
            {
                print_game(&sel[i]);
                i = i + 1;
            }
        }

        {
            double elapsed = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;
            FILE *lf = fopen("884985_quicksort.txt", "wb");
            if (lf != NULL)
            {
                fprintf(lf, "%s\t%lld\t%lld\t%.6f",
                        MATRICULA,
                        (long long)mt.comparacoes,
                        (long long)mt.movimentacoes,
                        elapsed);
                fclose(lf);
            }
        }
    }

    if (sel)
        free(sel);
    if (arr)
        free(arr);
    return retcode;
}
