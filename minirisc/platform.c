#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"

#define MEMORY_SIZE (32u * 1024 * 1024) /*la taille de memoire*/
#define START_MEMORY 0x8000000u /*adresse ou la memeoire commence*/
#define START_PERIFERIQUE 0x10000000u

platform_t* platform_new()
{
    platform_t *platform = malloc(sizeof(platform_t));
    if(platform == NULL) return NULL;

    platform->memoire = malloc(MEMORY_SIZE);
    if(platform->memoire == NULL){
        free(platform);
        return NULL;
    } 
    return platform;
}

void platform_free(platform_t *plt) {
    free(plt->memoire);
    plt->memoire = NULL;
    free(plt);
}

int platform_read(platform_t *plt, platform_access_type_t t, uint32_t addr, uint32_t *data) {
    
    uint32_t size = t + 1; 
    
    if(addr >= START_MEMORY && addr - START_MEMORY + size <= MEMORY_SIZE) {
        uint8_t *mem = plt->memoire;
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
}

int platform_load_program(platform_t *plt, const char *file_name) {
    FILE *f = fopen(file_name, "rb");
    if(f == NULL) return -1;

    size_t n = fread(plt->memoire, 1, MEMORY_SIZE, f);

    fclose(f);

    if (n==0) return -1;
    
    return 0;
}