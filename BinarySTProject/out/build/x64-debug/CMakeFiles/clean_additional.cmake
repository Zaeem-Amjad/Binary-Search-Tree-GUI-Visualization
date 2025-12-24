# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BinarySTProject_autogen"
  "CMakeFiles\\BinarySTProject_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BinarySTProject_autogen.dir\\ParseCache.txt"
  )
endif()
