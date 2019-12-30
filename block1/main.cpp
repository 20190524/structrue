#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<blocklist.h>
//区块结构
#define M 2000000


int main()
{
    //读入文件block
    FILE *fp;
    FILE *tfp;
    BlockList Block_L;
    BlockP bp;
    int num=LoadBlockData(fp,Block_L);// 存好区块链了
    printf("%d\n",num);
//    bp=Block_L.head->next;
//    while (bp) {
//        printf("%d %ld\n",bp->block_ID,bp->block_timestamp);
//        bp=bp->next;
//    }
    LoadTradeData(tfp,Block_L);//建好树了
//    bp=Block_L.head->next;
//    while (bp) {
//        printf("%d %ld %.4f\n",bp->block_ID,bp->block_timestamp,bp->Trade->data.Amount);
//        bp=bp->next;
//    }
    char checkID[35];
    printf("Which ID do you want to check?\n");
    scanf("%s",checkID);//字符串形式输入不用加&
    getchar();
    printf("Which time slot do you want to check?\n");
    int startID,endID;
    scanf("%d%d",&startID,&endID);
    getchar();
    //找区块间的相应信息
    int sum=0;
    bp=Block_L.head->next;
    while (bp) {
        if(bp->block_ID==startID)break;
        bp=bp->next;
    }
    LookUpRecord(checkID,bp->block_ID,Block_L,sum,M);
    while (bp->block_ID!=endID) {
        bp=bp->next;
        //计算一个区块中的记录数
        LookUpRecord(checkID,bp->block_ID,Block_L,sum,M);
    }
    printf("total records' number is: %d\n",sum);
    printf("please tell your k's value:\n");
    int k;
    scanf("%d",&k);
    sum=0;
    bp=Block_L.head->next;//重复查找一次,返回排名前k的记录
    while (bp) {
        if(bp->block_ID==startID)break;
        bp=bp->next;
    }
    LookUpRecord(checkID,bp->block_ID,Block_L,sum,k);
    if(sum<k)
    {
        while (bp->block_ID!=endID) {
            bp=bp->next;
            //计算一个区块中的记录数
            LookUpRecord(checkID,bp->block_ID,Block_L,sum,k);
        }
    }
    printf("now we are calculating an account's total money!\n"
           "please tell me who do you want to know?\n");
    char account[35];
    scanf("%s",account);
    getchar();
    int xid;
    printf("what time do you want to stop?\n");
    scanf("%d",&xid);
    double totalmoney=0;
    bp=Block_L.head->next;
    while (bp->block_ID!=xid) {
        LookUpRecord(account,bp->block_ID,Block_L,totalmoney);//这有个致命错误，导致重复运算
        bp=bp->next;
    }
    LookUpRecord(account,xid,Block_L,totalmoney);
    printf("total money is:%.4f\n",totalmoney);

    //土豪榜(๑•̀ㅂ•́)و✧
    printf("Do you want to know the rich list ?\n"
           "pleaese tell me your k's value:\n");
    int richnum;
    scanf("%d",&richnum);
    printf("And tell me the last time you want to end with :\n");
    int endtime;
    scanf("%d",&endtime);
    //先用链表存，再转换为树，最后遍历输出
    RichList richman;
    InitListR(richman);
    BuildRichList(richman,endtime,Block_L);//建好土豪链表
//    RichP rpt;
//    rpt=richman.head->next;
//    while (rpt) {
//        printf("%s %f\n",rpt->name,rpt->procession);
//        rpt=rpt->next;
//    }
    //开始建土豪树
    //建好树就把土豪链表删去！
    RichTree richtree=NULL;
    CreatRichTree(richman,richtree);
    TraverseRichTree(richtree,PrintRichList);
    DestroyRichList(richman);
    //再计算一次
    //创建区块链
    //读入文件data
    //初始化区块中的交易数据
    //
    return 0;
}
