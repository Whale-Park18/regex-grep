#include <unicode/ucnv.h>
#include <unicode/ustring.h>

#include <string>
#include <string_view>
#include <stdexcept>
#include <format>

inline std::wstring convert_to_wstring(const std::string& str, const std::string_view from_encoding)
{
    UErrorCode status = U_ZERO_ERROR;
    UConverter* converter = ucnv_open(from_encoding.data(), &status);
    if (U_FAILURE(status))
    {
        throw std::runtime_error(std::format("Failed to open converter for encoding: {}", from_encoding));
    }

    int32_t required_size = ucnv_toUChars(converter, nullptr, 0, str.c_str(), static_cast<int32_t>(str.size()), &status);
    if (status != U_BUFFER_OVERFLOW_ERROR && U_FAILURE(status))
    {
        ucnv_close(converter);
        throw std::runtime_error("Failed to get required size for conversion.");
    }

    status = U_ZERO_ERROR;
    std::wstring result(required_size, L'\0');
    ucnv_toUChars(converter, reinterpret_cast<UChar*>(result.data()), required_size, str.c_str(), static_cast<int32_t>(str.size()), &status);
    if (U_FAILURE(status))
    {
        ucnv_close(converter);
        throw std::runtime_error("Failed to convert string to wstring.");
    }

    ucnv_close(converter);
    return result;
}