#include <stdio.h>
#include <string.h>

#define MAX 101
#define MAX_STOCK 5

int stock = MAX_STOCK;
int in[MAX]  = {0};
int out[MAX] = {0};
int nam[MAX] = {0};
char stockName[MAX][50] = {0};
int totalin = 0, totalout = 0;

int  commandMenu(void);
void inputProductNames(void);
void stockIn(void);
void stockOut(void);
void pronaw(void);
void pronawone(void);
int  hikaru(void);
int  carlsen(void);

int main(void) {
    inputProductNames();

    while (1) {
        int menu = commandMenu();

        if (menu == 1) stockIn();
        else if (menu == 2) stockOut();
        else if (menu == 3) pronawone();
        else if (menu == 4) pronaw();
        else if (menu == 5) hikaru();
        else if (menu == 6) carlsen();
        else if (menu == 7) { printf("프로그램 종료\n"); break; }
        else printf("잘못된 입력입니다. 다시 선택하세요.\n");
    }
    return 0;
}

int commandMenu(void){
    int menu;
    printf("\n[쇼핑몰 재고 관리 프로그램]\n");
    printf("1. 입고\n2. 판매\n3. 개별현황\n4. 전체현황\n");
    printf("5. 상품정보 저장\n6. 상품정보 가져오기\n7. 프로그램 종료\n> 선택: ");
    if (scanf("%d", &menu) != 1)
        return 0;   
    return menu;
}

void inputProductNames(void) {
    printf("\n[상품명 입력] (총 %d개, ID 1~%d)\n", stock, stock);
    for (int i = 1; i <= stock; i++) {
        printf("ID%d 상품명: ", i);
        scanf("%49s", stockName[i]);
    }
}

void stockIn(void){
    int sub, id, qty;
    printf("입고수량 입력: 전체 1, 개별 2 선택 > ");
    if (scanf("%d", &sub) != 1) return;

    if (sub == 1) {
        printf("전체 상품 입고수량을 ID 1~%d 순서로 입력: ", stock);
        for (int i = 1; i <= stock; i++) {
            if (scanf("%d", &qty) != 1) return;
            if (qty < 0) qty = 0;
            in[i] += qty; nam[i] += qty; totalin += qty;
        }
    } else if (sub == 2) {
        printf("상품 ID 입력(1~%d): ", stock);
        if (scanf("%d", &id) != 1) return;
        if (id<1||id>stock){printf("잘못된 ID!\n");return;}
        printf("입고 수량 입력: ");
        if (scanf("%d", &qty) != 1) return;
        if (qty<0) qty=0;
        in[id]+=qty; nam[id]+=qty; totalin+=qty;
    }
}

void stockOut(void){
    int sub,id,qty;
    printf("판매수량 입력: 전체 1, 개별 2 선택 > ");
    if (scanf("%d", &sub)!=1) return;

    if (sub==1){
        printf("전체 상품 판매수량을 ID 1~%d 순서로 입력: ",stock);
        for(int i=1;i<=stock;i++){
            if(scanf("%d",&qty)!=1) return;
            if(qty<0) qty=0;
            out[i]+=qty; nam[i]-=qty; if(nam[i]<0) nam[i]=0; totalout+=qty;
        }
    }else if(sub==2){
        printf("상품 ID 입력(1~%d): ",stock);
        if(scanf("%d",&id)!=1) return;
        if(id<1||id>stock){printf("잘못된 ID!\n");return;}
        printf("판매 수량 입력: ");
        if(scanf("%d",&qty)!=1) return;
        if(qty<0) qty=0;
        out[id]+=qty; nam[id]-=qty; if(nam[id]<0) nam[id]=0; totalout+=qty;
    }
}

void pronaw(void){
    printf("\n[상품 현황]\n");
    printf("ID  %-12s %6s %6s %6s\n","상품이름","입고","판매","재고");
    for(int i=1;i<=stock;i++)
        printf("%-3d %-12s %6d %6d %6d\n",i,stockName[i],in[i],out[i],nam[i]);

    if(totalin>0){
        double rate=(double)totalout/totalin*100.0;
        printf("총입고:%d 총판매:%d (판매율 %.2f%%)\n",totalin,totalout,rate);
    }

    int max=out[1],min=out[1],maxId=1,minId=1;
    for(int i=2;i<=stock;i++){if(out[i]>max){max=out[i];maxId=i;} if(out[i]<min){min=out[i];minId=i;}}
    printf("최다 판매 : ID %d %s (%d개)\n",maxId,stockName[maxId],max);
    printf("최소 판매 : ID %d %s (%d개)\n",minId,stockName[minId],min);

    for(int i=1;i<=stock;i++) if(nam[i]<=2)
        printf("※ 재고부족: ID %d (%s) 남은 %d개\n",i,stockName[i],nam[i]);
}

void pronawone(void){
    int t;
    printf("상품 ID 입력(1~%d) > ",stock);
    if(scanf("%d",&t)!=1) return;
    if(t>=1 && t<=stock)
        printf("ID\t상품이름\t입고\t판매\t재고\n%d\t%s\t%d\t%d\t%d\n",t,stockName[t],in[t],out[t],nam[t]);
    else printf("잘못된 ID!\n");
}

int hikaru(void){
    char fn[256];
    printf("저장할 파일명: ");
    if(scanf("%255s",fn)!=1) return 0;
    FILE*fp=fopen(fn,"w");
    if(!fp){perror("파일 열기 실패");return 0;}
    fprintf(fp,"STOCK %d %d %d\n",stock,totalin,totalout);
    for(int i=1;i<=stock;i++)
        fprintf(fp,"%d %s %d %d %d\n",i,stockName[i],in[i],out[i],nam[i]);
    fclose(fp);
    printf("저장완료: %s\n",fn);
    return 1;
}

int carlsen(void){
    char fn[256];
    printf("불러올 파일명: ");
    if(scanf("%255s",fn)!=1) return 0;
    FILE*fp=fopen(fn,"r");
    if(!fp){perror("파일 열기 실패");return 0;}

    for(int i=0;i<MAX;i++){in[i]=out[i]=nam[i]=0;stockName[i][0]='\0';}
    totalin=totalout=0;

    char tag[16];
    if(fscanf(fp,"%15s",tag)!=1||strcmp(tag,"STOCK")!=0){printf("파일 형식 오류!\n");fclose(fp);return 0;}
    if(fscanf(fp,"%d %d %d",&stock,&totalin,&totalout)!=3){printf("파일 헤더 읽기 실패\n");fclose(fp);return 0;}
    if(stock<1||stock>=MAX){printf("상품 개수 오류!\n");fclose(fp);return 0;}

    for(int i=1;i<=stock;i++){
        int id,chessIn,chessOut,chessNam; char name[50];
        if(fscanf(fp,"%d %49s %d %d %d",&id,name,&chessIn,&chessOut,&chessNam)!=5){
            printf("%d번째 상품 읽기 실패\n",i);fclose(fp);return 0;
        }
        if(id<1||id>stock){printf("잘못된 ID %d\n",id);fclose(fp);return 0;}
        strncpy(stockName[id],name,49);stockName[id][49]='\0';
        in[id]=chessIn; out[id]=chessOut; nam[id]=chessNam;
    }

    fclose(fp);
    printf("불러오기 완료: %s\n",fn);
    return 1;
}
