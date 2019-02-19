cmake_minimum_required(VERSION 2.8.6)
project(qt_helloworld)

find_package(Qt4 QUIET)

if(QT4_FOUND)

   include(${QT_USE_FILE})

   set(CURR_QT_INCLUDES ${QT_INCLUDES})
   set(CURR_QT_LIBS ${QT_LIBRARIES})
   set(CURR_QT_DEFINITIONS ${QT_DEFINITIONS})
   
   qt4_generate_moc(main.h main_moc.cc)
   
else()
    find_package(Qt5Widgets REQUIRED)
 
    if(Qt5Widgets_FOUND)
   
        set(CURR_QT_INCLUDES ${Qt5Widgets_INCLUDE_DIRS})
        set(CURR_QT_LIBS ${Qt5Widgets_LIBRARIES})
        set(CURR_QT_DEFINITIONS ${Qt5Widgets_DEFINITIONS})
        
        qt5_generate_moc(main.h main_moc.cc)
    
    endif()
endif()

message(STATUS "includes:${CURR_QT_INCLUDES}")
message(STATUS "definitions:${CURR_QT_DEFINITIONS}")
message(STATUS "libraries:${CURR_QT_LIBS}")

include_directories(${CURR_QT_INCLUDES})
add_definitions(${CURR_QT_DEFINITIONS})

add_executable(qt_helloworld main.cc main_moc.cc)
target_link_libraries(qt_helloworld ${CURR_QT_LIBS} pthread)
