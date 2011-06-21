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

#
# LibTidy
#
IF (ZORBA_SUPPRESS_LIBTIDY)
  MESSAGE (STATUS "ZORBA_SUPPRESS_LIBTIDY is true - not searching for LibTidy.")
ELSE (ZORBA_SUPPRESS_LIBTIDY)

  MESSAGE (STATUS "Looking for LibTidy")
  FIND_PACKAGE (LibTidy)
  
  IF (LIBTIDY_FOUND)
    MESSAGE (STATUS "Found LibTidy library -- " ${LIBTIDY_LIBRARIES})
    SET (HTML_LINK_LIBRARIES ${LIBTIDY_LIBRARIES})

    INCLUDE_DIRECTORIES (${LIBTIDY_INCLUDE_DIR})
    INCLUDE_DIRECTORIES ("html.xq.src")
    GENERATE_MODULE_LIBRARY (html "${LIBTIDY_LIBRARIES}")
    ADD_TEST_DIRECTORY ("${PROJECT_SOURCE_DIR}/test_html")

  ELSE (LIBTIDY_FOUND)
    MESSAGE (STATUS "LibTidy library not found -- if you want to use HTML Tidy functionality please set LIBTIDY_INCLUDE_DIR and LIBTIDY_LIBRARIES cmake parameters.")
  ENDIF (LIBTIDY_FOUND)
ENDIF (ZORBA_SUPPRESS_LIBTIDY)


#
# LibXslt (requires LibXml2)
#
IF (ZORBA_SUPPRESS_LIBXSLT)
  MESSAGE (STATUS "ZORBA_SUPPRESS_LIBXSLT is true - not searching for LibXslt.")
ELSE (ZORBA_SUPPRESS_LIBXSLT)

  #
  # LibXml2
  #
  IF (NOT LIBXML2_FOUND)
    MESSAGE (STATUS "Looking for LibXml2")
    FIND_PACKAGE (LibXml2)
  ENDIF (NOT LIBXML2_FOUND)
         
  IF (LIBXML2_FOUND)
    MESSAGE (STATUS "Found LibXml2 library -- " ${LIBXML2_LIBRARIES})
      
    INCLUDE_DIRECTORIES (${LIBXML2_INCLUDE_DIR})
    SET (requiredlibs-store ${requiredlibs-store} ${LIBXML2_LIBRARIES})
    SET (CXXFLAGS ${CXXFLAGS} ${LIBXML2_DEFINITONS})

  ELSE (LIBXML2_FOUND)
    MESSAGE (FATAL_ERROR "The libxml2 library and headers are required in order to build xslt module.")
  ENDIF (LIBXML2_FOUND)

  #
  # LibXslt
  #
  MESSAGE (STATUS "Looking for LibXslt")
  FIND_PACKAGE (LibXslt)

  IF (LIBXSLT_FOUND)
    MESSAGE (STATUS "Found LibXslt library -- " ${LIBXSLT_LIBRARIES})

    INCLUDE_DIRECTORIES (${LIBXSLT_INCLUDE_DIR})
    SET (requiredlibs ${requiredlibs} ${LIBXSLT_LIBRARIES})
    SET (CXXFLAGS ${CXXFLAGS} ${LIBXSLT_DEFINITONS})
    INCLUDE_DIRECTORIES ("xslt.xq.src")
    GENERATE_MODULE_LIBRARY (xslt "${LIBXSLT_LIBRARIES}")
    ADD_TEST_DIRECTORY ("${PROJECT_SOURCE_DIR}/test_xslt")

  ELSE (LIBXSLT_FOUND)
    MESSAGE (STATUS "LibXslt library not found -- if you want to use XSLT functionality please set LIBXSLT_INCLUDE_DIR and LIBXSLT_LIBRARIES cmake parameters.")
  ENDIF (LIBXSLT_FOUND)
ENDIF (ZORBA_SUPPRESS_LIBXSLT)


#
# Jansson
#
IF (ZORBA_SUPPRESS_JANSSON)
  MESSAGE (STATUS "ZORBA_SUPPRESS_JANSSON is true - not searching for Jansson.")
ELSE (ZORBA_SUPPRESS_JANSSON)

  MESSAGE (STATUS "Looking for Jansson")
  FIND_PACKAGE (Jansson)
     
  IF (Jansson_FOUND)
    MESSAGE (STATUS "Found Jansson library -- " ${LIBXSLT_LIBRARIES})

    SET (JSON_LINK_LIBRARIES ${Jansson_LIBRARIES})
    INCLUDE_DIRECTORIES (${Jansson_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES ("json.xq.src")
    GENERATE_MODULE_LIBRARY (json "${Jansson_LIBRARIES}")
    ADD_TEST_DIRECTORY ("${PROJECT_SOURCE_DIR}/test_json")

  ELSE (Jansson_FOUND)
    MESSAGE (STATUS "Jansson library not found -- if you want to use Json functionality please set Jansson_INCLUDE_DIRS and Jansson_LIBRARIES cmake parameters.")
  ENDIF (Jansson_FOUND)
ENDIF (ZORBA_SUPPRESS_JANSSON)


# csv
GENERATE_MODULE_LIBRARY (csv "")

# add unit test for streambuf implementation in csv, related to streamable strings
CREATE_TEST_SOURCELIST(
  StreambufUnitTests
  StreambufUnitTests.cpp
  streambuftest.cpp
)
ADD_EXECUTABLE ("StreambufUnitTests" ${StreambufUnitTests} csv.xq.src/stringiterator_streambuf.cpp)
ADD_TEST ("streamable_string_streambuf" StreambufUnitTests "streambuftest")
