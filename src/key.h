#ifndef KEY_H
#define KEY_H

#include <stdbool.h>  // bool
#include <stdio.h>    // FILE

#include "file_formats/key.h"  // key_v1 structs

bool key_v1_parse_file(FILE* file);

bool key_v1_read_header(FILE* file, key_v1_header* header);
bool key_v1_read_bif_entry(FILE* file, key_v1_bif_entry* bif_entry);
bool key_v1_read_resource_entry(FILE* file,
                                key_v1_resource_entry* resource_entry);

void key_v1_log_header(const key_v1_header* header);
void key_v1_log_bif_entry(const key_v1_bif_entry* bif_entry);
void key_v1_log_resource_entry(const key_v1_resource_entry* resource_entry);

void key_v1_print_bif_entry_csv_header();
void key_v1_print_resource_entry_csv_header();

void key_v1_print_bif_entry_csv(const key_v1_bif_entry* bif_entry);
void key_v1_print_resource_entry_csv(
    const key_v1_resource_entry* resource_entry);

#endif  // KEY_H
