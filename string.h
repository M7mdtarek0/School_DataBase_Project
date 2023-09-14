/*
 * string.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Mohamed Tarek Elsaid
 */

#ifndef _STRING_H_
#define _STRING_H_

#include "Types.h"
#include "Config.h"

u32 custom_strlen(const u8* str)				 ;
void custom_strcpy(u8* dest, const u8* src)		 ;
s32 custom_strcmp(const u8* str1, const u8* str2);
u32 custom_atoi(const u8* str)					 ;

#endif