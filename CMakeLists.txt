cmake_minimum_required(VERSION 3.5)

project(MessengerDesktop LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Quick LinguistTools QuickControls2 Network REQUIRED)
find_library(LIBPHONENUMBER phonenumber HINTS libs/libphonenumber/cpp REQUIRED)

#set(TS_FILES MessengerDesktop_en_US.ts)
set(TS_FILES)


include_directories(Boost::headers)

set(FILES
        src/main.cpp
        src/data/settings.cpp
        src/data/settings.h
        src/misc/phonenumberformatterservice.cpp
        src/misc/phonenumberformatterservice.h
        src/api/api.cpp
        src/api/api.h
        src/qml/qml.qrc
        src/api/promise.cpp
        src/api/promise.h
        src/misc/restarter.cpp src/misc/restarter.h)
if (ANDROID)
    add_library(MessengerDesktop SHARED
            ${FILES}
            ${TS_FILES}
            )
else ()
    add_executable(MessengerDesktop
            ${FILES}
            ${TS_FILES}
            )
endif ()

target_compile_definitions(MessengerDesktop
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(MessengerDesktop
        PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2 Qt5::Network ${LIBPHONENUMBER})
#qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
