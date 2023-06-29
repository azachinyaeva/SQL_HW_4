cmake_minimum_required(VERSION 3.2)
project(HW_SQL_4)
set(PostgreSQL_ADDITIONAL_VERSIONS "15")
set(SOURCE_FILES
        DB.cpp
        DB.h)

add_executable(HW_SQL_4 main.cpp ${SOURCE_FILES})
add_subdirectory("D:\\Dev\\libpqxx-7.7.5" libpqxx-build)
target_link_libraries (HW_SQL_4 pqxx)
target_compile_features (HW_SQL_4 PRIVATE cxx_std_17)