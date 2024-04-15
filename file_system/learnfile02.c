#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char *filename = "text.txt";
    char *data1 = "New data appended\n";
    char *data2 = "kiem tra\n";

    // Mở file với cờ O_RDWR
    int fd = open(filename, O_RDWR | O_APPEND);
    if (fd == -1) {
        perror("Không thể mở file");
        exit(EXIT_FAILURE);
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Lỗi khi seek về đầu file");
        exit(EXIT_FAILURE);
    }

    // Ghi dữ liệu mới vào file
    ssize_t bytes_written = write(fd, data2, strlen(data2));
    if (bytes_written == -1) {
        perror("Lỗi khi ghi dữ liệu vào file");
        exit(EXIT_FAILURE);
    }

    printf("Dữ liệu mới đã được ghi vào file.\n");

    // Đóng file
    if (close(fd) == -1) {
        perror("Lỗi khi đóng file");
        exit(EXIT_FAILURE);
    }

    // Mở lại file để đọc nội dung
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Không thể mở lại file để đọc nội dung");
        exit(EXIT_FAILURE);
    }

    // Đọc nội dung từ file
    char buffer[1024];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("Lỗi khi đọc dữ liệu từ file");
        exit(EXIT_FAILURE);
    }

    printf("Nội dung trong file:\n");
    write(STDOUT_FILENO, buffer, bytes_read); // In nội dung ra màn hình

    // Đóng file sau khi đọc xong
    if (close(fd) == -1) {
        perror("Lỗi khi đóng file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
