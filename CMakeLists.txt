cmake_minimum_required(VERSION 3.5)

project(sql-studio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

if (APPLE)
    # qt
    set(CMAKE_PREFIX_PATH "/Users/dingrui/Qt/6.7.0/macos")
    # openssl
    set(OPENSSL_DIR "/usr/local/Cellar/openssl@3/3.3.1")
endif ()

# 查找Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
# 查找OpenSSL
find_package(OpenSSL REQUIRED)

option(TEST_DEBUG "调试日志开关" OFF)

if (TEST_DEBUG)
    add_definitions(-DTEST_DEBUG)
endif ()

# unit test
option(UNIT_TEST "unit test" OFF)
if (UNIT_TEST)
    # 在项目的top level开启ctest
    enable_testing()
    add_subdirectory(tests)
endif ()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 源码
aux_source_directory(. PROJECT_SOURCES)
# 头文件搜索路径
include_directories(
        # 自定义的库
        ${CMAKE_CURRENT_SOURCE_DIR}/mysql/include
        # OpenSSL库的头文件路径
        ${OPENSSL_DIR}/include
)

add_subdirectory(mysql)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET sql-studio APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(${PROJECT_NAME} SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(${PROJECT_NAME}
                ${PROJECT_SOURCES}
        )
    endif ()
endif ()


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.sql-studio)
endif ()
set_target_properties(${PROJECT_NAME} PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif ()

# 库文件路径
target_link_directories(${PROJECT_NAME}
        # 自定义的库文件
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/mysql/lib
        # OpenSSL库文件
        PRIVATE ${OPENSSL_DIR}/lib
)
# 链接库
target_link_libraries(${PROJECT_NAME}
        # Qt
        PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
        # 自己编译的库文件
        PRIVATE mysql-client
        # OpenSSl的库libssl.a
        PRIVATE ssl
)