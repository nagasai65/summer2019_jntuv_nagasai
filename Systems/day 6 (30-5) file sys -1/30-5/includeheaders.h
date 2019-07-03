#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define BLOCK_SIZE 16*1024
#define META_BLOCKS 4
#define FILE_NAME_LENGTH 20
#define MAGICNUM 0x444E524D
#define MAXFILECOUNT 32
#define NOOFBLOCKS 6000