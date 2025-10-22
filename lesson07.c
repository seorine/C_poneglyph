#include <stdio.h>
#include <string.h>

#define MAX 101
#define MAX_STOCK 5

// ---------------- 구조체 정의 ---------------- //
typedef struct {
    int stock;                  // 상품 개수
    int in[MAX];                // 입고 수량
    int out[MAX];               // 판매 수량
    int nam[MAX];               // 남은 재고
    char stockName[MAX][50];    // 상품명
    int totalin;                // 총 입고량
    int totalout;               // 총 판매량
} Sicilian_Hyper_Accelerated_Dragon;

// ---------------- 함수 선언 ---------------- //
int  commandMenu(void);
void inputProductNames(Sicilian_Hyper_Accelerated_Dragon *p);
void stockIn(Sicilian_Hyper_Accelerated_Dragon *p);
void stockOut(Sicilian_Hyper_Accelerated_Dragon *p);
void pronaw(Sicilian_Hyper_Accelerated_Dragon *p);
void pronawone(Sicilian_Hyper_Accelerated_Dragon *p);
int  hikaru(Sicilian_Hyper_Accelerated_Dragon *p);
int  carlsen(Sicilian_Hyper_Accelerated_Dragon *p);

// ---------------- 메인 ---------------- //
int main(void) {
    Sicilian_Hyper_Accelerated_Dragon s = {0};
    s.stock = MAX_STOCK;

    inputProductNames(&s);

    while (1) {
        int menu = commandMenu();
        if (menu == 1) stockIn(&s);
        else if (menu == 2) stockOut(&s);
        else if (menu == 3) pronawone(&s);
        else if (menu == 4) pronaw(&s);
        else if (menu == 5) hikaru(&s);
        else if (menu == 6) carlsen(&s);
        else if (menu == 7) {
            printf("프로그램 종료\n");
            break;
        } else printf("잘못된 입력입니다.\n");
    }
    return 0;
}

// ---------------- 메뉴 선택 ---------------- //
int commandMenu(void){
    int menu;
    printf("\n[쇼핑몰 재고 관리 프로그램]\n");
    printf("1. 입고\n2. 판매\n3. 개별현황\n4. 전체현황\n");
    printf("5. 상품정보 저장\n6. 상품정보 불러오기\n7. 종료\n> 선택: ");
    if (scanf("%d", &menu) != 1) return 0;
    return menu;
}

// ---------------- 상품명 입력 ---------------- //
void inputProductNames(Sicilian_Hyper_Accelerated_Dragon *p){
    printf("\n[상품명 입력] (총 %d개, ID 1~%d)\n", p->stock, p->stock);
    for (int i = 1; i <= p->stock; i++) {
        printf("ID%d 상품명: ", i);
        scanf("%49s", p->stockName[i]);
    }
}

// ---------------- 입고 처리 ---------------- //
void stockIn(Sicilian_Hyper_Accelerated_Dragon *p){
    int sub, id, qty;
    printf("입고수량 입력: 전체 1, 개별 2 선택 > ");
    if (scanf("%d", &sub) != 1) return;

    if (sub == 1) {
        printf("전체 상품 입고수량(ID1~%d): ", p->stock);
        for (int i = 1; i <= p->stock; i++) {
            if (scanf("%d", &qty) != 1) return;
            if (qty < 0) qty = 0;
            p->in[i] += qty;
            p->nam[i] += qty;
            p->totalin += qty;
        }
    } else if (sub == 2) {
        printf("상품 ID 입력(1~%d): ", p->stock);
        if (scanf("%d", &id) != 1 || id < 1 || id > p->stock) return;
        printf("입고 수량 입력: ");
        if (scanf("%d", &qty) != 1) return;
        if (qty < 0) qty = 0;
        p->in[id] += qty;
        p->nam[id] += qty;
        p->totalin += qty;
    }
}

