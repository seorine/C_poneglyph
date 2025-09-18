#include <stdio.h>

int main() {
    int stock; // 상품 개수
    int in[100] = {0};   // 입고
    int out[100] = {0};  // 판매
    int nam[100] = {0};  // 남은 재고

    int menu, sub, id, quantity; // 메뉴, 서브, 상품ID, 수량
    int totalin = 0, totalout = 0; // 총 입고, 총 판매

    printf("상품 개수 입력: ");
    scanf("%d", &stock);

    while (1) {
        printf("\n[쇼핑몰 재고 관리 프로그램]\n");
        printf("> 원하는 메뉴를 선택하세요. (1. 입고, 2. 판매, 3. 상품현황, 4. 종료)\n> ");
        scanf("%d", &menu);

        if (menu == 1) {  // === 입고 기능 ===
            printf("입고수량 입력: 전체 1, 개별 2 선택 > ");
            scanf("%d", &sub);

            if (sub == 1) { // 전체 상품 입고
                printf("전체 상품 입고수량 입력: ");
                for (int i = 0; i < stock; i++) {
                    scanf("%d", &quantity);
                    in[i] += quantity;
                    nam[i] += quantity;
                    totalin += quantity;
                }
            }
            else if (sub == 2) { // 개별 상품 입고
                printf("상품 ID 입력(0~%d): ", stock - 1);
                scanf("%d", &id);
                printf("입고 수량 입력: ");
                scanf("%d", &quantity);
                in[id] += quantity;
                nam[id] += quantity;
                totalin += quantity;
            }
        }
        else if (menu == 2) {  // === 판매 기능 ===
            printf("판매수량 입력: 전체 1, 개별 2 선택 > ");
            scanf("%d", &sub);

            if (sub == 1) { // 전체 상품 판매
                printf("전체 상품 판매수량 입력: ");
                for (int i = 0; i < stock; i++) {
                    scanf("%d", &quantity);
                    out[i] += quantity;
                    nam[i] -= quantity;
                    totalout += quantity;
                }
            }
            else if (sub == 2) { // 개별 상품 판매
                printf("상품 ID 입력(0~%d): ", stock - 1);
                scanf("%d", &id);
                printf("판매 수량 입력: ");
                scanf("%d", &quantity);
                out[id] += quantity;
                nam[id] -= quantity;
                totalout += quantity;
            }
        }
        else if (menu == 3) {  // === 상품 현황 출력 ===
            printf("\n[상품 현황]\n");
            printf("ID\t입고\t판매\t재고\n");
            for (int i = 0; i < stock; i++) {
                printf("%d\t%d\t%d\t%d\n", i, in[i], out[i], nam[i]);
            }

            if (totalin > 0) {
                double rate = (double)totalout / totalin * 100;
                printf("총판매량: %d (판매율 %.2f%%)\n", totalout, rate);
            }

            int max = out[0], min = out[0];
            int maxId = 0, minId = 0;

            for (int i = 1; i < stock; i++) {
                if (out[i] > max) {
                    max = out[i];
                    maxId = i;
                }
                if (out[i] < min) {
                    min = out[i];
                    minId = i;
                }
            }

            printf("가장 많이 판매된 상품 : ID %d, 판매량 %d\n", maxId, max);
            printf("가장 적게 판매된 상품 : ID %d, 판매량 %d\n", minId, min);

            for (int i = 0; i < stock; i++) {
                if (nam[i] <= 2) {
                    printf("상품 ID %d : 재고부족(%d)\n", i, nam[i]);
                }
            }
        }
        else if (menu == 4) {  // === 종료 ===
            printf("프로그램 종료\n");
            break;
        }
        else {
            printf("잘못된 입력입니다.\n");
        }
    }

    return 0;
}

   
