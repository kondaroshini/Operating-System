#include <stdio.h>

int main() {
    int numFrames, numPages, frames[10], pages[30], temp[10], flag1, flag2, flag3, i, j, k, pos, max, faults = 0, hits = 0;
    
    printf("Enter number of frames: ");
    scanf("%d", &numFrames);
    
    printf("Enter number of pages: ");
    scanf("%d", &numPages);
    
    printf("Enter page reference string: ");
    
    for(i = 0; i < numPages; ++i){
        scanf("%d", &pages[i]);
    }
    
    for(i = 0; i < numFrames; ++i){
        frames[i] = 0;
    }
    
    for(i = 0; i < numPages; ++i){
        flag1 = flag2 = 0;
        
        for(j = 0; j < numFrames; ++j){
            if(frames[j] == pages[i]){
                flag1 = flag2 = 1;
                hits++;
                break;
            }
        }
        
        if(flag1 == 0){
            for(j = 0; j < numFrames; ++j){
                if(frames[j] == 0){
                    faults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }    
        }
        
        if(flag2 == 0){
            flag3 = 0;
        
            for(j = 0; j < numFrames; ++j){
                temp[j] = -1;
            
                for(k = i + 1; k < numPages; ++k){
                    if(frames[j] == pages[k]){
                        temp[j] = k;
                        break;
                    }
                }
            }
            
            for(j = 0; j < numFrames; ++j){
                if(temp[j] == -1){
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }
            
            if(flag3 == 0){
                max = temp[0];
                pos = 0;
            
                for(j = 1; j < numFrames; ++j){
                    if(temp[j] > max){
                        max = temp[j];
                        pos = j;
                    }
                }            
            }
            frames[pos] = pages[i];
            faults++;
        }
        
        printf("\n");
        
        for(j = 0; j < numFrames; ++j){
            printf("%d\t", frames[j]);
        }
    }
    
    printf("\n\nTotal Page Faults = %d\n", faults);
    printf("Total Page Hits = %d\n", hits);
    
    return 0;
}

