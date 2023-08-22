/* testtruth.c zum Testen der Belegaufgabe 6 */
#include <stdio.h> // fuer printf ()
#include <stdlib.h>
// Deklaration der Aufgabenfunktion
int sat(const char term[]);
unsigned long Get_String_Length(const char *term);
int count_varialbe(const char *term);


int main(int argc, const char *const *args)
{
    argc = 2;
    if (argc != 2)
        return -1;
    // const char* const* text = {"(x&y)|(x&z)"}; // warning: initialization of 'const char * const*' from incompatible pointer type 'char *'
    // args = "(x&y)|(x&z)";initialization of 'const char * const*' from incompatible pointer typ
    const char *const text[] = {"(~a&b)"};
    switch (sat(*text))
    {
    case 1:
        printf("%s ist erfullbar.\n", text[0]);
        break;
    case 0:
        printf("%s ist nicht erfüllbar.\n", text[0]);
        break;
    default:
        printf("%s ist kein gültiger Ausdruck.\n", text[0]);
        break;
    }
    return 0; // 0 bedeutet alles okay
}

unsigned long Get_String_Length(const char *term)
{
    if (term[0] == 0)
    {
        return 1;
    }
    return 1 + Get_String_Length(term + 1);
}
int sat(const char term[])
{
    int length = Get_String_Length(term);
    int check_for_klammen = 0;
    int count_parantheses = 0;
    int count_p = 0;
    int chech_repeat = 0;
    int *check_return = (calloc(count_parantheses, sizeof(int)));
    char *new_array = calloc(length, sizeof(int));
    for (int i = 0; i < length; i++)
    {
        // check if all parentheses open and close
        if (term[i] == '(')
        {
            count_parantheses++;
            check_for_klammen++;
        }
        else if (term[i] == ')')
        {
            check_for_klammen--;
        }
        // sat("(a|b)|( c))"); // -1 ( Oder in Klammerausdruck )
        if (check_for_klammen > 0 && term[i] == '|')
        {
            free(check_return);
            free(new_array);
            return -1;
        }
        // sat("(x&y)&( z))"); // -1 ( Und zwischen Klammerausdrücken )
        if (check_for_klammen == 0 && term[i] == '&')
        {
            free(check_return);
            free(new_array);
            return -1;
        }
        // sat("~(a&b )|( c))"); // -1 ( Negation vor Klammer )
        if (term[i] == '(' && term[i - 1] == '~')
        {
            free(check_return);
            free(new_array);
            return -1;
        }
    }
    if (check_for_klammen != 0)
    {
        free(check_return);
        free(new_array);
        return -1;
    }
    for (int i = 1; i <= length; i++)
    {
        if (term[i] == ')')
        {
            if (chech_repeat == 0)
            {
                check_return[count_p] = 1;
            }
            count_p++;
            continue;
        }
        for (int j = i - 1; term[j] != '('; j--)
        {
            if ((term[j] <= 'z' && term[j] >= 'a') || term[j] == '~')
            {
                if (term[i] == term[j])
                {
                    if ((term[i - 1] == '~' && term[j] != '~') || (term[i] != '~' && term[j - 1] == '~'))
                    {
                        check_return[count_p] = 0;
                        chech_repeat = 1;
                    }
                    else
                    {
                        check_return[count_p] = 1;
                        chech_repeat = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < count_parantheses; i++)
    {
        if (check_return[i] == 1)
        {
            free(check_return);
            free(new_array);
            return 1;
        }
    }

    free(check_return);
    free(new_array);
    return 0;
}