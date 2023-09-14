/*
 * string.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Mohamed Tarek Elsaid
 */

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Types.h"

// Custom string length function
u32 custom_strlen(const u8* str) {
    u32 len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Custom string copy function // dest means the destination and src means the source
void custom_strcpy(u8* dest, const u8* src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // Putting a null to the end of the destination string
}

// Custom string comparison function
// this function Compares two strings character by character to determine their lexicographic order.
s32 custom_strcmp(const u8* str1, const u8* str2) {
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }

    if (*str1 == '\0' && *str2 == '\0') {
        return 0;  // Strings are equal
    } else if (*str1 < *str2) {
        return -1; // str1 comes before str2
    } else {
        return 1;  // str1 comes after str2
    }
}

// function to convert a string of numerical characters (representing an integer) into an equivalent integer value
u32 custom_atoi(const u8* str) {
    u32 result = 0;
    while (*str >= '0' && *str <= '9') {
		// Calculate the new result:
        // - Multiply the current result by 10 to shift its digits left.
        // - Add the numerical value of the current character to the result.
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}