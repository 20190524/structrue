#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#define ERROR -1
#define TRUE 1
#define FALSE 0
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

typedef struct TXData
{
    long int tx_ID;//交易编号
    int block_ID;//区块编号
    char FromID[35];//转出者
    double Amount;//交易金额
    char ToID[35];//转入者
}TXData,*TXDataP;

typedef struct TXNode
{
    TXData data;
    struct TXNode *lchild,*rchild;
}TXNode,*TXTree;

//土豪树结构

typedef struct RichInfo
{
    char name[35];
    double pocession;
}RichInfo,*RichInfoP;

typedef struct RichNode
{
    RichInfo info;
    struct RichNode *lchild,*rchild;
}RichNode,*RichTree;


typedef struct Block
{
    int block_ID;//区块ID
    long int block_timestamp;//时间戳
    struct TXNode* Trade;//交易记录
    struct Block *next;
}*BlockP,*BlockPos,BlockNode;

typedef struct
{
    BlockP head,tail;//头指针，尾指针
    int len;//个数
}BlockList;

//土豪个人资料
typedef struct Rich
{
    double procession;
    char name[35];
    struct Rich *next;
}Rich,*RichP,*RichPos;

//土豪榜
typedef struct
{
    RichP head,tail;
    int num;
}RichList;




int MakeNode(BlockP &p,int id,long time){
    p=(BlockP)malloc(sizeof(Block));
    if(!p)return ERROR;
    p->block_ID=id;
    p->block_timestamp=time;
    p->Trade=NULL;
    p->next=NULL;
}

//土豪资料填写
int MakeRich(RichP &r,double money,char *name){
    r=(RichP)malloc(sizeof(Rich));
    if(!r)return ERROR;
    r->procession=money;
    strcpy(r->name,name);
    r->next=NULL;
}

void FreeNode(BlockP &p){
    free(p);
    p=NULL;
}

//清除土豪
void FreeRich(RichP &r){
    free(r);
    r=NULL;
}

int InitListP(BlockList &L){
    L.head=(BlockP)malloc(sizeof(Block));
    L.head->block_ID=0;
    L.head->block_timestamp=0;
    L.tail=L.head;
    L.tail->next=NULL;
    L.len=0;
}


//初始化土豪链表
int InitListR(RichList &L){
    L.head=(RichP)malloc(sizeof(Rich));
    L.head->procession=0;
//    L.head->name="\0";
    strcpy(L.head->name,"\0");
    L.tail=L.head;
    L.tail->next=NULL;
    L.num=0;
}



int DestroyList(BlockList &L){
    Block* p;
    while (L.head) {
        p=L.head;
        L.head=L.head->next;
        free(p);
    }
}


//销毁土豪链表
int DestroyRichList(RichList &L){
    Rich* r;
    while (L.head) {
        r=L.head;
        L.head=L.head->next;
        free(r);
    }
}

int ClearList(BlockList &L){
    Block*p;
    while (L.head->next) {
        p=L.head->next;
        L.head->next=p->next;
        free(p);
    }
    L.tail=L.head;
    L.tail->next=NULL;
    L.len=0;
}

//清除土豪榜
int ClearRichList(RichList &L){
    Rich*p;
    while (L.head->next) {
        p=L.head->next;
        L.head->next=p->next;
        free(p);
    }
    L.tail=L.head;
    L.tail->next=NULL;
    L.num=0;
}



int DelFirst(BlockP h,BlockP &q,BlockList &p){//已知h指向线性链表的头结点，删除链表中第一个结点并以q返回
    if(h->next==NULL)return ERROR;
    q=h->next;
    h->next=h->next->next;
    if(q->next=NULL)p.tail=h;
    free(q);
}

int Append(BlockList&L,BlockP s){//将指针s所指的一串结点链接在线性表l的最后一个结点之后，并改变链表l的尾指针指向新的尾结点
    BlockP p;
    p=s;
    while (p->next!=NULL) {
        p=p->next;
    }
    L.tail->next=s;
    L.tail=p;
}


//插入土豪
int InsertRichMan(RichList&L,RichP s){//将指针s所指的一串结点链接在线性表l的最后一个结点之后，并改变链表l的尾指针指向新的尾结点
    RichP p;
    p=s;
    while (p->next!=NULL) {
        p=p->next;
    }
    L.tail->next=s;
    L.tail=p;
}


int Remove(BlockList & L,BlockP &q){//删除线性链表中的尾结点并以q返回，改变链表l的尾指针指向新的尾结点
    BlockP p;
    p=L.head;
    while (p->next!=L.tail) {
        p=p->next;
    }
    q=L.tail;
    free(q);
    L.tail=p;
    L.tail->next=NULL;
//    free(p);
}

