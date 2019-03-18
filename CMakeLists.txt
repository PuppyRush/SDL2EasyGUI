cmake_minimum_required(VERSION 3.12)
project(SDL2EasyGUI)

SET(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

set(SDL2_PATH "${PROJECT_SOURCE_DIR}/SDL")

set(Boost_INCLUDE_DIR /usr/include)
set(BOOST_SOURCE /usr/include)
set(Boost_LIBRARIES /usr/lib/x86_64-linux-gnu/)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Boost 1.65.1 REQUIRED COMPONENTS system filesystem serialization)
find_package(PkgConfig REQUIRED)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
if (Threads_FOUND)
    message("-- OK.")
else ()
    message(FATAL_ERROR "Threads not found.")
endif ()


include_directories(.)
include_directories(src)
include_directories(src/Command)
include_directories(src/Controller)
include_directories(src/Display)
include_directories(src/Subjector)
include_directories(src/Windows)

include_directories(
        SYSTEM ${Boost_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
)

#configure_file("src/" "../SDL2_Tetris_Client/lib/SDL2EasyGUI" COPYONLY)


file(COPY DIRECTORY "src/"
        DESTINATION "include"
        FILES_MATCHING PATTERN "*.h"
        )


ADD_LIBRARY( SDL2EasyGUI STATIC
    src/Command/Commander.h
    src/Command/EventCommand.h
    src/Controller/Border.cpp
    src/Controller/Border.h
    src/Controller/Button.cpp
    src/Controller/Button.h
    src/Controller/ButtonBasic.cpp
    src/Controller/ButtonBasic.h
    src/Controller/ComboBox.cpp
    src/Controller/ComboBox.h
    src/Controller/Controll.cpp
    src/Controller/Controll.h
    src/Controller/ControllBuilder.cpp
    src/Controller/ControllBuilder.h
    src/Controller/EditLabel.cpp
    src/Controller/EditLabel.h
    src/Controller/GroupControllManager.cpp
    src/Controller/GroupControllManager.h
    src/Controller/ListBox.cpp
    src/Controller/ListBox.h
    src/Controller/RadioButton.cpp
    src/Controller/RadioButton.h
    src/Controller/StaticLabel.cpp
    src/Controller/StaticLabel.h
    src/Display/InputDialog.cpp
    src/Display/InputDialog.h
    src/Display/MessageDialog.cpp
    src/Display/MessageDialog.h
        src/Windows/DisplayController.cpp
    src/Windows/DisplayController.h
    src/Windows/DisplayInterface.cpp
    src/Windows/DisplayInterface.h
    src/Windows/EventDelivery.h
    src/Windows/EventListener.h
    src/Windows/EventQueue.cpp
    src/Windows/EventQueue.h
    src/Windows/GraphicInterface.h
    src/Windows/SEG_Window.cpp
    src/Windows/SEG_Window.h
    src/SEG_Constant.h
    src/SEG_Event.cpp
    src/SEG_Event.h
    src/SEG_Initiator.h
    src/SEG_Property.h
    src/SEG_Quit.h
    src/SEG_Resource.h
    src/SEG_Struct.h
    src/SEG_Type.h
    src/SEG_TypeTraits.h
        src/SEG_Define.h src/Windows/GraphicInterface.cpp)

target_link_libraries(SDL2EasyGUI
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_LIBRARY}
        Threads::Threads)
