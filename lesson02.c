#include <stdio.h>

int main() {
    int stock;//상품 개수
    int id;
    int in[100] = { 0 }; //입고
    int out[100] = { 0 };//출고
    int nam[100] = { 0 };//남은 재고
    int max = out[0];//가장 많이 판매된 상품
    int min = out[0];//가장 적게 판매된 상품
    int minmaxid[2] = { 0, 0 };//가장적게많이 판매된 상품과 id
    int totalin = 0;//총입고
    int totalout = 0;//총판매


    printf("상품 개수: ");
    scanf_s("%d", &stock);

    printf("상품별 입고 수량: ");
    for (int i = 0; i < stock; i++) {
        scanf_s("%d", &in[i]);
        totalin += in[i];
    }

    printf("상품별 판매 수량: ");
    for (int i = 0; i < stock; i++) {
        scanf_s("%d", &out[i]);
        totalout += out[i];
    }
    for (int i = 0; i < stock; i++) {
        nam[i] = in[i] - out[i];
    }

    double totalsell;
    totalsell = (double)totalout / totalin * 100;
    printf("총판매량: %d (판매율 %.2f%%)\n", totalout, totalsell);

    for (int i = 1; i < stock; i++) {
        if (out[i] > max) {
            max = out[i];
            minmaxid[0] = i;
        }
        if (out[i] < min) {
            min = out[i];
            minmaxid[1] = i;
        }
    }
    printf("가장 많이 판매된 상품 : ID %d, 판매량 %d\n", minmaxid[0] + 1, max);
    printf("가장 적게 판매된 상품 : ID %d, 판매량 %d\n", minmaxid[1] + 1, min);

    for (int i = 0; i < stock; i++) {
        if (nam[i] <= 2) {
            printf("상품 ID %d : 재고부족(%d)\n", i + 1, nam[i]);
        }
    }
    scanf_s("%d", &id);

    printf("%d\n", nam[id - 1]);
    for (int i = 0; i < stock; i++) {
        printf("%d ", nam[i]);
        printf(" ");
    }
    printf("\n");
    return 0;
}


