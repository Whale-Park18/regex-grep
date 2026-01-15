add_executable(${PROJECT_NAME} main.cpp regex_grep.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    spdlog::spdlog
    ICU::uc
    ICU::i18n
)