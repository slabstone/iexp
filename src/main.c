#include <stdio.h>   // FILE, fopen, fread, rewind, fclose
#include <stdlib.h>  // EXIT_FAILURE, EXIT_SUCCESS
#include <string.h>  // strncmp

#include "bif.h"
#include "key.h"
#include "log.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    log_error("usage: %s <filename>", argv[0]);
    return EXIT_FAILURE;
  }

  const char* filename = argv[1];

  log_debug("reading file: %s", filename);
  FILE* file = fopen(filename, "rb");

  log_debug("reading file header");

  ie_header_signature header_signature;
  if (fread(&header_signature, sizeof(header_signature), 1, file) != 1) {
    log_error("failed to read file header signature");
    fclose(file);
    return EXIT_FAILURE;
  }

  ie_header_version header_version;
  if (fread(&header_version, sizeof(header_version), 1, file) != 1) {
    log_error("failed to read file header version");
    fclose(file);
    return EXIT_FAILURE;
  }

  log_debug("reading file header - done");

  log_info("file format: " IE_PRI_SIGNATURE " " IE_PRI_VERSION,
           header_signature.data, header_version.data);

  rewind(file);

  if (strncmp(header_signature.data, "KEY ", HEADER_SIGNATURE_SIZE) == 0) {
    key_v1_parse_file(file);
  } else if (strncmp(header_signature.data, "BIFF", HEADER_SIGNATURE_SIZE) ==
             0) {
    biff_v1_parse_file(file);
  } else {
    log_error("unknown file format");
    fclose(file);
    return EXIT_FAILURE;
  }

  fclose(file);
  return EXIT_SUCCESS;
}
