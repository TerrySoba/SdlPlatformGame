#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include <optional>
#include <cstdint>
#include <string>

struct CommandLineParameters
{
    uint32_t screenWidth;
    uint32_t screenHeight;
    std::string sdlRenderer;
    bool fullscreen;
};

std::optional<CommandLineParameters> parseCommandLine(int argc, char* argv[]);

#endif