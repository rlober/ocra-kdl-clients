project(example-client CXX)

file(GLOB folder_source src/*.cpp)
file(GLOB folder_header include/${PROJECT_NAME}/*.h)

source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})

include_directories(
${YARP_INCLUDE_DIRS}
${OcraRecipes_INCLUDE_DIRS}
${OcraIcub_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${folder_source} ${folder_header})

list(APPEND link_libs   ${OcraRecipes_LIBRARIES}
                        ${USE_OROCOS_LIBRARIES}
                        ${catkin_LIBRARIES}
                        )

target_link_libraries(${PROJECT_NAME} ${link_libs})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