void DeleteBlockLink(BlockList &l,BlockP &p){//要求要删除的结点存在
    BlockP q;
    q=l.head;
    while (q->next!=p) {
        q=q->next;
    }
    q->next=p->next;
    if(p->next==NULL)l.tail=q;
    free(p);
}
int InsAfter(BlockList &L,BlockP &p,BlockP s){//已知p指向线性链表l中的一个结点，将s所指结点插入在p所指结点之后，并修改指针p指向新插入的结点
    s->next=p->next;
    p->next=s;
    p=s;
}

int InsBefore(BlockList &L,BlockP &p,BlockP s){//之前
    BlockP q;
    q=L.head;
    while (q->next!=p) {
        q=q->next;
    }
    s->next=p;
    q->next=s;
    p=s;
}

void SetCurElem(BlockP &p,int id,int time){//已知p指向线性链表中的一个结点，用e更新p所指结点中元素的值
    p->block_ID=id;
    p->block_timestamp=time;
}


int BlockListEmpty(BlockList L){
    if(L.head==L.tail)return TRUE;
    return FALSE;
}

int BlockListLength(BlockList L){
    int i=0;
    BlockP p;
    p=L.head;
    while (p->next) {
        i++;
        p=p->next;
    }
    return i;
}

BlockPos GetHead(BlockList L){
    return L.head;
}

BlockPos GetLast(BlockList L){
    return L.tail;
}

BlockPos PriorPos(BlockList L,BlockP p){
    if(p==L.head)return NULL;
    BlockP q;
    q=L.head;
    while (q->next!=p) {
        q=q->next;
    }
    return q;
}

BlockPos NextPos(BlockP p){
    if(p->next==NULL)return NULL;
    return p->next;
}


BlockPos LocateData(BlockList L,int id,bool (*compare)(int,int)){
    //返回线性链表中第一个与e满足函数判定关系的元素的位置
    BlockP p;
    p=L.head->next;
    int i=1;
    while (p!=NULL) {
        if(compare(p->block_ID,id))return p;
        p=p->next;
        i++;
    }
    free(p);
    return NULL;
}

//判断是不是那个土豪
bool NameCheck(char *name1,char *name2){
    if(strcmp(name1,name2)==0)return true;
    return false;
}


//找到相应的土豪
RichPos LocateRich(RichList R,char *name,bool (*compare)(char *,char *)){
    RichP r;
    r=R.head->next;
    while (r) {
        if(compare(r->name,name))return r;
        r=r->next;
    }
    free(r);
    return NULL;
}


void DestroyBlockList(BlockList &p){
    DestroyList(p);
}


int ListLength(BlockList p){
    return BlockListLength(p);
}

int cmp(int a,int b){
    if(a==b)return 0;
    if(a>b)return 1;
    if(a<b)return -1;
}



int LoadBlockData(FILE *filename,BlockList &BL){
    char str[2130][100];//存储每一行文件字符串
    int line =0;//第几条数据
    int id[2130];
    long time[2130];
    InitListP(BL);
    filename=fopen("C:\\Users\\cl\\Documents\\block1\\block_part1.csv","r");
    if(filename==NULL)return 0;
    //表头已去
    char *s1=NULL,*s2=NULL,*s3=NULL;
    while (!feof(filename)) {
        fgets(str[line],100,filename);
        //读取ID
        s1=strtok(str[line],",");
        id[line]=atoi(s1);
        //不存储哈希值
        s2=strtok(NULL,",");
        //存储时间
        s3=strtok(NULL,",");
        time[line]=atol(s3);
        //创建链表
        if(s1&&s2){//数据存在则创建
            BlockP Bp;
            if(MakeNode(Bp,id[line],time[line]))
                Append(BL,Bp);
            BL.len++;
        }
        line++;
    }
    fclose(filename);
    return line;
}

//构建区块中的树

int MakeTradeNode(TXTree &t,long txid,int bid,char *fid,double amount,char *tid){
    t=(TXTree)malloc(sizeof(TXNode));
    if(!t)return ERROR;
    t->data.tx_ID=txid;
    t->data.block_ID=bid;
    strcpy(t->data.FromID,fid);
    t->data.Amount=amount;
    strcpy(t->data.ToID,tid);
    t->lchild=NULL;
    t->rchild=NULL;
}

int cmpkey(long a,long b){
    if(a==b)return 0;
    if(a>b)return 1;
    return -1;
}

int cmpkey(double a,double b){
    if(a==b)return 0;
    if(a>b)return 1;
    return -1;
}

