#include <stdio.h>
#include <string.h>

#define MAX 101        // 1~100 사용 (0은 미사용)
#define MAX_STOCK 5    // 기본 상품 개수

// 전역 데이터
int stock = MAX_STOCK;             // 상품 개수 (기본 5개)
int in[MAX]  = {0};                // 입고 수량
int out[MAX] = {0};                // 판매 수량
int nam[MAX] = {0};                // 남은 재고
char stockName[MAX][50] = {0};     // 상품명
int totalin = 0, totalout = 0;     // 총 입고/판매

// 함수 원형
int  commandMenu(void);       // 메뉴 출력 및 선택
void inputProductNames(void); // 상품명 입력
void stockIn(void);           // 입고 처리
void stockOut(void);          // 판매 처리
void pronaw(void);            // 전체 현황
void pronawone(void);         // 개별 현황
int  hikaru(void);            // 파일 저장
int  carlsen(void);           // 파일 불러오기


// 메인
int main(void) {
    // 초기 상품명 입력 (1~stock)
    inputProductNames();

    while (1) {
        int menu = commandMenu();

        if (menu == 1) {           // 입고
            stockIn();
        } else if (menu == 2) {    // 판매
            stockOut();
        } else if (menu == 3) {    // 개별현황
            pronawone();
        } else if (menu == 4) {    // 전체현황
            pronaw();
        } else if (menu == 5) {    // 파일 저장
            hikaru();
        } else if (menu == 6) {    // 파일 불러오기
            carlsen();
        } else if (menu == 7) {    // 종료
            printf("프로그램 종료\n");
            break;
        } else {
            printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }
    return 0;
}

// 메뉴 출력/선택
int commandMenu(void){
    int menu;
    printf("\n[쇼핑몰 재고 관리 프로그램]\n");
    printf("1. 입고\n");
    printf("2. 판매\n");
    printf("3. 개별현황\n");
    printf("4. 전체현황\n");
    printf("5. 상품정보 저장\n");
    printf("6. 상품정보 가져오기\n");
    printf("7. 프로그램 종료\n");
    printf("> 선택: ");
    return menu;
}

// 상품명 입력 (ID 1~stock)
void inputProductNames(void) {
    printf("\n[상품명 입력] (총 %d개, ID 1~%d)\n", stock, stock);
    for (int i = 1; i <= stock; i++) {
        printf("ID%d 상품명: ", i);
        scanf("%49s", stockName[i]);
    }
}

// 입고 처리
void stockIn(void){
    int sub, id, qty;
    printf("입고수량 입력: 전체 1, 개별 2 선택 > ");
    if (scanf("%d", &sub) != 1) return;

    if (sub == 1) { // 전체
        printf("전체 상품 입고수량을 ID 1~%d 순서로 입력: ", stock);
        for (int i = 1; i <= stock; i++) {
            if (scanf("%d", &qty) != 1) return;
            if (qty < 0) qty = 0; // 음수 방지
            in[i] += qty;
            nam[i] += qty;
            totalin += qty;
        }
    } else if (sub == 2) { // 개별
        printf("상품 ID 입력(1~%d): ", stock);
        if (scanf("%d", &id) != 1) return;
        if (id < 1 || id > stock) { printf("잘못된 ID입니다!\n"); return; }
        printf("입고 수량 입력: ");
        if (scanf("%d", &qty) != 1) return;
        if (qty < 0) qty = 0;
        in[id] += qty;
        nam[id] += qty;
        totalin += qty;
    } else {
        printf("잘못된 선택입니다.\n");
    }
}

// 판매 처리
void stockOut(void){
    int sub, id, qty;
    printf("판매수량 입력: 전체 1, 개별 2 선택 > ");
    if (scanf("%d", &sub) != 1) return;

    if (sub == 1){ // 전체
        printf("전체 상품 판매수량을 ID 1~%d 순서로 입력: ", stock);
        for (int i = 1; i <= stock; i++) {
            if (scanf("%d", &qty) != 1) return;
            if (qty < 0) qty = 0;
            out[i] += qty;
            nam[i] -= qty;
            if (nam[i] < 0) nam[i] = 0; // 재고 음수 방지
            totalout += qty;
        }
    } else if (sub == 2) { // 개별
        printf("상품 ID 입력(1~%d): ", stock);
        if (scanf("%d", &id) != 1) return;
        if (id < 1 || id > stock) { printf("잘못된 ID입니다!\n"); return; }
        printf("판매 수량 입력: ");
        if (scanf("%d", &qty) != 1) return;
        if (qty < 0) qty = 0;
        out[id] += qty;
        nam[id] -= qty;
        if (nam[id] < 0) nam[id] = 0;
        totalout += qty;
    } else {
        printf("잘못된 선택입니다.\n");
    }
}

// 전체 현황
void pronaw(void){
    printf("\n[상품 현황]\n");
    printf("ID  %-12s %6s %6s %6s\n", "상품이름", "입고", "판매", "재고");
    for (int i = 1; i <= stock; i++) {
        printf("%-3d %-12s %6d %6d %6d\n",
               i, stockName[i], in[i], out[i], nam[i]);
    }

    if (totalin > 0) {
        double rate = (double)totalout / totalin * 100.0;
        printf("총입고량: %d, 총판매량: %d (판매율 %.2f%%)\n", totalin, totalout, rate);
    } else {
        printf("아직 입고 데이터가 없습니다.\n");
    }

    // 최다/최소 판매
    int max = out[1], min = out[1];
    int maxId = 1, minId = 1;
    for (int i = 2; i <= stock; i++){
        if (out[i] > max){ max = out[i]; maxId = i; }
        if (out[i] < min){ min = out[i]; minId = i; }
    }
    printf("가장 많이 판매된 상품 : ID %d, 상품명 %s, 판매량 %d\n", maxId, stockName[maxId], max);
    printf("가장 적게 판매된 상품 : ID %d, 상품명 %s, 판매량 %d\n", minId, stockName[minId], min);

    // 재고 부족 경고 (≤2)
    for (int i = 1; i <= stock; i++) {
        if (nam[i] <= 2) {
            printf("※ 재고부족 경고: ID %d (%s) 재고 %d개\n", i, stockName[i], nam[i]);
        }
    }
}

// 개별 현황
void pronawone(void) {
    int target;
    printf("상품 ID 입력(1~%d) > ", stock);
    if (scanf("%d", &target) != 1) return;

    if (target >= 1 && target <= stock) {
        printf("ID\t상품이름\t입고\t판매\t재고\n");
        printf("%d\t%s\t%d\t%d\t%d\n",
               target, stockName[target], in[target], out[target], nam[target]);
    } else {
        printf("잘못된 ID 입니다!\n");
    }
}

// 파일 저장 (텍스트)
// 형식:
// STOCK <개수>
// <ID> <상품명> <입고> <판매> <재고>
// ...
int hikaru(void) {
    char filename[256];
    printf("저장할 파일명 입력: ");
    if (scanf("%255s", filename) != 1) return 0;

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("파일 열기 실패");
        return 0;
    }

    // 헤더: 상품 개수
    fprintf(fp, "STOCK %d\n", stock);
    // 1~stock 라인 저장
    for (int i = 1; i <= stock; i++) {
        fprintf(fp, "%d %s %d %d %d\n",
                i, stockName[i], in[i], out[i], nam[i]);
    }

    fclose(fp);
    printf("저장 완료: %s\n", filename);
    return 1;
}

