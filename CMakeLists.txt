cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(vitacontrol)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -fno-rtti -fno-exceptions")

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/controller.cpp
  src/controllers/dualshock3_controller.cpp
  src/controllers/dualshock4_controller.cpp
  src/controllers/dualsense_controller.cpp
  src/controllers/xbox_one_controller.cpp
  src/controllers/xbox_one_controller_2016.cpp
  src/controllers/switch_pro_controller.cpp
)

target_link_libraries(${PROJECT_NAME}
  SceBtForDriver_stub
  SceCtrlForDriver_stub
  SceSysclibForDriver_stub
  SceSysmemForDriver_stub
  SceThreadmgrForDriver_stub
  taihenForKernel_stub
  ScePower_stub 
  SceKernelSuspendForDriver_stub 
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_FLAGS "-nostdlib"
)

vita_create_self(${PROJECT_NAME}.skprx ${PROJECT_NAME}
  CONFIG vitacontrol.yml
  UNSAFE
)
