#pragma once
#include <string>
#include <string_view>
#include <vector>

#include <Windows.h>
#include <spdlog/spdlog.h>

inline std::wstring AtoW(std::string_view src, UINT encoding = CP_ACP)
{
    std::wstring buffer;

    do
    {
        // 빈 입력 빠르게 처리
        if (src.empty())
        {
            break;
        }

        // 플래그: UTF-8 변환의 경우 오류 감지를 위해 MB_ERR_INVALID_CHARS 권장
        DWORD flags = MB_PRECOMPOSED;
        if (encoding == CP_UTF8)
        {
            flags = MB_ERR_INVALID_CHARS;
        }

        // 버퍼 길이 확인
        int needBufferSize = MultiByteToWideChar(encoding, flags, src.data(), static_cast<int>(src.size()), nullptr, 0);
        if (needBufferSize == 0)
        {
            spdlog::error("MultiByteToWideChar failed to get buffer size. Error code: {}", GetLastError());
            break;
        }

        // 결과 문자열을 정확한 길이로 확보하고 변환
        buffer.resize(static_cast<size_t>(needBufferSize));
        int converted = MultiByteToWideChar(encoding, flags, src.data(), static_cast<int>(src.size()), buffer.data(), buffer.size());
        if (converted == 0)
        {
            spdlog::error("MultiByteToWideChar failed to convert string. Error code: {}", GetLastError());
            break;
        }

    } while (false);

    return buffer;
}