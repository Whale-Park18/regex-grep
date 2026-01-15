# regex-grep

`regex-grep`은 정규 표현식을 활용하여 텍스트 데이터에서 특정 패턴을 검색하고 추출하는 도구입니다.

## 주요 기능 (Features)

- **텍스트 추출 (Extract)**: 사용자가 정의한 정규 표현식 패턴에 매칭되는 텍스트를 추출합니다.

## 사용법 (Usage)

```bash
# 예시: 파일에서 이메일 패턴 추출
regex-grep input.txt output.txt "[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}"
```