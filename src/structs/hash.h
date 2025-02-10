#pragma once 


/* Hash Function */
static unsigned int hash_pjw(const char *key)
{
    const char *ptr = key;
    unsigned int val = 0;
    while (*ptr != '\0')
    {
        unsigned int tmp;
        val = (val << 4) + (*ptr);
        if ((tmp = (val & 0xf0000000)))
        {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }
        ptr++;
    }
    return val;
}