#include <regex>
#include <string>
#include <vector>
#include <filesystem>

class regex_grep
{
public:

	/// @brief input_file_path을 읽어서, logList에 저장하는 생성자
	regex_grep(const std::filesystem::path& input_file_path);

	/// @brief 정규 표현식을 사용하여 logList에서 일치하는 라인을 extractList에 저장
	/// @param regex 정규 표현식
	/// @return true: 성공, false: 실패
	bool extract(const std::wregex& regex);

	/// @brief 추출된 라인을 지정된 출력 파일에 저장
	/// @param output_file_path 추출된 라인을 저장할 출력 파일 경로
	/// @return true: 성공, false: 실패
	bool save(const std::filesystem::path& output_file_path);

private:

	/// @brief 지정된 입력 파일에서 라인들을 로드하여 logList에 저장
	/// @param input_file_path 입력 파일 경로
	void load(const std::filesystem::path& input_file_path);

	std::vector<std::wstring> log_list;
	std::vector<std::wstring> extract_list;
};