int SearchTradeTree(TXTree T,long idkey1,double key2,TXTree parent,TXTree &tp){
    //tp为用作遍历的结点指针，parent为当前遍历指针的父亲结点，idkey是交易记录，T是要构建的树
    //首先以交易金额作为排序依据，如果交易金额一样则比较交易ID
    if(!T){
        tp=parent;
        return FALSE;//空树，查找不成功，生成根结点
    }
    else if(cmpkey(key2,T->data.Amount)==0){
        if(cmpkey(idkey1,T->data.tx_ID)==0){
            tp=T;
            return TRUE;//找到且为根结点
        }
        else if(cmpkey(idkey1,T->data.tx_ID)==1)
            return SearchTradeTree(T->lchild,idkey1,key2,T,tp);
        else return SearchTradeTree(T->rchild,idkey1,key2,T,tp);
    }
    else if(cmpkey(key2,T->data.Amount)==1){
        return SearchTradeTree(T->lchild,idkey1,key2,T,tp);//关键字是按交易id
    }
    else return SearchTradeTree(T->rchild,idkey1,key2,T,tp);
}

int InsertTxNode(TXTree &tt,long idkey ,double tamount,int blockid,char *fromid,char *toid){
    TXTree tp;
    if(!SearchTradeTree(tt,idkey,tamount,NULL,tp)){
        TXTree newtt;
        MakeTradeNode(newtt,idkey,blockid,fromid,tamount,toid);
        if(!tp)tt=newtt;//根结点
        else {
            if(cmpkey(tamount,tp->data.Amount)==-1)tp->rchild=newtt;//比较是按交易金额进行比较
            else tp->lchild=newtt;//我就改了一下顺序。。。。。
        }
        return TRUE;
    }
    else return FALSE;
}

void CreatTradeTree(BlockList &bl,int blockID,long txid,char *fromid, char *toid, double amount/*,long &sum*/){
    BlockP bp;
    bp=bl.head;
    while (bp!=NULL) {
        bp=bp->next;
        if(bp->block_ID==blockID){
            InsertTxNode(bp->Trade,txid,amount,blockID,fromid,toid);
//            sum++;
            break;
        }
    }
}

int CreatRichNode(char *name,double money,RichTree &rn){
    strcpy(rn->info.name,name);
    rn->info.pocession=money;
    rn->lchild=NULL;
    rn->rchild=NULL;
}

int SearchRichTree(RichTree RT,double money,RichTree parent,RichTree &rtp){
    if(!RT){
        rtp=parent;
        return FALSE;
    }
    else if(cmpkey(money,RT->info.pocession)==0){
        rtp=RT;
        return TRUE;
    }
    else if(cmpkey(money,RT->info.pocession)==1)
        return SearchRichTree(RT->lchild,money,RT,rtp);
    else return SearchRichTree(RT->rchild,money,RT,rtp);
}

int InsertRNode(RichTree &rt,char *name,double money){
    RichTree rtp;
    if(!SearchRichTree(rt,money,NULL,rtp)){
        RichTree newrich;
        CreatRichNode(name,money,newrich);
        if(!rtp)rt=newrich;
        else {
            if(cmpkey(money,rtp->info.pocession)==-1)rtp->lchild=newrich;
            else rtp->lchild=newrich;
        }
        return TRUE;
    }
    else return FALSE;
}

void CreatRichTree(RichList rl,RichTree &rt){
    RichP rp;
    rp=rl.head->next;
    while (rp!=NULL) {
        InsertRNode(rt,rp->name,rp->procession);
        rp=rp->next;
    }
}

int LoadTradeData(FILE *Tfilename,BlockList &bl){
    char line[100];
    long tx_id;
    int block_id;
    double amount;
    char *tx_ids=NULL;
    char *block_ids=NULL;
    char *From_id=NULL;
    char *amounts=NULL;
    char *To_id=NULL;
    long sum=0;
    Tfilename=fopen("C:\\Users\\cl\\Documents\\block1\\tx_data_part1_v2.csv","r");
    if(Tfilename==NULL)return 0;
    fseek(Tfilename,39L,0);
    while (!feof(Tfilename)) {
        fgets(line,100,Tfilename);
        tx_ids=strtok(line,",");
        tx_id=atol(tx_ids);
        block_ids=strtok(NULL,",");
        block_id=atoi(block_ids);
        From_id=strtok(NULL,",");
        amounts=strtok(NULL,",");
        amount=atof(amounts);
        To_id=strtok(NULL,"\n");
        if(tx_ids&&block_ids&&From_id&&amounts&&To_id)
            //给一个结点赋值
        {
            CreatTradeTree(bl,block_id,tx_id,From_id,To_id,amount);
//            sum++;
        }
    }
    fclose(Tfilename);
//    printf("total num: %ld\n",sum);
}



