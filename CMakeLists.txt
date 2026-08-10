cmake_minimum_required(VERSION 3.20)

project(SolarUI
VERSION 1.0
LANGUAGES C
)

# ==============================================
# C STANDARD
# ==============================================

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ==============================================
# EXTERNAL LIBRARY PATHS
# ==============================================

set(FREEGLUT_DIR
${PROJECT_SOURCE_DIR}/src/external/freeglut-3.0.0
)

set(LIBVLC_DIR
${PROJECT_SOURCE_DIR}/src/external/libVLC
)

# ==============================================
# SOURCE FILES
# ==============================================

set(SOLARUI_SOURCES

src/Solar_UI.c

src/internal/Solar_UI_Manager.c
src/internal/Solar_UI_Render.c
src/internal/Solar_UI_Input.c
src/internal/Solar_UI_Media.c

src/bridges/Solar_UI_freeGlut_Bridge.c
src/bridges/Solar_UI_Input_Bridge.c

src/Elements/Button/Button.c
src/Elements/Checkbox/Checkbox.c
src/Elements/Dropdown/Dropdown.c
src/Elements/Image/Image.c
src/Elements/InputBox/InputBox.c
src/Elements/Label/Label.c
src/Elements/Slider/Slider.c
src/Elements/Video/Video.c

)

# ==============================================
# BUILD OPTIONS
# ==============================================

option(SOLARUI_BUILD_SHARED "Build SolarUI as a shared library (DLL)" ON)

if(SOLARUI_BUILD_SHARED)
    set(SOLARUI_LIB_TYPE SHARED)
else()
    set(SOLARUI_LIB_TYPE STATIC)
endif()

# ==============================================
# DLL TARGET
# ==============================================

add_library(
SolarUI
${SOLARUI_LIB_TYPE}
${SOLARUI_SOURCES}
)

# ==============================================
# DLL EXPORT DEFINE
# ==============================================

target_compile_definitions(
SolarUI

PRIVATE
    SOLARUI_BUILD_DLL

PUBLIC
    $<$<NOT:$<BOOL:${SOLARUI_BUILD_SHARED}>>:SOLARUI_STATIC>

)

# ==============================================
# INCLUDE DIRECTORIES
# ==============================================

target_include_directories(
SolarUI

PUBLIC
    ${PROJECT_SOURCE_DIR}/include

PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/external

    # FreeGLUT
    ${FREEGLUT_DIR}/include

    # LibVLC
    ${LIBVLC_DIR}/include

)

# ==============================================
# OPENGL
# ==============================================

find_package(OpenGL REQUIRED)

target_link_libraries(
SolarUI

PRIVATE
    OpenGL::GL

)

# ==============================================
# FREEGLUT
# ==============================================

target_link_directories(
SolarUI

PRIVATE
    ${FREEGLUT_DIR}/lib/x64

)

target_link_libraries(
SolarUI

PRIVATE
    freeglut

)

# ==============================================
# LIBVLC
# ==============================================

if(WIN32)

target_link_directories(
    SolarUI

    PRIVATE
        ${LIBVLC_DIR}
)

target_link_libraries(
    SolarUI

    PRIVATE
        libvlc
        libvlccore
)

endif()

#==============================================
# OUTPUT
#==============================================

set_target_properties(
SolarUI

PROPERTIES

    OUTPUT_NAME "SolarUI"

    RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_SOURCE_DIR}/bin

    LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_SOURCE_DIR}/bin

)

# ==============================================
# TEST EXECUTABLE
# ==============================================
# Builds against either SHARED or STATIC SolarUI.
# Only needs "SolarUI.h" - it pulls in every
# element header and the input feed functions
# itself, and both build modes export everything
# it calls.

option(SOLARUI_BUILD_TESTS "Build the SolarUI smoke test" OFF)

if(SOLARUI_BUILD_TESTS)

    enable_language(CXX)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    add_executable(
    SolarUITest
    test/test.cpp
    )

    target_include_directories(
    SolarUITest

    PRIVATE
        ${FREEGLUT_DIR}/include
    )

    target_link_libraries(
    SolarUITest

    PRIVATE
        SolarUI
        OpenGL::GL
    )

    target_link_directories(
    SolarUITest

    PRIVATE
        ${FREEGLUT_DIR}/lib/x64
    )

    target_link_libraries(
    SolarUITest

    PRIVATE
        freeglut
    )

    # A static SolarUI doesn't pull libvlc's symbols
    # in for us - a shared SolarUI already resolved
    # them internally when the DLL itself was built.
    if(NOT SOLARUI_BUILD_SHARED)

        target_include_directories(
        SolarUITest

        PRIVATE
            ${LIBVLC_DIR}/include
        )

        target_link_directories(
        SolarUITest

        PRIVATE
            ${LIBVLC_DIR}
        )

        target_link_libraries(
        SolarUITest

        PRIVATE
            libvlc
            libvlccore
        )

    endif()

    set_target_properties(
    SolarUITest

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
            ${PROJECT_SOURCE_DIR}/bin
    )

endif()