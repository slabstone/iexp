#ifndef FILE_FORMATS_DATA_TYPES_H
#define FILE_FORMATS_DATA_TYPES_H

// Infinity Engine data types
// https://gibberlings3.github.io/iesdp/file_formats/general.htm

#include <assert.h>    // static_assert
#include <inttypes.h>  // PRI macros
#include <stdint.h>    // int8_t, int16_t, int32_t

// ASCII character
typedef char ie_char;
static_assert(sizeof(ie_char) == 1, "unexpected char size");

// A little-endian "byte" of 8-bits
typedef int8_t ie_byte;
static_assert(sizeof(ie_byte) == 1, "unexpected byte size");

// printf conversion specifications for byte
#define IE_PRIdB "%" PRId8
#define IE_PRIxB "0x%02" PRIx8

// A little-endian "word" of 16-bits
typedef int16_t ie_word;
static_assert(sizeof(ie_word) == 2, "unexpected word size");

// printf conversion specifications for word
#define IE_PRIdW "%" PRId16
#define IE_PRIxW "0x%04" PRIx16

// A little-endian "double-word" of 32-bits
typedef int32_t ie_dword;
static_assert(sizeof(ie_dword) == 4, "unexpected dword size");

// printf conversion specifications for dword
#define IE_PRIdDW "%" PRId32
#define IE_PRIxDW "0x%08" PRIx32

// A point within some reference frame, composed of two 16-bit words; the first
// is the x-coordinate and the second is the y-coordinate.
typedef struct ie_point_tag {
  ie_word x;
  ie_word y;
} ie_point;
static_assert(sizeof(ie_point) == 4, "unexpected point size");

// A rectangle within some reference frame, composed of 4 16-bit words; the
// order of the coordinates is: left, top, right, bottom. Typically this is used
// to store bounding boxes of various objects.
typedef struct ie_rect_tag {
  ie_word left;
  ie_word top;
  ie_word right;
  ie_word bottom;
} ie_rect;
static_assert(sizeof(ie_rect) == 8, "unexpected rect size");

// A reference into the 'TLK' resource.
typedef struct ie_strref_tag {
  // Stored as a 32-bit number (though the top 8 bits refer to an internal file
  // Id, e.g. 0x01 refers to dialogf.tlk) which can be mapped to a string via a
  // lookup into the TLK table.
  union {
    ie_dword value;
    struct {
      ie_dword reference : 24;
      ie_dword file_id : 8;
    };
  };
} ie_strref;
static_assert(sizeof(ie_strref) == 4, "unexpected strref size");

// A reference to a specific resource -- a string (max 8 characters) which is
// mapped to a resource (stored in a BIF file or an override directory) via the
// KEY file. Note that these are always treated as 8 characters long; unused
// characters should generally be filled with NUL bytes.
#define RESREF_SIZE 8
typedef struct ie_resref_tag {
  ie_char data[RESREF_SIZE];
} ie_resref;
static_assert(sizeof(ie_resref) == RESREF_SIZE, "unexpected resref size");

#define IE_PRI_RESREF "%.8s"

#endif  // FILE_FORMATS_DATA_TYPES_H
