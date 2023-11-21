#include <stdio.h>

// D4 D3 D2 P3 D1 P2 P1
// 6  5  4  3  2  1  0
void hammingCode(int data[7]) {
    // Calculation of even parity
    data[6] = data[0] ^ data[2] ^ data[4];
    data[5] = data[0] ^ data[1] ^ data[4];
    data[3] = data[0] ^ data[1] ^ data[2];
}

void hammingDecode(int dataatrec[7]) {
    int c1 = dataatrec[6] ^ dataatrec[4] ^ dataatrec[2] ^ dataatrec[0];
    int c2 = dataatrec[5] ^ dataatrec[4] ^ dataatrec[1] ^ dataatrec[0];
    int c3 = dataatrec[3] ^ dataatrec[2] ^ dataatrec[1] ^ dataatrec[0];
    int c = c3 * 4 + c2 * 2 + c1;

    if (c == 0) {
        printf("\nNo error while transmission of data\n");
    } else {
        printf("\nError on position %d", c);

        printf("\nData received: ");
        for (int i = 0; i < 7; i++)
            printf("%d", dataatrec[i]);
        printf("\nCorrect message is\n");

        // If the erroneous bit is 0, complement it; otherwise, vice versa
        if (dataatrec[7 - c] == 0)
            dataatrec[7 - c] = 1;
        else
            dataatrec[7 - c] = 0;
        for (int i = 0; i < 7; i++) {
            printf("%d", dataatrec[i]);
        }
    }
}

int main() {
    int data[7];
    int dataatrec[7];

    printf("Enter 4 bits of data one by one\n");
    scanf("%d", &data[0]);
    scanf("%d", &data[1]);
    scanf("%d", &data[2]);
    scanf("%d", &data[4]);

    hammingCode(data);

    printf("\nEncoded data is\n");
    for (int i = 0; i < 7; i++)
        printf("%d", data[i]);

    printf("\n\nEnter received data bits one by one\n");
    for (int i = 0; i < 7; i++)
        scanf("%d", &dataatrec[i]);

    hammingDecode(dataatrec);

    return 0;
}
