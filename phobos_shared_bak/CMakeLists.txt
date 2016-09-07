cmake_minimum_required(VERSION 2.8.3)
project(phobos_shared)

find_package(catkin REQUIRED COMPONENTS
    message_generation
    std_msgs
)


add_message_files(
  FILES
  JointsState16.msg
  ArmVel16.msg
  WheelsVel16.msg
  EncodersAll.msg
  EncodersArm.msg
  EncodersRockerBogie.msg
  EncodersWheels.msg
  TeleopWheels.msg
  TeleopArm.msg
  TeleopWheelsFloat.msg
  TeleopArmFloat.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs  # Or other packages containing msgs
)
catkin_package(
  CATKIN_DEPENDS message_runtime
)

add_executable(header_test
    src/header_test/Main.cpp)
target_link_libraries(header_test ${catkin_LIBRARIES})
