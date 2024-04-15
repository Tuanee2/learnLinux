#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    char *path = "text.txt";
    int fd;

    // Tạo hoặc mở tệp với quyền đọc và ghi
    fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Không thể mở hoặc tạo tệp");
        exit(1);
    }

    // Chuỗi chứa nội dung muốn ghi vào tệp
    char *content = "chuc mung thanh cong\n";

    // Sử dụng hàm write() để ghi vào tệp
    ssize_t bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("Lỗi ghi vào tệp");
        exit(1);
    }

    printf("Ghi vào tệp thành công: %s\n", path);
    
    // Cấp phát bộ nhớ cho inf_file
    struct stat *inf_file = (struct stat *)malloc(sizeof(struct stat));
    if (inf_file == NULL) {
        perror("Không thể cấp phát bộ nhớ");
        exit(1);
    }

    // Lấy thông tin về tệp
    int inf = fstat(fd, inf_file);
    if (inf == -1) {
        perror("Lỗi khi lấy thông tin về tệp");
        exit(1);
    }

    printf("Thông tin file:\n");
    printf("Name : %s\n", path);
    printf("File mode: %o\n", inf_file->st_mode);
    printf("Time of last status change: %ld\n", (long)inf_file->st_ctime);
    printf("Size of file : %lld \n", (long long)inf_file->st_size);

    // Giải phóng bộ nhớ đã được cấp phát cho inf_file
    free(inf_file);

    // Đóng tệp sau khi ghi xong
    if (close(fd) == -1) {
        perror("Lỗi khi đóng tệp");
        exit(1);
    }

    return 0;
}
