# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/MNote_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/MNote_autogen.dir/ParseCache.txt"
  "MNote_autogen"
  )
endif()
