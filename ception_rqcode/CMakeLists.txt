cmake_minimum_required(VERSION 3.8)
project(ception_rqcode)






# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(ZXing REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

#INCLUDE_DIRECTORIES(/usr/local/include/ZXing)
#INCLUDE_DIRECTORIES(/usr/local/include/ZXing/)
#LINK_DIRECTORIES(/usr/local/lib/)
add_executable(rqcode_reader src/ception_rqcode_reader.cpp)
#target_link_libraries(rqcode_reader /usr/local/lib/libZXing.so)

# target_link_directories(/usr/local/lib/)

ament_target_dependencies(rqcode_reader rclcpp std_msgs sensor_msgs ZXing)

message("CMAKE_INSTALL_PREFIX:${CMAKE_INSTALL_PREFIX}")

install(TARGETS
  rqcode_reader
  DESTINATION lib/${PROJECT_NAME})


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()
ament_export_dependencies(ZXing)
ament_package()
