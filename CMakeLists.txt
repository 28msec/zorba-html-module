# Copyright 2006-2010 The FLWOR Foundation.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

MESSAGE(STATUS "")
MESSAGE(STATUS "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
MESSAGE(STATUS "Configuring external module <html>")
MESSAGE(STATUS "-------------------------------------------------------------")
MESSAGE(STATUS "")

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT (zorba_html_module)
ENABLE_TESTING ()
INCLUDE (CTest)

IF (WIN32)
  # On Windows we use proxy modules that try to guess first the location
  # of the required third party libraries. This will search in order in:
  # 1. the path pointed by ZORBA_THIRD_PARTY_REQUIREMENTS
  # 2. the Program Files directory available on the users computer
  # 3. the PATH environment variable
  # The logic is implemented by the macros in the ProxyFindModule.cmake module.
  LIST (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules/Windows")
ENDIF (WIN32)
LIST (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")

FIND_PACKAGE (Zorba REQUIRED HINTS "${ZORBA_BUILD_DIR}")
MESSAGE(STATUS "Zorba_USE_FILE ${Zorba_USE_FILE}")
INCLUDE ("${Zorba_USE_FILE}")

#
# LibTidy
#
IF (ZORBA_SUPPRESS_LIBTIDY)
  MESSAGE (STATUS "ZORBA_SUPPRESS_LIBTIDY is true - not searching for LibTidy.")
  
  MESSAGE(STATUS "")
  MESSAGE(STATUS "-------------------------------------------------------------")  
  MESSAGE(STATUS "Configuration SUPPRESSED for external module <html>")
  
ELSE (ZORBA_SUPPRESS_LIBTIDY)

  MESSAGE (STATUS "Looking for LibTidy")
  FIND_PACKAGE (LibTidy)
  
  IF (LIBTIDY_FOUND)
    MESSAGE (STATUS "Found LibTidy library -- " ${LIBTIDY_LIBRARIES})
    SET (HTML_LINK_LIBRARIES ${LIBTIDY_LIBRARIES})

    INCLUDE_DIRECTORIES (${LIBTIDY_INCLUDE_DIR})
    INCLUDE_DIRECTORIES ("html.xq.src")
    
    ADD_SUBDIRECTORY("src")    
    ADD_TEST_DIRECTORY ("${PROJECT_SOURCE_DIR}/test")

    ADD_TEST(zorba_html_module/link_crawler_test_for_compilation "${ZORBA_EXE}" -f -q "${PROJECT_SOURCE_DIR}/test/Queries/link_crawler2.xq2" --compile-only)
    
    MESSAGE(STATUS "")
    MESSAGE(STATUS "-------------------------------------------------------------")
    MESSAGE(STATUS "Configuration SUCCEEDED for external module <html>")
    
  ELSE (LIBTIDY_FOUND)
    MESSAGE (STATUS "LibTidy library not found -- if you want to use HTML Tidy functionality please set LIBTIDY_INCLUDE_DIR and LIBTIDY_LIBRARIES cmake parameters.")
    SET_PROPERTY (GLOBAL PROPERTY ZORBA_PROJECT_UNAVAILABLE 1)
    
    MESSAGE(STATUS "")
    MESSAGE(STATUS "-------------------------------------------------------------")  
    MESSAGE(STATUS "Configuration FAILED for external module <html>")
    
  ENDIF (LIBTIDY_FOUND)
ENDIF (ZORBA_SUPPRESS_LIBTIDY)

DONE_DECLARING_ZORBA_URIS()
MESSAGE(STATUS "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
