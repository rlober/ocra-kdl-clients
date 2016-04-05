cmake_minimum_required(VERSION 2.8.3)
project(ocra-kdl-clients CXX)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  roscpp
)

find_package(OROCOS-RTT REQUIRED)
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)
orocos_use_package(rtt_ros_kdl_tools)
orocos_use_package(rtt_rosclock)
orocos_use_package(ocra-kdl)

find_package(YCM REQUIRED)
find_package(OcraRecipes REQUIRED)

list(APPEND CMAKE_MODULE_PATH
        ${YARP_MODULE_PATH}
        ${YCM_MODULE_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules
     )

catkin_package(INCLUDE_DIRS example-client/include)

include_directories(
    ${catkin_INCLUDE_DIRS}
    ${USE_OROCOS_INCLUDE_DIRS}
)

add_subdirectory(example-client)


include(AddUninstallTarget)
