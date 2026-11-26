#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"

#define MEMORY_SIZE (32u * 1024 * 1024) /*la taille de memoire*/
#define START_MEMORY 0x80000000u /*adresse ou la memoire commence*/
#define START_PERIFERIQUE 0x10000000u

platform_t* platform_new()
{
    platform_t *platform = malloc(sizeof(platform_t));
    if(platform == NULL) return NULL;

    platform->memory = malloc(MEMORY_SIZE);
    if(platform->memory == NULL){
        free(platform);
        return NULL;
    } 
    return platform;
}

void platform_free(platform_t *plt) {
    free(plt->memory);
    plt->memory = NULL;
    free(plt);
}

int platform_read(platform_t *plt, platform_access_type_t t, uint32_t addr, uint32_t *data) {
    
    uint32_t size = t + 1; 
    
    if(addr >= START_MEMORY && addr - START_MEMORY + size <= MEMORY_SIZE) {
        uint8_t *mem = (uint8_t*) plt->memory;
        uint32_t off = addr - START_MEMORY;
        uint32_t read_data = 0;

        for(int i=0; i<size; i++){
            read_data |= (uint32_t)mem[off + i] << (8*i);
        }
        *data = read_data;
        return 0;
    }
    return -1;
} 

int platform_write(platform_t *plt, platform_access_type_t t, uint32_t addr, uint32_t data) {

    uint32_t size = t + 1; 
    if((addr & t) !=0){
        return -1;
    }
        if(addr >= START_MEMORY && addr - START_MEMORY + size <= MEMORY_SIZE) {
        uint8_t *mem = (uint8_t *) plt->memory;
        uint32_t off = addr - START_MEMORY;

        for(int i=0; i<size; i++){
        mem[off + i] =  (data >> (8*i)) & 0XFF;
        }
    return 0;}

        if (addr == START_PERIFERIQUE) { printf("%c",data & 0xFF );
                                        return 0;}/*afficher caractere*/
        if (addr == START_PERIFERIQUE + 4)  { printf("%d", (int32_t)data );
                                             return 0;} /*affficher lentier signe*/
        if (addr == START_PERIFERIQUE + 8) { printf("%x", data ); /*afficher en hexa*/
                                             return 0;}/*afficher en hexa*/
    
    return -1;
}

int platform_load_program(platform_t *plt, const char *file_name) {
    FILE *f = fopen(file_name, "rb");
    if(f == NULL) return -1;

    size_t n = fread(plt->memory, 1, MEMORY_SIZE, f);

    fclose(f);

    if (n==0) return -1;
    
    return 0;
}