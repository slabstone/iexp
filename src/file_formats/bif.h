#ifndef FILE_FORMATS_BIF_H
#define FILE_FORMATS_BIF_H

#include <assert.h>  // static_assert
#include <stddef.h>  // offsetof

#include "data_types.h"  // ie_word, ie_dword
#include "header.h"      // ie_header_signature, ie_header_version

// BIFF file format
// https://gibberlings3.github.io/iesdp/file_formats/ie_formats/bif_v1.htm

// BIFF V1

// BIFF V1 Header
typedef struct biff_v1_header_tag {
  // Signature ('BIFF')
  ie_header_signature signature;

  // Version ('V1  ')
  ie_header_version version;

  // Count of file entries
  ie_dword file_count;

  // Count of tileset entries
  ie_dword tileset_count;

  // Offset (from start of file) to file entries
  ie_dword file_offset;
} biff_v1_header;
static_assert(offsetof(biff_v1_header, signature) == 0x0000,
              "BIFF V1 Header signature offset mismatch");
static_assert(offsetof(biff_v1_header, version) == 0x0004,
              "BIFF V1 Header version offset mismatch");
static_assert(offsetof(biff_v1_header, file_count) == 0x0008,
              "BIFF V1 Header file_count offset mismatch");
static_assert(offsetof(biff_v1_header, tileset_count) == 0x000c,
              "BIFF V1 Header tileset_count offset mismatch");
static_assert(offsetof(biff_v1_header, file_offset) == 0x0010,
              "BIFF V1 Header file_offset offset mismatch");
static_assert(sizeof(biff_v1_header) == 20, "BIFF V1 Header size mismatch");

// BIFF V1 File Entry
typedef struct biff_v1_file_entry_tag {
  union {
    // Resource locator
    ie_dword resource_locator;

    // NB: On disk, only bits 0-13 are matched. They are matched against the
    // file index in the "resource locator" field from the KEY file resource
    // entries which claim to exist in this BIFF.
    struct {
      // bits 0-13: file index
      ie_dword file_index : 14;

      // Unused
      ie_dword unused : 18;
    };
  };

  // Offset (from start of file) to resource data
  ie_dword data_offset;

  // Size of this resource
  ie_dword resource_size;

  // Type of this resource
  ie_word resource_type;

  // Unknown
  ie_word unknown;
} biff_v1_file_entry;
static_assert(offsetof(biff_v1_file_entry, resource_locator) == 0x0000,
              "BIFF V1 File Entry resource_locator offset mismatch");
static_assert(offsetof(biff_v1_file_entry, data_offset) == 0x0004,
              "BIFF V1 File Entry data_offset offset mismatch");
static_assert(offsetof(biff_v1_file_entry, resource_size) == 0x0008,
              "BIFF V1 File Entry resource_size offset mismatch");
static_assert(offsetof(biff_v1_file_entry, resource_type) == 0x000c,
              "BIFF V1 File Entry resource_type offset mismatch");
static_assert(offsetof(biff_v1_file_entry, unknown) == 0x000e,
              "BIFF V1 File Entry unknown offset mismatch");
static_assert(sizeof(biff_v1_file_entry) == 16,
              "BIFF V1 File Entry size mismatch");

// BIFF V1 Tileset Entry
typedef struct biff_v1_tileset_entry_tag {
  union {
    // Resource locator
    ie_dword resource_locator;

    // NB: On disk, only bits 14-19 are matched upon. They are matched against
    // the tileset index in the "resource locator" field from the KEY file
    // resource entries which claim to exist in this BIFF.
    struct {
      // unused
      ie_dword unused : 14;

      // bits 14-19: tileset index
      ie_dword tileset_index : 6;
    };
  };

  // Offset (from start of file) to resource data
  ie_dword data_offset;

  // Count of tiles in this resource
  ie_dword tile_count;

  // Size of each tile in this resource
  ie_dword tile_size;

  // Type of this resource (always 0x3eb - TIS)
  ie_word resource_type;

  // Unknown
  ie_word unknown;
} biff_v1_tileset_entry;
static_assert(offsetof(biff_v1_tileset_entry, resource_locator) == 0x0000,
              "BIFF V1 Tileset Entry resource_locator offset mismatch");
static_assert(offsetof(biff_v1_tileset_entry, data_offset) == 0x0004,
              "BIFF V1 Tileset Entry data_offset offset mismatch");
static_assert(offsetof(biff_v1_tileset_entry, tile_count) == 0x0008,
              "BIFF V1 Tileset Entry tile_count offset mismatch");
static_assert(offsetof(biff_v1_tileset_entry, tile_size) == 0x000c,
              "BIFF V1 Tileset Entry tile_size offset mismatch");
static_assert(offsetof(biff_v1_tileset_entry, resource_type) == 0x0010,
              "BIFF V1 Tileset Entry resource_type offset mismatch");
static_assert(offsetof(biff_v1_tileset_entry, unknown) == 0x0012,
              "BIFF V1 Tileset Entry unknown offset mismatch");
static_assert(sizeof(biff_v1_tileset_entry) == 20,
              "BIFF V1 Tileset Entry size mismatch");

#endif  // FILE_FORMATS_BIF_H
