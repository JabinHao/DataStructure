#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode
{
    /* data */
    int coef;
    int expon;
    Polynomial link;
};

void Attach(int c, int e, Polynomial *pRear);
Polynomial ReadPoly();
Polynomial Add(Polynomial P1, Polynomial P2);

Polynomial ReadPoly(){
    Polynomial P, Rear, temp;
    int N, c, e;

    scanf("%d",&N);
    P=(Polynomial)malloc(sizeof(struct PolyNode));
    P->link=NULL;
    Rear=P;
    while(N--){
        scanf("%d %d",&c,&e);
        Attach(c,e,&Rear);
    };
    temp=P; P=P->link; free(temp);
    return P;
}

void Attach(int c, int e, Polynomial *pRear){
    Polynomial P;
    P=(Polynomial)malloc(sizeof(struct PolyNode));
    P->coef=c;
    P->expon=e;
    P->link=NULL;
    (*pRear)->link=P; //将传入结点的link指向新建的结点
    *pRear=P; //使传入的指针指向新节点
}

Polynomial Add(Polynomial P1, Polynomial P2){
    Polynomial P, Rear, temp, t1, t2;
    t1=P1; t2=P2;
    P=(Polynomial)malloc(sizeof(struct PolyNode));
    P->link=NULL;
    Rear=P;
    while(t1&&t2){
        if(t1->expon>t2->expon){
            Attach(t1->coef,t1->expon,&Rear);
            t1=t1->link;
        }
        else if(t1->expon<t2->expon){
            Attach(t2->coef,t2->expon,&Rear);
            t2=t2->link;
        }
        else{
            if(t1->coef + t2->coef)
                Attach(t1->coef + t2->coef, t1->expon, &Rear);
            t1=t1->link;
            t2=t2->link;
        }
    }
    while(t1){
        Attach(t1->coef,t1->expon,&Rear);
        t1=t1->link;
    }
    while(t2){
        Attach(t2->coef,t2->expon,&Rear);
        t2=t2->link;
    }
    Rear->link=NULL;
    temp=P; P=P->link; free(temp);
    return P;
}

Polynomial Mult(Polynomial P1,Polynomial P2){
    Polynomial P,temp,Rear,t1,t2;
    int c,e;

    if(!P1||!P2) return NULL;

    t1=P1; t2=P2;
    P=(Polynomial)malloc(sizeof(struct PolyNode));P->link=NULL;
    Rear=P;
    // t1各项与t2相乘得到初始多项式，后面再将其他结果插入
    while(t2){
        Attach(t1->coef*t2->coef,t1->expon+t2->expon,&Rear);
        t2=t2->link;
    }
    t1=t1->link;
    while(t1){
        t2=P2;Rear=P; //t1的某项*t2，首先将t2指向多项式2头，将Rear指向新多项式头
        while(t2){
            c = t1->coef*t2->coef;//x系数相乘
            e = t1->expon + t2->expon;//指数相加
            /*寻找t1当前项*t2最高次项后应插入的位置，其他项次数低于此项，必在该项之后*/
            while(Rear->link && Rear->link->expon>e){
                Rear=Rear->link;
            }
            if (Rear->link && Rear->link->expon == e)//找到同次项后插入
            {
                if(Rear->link->coef+c)
                    Rear->link->coef += c;
                /* 系数相加后为零则删除该项*/
                else{
                    temp=Rear->link;
                    Rear->link=temp->link;
                    free(temp);
                }

            }
            else {//没有同次项则新建结点
                temp = Rear->link;//记录下一项
                Attach(c,e,&Rear);//在Rear后添加一项
                /*temp = (Polynomial)malloc(sizeof(struct PolyNode));
                temp->coef=c; temp->expon=e;
                temp->link = Rear->link;*/
                Rear->link=temp;//将后面的项接到新节点后面
                //Rear = Rear->link;
            }
            t2=t2->link;
        }
        t1=t1->link;
    }
    temp=P;  P=P->link; free(temp);
    return P;
}

void PrintPoly(Polynomial P){
    /*输出多项式*/
    int flag=1; /*调整格式，相邻项之间以空格隔开最后没有空格*/
    
    /*空表则输出 0 0*/
    if(!P) {
        printf("0 0\n");
        return;
    }

    while(P){
        if(flag) flag=0;//开头，无需输入空格
        else printf(" ");//中间项，使用空格隔开
        printf("%d %d",P->coef,P->expon);
        P=P->link;
        
    }
    printf("\n");
}

int main(){
    Polynomial P1, P2, PP, PS;
    P1=ReadPoly();
    P2=ReadPoly();
    PP=Mult(P1,P2);
    PS=Add(P1,P2);
    PrintPoly(PP);
    PrintPoly(PS);
//    PrintPoly(P1);

    return 0;
}
