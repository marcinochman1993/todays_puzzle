
function(Prepend var prefix)
  set(listVar "")
  foreach(f ${ARGN})
    list(APPEND listVar "${prefix}/${f}")
  endforeach(f)
  set(${var} "${listVar}" PARENT_SCOPE)
endfunction(Prepend)


function(SetupClangTidy TARGET)
  get_target_property(TARGET_SOURCES ${TARGET} SOURCES)
  Prepend(ABSOLUTE_TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR} ${TARGET_SOURCES})

  set(ANALYSIS_FILE_PATH ${CMAKE_BINARY_DIR}/${TARGET}_check_output.txt)

  add_custom_target(${TARGET}_check
    COMMAND ${CLANG_TIDY_EXE} "-p" "${CMAKE_BINARY_DIR}" "-checks=*" ${ABSOLUTE_TARGET_SOURCES} > ${ANALYSIS_FILE_PATH}
    COMMAND cmake -E echo "clang-tidy output is available in ${ANALYSIS_FILE_PATH}"
    VERBATIM
    )

endfunction()
