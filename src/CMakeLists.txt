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
    DECLARE_ZORBA_SCHEMA (FILE "html-options.xsd"
      URI "http://www.zorba-xquery.com/modules/converters/html-options")
    DECLARE_ZORBA_MODULE (URI "http://www.zorba-xquery.com/modules/converters/html" VERSION 1.0 FILE "html.xq" LINK_LIBRARIES "${LIBTIDY_LIBRARIES}")
    ADD_TEST_DIRECTORY ("${PROJECT_SOURCE_DIR}/test")

    ADD_TEST(zorba_html_module/link_crawler_test_for_compilation "${ZORBA_EXE}" -f -q "${PROJECT_SOURCE_DIR}/test/Queries/link_crawler2.xq2" --compile-only)
  ELSE (LIBTIDY_FOUND)
    MESSAGE (STATUS "LibTidy library not found -- if you want to use HTML Tidy functionality please set LIBTIDY_INCLUDE_DIR and LIBTIDY_LIBRARIES cmake parameters.")
  ENDIF (LIBTIDY_FOUND)
ENDIF (ZORBA_SUPPRESS_LIBTIDY)
MESSAGE (STATUS "")

