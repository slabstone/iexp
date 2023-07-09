#include "bif.h"

#include <stdbool.h>  // bool
#include <stdio.h>    // FILE, fseek, fread, printf

#include "file_formats/data_types.h"
#include "log.h"

bool biff_v1_parse_file(FILE* file) {
  log_debug("reading BIFF V1 file");

  log_debug("reading header");
  biff_v1_header header;
  biff_v1_read_header(file, &header);
  log_debug("reading header - done");

  biff_v1_log_header(&header);

  fseek(file, header.file_offset, SEEK_SET);

  if (header.file_count > 0) {
    log_debug("reading file entries");

    biff_v1_print_file_entry_csv_header();

    biff_v1_file_entry file_entries[header.file_count];

    for (int i = 0; i < header.file_count; ++i) {
      log_debug("reading file entry %d", i);
      biff_v1_read_file_entry(file, &file_entries[i]);
      log_debug("reading file entry %d - done", i);

      biff_v1_log_file_entry(&file_entries[i]);

      biff_v1_print_file_entry_csv(&file_entries[i]);
    }

    log_debug("reading file entries - done");
  } else {
    log_warn("no file entries");
  }

  if (header.tileset_count > 0) {
    log_debug("reading tileset entries");

    biff_v1_print_tileset_entry_csv_header();

    biff_v1_tileset_entry tileset_entries[header.tileset_count];

    for (int i = 0; i < header.tileset_count; ++i) {
      log_debug("reading tileset entry %d", i);
      biff_v1_read_tileset_entry(file, &tileset_entries[i]);
      log_debug("reading tileset entry %d - done", i);

      biff_v1_log_tileset_entry(&tileset_entries[i]);

      biff_v1_print_tileset_entry_csv(&tileset_entries[i]);
    }
    log_debug("reading tileset entries - done");
  } else {
    log_warn("no tileset entries");
  }

  log_debug("reading BIFF V1 file - done");

  return true;
}

bool biff_v1_read_header(FILE* file, biff_v1_header* header) {
  return fread(header, sizeof(*header), 1, file) == 1;
}

bool biff_v1_read_file_entry(FILE* file, biff_v1_file_entry* file_entry) {
  return fread(file_entry, sizeof(*file_entry), 1, file) == 1;
}

bool biff_v1_read_tileset_entry(FILE* file,
                                biff_v1_tileset_entry* tileset_entry) {
  return fread(tileset_entry, sizeof(*tileset_entry), 1, file) == 1;
}

void biff_v1_log_header(const biff_v1_header* header) {
  log_info("Signature:\t" IE_PRI_SIGNATURE, header->signature.data);
  log_info("Version:\t" IE_PRI_VERSION, header->version.data);
  log_info("File count:\t" IE_PRIdDW, header->file_count);
  log_info("Tileset count:\t" IE_PRIdDW, header->tileset_count);
  log_info("File offset:\t" IE_PRIxDW, header->file_offset);
}

void biff_v1_log_file_entry(const biff_v1_file_entry* file_entry) {
  log_info("Resource locator:\t" IE_PRIxDW, file_entry->resource_locator);
  log_info("File index:\t\t" IE_PRIdDW, file_entry->file_index);
  log_info("Resource data offset:\t" IE_PRIxDW, file_entry->data_offset);
  log_info("Resource size:\t\t" IE_PRIdDW, file_entry->resource_size);
  log_info("Resource type:\t\t" IE_PRIxW, file_entry->resource_type);
  log_info("Unknown:\t\t" IE_PRIxW, file_entry->unknown);
}

void biff_v1_log_tileset_entry(const biff_v1_tileset_entry* tileset_entry) {
  log_debug("Resource locator:\t" IE_PRIxDW, tileset_entry->resource_locator);
  log_debug("Tileset index:\t\t" IE_PRIdDW, tileset_entry->tileset_index);
  log_debug("Resource data offset:\t" IE_PRIxDW, tileset_entry->data_offset);
  log_debug("Tile count:\t\t" IE_PRIdDW, tileset_entry->tile_count);
  log_debug("Tile size:\t\t" IE_PRIdDW, tileset_entry->tile_size);
  log_debug("Resource type:\t" IE_PRIxW, tileset_entry->resource_type);
  log_debug("Unknown:\t\t" IE_PRIxW, tileset_entry->unknown);
}

void biff_v1_print_file_entry_csv_header() {
  printf("resource_locator,");
  printf("file_index,");
  printf("data_offset,");
  printf("resource_size,");
  printf("resource_type,");
  printf("unknown\n");
}

void biff_v1_print_tileset_entry_csv_header() {
  printf("resource_locator,");
  printf("tileset_index,");
  printf("data_offset,");
  printf("tile_count,");
  printf("tile_size,");
  printf("resource_type,");
  printf("unknown\n");
}

void biff_v1_print_file_entry_csv(const biff_v1_file_entry* file_entry) {
  printf(IE_PRIxDW ",", file_entry->resource_locator);
  printf(IE_PRIdDW ",", file_entry->file_index);
  printf(IE_PRIxDW ",", file_entry->data_offset);
  printf(IE_PRIdDW ",", file_entry->resource_size);
  printf(IE_PRIxW ",", file_entry->resource_type);
  printf(IE_PRIxW "\n", file_entry->unknown);
}

void biff_v1_print_tileset_entry_csv(
    const biff_v1_tileset_entry* tileset_entry) {
  printf(IE_PRIxDW ",", tileset_entry->resource_locator);
  printf(IE_PRIdDW ",", tileset_entry->tileset_index);
  printf(IE_PRIxDW ",", tileset_entry->data_offset);
  printf(IE_PRIdDW ",", tileset_entry->tile_count);
  printf(IE_PRIdDW ",", tileset_entry->tile_size);
  printf(IE_PRIxW ",", tileset_entry->resource_type);
  printf(IE_PRIxW "\n", tileset_entry->unknown);
}