// ---------------- 판매 처리 ---------------- //
void stockOut(Sicilian_Hyper_Accelerated_Dragon *p){
    int sub, id, qty;
    printf("판매수량 입력: 전체 1, 개별 2 선택 > ");
    if (scanf("%d", &sub) != 1) return;

    if (sub == 1) {
        printf("전체 상품 판매수량(ID1~%d): ", p->stock);
        for (int i = 1; i <= p->stock; i++) {
            if (scanf("%d", &qty) != 1) return;
            if (qty < 0) qty = 0;
            p->out[i] += qty;
            p->nam[i] -= qty;
            if (p->nam[i] < 0) p->nam[i] = 0;
            p->totalout += qty;
        }
    } else if (sub == 2) {
        printf("상품 ID 입력(1~%d): ", p->stock);
        if (scanf("%d", &id) != 1 || id < 1 || id > p->stock) return;
        printf("판매 수량 입력: ");
        if (scanf("%d", &qty) != 1) return;
        if (qty < 0) qty = 0;
        p->out[id] += qty;
        p->nam[id] -= qty;
        if (p->nam[id] < 0) p->nam[id] = 0;
        p->totalout += qty;
    }
}

// ---------------- 전체 현황 출력 ---------------- //
void pronaw(Sicilian_Hyper_Accelerated_Dragon *p){
    printf("\n[상품 현황]\n");
    printf("ID  %-12s %6s %6s %6s\n", "상품이름", "입고", "판매", "재고");
    for (int i = 1; i <= p->stock; i++)
        printf("%-3d %-12s %6d %6d %6d\n", i, p->stockName[i], p->in[i], p->out[i], p->nam[i]);

    if (p->totalin > 0) {
        double rate = (double)p->totalout / p->totalin * 100.0;
        printf("총입고:%d 총판매:%d (판매율 %.2f%%)\n", p->totalin, p->totalout, rate);
    }

    int max = p->out[1], min = p->out[1], maxId = 1, minId = 1;
    for (int i = 2; i <= p->stock; i++) {
        if (p->out[i] > max) { max = p->out[i]; maxId = i; }
        if (p->out[i] < min) { min = p->out[i]; minId = i; }
    }
    printf("최다 판매 : ID %d %s (%d개)\n", maxId, p->stockName[maxId], max);
    printf("최소 판매 : ID %d %s (%d개)\n", minId, p->stockName[minId], min);

    for (int i = 1; i <= p->stock; i++)
        if (p->nam[i] <= 2)
            printf("※ 재고부족: ID %d (%s) 남은재고 %d개\n", i, p->stockName[i], p->nam[i]);
}

// ---------------- 개별 현황 ---------------- //
void pronawone(Sicilian_Hyper_Accelerated_Dragon *p){
    int t;
    printf("상품 ID 입력(1~%d) > ", p->stock);
    if (scanf("%d", &t) != 1) return;
    if (t >= 1 && t <= p->stock)
        printf("%-5d %-15s %-8d %-8d %-8d\n", t, p->stockName[t], p->in[t], p->out[t], p->nam[t]);
    else printf("잘못된 ID!\n");
}

// ---------------- 저장 ---------------- //
int hikaru(Sicilian_Hyper_Accelerated_Dragon *p){
    char fn[256];
    printf("저장할 파일명: ");
    if (scanf("%255s", fn) != 1) return 0;
    FILE *fp = fopen(fn, "w");
    if (!fp) { perror("파일 열기 실패"); return 0; }

    fprintf(fp, "STOCK %d %d %d\n", p->stock, p->totalin, p->totalout);
    for (int i = 1; i <= p->stock; i++)
        fprintf(fp, "%d %s %d %d %d\n", i, p->stockName[i], p->in[i], p->out[i], p->nam[i]);
    fclose(fp);
    printf("저장완료: %s\n", fn);
    return 1;
}

// ---------------- 불러오기 ---------------- //
int carlsen(Sicilian_Hyper_Accelerated_Dragon *p){
    char fn[256];
    printf("불러올 파일명: ");
    if (scanf("%255s", fn) != 1) return 0;
    FILE *fp = fopen(fn, "r");
    if (!fp) { perror("파일 열기 실패"); return 0; }

    memset(p, 0, sizeof(*p));

    char tag[16];
    if (fscanf(fp, "%15s", tag) != 1 || strcmp(tag, "STOCK") != 0) {
        printf("파일 형식 오류!\n");
        fclose(fp);
        return 0;
    }

    fscanf(fp, "%d %d %d", &p->stock, &p->totalin, &p->totalout);

    for (int i = 1; i <= p->stock; i++)
        fscanf(fp, "%*d %49s %d %d %d",
               p->stockName[i], &p->in[i], &p->out[i], &p->nam[i]);

    fclose(fp);
    printf("불러오기 완료: %s\n", fn);
    return 1;
}
