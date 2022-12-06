cmake_minimum_required(VERSION 3.5)
project(CFS_CI_LAB C)

aux_source_directory(fsw/src APP_SRC_FILES)

# Create the app module
add_cfe_app(ci_lab ${APP_SRC_FILES})

# This permits direct access to public headers in the fsw/inc dir
target_include_directories(ci_lab PUBLIC fsw/inc)