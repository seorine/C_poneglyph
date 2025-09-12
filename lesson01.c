#include <stdio.h>

int main() {
    int stock;//상품개수
    int in[101];//입고
    int out[101];//출고
    int nam[101];//남은재고
    int id;

    scanf("%d", &stock);

    for (int i = 0; i < stock; i++) {
        scanf("%d", &in[i]);
    }
    for (int i = 0; i < stock; i++) {
        scanf("%d", &out[i]);
    }
    for (int i = 0; i < stock; i++) {
        nam[i] = in[i] - out[i];
    }

    scanf("%d", &id);

    printf("");
    for (int i = 0; i < stock; i++) {
        printf("%d ", nam[i]);
    }
    printf("\n");

    return 0;
}