// 파일 불러오기 (텍스트)
// 위 저장 형식 그대로 읽어옴.
int carlsen(void) {
    char filename[256];
    printf("불러올 파일명 입력: ");
    if (scanf("%255s", filename) != 1) return 0;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("파일 열기 실패");
        return 0;
    }

    // 기존 데이터 초기화
    for (int i = 0; i < MAX; i++) {
        in[i] = out[i] = nam[i] = 0;
        stockName[i][0] = '\0';
    }
    totalin = totalout = 0;

    // 헤더 읽기
    char tag[16];
    int newStock = 0;
    if (fscanf(fp, "%15s %d", tag, &newStock) != 2 || strcmp(tag, "STOCK") != 0) {
        printf("파일 형식 오류: 헤더를 읽을 수 없습니다.\n");
        fclose(fp);
        return 0;
    }
    if (newStock < 1 || newStock >= MAX) {
        printf("파일의 상품 개수(%d)가 범위를 벗어났습니다.\n", newStock);
        fclose(fp);
        return 0;
    }
    stock = newStock;

    // 각 라인 읽기
    for (int i = 1; i <= stock; i++) {
        int id, chessIn, chessOut, chessNam;   // ← 이름 변경
        char name[50];
        if (fscanf(fp, "%d %49s %d %d %d", &id, name, &chessIn, &chessOut, &chessNam) != 5) {
            printf("파일 형식 오류: %d번째 상품 정보를 읽을 수 없습니다.\n", i);
            fclose(fp);
            return 0;
        }
        if (id < 1 || id > stock) {
            printf("파일 형식 오류: 잘못된 ID %d\n", id);
            fclose(fp);
            return 0;
        }
        strncpy(stockName[id], name, 49);
        stockName[id][49] = '\0';
        in[id]  = chessIn;   // ← 이름 변경 반영
        out[id] = chessOut;
        nam[id] = chessNam;
    }

    fclose(fp);
    recompute_totals();
    printf("불러오기 완료: %s (상품 %d개)\n", filename, stock);
    return 1;
}

