set(TARGET_NAME iexp)

add_executable(${TARGET_NAME} main.c
  bif.h bif.c
  key.h key.c
)

target_sources(${TARGET_NAME} INTERFACE
  file_formats/bif.h
  file_formats/header.h
  file_formats/data_types.h
  file_formats/key.h
)

set_target_properties(${TARGET_NAME} PROPERTIES C_STANDARD 11)

target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(${TARGET_NAME} PRIVATE -Werror)
endif()

target_link_libraries(${TARGET_NAME} log.c)

# add Cppcheck
find_program(CPPCHECK cppcheck)

if(CPPCHECK)
  set(CPPCHECK_ARGS
    --enable=all
    --error-exitcode=1
    --force
    -I ${CMAKE_SOURCE_DIR}/log.c/src
    --inconclusive
    --language=c
    --std=c11
    --template=gcc
  )

  set(CPPCHECK_SUPPRESS
    unusedFunction
    unmatchedSuppression
    missingIncludeSystem
  )
  list(TRANSFORM CPPCHECK_SUPPRESS PREPEND "--suppress=")

  list(APPEND CPPCHECK_ARGS ${CPPCHECK_SUPPRESS})

  set_target_properties(${TARGET_NAME} PROPERTIES
    C_CPPCHECK "${CPPCHECK};${CPPCHECK_ARGS}"
  )

  add_test(NAME cppcheck
    COMMAND ${CPPCHECK} ${CPPCHECK_ARGS} ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND_EXPAND_LISTS
  )
endif()
