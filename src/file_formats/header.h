#ifndef FILE_FORMATS_HEADER_H
#define FILE_FORMATS_HEADER_H

#include <assert.h>  // static_assert

#include "data_types.h"  // ie_char

// Signature (e.g. 'KEY ')
#define HEADER_SIGNATURE_SIZE 4
typedef struct ie_header_signature_tag {
  ie_char data[HEADER_SIGNATURE_SIZE];
} ie_header_signature;
static_assert(sizeof(ie_header_signature) == HEADER_SIGNATURE_SIZE,
              "header signature char array size mismatch");

#define IE_PRI_SIGNATURE "%.4s"

// Version (e.g. 'V1  ')
#define HEADER_VERSION_SIZE 4
typedef struct ie_header_version_tag {
  ie_char data[HEADER_VERSION_SIZE];
} ie_header_version;
static_assert(sizeof(ie_header_version) == HEADER_VERSION_SIZE,
              "header version char array size mismatch");

#define IE_PRI_VERSION "%.4s"

#endif  // FILE_FORMATS_HEADER_H
