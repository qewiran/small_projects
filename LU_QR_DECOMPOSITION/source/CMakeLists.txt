

set (SOURCES main.cpp Matrix.cpp ${CMAKE_INCLUDE_PATH}/Matrix.h)
set(SOURCES ${SOURCES} LU_Decomposer.cpp ${CMAKE_INCLUDE_PATH}/LU_Decomposer.h)
set(SOURCES ${SOURCES} GR_Decomposer.cpp GR_Decomposer.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_INCLUDE_PATH})