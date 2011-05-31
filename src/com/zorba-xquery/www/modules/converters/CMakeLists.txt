# Copyright 2006-2008 The FLWOR Foundation.
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

# libTidy is required
IF(ZORBA_SUPPRESS_LIBTIDY)
  MESSAGE(STATUS "ZORBA_SUPPRESS_LIBTIDY is true - not searching for libTidy.")
ELSE(ZORBA_SUPPRESS_LIBTIDY)
  IF(WIN32)
    INCLUDE (${PROJECT_SOURCE_DIR}/cmake_modules/Windows/FindLibTidy.cmake)
  ELSE(WIN32)
    INCLUDE (${PROJECT_SOURCE_DIR}/cmake_modules/FindLibTidy.cmake)
  ENDIF(WIN32)
  
  IF(LIBTIDY_FOUND)
    SET(HTML_LINK_LIBRARIES ${LIBTIDY_LIBRARIES})

    SET(BUILD_MODULE 1)

    INCLUDE_DIRECTORIES(${LIBTIDY_INCLUDE_DIR})

    INCLUDE_DIRECTORIES("html.xq.src")

    IF (BUILD_MODULE)
      GENERATE_MODULE_LIBRARY(html "${LIBTIDY_LIBRARIES}")
    ENDIF (BUILD_MODULE)

    ADD_TEST_DIRECTORY("${PROJECT_SOURCE_DIR}/test_html")

  ELSE(LIBTIDY_FOUND)
    MESSAGE(STATUS "LibTidy library not found -- if you want to use HTML Tidy functionality please set LIBTIDY_INCLUDE_DIR and LIBTIDY_LIBRARIES cmake parameters.")
  ENDIF(LIBTIDY_FOUND)
ENDIF(ZORBA_SUPPRESS_LIBTIDY)


# libxml and libxslt
IF(ZORBA_SUPPRESS_LIBXSLT)
  MESSAGE(STATUS "ZORBA_SUPPRESS_LIBXSLT is true - not searching for libxslt.")
ELSE(ZORBA_SUPPRESS_LIBXSLT)

  #
  #  LibXml2 required by libxslt
  #
  IF(NOT LIBXML2_FOUND)
  
    MESSAGE(STATUS "Looking for LibXml2")
    
    IF(WIN32)
      INCLUDE (${CMAKE_SOURCE_DIR}/cmake_modules/Windows/FindLibXml2.cmake)
    ELSE(WIN32)
      FIND_PACKAGE(LibXml2)
    ENDIF(WIN32)
    
  ENDIF(NOT LIBXML2_FOUND)
         
  IF(LIBXML2_FOUND)
    MESSAGE(STATUS "Found LIBXML2 library -- " ${LIBXML2_LIBRARIES})
      
    INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
    SET(requiredlibs-store ${requiredlibs-store} ${LIBXML2_LIBRARIES})
    SET(CXXFLAGS ${CXXFLAGS} ${LIBXML2_DEFINITONS})
  ELSE(LIBXML2_FOUND)
    MESSAGE(FATAL_ERROR "The libxml2 library and headers are required in order to build xslt module.")
  ENDIF(LIBXML2_FOUND)

#
#  LibXslt
#
  MESSAGE(STATUS "Looking for LibXslt")
  IF(WIN32)
    INCLUDE (${PROJECT_SOURCE_DIR}/cmake_modules/Windows/FindLibXslt.cmake)
  ELSE(WIN32)
    FIND_PACKAGE(LibXslt)
  ENDIF(WIN32)

  IF(LIBXSLT_FOUND)
    MESSAGE(STATUS "Found LIBXSLT library -- " ${LIBXSLT_LIBRARIES})

    INCLUDE_DIRECTORIES(${LIBXSLT_INCLUDE_DIR})
    SET(requiredlibs ${requiredlibs} ${LIBXSLT_LIBRARIES})
    SET(CXXFLAGS ${CXXFLAGS} ${LIBXSLT_DEFINITONS})

    INCLUDE_DIRECTORIES("xslt.xq.src")

    IF (BUILD_MODULE)
      GENERATE_MODULE_LIBRARY(xslt "${LIBXSLT_LIBRARIES}")
    ENDIF (BUILD_MODULE)

    ADD_TEST_DIRECTORY("${PROJECT_SOURCE_DIR}/test_xslt")

  ELSE(LIBXSLT_FOUND)
    MESSAGE(STATUS "LibXslt library not found -- if you want to use XSLT functionality please set LIBXSLT_INCLUDE_DIR and LIBXSLT_LIBRARIES cmake parameters.")
  ENDIF(LIBXSLT_FOUND)
ENDIF(ZORBA_SUPPRESS_LIBXSLT)


GENERATE_MODULE_LIBRARY(csv "")

#add unit test for streambuf implementation in csv, related to streamable strings
CREATE_TEST_SOURCELIST(StreambufUnitTests StreambufUnitTests.cpp
						streambuftest.cpp
						)
ADD_EXECUTABLE("StreambufUnitTests" ${StreambufUnitTests} csv.xq.src/stringiterator_streambuf.cpp)
ADD_TEST("streamable_string_streambuf" StreambufUnitTests "streambuftest")


# Jansson is required
IF(ZORBA_SUPPRESS_JANSSON)
  MESSAGE(STATUS "ZORBA_SUPPRESS_JANSSON is true - not searching for Jansson.")
ELSE(ZORBA_SUPPRESS_JANSSON)

    INCLUDE (${PROJECT_SOURCE_DIR}/cmake_modules/FindJansson.cmake)  
     
  IF(Jansson_FOUND)
    SET(JSON_LINK_LIBRARIES ${Jansson_LIBRARIES})

    SET(BUILD_MODULE 1)

    INCLUDE_DIRECTORIES(${Jansson_INCLUDE_DIRS})

    INCLUDE_DIRECTORIES("json.xq.src")

    IF (BUILD_MODULE)
      GENERATE_MODULE_LIBRARY(json "${Jansson_LIBRARIES}")
    ENDIF (BUILD_MODULE)

    ADD_TEST_DIRECTORY("${PROJECT_SOURCE_DIR}/test_json")

  ELSE(Jansson_FOUND)
    MESSAGE(STATUS "Jansson library not found -- if you want to use Json functionality please set Jansson_INCLUDE_DIRS and Jansson_LIBRARIES cmake parameters.")
  ENDIF(Jansson_FOUND)
ENDIF(ZORBA_SUPPRESS_JANSSON)