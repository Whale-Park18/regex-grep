#include "regex_log_extractor.h"

#include <spdlog/spdlog.h>
#include <common/string.h>

enum class Argvuments
{
	InputFilePath	= 1,
	OutputFilePath	= 2,
	RegexPattern	= 3
};

// arguments: input_log_file output_log_file regex_pattern
int main(int argc, char* argv[])
{
	int returnCode = -1;

	do
	{
		if (argc != 4)
		{
			spdlog::info("Usage: RegexLogExtract <input_log_file> <output_log_file> <regex_pattern>");
			break;
		}

		RegexLogExtractor extractor(argv[static_cast<int>(Argvuments::InputFilePath)]);

		if (extractor.Extract(std::wregex(AtoW(argv[static_cast<int>(Argvuments::RegexPattern)]))) == false)
		{
			spdlog::error("Failed to extract logs with the given regex pattern.");
			break;
		}

		if (extractor.Save(argv[static_cast<int>(Argvuments::OutputFilePath)]) == false)
		{
			spdlog::error("Failed to save extracted logs to output file.");
			break;
		}

		spdlog::info("Log extraction completed successfully.");
		returnCode = 0;

	} while (false);

	return returnCode;
}