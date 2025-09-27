#include <stdio.h>
#include <string.h>

#define MAX 100   // 최대 상품 개수

// 전역 변수 (상품 관련 데이터 저장)
int stock; // 상품 개수
int in[MAX] = {0};   // 입고 수량
int out[MAX] = {0};  // 판매 수량
int nam[MAX] = {0};  // 남은 재고
char stockName[MAX][50] = {0}; // 상품명 저장

int totalin = 0, totalout = 0; // 총 입고, 총 판매


int commandMenu(void);       // 메뉴 출력 및 선택
void stockIn();              // 입고 처리
void stockOut();             // 판매 처리
void pronaw();               // 상품 현황 출력
void inputProductNames(void);// 상품명 입력


// 메인 함수
int main(void) {
    printf("상품 개수 입력: ");
    scanf("%d", &stock);

    while (1) {
        int menu = commandMenu();

        if (menu == 1) {           // 입고
            stockIn();
        }
        else if (menu == 2) {      // 판매
            stockOut();
        }
        else if (menu == 3) {      // 상품 현황
            pronaw();
        }
        else if (menu == 4) {      // 상품명 입력
            inputProductNames();
        }
        else if (menu == 5) {      // 종료
            printf("프로그램 종료\n");
            break;
        }
        else {                     // 잘못된 입력 처리
            printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }

    return 0;
}


// 메뉴 출력 및 선택 함수
int commandMenu(void){
    int menu;
    printf("\n[쇼핑몰 재고 관리 프로그램]\n");
    printf("1. 입고\n");
    printf("2. 판매\n");
    printf("3. 상품 현황\n");
    printf("4. 상품명 입력\n");
    printf("5. 종료\n");
    printf("> 선택: ");
    scanf("%d", &menu);

    return menu;
}


// 상품 입고 함수
void stockIn(void){
    int sub, id, qty;
    printf("입고수량 입력: 전체 1, 개별 2 선택 > ");
    scanf("%d", &sub);

    if (sub == 1) { // 전체 상품 입고
        printf("전체 상품 입고수량 입력: ");
        for (int i = 0; i < stock; i++) {
            scanf("%d", &qty);
            in[i] += qty;       // 입고량 누적
            nam[i] += qty;      // 재고 증가
            totalin += qty;     // 총 입고량 증가
        }
    } 
    else if (sub == 2) { // 개별 상품 입고
        printf("상품 ID 입력(0~%d): ", stock - 1);
        scanf("%d", &id);
        printf("입고 수량 입력: ");
        scanf("%d", &qty);
        in[id] += qty;       // 해당 상품 입고량 누적
        nam[id] += qty;      // 해당 상품 재고 증가
        totalin += qty;      // 총 입고량 증가
    }
}


// 상품 판매 함수
void stockOut(void){
    int sub, id, qty;
    printf("판매수량 입력: 전체 1, 개별 2 선택 > ");
    scanf("%d", &sub);

    if (sub == 1){ // 전체 상품 판매
        printf("전체 상품 판매수량 입력: ");
        for (int i = 0; i < stock; i++) {
            scanf("%d", &qty);
            out[i] += qty;      // 판매량 누적
            nam[i] -= qty;      // 재고 감소
            totalout += qty;    // 총 판매량 증가
        }
    }
    else if (sub == 2) { // 개별 상품 판매
        printf("상품 ID 입력(0~%d): ", stock - 1);
        scanf("%d", &id);
        printf("판매 수량 입력: ");
        scanf("%d", &qty);
        out[id] += qty;      // 해당 상품 판매량 누적
        nam[id] -= qty;      // 해당 상품 재고 감소
        totalout += qty;     // 총 판매량 증가
    }
}


// 상품 현황 출력 함수
void pronaw(void){
    printf("\n[상품 현황]\n");
    printf("ID\t상품이름\t입고\t판매\t재고\n");

    // 상품별 현황 출력
    for (int i = 0; i < stock; i++) {
        printf("%d\t%s\t%d\t%d\t%d\n", i, stockName[i], in[i], out[i], nam[i]);
    }

    // 총 판매율 계산 (총 판매량 / 총 입고량)
    if (totalin > 0) {
        double carlsn = (double)totalout / totalin * 100;
        printf("총판매량: %d (판매율 %.2f%%)\n", totalout, carlsn);
    }

    // 최다 판매, 최소 판매 상품 찾기
    int max = out[0], min = out[0];
    int maxId = 0, minId = 0;

    for (int i = 1; i < stock; i++){
        if (out[i] > max){
            max = out[i];
            maxId = i;
        }
        if (out[i] < min){
            min = out[i];
            minId = i;
        }
    }
    printf("가장 많이 판매된 상품 : ID %d, 상품명 %s 판매량 %d\n", maxId, stockName[maxId], max);
    printf("가장 적게 판매된 상품 : ID %d, 상품명 %s 판매량 %d\n", minId, stockName[minId], min);

    // 재고 부족(2개 이하) 경고 출력
    for (int i = 0; i < stock; i++) {
        if (nam[i] <= 2) {
            printf("상품 ID %d: 상품명 %s : 재고부족(%d)\n", i, stockName[i], nam[i]);
        }
    }
}


// 상품명 입력 함수
void inputProductNames(void) {
    for (int i = 0; i < stock; i++) {
        printf("ID%d 상품명: ", i);
        scanf("%s", stockName[i]);
    }
}
