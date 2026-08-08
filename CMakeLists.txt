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
# DLL TARGET
# ==============================================

add_library(
SolarUI
SHARED
${SOLARUI_SOURCES}
)

# ==============================================
# DLL EXPORT DEFINE
# ==============================================

target_compile_definitions(
SolarUI

PRIVATE
    SOLARUI_BUILD_DLL

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