//以下用来返回所有记录
int PrintRecord(TXNode tn,char *id,int &sum,long k){
    if((strcmp(tn.data.FromID,id)==0||strcmp(tn.data.ToID,id)==0)&&sum<k)
    {
        sum++;
        printf("%s gave %.4f to %s\n",tn.data.FromID,tn.data.Amount,tn.data.ToID);
        return TRUE;
    }
    return FALSE;
}

int InOrderTraverse(TXTree T,int (*visit)(TXNode tn,char *id,int &sumi,long k1),char *recordid,int &sum,long k){
    if(T){
        InOrderTraverse(T->lchild,visit,recordid,sum,k);
        visit(*T,recordid,sum,k);
        InOrderTraverse(T->rchild,visit,recordid,sum,k);//这里导致一些数据没办法读出
        return TRUE;
    }
    return FALSE;
}

int LookUpRecord(char *ID,int blockid,BlockList BL,int &sum,long k){
    BlockP bp;
    bp=BL.head;
    while (bp->block_ID!=blockid) {
        bp=bp->next;
    }
    if(bp->block_ID==blockid){
        InOrderTraverse(bp->Trade,PrintRecord,ID,sum,k);
    }
}


//以下用来计算前k个记录
int CalculateMoney(TXNode tn,char *id,double &summoney){
    if(strcmp(tn.data.FromID,id)==0){
        summoney-=tn.data.Amount;
        return TRUE;
    }
    if(strcmp(tn.data.ToID,id)==0){
        summoney+=tn.data.Amount;
        return TRUE;
    }
    return FALSE;
}

int InOrderTraverse(TXTree T,int (*visit)(TXNode tn,char *id,double &sum1),char *recordid,double &sum){
    if(T){
        InOrderTraverse(T->lchild,visit,recordid,sum);
        visit(*T,recordid,sum);
        InOrderTraverse(T->rchild,visit,recordid,sum);//这里导致一些数据没办法读出
        return TRUE;
    }
    return FALSE;
}

int LookUpRecord(char *ID,int blockid,BlockList BL,double &sum){
    BlockP bp;
    bp=BL.head;
    while (bp->block_ID!=blockid) {
        bp=bp->next;
    }
    if(bp->block_ID==blockid){
        InOrderTraverse(bp->Trade,CalculateMoney,ID,sum);
    }
}

int RecordRichMan(RichList &rl,TXNode tn){
    RichP rp1,rp2;
    rp1=LocateRich(rl,tn.data.FromID,NameCheck);
    rp2=LocateRich(rl,tn.data.ToID,NameCheck);
    if(rp1||rp2){
        if(rp1) rp1->procession-=tn.data.Amount;
        if(rp2) rp2->procession+=tn.data.Amount;
    }
    else {
        if(!rp1){
            RichP rpp;
            MakeRich(rpp,-tn.data.Amount,tn.data.FromID);
            InsertRichMan(rl,rpp);
            rl.num++;
        }
        if(!rp2){
            RichP rpp1;
            MakeRich(rpp1,tn.data.Amount,tn.data.ToID);
            InsertRichMan(rl,rpp1);
            rl.num++;
        }
    }
}

int PrintRichList(RichNode rn){
    printf("%s %.4f",rn.info.name,rn.info.pocession);
}


//遍历富豪榜
int TraverseRichTree(RichTree rt,int (*visit)(RichNode rn)){
    if(rt){
        TraverseRichTree(rt->lchild,visit);
        visit(*rt);
        TraverseRichTree(rt->rchild,visit);
        return TRUE;
    }
    return FALSE;
}


int InOrderTraverse(RichList &R,TXTree T,int (*visit)(RichList &rl,TXNode tn)){
    if(T){
        InOrderTraverse(R,T->lchild,visit);
        visit(R,*T);
        InOrderTraverse(R,T->rchild,visit);
        return TRUE;
    }
    return FALSE;
}


int LookUpRecord(int blockid,BlockList BL,RichList &R){
    BlockP bp;
    bp=BL.head;
    while (bp->block_ID!=blockid) {
        bp=bp->next;
    }
    if(bp->block_ID==blockid){
        InOrderTraverse(R,bp->Trade,RecordRichMan);
    }
}


void BuildRichList(RichList &R,int blockid,BlockList BL){
    BlockP p;//用来遍历区块
    p=BL.head;
    while (p->block_ID!=blockid) {
        p=p->next;
        LookUpRecord(p->block_ID,BL,R);
    }
    if(p->block_ID==blockid)
        LookUpRecord(blockid,BL,R);
}


#endif // BLOCKLIST_H
