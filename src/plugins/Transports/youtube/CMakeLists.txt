project(libyoutube)

cmake_minimum_required(VERSION 2.4.7)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
    cmake_policy(SET CMP0005 NEW)
endif(COMMAND cmake_policy) 

# qt plugin
ADD_DEFINITIONS( -Wall )
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_SHARED)
ADD_DEFINITIONS(-DQT_THREAD)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

SET(QT_INCLUDES
  ${QT_INCLUDES}
  ${CMAKE_CURRENT_BINARY_DIR}/../../../
)

# libqmmp
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../../qmmp)

#########################################
# libcurl
#pkg_search_module(CURL libcurl)
find_package(CURL)
# this is the top level directory of your build tree 
MESSAGE( STATUS "USE_CURL:         " ${USE_CURL} )
# this is the top level directory of your build tree 
MESSAGE( STATUS "CURL_FOUND:       " ${CURL_FOUND} )

########################################

include_directories(${CURL_INCLUDE_DIRS})
link_directories(${CURL_LIBRARY_DIRS})
ADD_DEFINITIONS(${CURL_CFLAGS})

# libenca
IF(USE_ENCA AND ENCA_FOUND)
ADD_DEFINITIONS(-DWITH_ENCA)
include_directories(${ENCA_INCLUDE_DIRS})
link_directories(${ENCA_LIBRARY_DIRS})
ENDIF(USE_ENCA AND ENCA_FOUND)

SET(libyoutube_SRCS
    youtubestreamreader.cpp
    youtubeinputfactory.cpp
    youtubeinputsource.cpp
    settingsdialog.cpp
)

SET(libyoutube_MOC_HDRS
    youtubeinputfactory.h
    youtubeinputsource.h
    youtubestreamreader.h
    settingsdialog.h
)

# resources
SET(libyoutube_RCCS translations/translations.qrc)
QT4_ADD_RESOURCES(libyoutube_RCC_SRCS ${libyoutube_RCCS})

# user interface
SET(libyoutube_UIS
    settingsdialog.ui
)
QT4_WRAP_UI(libyoutube_UIS_H ${libyoutube_UIS})



QT4_WRAP_CPP(libyoutube_MOC_SRCS ${libyoutube_MOC_HDRS})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
include_directories(${CMAKE_CURRENT_BINARY_DIR})

IF(CURL_FOUND)
ADD_LIBRARY(youtube MODULE ${libyoutube_SRCS} ${libyoutube_MOC_SRCS} ${libyoutube_UIS_H} ${libyoutube_RCC_SRCS})

IF(USE_ENCA AND ENCA_FOUND)
target_link_libraries(youtube ${QT_LIBRARIES} -lqmmp -lcurl ${CURL_LDFLAGS} ${CURL_CFLAGS} ${ENCA_LDFLAGS} ${ENCA_CFLAGS})
ELSE(USE_ENCA AND ENCA_FOUND)
target_link_libraries(youtube ${QT_LIBRARIES} -lqmmp -lcurl ${CURL_LDFLAGS})
ENDIF(USE_ENCA AND ENCA_FOUND)

add_dependencies(youtube qmmp)
install(TARGETS youtube DESTINATION ${LIB_DIR}/qmmp/Transports)
ENDIF(CURL_FOUND)
