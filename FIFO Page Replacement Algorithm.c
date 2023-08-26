#include <stdio.h>
int main() {
    
    int frames;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    int incomingStream[100];  
    int pages;
    printf("Enter the number of pages in the incoming stream: ");
    scanf("%d", &pages);
    printf("Enter the page numbers in the incoming stream:\n");
    for (int i = 0; i < pages; i++) {
        
        scanf("%d", &incomingStream[i]);
    }
    
    int pageFaults = 0;
    int hitcounts[pages];
    for(int i=0;i<pages;i++){
    hitcounts[i]=0;
    }
    int temp[frames];
    for (int m = 0; m < frames; m++) {
        temp[m] = -1;
    }
    printf("Incoming\tFrame 1\t\tFrame 2\t\tFrame 3\n");
    for (int m = 0; m < pages; m++) {
        int s = 0;
        for (int n = 0; n < frames; n++) {
            if (incomingStream[m] == temp[n]) {
                s++;
                hitcounts[incomingStream[m]]++;
                pageFaults--;
            }
        }
        pageFaults++;
        if ((pageFaults <= frames) && (s == 0)) {
            temp[m] = incomingStream[m];
        }
        else if (s == 0) {
            temp[(pageFaults - 1) % frames] = incomingStream[m];
        }
        printf("%d\t\t", incomingStream[m]);
        for (int n = 0; n < frames; n++) {
            if (temp[n] != -1)
                printf("%d\t\t", temp[n]);
            else
                printf("-\t\t");
            }
            printf("\n");
        }
    
        printf("Total Page Faults:%d\n", pageFaults);
        printf("page Hit counts:\n");
        for(int i=0;i<pages;i++){
            printf("page %d : %d hits\n",hitcounts[i]);
    }
    return 0;
}