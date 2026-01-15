#include <string.hpp>
#include <regex_grep.hpp>

#include <spdlog/spdlog.h>

#include <stdexcept>
#include <filesystem>
#include <regex>

enum class arguments : int
{
    program_path     = 0,
    input_file_path  = 1,
    output_file_path = 2,
    regex_pattern    = 3,
    __max__
};

template <arguments arg>
auto get_argument(char* argv[])
{
    if constexpr (arg == arguments::input_file_path)
    {
        return std::filesystem::path(argv[static_cast<int>(arguments::input_file_path)]);
    }
    else if constexpr (arg == arguments::output_file_path)
    {
        return std::filesystem::path(argv[static_cast<int>(arguments::output_file_path)]);
    }
    else if constexpr (arg == arguments::regex_pattern)
    {
        auto regex_pattern = convert_to_wstring(argv[static_cast<int>(arguments::regex_pattern)], "UTF-8");
        return std::wregex(regex_pattern);
    }
    else
    {
        throw std::invalid_argument("Invalid argument type");
    }
}

int main(int argc, char* argv[])
{
    auto return_code = EXIT_FAILURE;
    try
    {
        if(argc != static_cast<int>(arguments::__max__))
        {
            spdlog::error("Usage: {} <input_file_path> <output_file_path> <regex_pattern>", argv[static_cast<int>(arguments::program_path)]);
            return EXIT_FAILURE;
        }
    
        regex_grep extractor(get_argument<arguments::input_file_path>(argv));
        if(extractor.extract(get_argument<arguments::regex_pattern>(argv)) == false)
        {
            spdlog::error("Failed to extract logs with the given regex pattern.");
            return EXIT_FAILURE;
        }
    
        if (extractor.save(get_argument<arguments::output_file_path>(argv)) == false)
        {
            spdlog::error("Failed to save extracted logs to output file.");
            return EXIT_FAILURE;
        }
        
        return_code = EXIT_SUCCESS;
        spdlog::info("Log extraction completed successfully.");
    }
    catch(const std::exception& e)
    {
        spdlog::error("Exception occurred: {}", e.what());
        return_code = EXIT_FAILURE;
    }

    return return_code;
}