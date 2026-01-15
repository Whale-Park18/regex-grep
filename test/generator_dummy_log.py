import random
from datetime import datetime, timedelta

def generate_dummy_logs(filename="dummy_log.txt", count=1000):
    log_types = ["INFO", "DEBUG", "WARN", "ERROR"]
    messages = [
        "User authentication successful.",
        "Failed to allocate memory for buffer.",
        "Disk I/O latency detected on C: drive.",
        "Incoming connection from 127.0.0.1.",
        "Module 'Win32_NetworkAdapter' initialized.",
        "Registry key 'HKLM\\Software\\App' modified.",
        "Thread pool reached maximum capacity.",
        "Pointer address 0x00FF23A1 accessed.",
        "TCP/IP handshake completed.",
        "Application watchdog heart-beat detected."
    ]

    # 시작 시간 설정 (2026-01-15 14:00:00)
    start_time = datetime(2026, 1, 15, 14, 0, 0)
    logs = []

    for _ in range(count):
        # 0초에서 600초(10분) 사이의 랜덤한 시간 추가
        random_seconds = random.uniform(0, 600)
        log_time = start_time + timedelta(seconds=random_seconds)
        
        log_type = random.choice(log_types)
        message = random.choice(messages)
        
        # 요청하신 형식: [YYYY-MM-DD HH:MM:SS.mmm] [{log_type}] { log_message }
        formatted_time = log_time.strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
        log_entry = f"[{formatted_time}] [{log_type}] {message}"
        logs.append((log_time, log_entry))

    # 시간순으로 정렬 (실제 로그 파일처럼)
    logs.sort()

    with open(filename, "w", encoding="utf-8") as f:
        for _, entry in logs:
            f.write(entry + "\n")

    print(f"Successfully generated {count} lines in '{filename}'.")

if __name__ == "__main__":
    generate_dummy_logs()