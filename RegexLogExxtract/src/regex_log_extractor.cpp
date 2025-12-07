#include "regex_log_extractor.h"

#include <fstream>
#include <system_error>

#include <spdlog/spdlog.h>

RegexLogExtractor::RegexLogExtractor(const std::filesystem::path& inputFile)
{
	this->Initialized(inputFile);
}

bool RegexLogExtractor::Extract(const std::wregex& filterRegex)
{
	if (this->logList.empty())
	{
		spdlog::error("Log list is empty");
		return false;
	}

	this->extractList.clear();
	for (const auto& line : this->logList)
	{
		if (std::regex_search(line, filterRegex))
		{
			this->extractList.emplace_back(line);
		}
	}

	return true;
}

bool RegexLogExtractor::Save(const std::filesystem::path& outputFile)
{
	std::wofstream ofs(outputFile, std::ios::out | std::ios::trunc);
	if (ofs.fail())
	{
		spdlog::error("Failed create output file: {}", outputFile.string());
		return false;
	}

	for (const auto& line : this->extractList)
	{
		ofs << line << std::endl;
	}
	ofs.close();

	return true;
}

void RegexLogExtractor::Initialized(const std::filesystem::path& inputFile)
{
	do
	{
		if (std::filesystem::exists(inputFile) == false)
		{
			spdlog::error("File not found: {}", inputFile.string());
			break;
		}

		if (std::filesystem::is_directory(inputFile))
		{
			spdlog::error("File is directory: {}", inputFile.string());
			break;
		}

		if (std::filesystem::is_regular_file(inputFile) == false)
		{
			spdlog::error("File is not regular file: {}", inputFile.string());
			break;
		}

		std::wifstream ifs(inputFile);
		if (ifs.fail())
		{
			spdlog::error("Failed open input file: {}", inputFile.string());
			break;
		}

		std::wstring line;
		while (std::getline(ifs, line))
		{
			this->logList.emplace_back(line);
		}
		ifs.close();

	} while (false);
}
