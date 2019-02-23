cmake_minimum_required (VERSION 2.8)

project (cros_system_monitor)

aux_source_directory(. DIR_SRCS)

add_executable(cros_system_monitor ${DIR_SRCS})
