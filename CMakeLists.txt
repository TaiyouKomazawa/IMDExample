cmake_minimum_required(VERSION 3.0.0)
project(imd_example VERSION 1.0.0)

include(CTest)
enable_testing()

#ライブラリのあるフォルダを読み込む
add_subdirectory(IMDController)

#check_serialnumberのビルド
add_executable(check_serialnumber check_serialnumber.cpp)
#imd_controllerを実行ファイルにリンクする
target_link_libraries(check_serialnumber imd_controller)

#motor_driveのビルド
add_executable(motor_drive motor_drive.cpp)
#imd_controllerを実行ファイルにリンクする
target_link_libraries(motor_drive imd_controller)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
