#include <regex>
#include <string>
#include <vector>
#include <filesystem>


class RegexLogExtractor
{
public:
	RegexLogExtractor(const std::filesystem::path& inputFile);

	bool Extract(const std::wregex& filterRegex);

	bool Save(const std::filesystem::path& outputFile);

private:

	void Initialized(const std::filesystem::path& inputFile);

	std::vector<std::wstring> logList;
	std::vector<std::wstring> extractList;
};