#include "regex_grep.hpp"

#include <fstream>
#include <system_error>

#include <spdlog/spdlog.h>

regex_grep::regex_grep(const std::filesystem::path& input_file_path)
{
	this->load(input_file_path);
}

bool regex_grep::extract(const std::wregex& regex)
{
	if (this->log_list.empty())
	{
		spdlog::error("Log list is empty");
		return false;
	}

	this->extract_list.clear();
	for (const auto& line : this->log_list)
	{
		if (std::regex_search(line, regex))
		{
			this->extract_list.emplace_back(line);
		}
	}

	return true;
}

bool regex_grep::save(const std::filesystem::path& output_file_path)
{
	std::wofstream ofs(output_file_path, std::ios::out | std::ios::trunc);
	if (ofs.fail())
	{
		spdlog::error("Failed create output file: {}", output_file_path.string());
		return false;
	}

	for (const auto& line : this->extract_list)
	{
		ofs << line << std::endl;
	}
	ofs.close();

	return true;
}

void regex_grep::load(const std::filesystem::path& input_file_path)
{
	do
	{
		if (std::filesystem::exists(input_file_path) == false)
		{
			spdlog::error("File not found: {}", input_file_path.string());
			break;
		}

		if (std::filesystem::is_directory(input_file_path))
		{
			spdlog::error("File is directory: {}", input_file_path.string());
			break;
		}

		if (std::filesystem::is_regular_file(input_file_path) == false)
		{
			spdlog::error("File is not regular file: {}", input_file_path.string());
			break;
		}

		std::wifstream ifs(input_file_path);
		if (ifs.fail())
		{
			spdlog::error("Failed open input file: {}", input_file_path.string());
			break;
		}

		std::wstring line;
		while (std::getline(ifs, line))
		{
			this->log_list.emplace_back(line);
		}
		ifs.close();

	} while (false);
}
