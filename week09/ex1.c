#include <stdio.h>

const int NUMBER_OF_PAGE_FRAME_BITS = 8;

struct pageStruct{
    int pageNumber;
    int pageFrame;
};

int numOfPages;

int main() {
    puts("Please input the number of page frames:");
    scanf("%d", &numOfPages);
    if (numOfPages < 1){
        printf( "Number of pages should be a positive integer!" );
        return -1;
    }
    struct pageStruct pageArr[numOfPages];
    for (int i = 0; i < numOfPages; i++){
        pageArr[i].pageNumber = -1;
        pageArr[i].pageFrame = -1;
    }
    char fileName[50] = "C:\\Users\\prhas\\Desktop\\Lab 09 input.txt";
    FILE *myFile = fopen(fileName, "r");
    if (myFile == NULL){
        printf( "Input file failed to open." );
        return -1;
    }
    int cur;
    fscanf (myFile, "%d", &cur);
    int curSize = 0;
    int tot = 0;
    int hitNum = 0;
    int missNum = 0;
    while(!feof(myFile)){
        tot++;
        //printf("%d\n", cur);
        int mn = 0;
        int isHit = 0;
        for (int i = 0; i < curSize; i++){
            if (pageArr[i].pageFrame < pageArr[mn].pageFrame){
                mn = i;
            }
            if (cur == pageArr[i].pageNumber){
                pageArr[i].pageFrame /= 2;
                pageArr[i].pageFrame += (1 << (NUMBER_OF_PAGE_FRAME_BITS - 1));
                isHit = 1;
            }
            else{
                pageArr[i].pageFrame /= 2;
            }
        }
        if (isHit){
            hitNum++;
        }
        else{
            if (curSize < numOfPages){
                pageArr[curSize].pageNumber = cur;
                pageArr[curSize].pageFrame = (1 << (NUMBER_OF_PAGE_FRAME_BITS - 1));
                curSize++;
            }
            else{
                pageArr[mn].pageNumber = cur;
                pageArr[mn].pageFrame = (1 << (NUMBER_OF_PAGE_FRAME_BITS - 1));
            }
        }
        fscanf (myFile, "%d", &cur);
    }
    missNum = tot - hitNum;
    printf("Total references is %d.\n", tot);
    printf("Number of hits is %d.\n", hitNum);
    printf("Number of misses is %d.\n", missNum);
    printf("Hit Rate is: %f\n", (float)hitNum / (float)tot);
    printf("Miss Rate is: %f\n", (float)missNum / (float)tot);
    printf("Hit/Miss Rate is: %f\n", (float)hitNum / (float)missNum);
    fclose(myFile);
    return 0;
}
