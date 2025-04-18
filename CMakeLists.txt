cmake_minimum_required(VERSION 3.16)
project(SdlPlatformGame)

find_package(SDL3 REQUIRED)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
#add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_library(game_lib STATIC
    DosPlatformGame/source/tga_image.cpp
    DosPlatformGame/source/credits_loader.cpp
    DosPlatformGame/source/tiny_string.cpp
    DosPlatformGame/source/font.cpp
    DosPlatformGame/source/font_writer.cpp
    DosPlatformGame/source/blit.cpp
    DosPlatformGame/source/i18n.cpp
    DosPlatformGame/source/exception.cpp
    DosPlatformGame/source/level.cpp
    DosPlatformGame/source/detect_lines.cpp
    DosPlatformGame/source/rectangle.cpp
    DosPlatformGame/source/physics.cpp
    DosPlatformGame/source/time_tools.cpp
    DosPlatformGame/source/sprite.cpp
    DosPlatformGame/source/framebuffer_gfx.cpp
    DosPlatformGame/source/animation.cpp
    DosPlatformGame/source/game.cpp
    DosPlatformGame/source/enemy.cpp
    DosPlatformGame/source/tentacle.cpp
    DosPlatformGame/source/tentacle_arm.cpp
    DosPlatformGame/source/eye.cpp
    DosPlatformGame/source/fire_ball.cpp
    DosPlatformGame/source/boss1.cpp
    DosPlatformGame/source/boss2.cpp
    DosPlatformGame/source/seeker_enemy.cpp
    DosPlatformGame/source/text.cpp
    DosPlatformGame/source/key_mapper.cpp
    DosPlatformGame/source/game_save.cpp


    DosPlatformGame/source/platform/sdl/keyboard_sdl.cpp
    DosPlatformGame/source/platform/sdl/joystick_sdl.cpp

    sdl_gfx.cpp
    commandline_parser.cpp
)

string(TIMESTAMP CMAKE_BUILD_DATE "%Y-%m-%d")
target_compile_definitions(game_lib PRIVATE PLATFORM_SDL BUILD_DATE="${CMAKE_BUILD_DATE}")

#target_compile_options(game_lib PRIVATE -fsanitize=address)
#target_link_options(game_lib PRIVATE -fsanitize=address)

target_include_directories(game_lib PUBLIC DosPlatformGame/source)

# Create your game executable target as usual
add_executable(SdlPlatformGame main.cpp)
target_link_libraries(SdlPlatformGame PRIVATE game_lib)
target_compile_definitions(SdlPlatformGame PRIVATE PLATFORM_SDL BUILD_DATE="${CMAKE_BUILD_DATE}")
target_link_libraries(SdlPlatformGame PRIVATE SDL3::SDL3)

# install(TARGETS SDL3-shared DESTINATION bin)

install(TARGETS SdlPlatformGame DESTINATION bin)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/DosPlatformGame/levels/"
    DESTINATION bin
    FILES_MATCHING PATTERN "*.map"
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/DosPlatformGame/images/"
    DESTINATION bin
    FILES_MATCHING PATTERN "*.tga" PATTERN "*.ani" 
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/DosPlatformGame/text/"
    DESTINATION bin
    FILES_MATCHING PATTERN "*.en" PATTERN "*.de" 
)


set(TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/DosPlatformGame/testdata/")

configure_file(DosPlatformGame/source/test_data.h.in
    DosPlatformGame/source/test_data.h
)


# Create test executable target
add_executable(test
    DosPlatformGame/source/test_main.cpp
    DosPlatformGame/source/test_class.cpp

    # DosPlatformGame/source/animation_test.cpp
    DosPlatformGame/source/blit_test.cpp
    # DosPlatformGame/source/compiled_sprite_test.cpp
    DosPlatformGame/source/sprite_test.cpp
    DosPlatformGame/source/credits_loader_test.cpp
    DosPlatformGame/source/font_test.cpp
    DosPlatformGame/source/font_writer_test.cpp
    DosPlatformGame/source/i18n_test.cpp
    DosPlatformGame/source/level_test.cpp
    DosPlatformGame/source/map_test.cpp
    DosPlatformGame/source/physics_test.cpp
    DosPlatformGame/source/ptr_vector_test.cpp
    DosPlatformGame/source/raii_ptr_test.cpp
    DosPlatformGame/source/rectangle_test.cpp
    DosPlatformGame/source/shared_ptr_test.cpp
    DosPlatformGame/source/text_layout_test.cpp
    DosPlatformGame/source/tga_image_test.cpp
    DosPlatformGame/source/time_tools_test.cpp
    DosPlatformGame/source/tiny_string_test.cpp
    DosPlatformGame/source/unit_test.cpp
    DosPlatformGame/source/vector_test.cpp
)

target_include_directories(test PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/DosPlatformGame/source
)

target_link_libraries(test PRIVATE game_lib)

# Enable AddressSanitizer for the test target
target_compile_options(test PRIVATE -fsanitize=address)
target_link_options(test PRIVATE -fsanitize=address)


