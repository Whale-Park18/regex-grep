# CMake 최소 버전
cmake_minimum_required(VERSION 3.16)

# 프로젝트 이름
project(
    regex_grep
    VERSION 1.0.0
    DESCRIPTION "A simple regex grep tool"
    LANGUAGES CXX
)

# 1. C++ 표준 설정
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. 외부 패키지 찾기
find_package(ICU REQUIRED COMPONENTS uc i18n)
find_package(spdlog CONFIG REQUIRED)

# 3. include 헤더 디렉토리 설정
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 4. 하위 디렉토리 추가
add_subdirectory(src)