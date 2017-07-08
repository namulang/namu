CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\tbuilding macro...")
message("\t\tconfigure_files...")
configure_file(BuildInformation.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/BuildInformation.hpp)