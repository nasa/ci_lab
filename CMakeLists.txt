cmake_minimum_required(VERSION 3.5)
project(CFS_CI_LAB C)

set(APP_SRC_FILES
    fsw/src/ci_lab_app.c
    fsw/src/ci_lab_cmds.c
    fsw/src/ci_lab_dispatch.c
    fsw/src/ci_lab_passthru_decode.c
)

# Create the app module
add_cfe_app(ci_lab ${APP_SRC_FILES})

target_include_directories(ci_lab PUBLIC fsw/inc)
