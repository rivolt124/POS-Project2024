cmake_minimum_required(VERSION 3.20)
project(Snake)

set(CMAKE_C_STANDARD 99)

# Add the Assets library
add_library(AssetsLibrary STATIC
        Assets/communication.c
        Assets/utils.c
)

# Add the Client library
add_library(ClientLibrary STATIC
        Client/client.c
        Client/inputHandler.c
        Client/menuInterface.c
)

target_include_directories(ClientLibrary PUBLIC Client)
target_link_libraries(ClientLibrary AssetsLibrary)

# Add the Server library
add_library(ServerLibrary STATIC
        Server/gameLogic.c
        Server/mapGenerator.c
        Server/server.c
)

target_include_directories(ServerLibrary PUBLIC Server)
target_link_libraries(ServerLibrary AssetsLibrary)

# Add the main executable
add_executable(Snake main.c)
target_link_libraries(Snake
        AssetsLibrary
        ClientLibrary
        ServerLibrary
)

# Add the server executable
add_executable(server
        Server/server.c
        Assets/communication.c
)

# Add the client executable
add_executable(client
        Client/client.c
        Assets/communication.c
)

# Link libraries to server and client executables
target_link_libraries(server
        AssetsLibrary
        ServerLibrary
)
target_link_libraries(client
        AssetsLibrary
        ClientLibrary
)

# Windows-specific library linking
if(WIN32)
    target_link_libraries(server kernel32 user32)
    target_link_libraries(client kernel32 user32)
    target_link_libraries(Snake kernel32 user32)
endif()

# Install Maps directory if needed
install(DIRECTORY Maps/ DESTINATION maps)
