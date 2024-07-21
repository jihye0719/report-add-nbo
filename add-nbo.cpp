#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf

// 2개의 파일로부터 32bit의 숫자를 불러들여 합을 출력하는 프로그램
int main(int argc, char *argv[]) {

    FILE *file1, *file2;
    uint8_t bufferA[4], bufferB[4];
    uint32_t A = 0, B = 0;
   
    // 파일 열기 
    file1 = fopen(argv[1], "rb");
    file2 = fopen(argv[2], "rb");
    if (file1 == NULL or file2 == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 파일에서 4바이트 읽기
    size_t bytesRead1 = fread(bufferA, 1, 4, file1);
    size_t bytesRead2 = fread(bufferB, 1, 4, file2);

    if (bytesRead1 != 4 or bytesRead2 != 4) {
        perror("Error reading file");
        fclose(file1);
        fclose(file2);
        return 1;
    }

    A = (uint32_t)bufferA[3]
        | ((uint32_t)bufferA[2] << 8)
        | ((uint32_t)bufferA[1] << 16)
        | ((uint32_t)bufferA[0] << 24);

    B = (uint32_t)bufferB[3]
        | ((uint32_t)bufferB[2] << 8)
        | ((uint32_t)bufferB[1] << 16)
        | ((uint32_t)bufferB[0] << 24);

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", A, A, B, B, A+B, A+B);

    // 파일 닫기
    fclose(file1);
    fclose(file2);
    return 0;
}