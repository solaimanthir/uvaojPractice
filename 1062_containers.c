#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int get_unq_chars(char * arrival, int slen)
{
    int i, unq_len = 0;
    bool alp_flag[26];
    memset(alp_flag, 0, 26);
    for(i = 0; i < slen; ++i)
    {
        if(alp_flag[arrival[i]-'A'] == false)
            alp_flag[arrival[i]-'A'] = true;
    }
    for(i = 0; i < 26; ++i){
        if(alp_flag[i] == true)
            ++unq_len;
    }
    return unq_len;
}

int min_num_stks(char * arrival, int slen)
{
    int i, j, stks = 0;
    int unq_len = get_unq_chars(arrival, slen);
    char * stk_top = calloc(unq_len, sizeof(char));
    memset(stk_top, -1, unq_len);
    for(i = 0; i < slen; ++i){
        for(j = 0; j < unq_len; ++j) {
            if(stk_top[j] == -1)
            {
                ++stks;
                stk_top[j] = arrival[i];
                break;
            }
            else
            {
                if(stk_top[j] >= arrival[i])
                {
                    stk_top[j] = arrival[i];
                    break;
                }
            }
        }
    }
    free(stk_top);
    return stks;
}
int main()
{
    char arrival[1001];
    int casen = 0;
    while(1) {
        int slen;
        memset(arrival, 0, 1001);
        scanf("%s", arrival);
        if(strcmp(arrival, "end") == 0)
            break;
        slen = strlen(arrival);
        printf("Case %d: %d\n", ++casen, min_num_stks(arrival, slen));
    }

    return 0;
}