#ifndef BIF_H
#define BIF_H

#include <stdbool.h>  // bool
#include <stdio.h>    // FILE

#include "file_formats/bif.h"  // biff_v1 structs

bool biff_v1_parse_file(FILE* file);

bool biff_v1_read_header(FILE* file, biff_v1_header* header);
bool biff_v1_read_file_entry(FILE* file, biff_v1_file_entry* file_entry);
bool biff_v1_read_tileset_entry(FILE* file,
                                biff_v1_tileset_entry* tileset_entry);

void biff_v1_log_header(const biff_v1_header* header);
void biff_v1_log_file_entry(const biff_v1_file_entry* file_entry);
void biff_v1_log_tileset_entry(const biff_v1_tileset_entry* tileset_entry);

void biff_v1_print_file_entry_csv_header();
void biff_v1_print_tileset_entry_csv_header();

void biff_v1_print_file_entry_csv(const biff_v1_file_entry* file_entry);
void biff_v1_print_tileset_entry_csv(
    const biff_v1_tileset_entry* tileset_entry);

#endif  // BIF_H
