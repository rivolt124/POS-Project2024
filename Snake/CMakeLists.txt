cmake_minimum_required(VERSION 3.10)
project(Snake)

set(CMAKE_C_STANDARD 99)

# Add subdirectories
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(Assets)

# Add the main executable
add_executable(Snake main.c)

# Link libraries or targets from subdirectories (if needed)
# Example: target_link_libraries(Snake ClientLibrary ServerLibrary)
