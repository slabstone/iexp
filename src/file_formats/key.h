#ifndef FILE_FORMATS_KEY_H
#define FILE_FORMATS_KEY_H

#include <assert.h>   // static_assert
#include <stdbool.h>  // bool
#include <stddef.h>   // offsetof

#include "data_types.h"  // ie_word, ie_dword, ie_resref
#include "header.h"      // ie_header_signature, ie_header_version

// KEY file format
// https://gibberlings3.github.io/iesdp/file_formats/ie_formats/key_v1.htm

// KEY V1 Header
typedef struct key_v1_header_tag {
  // Signature ('KEY ')
  ie_header_signature signature;

  // Version ('V1  ')
  ie_header_version version;

  // Count of BIF entries
  ie_dword bif_count;

  // Count of resource entries
  ie_dword resource_count;

  // Offset (from start of file) to BIF entries
  ie_dword bif_offset;

  // Offset (from start of file) to resource entries
  ie_dword resource_offset;
} key_v1_header;
static_assert(offsetof(key_v1_header, signature) == 0x0000,
              "KEY V1 Header signature offset mismatch");
static_assert(offsetof(key_v1_header, version) == 0x0004,
              "KEY V1 Header version offset mismatch");
static_assert(offsetof(key_v1_header, bif_count) == 0x0008,
              "KEY V1 Header bif_count offset mismatch");
static_assert(offsetof(key_v1_header, resource_count) == 0x000c,
              "KEY V1 Header resource_count offset mismatch");
static_assert(offsetof(key_v1_header, bif_offset) == 0x0010,
              "KEY V1 Header bif_offset offset mismatch");
static_assert(offsetof(key_v1_header, resource_offset) == 0x0014,
              "KEY V1 Header resource_offset offset mismatch");
static_assert(sizeof(key_v1_header) == 24, "KEY V1 Header size mismatch");

// KEY V1 BIF Entry
typedef struct key_v1_bif_entry_tag {
  // Length of BIF file
  ie_dword bif_length;

  // Offset from start of file to ASCIIZ BIF filename
  ie_dword bif_filename_offset;

  // Length, including terminating NUL, of ASCIIZ BIF filename
  ie_word bif_filename_length;

  union {
    // The 16 bits of this field are used individually to mark the location of
    // the relevant file.
    ie_word bif_location;

    // (MSB) xxxx xxxx ABCD EFGH (LSB)
    // * Bits marked A to F determine on which CD the file is stored (A = CD6,
    //   F = CD1)
    // * Bit G determines if the file is in the \cache directory
    // * Bit H determines if the file is in the \data directory
    struct {
      bool data : 1;   // \data directory
      bool cache : 1;  // \cache directory
      bool cd1 : 1;    // CD1
      bool cd2 : 1;    // CD2
      bool cd3 : 1;    // CD3
      bool cd4 : 1;    // CD4
      bool cd5 : 1;    // CD5
      bool cd6 : 1;    // CD6
    };
  };
} key_v1_bif_entry;
static_assert(offsetof(key_v1_bif_entry, bif_length) == 0x0000,
              "KEY V1 BIF Entry bif_length offset mismatch");
static_assert(offsetof(key_v1_bif_entry, bif_filename_offset) == 0x0004,
              "KEY V1 BIF Entry bif_filename_offset offset mismatch");
static_assert(offsetof(key_v1_bif_entry, bif_filename_length) == 0x0008,
              "KEY V1 BIF Entry bif_filename_length offset mismatch");
static_assert(offsetof(key_v1_bif_entry, bif_location) == 0x000a,
              "KEY V1 BIF Entry bif_location offset mismatch");
static_assert(sizeof(key_v1_bif_entry) == 12, "KEY V1 BIF Entry size mismatch");

// KEY V1 Resource Entry
typedef struct __attribute__((packed)) key_v1_resource_entry_tag {
  // Resource name
  ie_resref resource_name;

  // Resource type
  ie_word resource_type;

  // Resource locator
  union {
    // The IE resource manager uses 32-bit values as a 'resource index', which
    // codifies the source of the resource as well as which source it refers to.
    // The layout of this value is below.
    ie_dword resource_locator;

    struct {
      // bits 13- 0: non-tileset file index (any 12 bit value, so long as it
      // matches the value used in the BIF file)
      ie_dword file_index : 14;

      // bits 19-14: tileset index
      ie_dword tileset_index : 6;

      // bits 31-20: source index (the ordinal value giving the index of the
      // corresponding BIF entry)
      ie_dword source_index : 12;
    };
  };
} key_v1_resource_entry;
static_assert(sizeof(key_v1_resource_entry) == 14,
              "KEY V1 Resource Entry size mismatch");
static_assert(offsetof(key_v1_resource_entry, resource_name) == 0x0000,
              "KEY V1 Resource Entry resource name offset mismatch");
static_assert(offsetof(key_v1_resource_entry, resource_type) == 0x0008,
              "KEY V1 Resource Entry resource type offset mismatch");
static_assert(offsetof(key_v1_resource_entry, resource_locator) == 0x000a,
              "KEY V1 Resource Entry resource locator offset mismatch");

#endif  // FILE_FORMATS_KEY_H
