#include "key.h"

#include <stdbool.h>  // bool
#include <stdio.h>    // FILE, fseek, fread, printf
#include <stdlib.h>   // malloc, free

#include "file_formats/data_types.h"
#include "log.h"

bool key_v1_parse_file(FILE* file) {
  log_debug("reading KEY V1 file");

  log_debug("reading header");
  key_v1_header header;
  key_v1_read_header(file, &header);
  log_debug("reading header - done");

  key_v1_log_header(&header);

  if (header.bif_count > 0) {
    fseek(file, header.bif_offset, SEEK_SET);

    log_debug("reading BIF entries");

    key_v1_print_bif_entry_csv_header();

    key_v1_bif_entry bif_entries[header.bif_count];
    ie_char* bif_filenames[header.bif_count];

    for (int i = 0; i < header.bif_count; i++) {
      log_debug("reading BIF entry %d", i + 1);
      key_v1_read_bif_entry(file, &bif_entries[i]);
      log_debug("reading BIF entry %d - done", i + 1);

      log_debug("reading BIF filename");

      const long current_position = ftell(file);
      fseek(file, bif_entries[i].bif_filename_offset, SEEK_SET);

      bif_filenames[i] = malloc(bif_entries[i].bif_filename_length);
      if (fgets(bif_filenames[i], bif_entries[i].bif_filename_length, file) ==
          NULL) {
        log_error("failed to read BIF filename");
        return false;
      }

      log_debug("reading BIF filename - done");
      fseek(file, current_position, SEEK_SET);

      key_v1_log_bif_entry(&bif_entries[i]);
      log_info("Filename: %s", bif_filenames[i]);

      printf("%d,", i);
      key_v1_print_bif_entry_csv(&bif_entries[i]);
      printf("%s\n", bif_filenames[i]);

      free(bif_filenames[i]);
    }

    log_debug("reading BIF entries - done");
  } else {
    log_warn("no BIF entries");
  }

  if (header.resource_count > 0) {
    fseek(file, header.resource_offset, SEEK_SET);

    log_debug("reading resource entries");

    key_v1_print_resource_entry_csv_header();

    key_v1_resource_entry resource_entries[header.resource_count];
    for (int i = 0; i < header.resource_count; i++) {
      log_debug("reading resource entry %d", i + 1);
      key_v1_read_resource_entry(file, &resource_entries[i]);
      log_debug("reading resource entry %d - done", i + 1);

      key_v1_log_resource_entry(&resource_entries[i]);
      key_v1_print_resource_entry_csv(&resource_entries[i]);
    }

    log_debug("reading resource entries - done");
  } else {
    log_warn("no resource entries");
  }

  log_debug("parsing KEY V1 file - done");

  return true;
}

bool key_v1_read_header(FILE* file, key_v1_header* header) {
  return fread(header, sizeof(*header), 1, file) == 1;
}

bool key_v1_read_bif_entry(FILE* file, key_v1_bif_entry* bif_entry) {
  return fread(bif_entry, sizeof(*bif_entry), 1, file) == 1;
}

bool key_v1_read_resource_entry(FILE* file,
                                key_v1_resource_entry* resource_entry) {
  return fread(resource_entry, sizeof(*resource_entry), 1, file) == 1;
}

void key_v1_log_header(const key_v1_header* header) {
  log_info("Signature:\t\t" IE_PRI_SIGNATURE, header->signature.data);
  log_info("Version:\t\t" IE_PRI_VERSION, header->version.data);
  log_info("BIF count:\t\t" IE_PRIdDW, header->bif_count);
  log_info("Resource count:\t" IE_PRIdDW, header->resource_count);
  log_info("BIF offset:\t\t" IE_PRIxDW, header->bif_offset);
  log_info("Resource offset:\t" IE_PRIxDW, header->resource_offset);
}

void key_v1_log_bif_entry(const key_v1_bif_entry* bif_entry) {
  log_info("File length:\t\t" IE_PRIdDW, bif_entry->bif_length);
  log_info("Filename offset:\t" IE_PRIxDW, bif_entry->bif_filename_offset);
  log_info("Filename length:\t" IE_PRIdW, bif_entry->bif_filename_length);
  log_info("Location:\t\t" IE_PRIxW, bif_entry->bif_location);
  log_info("CD6:\t\t%d", bif_entry->cd6);
  log_info("CD5:\t\t%d", bif_entry->cd5);
  log_info("CD4:\t\t%d", bif_entry->cd4);
  log_info("CD3:\t\t%d", bif_entry->cd3);
  log_info("CD2:\t\t%d", bif_entry->cd2);
  log_info("CD1:\t\t%d", bif_entry->cd1);
  log_info("Cache:\t%d", bif_entry->cache);
  log_info("Data:\t\t%d", bif_entry->data);
}

void key_v1_log_resource_entry(const key_v1_resource_entry* resource_entry) {
  log_info("Resource name:\t\t" IE_PRI_RESREF,
           resource_entry->resource_name.data);
  log_info("Resource type:\t\t" IE_PRIxW, resource_entry->resource_type);
  log_info("Resource locator:\t" IE_PRIxDW, resource_entry->resource_locator);
  log_info("Source index:\t\t" IE_PRIdDW, resource_entry->source_index);
  log_info("Tileset index:\t\t" IE_PRIdDW, resource_entry->tileset_index);
  log_info("File index:\t\t" IE_PRIdDW, resource_entry->file_index);
}

void key_v1_print_bif_entry_csv_header() {
  printf("bif_index,");
  printf("bif_length,");
  printf("bif_filename_offset,");
  printf("bif_filename_length,");
  printf("bif_location,");
  printf("cd6,cd5,cd4,cd3,cd2,cd1,cache,data,");
  printf("bif_filename\n");
}

void key_v1_print_resource_entry_csv_header() {
  printf("resource_name,");
  printf("resource_type,");
  printf("resource_locator,");
  printf("source_index,");
  printf("tileset_index,");
  printf("file_index\n");
}

void key_v1_print_bif_entry_csv(const key_v1_bif_entry* bif_entry) {
  // bif_index is printed outside
  printf(IE_PRIdDW ",", bif_entry->bif_length);
  printf(IE_PRIxDW ",", bif_entry->bif_filename_offset);
  printf(IE_PRIdW ",", bif_entry->bif_filename_length);
  printf(IE_PRIxW ",", bif_entry->bif_location);
  printf("%d,", bif_entry->cd6);
  printf("%d,", bif_entry->cd5);
  printf("%d,", bif_entry->cd4);
  printf("%d,", bif_entry->cd3);
  printf("%d,", bif_entry->cd2);
  printf("%d,", bif_entry->cd1);
  printf("%d,", bif_entry->cache);
  printf("%d,", bif_entry->data);
  // bif_filename is printed outside
}

void key_v1_print_resource_entry_csv(
    const key_v1_resource_entry* resource_entry) {
  printf(IE_PRI_RESREF ",", resource_entry->resource_name.data);
  printf(IE_PRIxW ",", resource_entry->resource_type);
  printf(IE_PRIxDW ",", resource_entry->resource_locator);
  printf(IE_PRIdDW ",", resource_entry->source_index);
  printf(IE_PRIdDW ",", resource_entry->tileset_index);
  printf(IE_PRIdDW "\n", resource_entry->file_index);
}
