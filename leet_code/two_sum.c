#include <stdio.h>



int main(){
    int list[] = {1, 4, 7, 11};
    int target = 11;
    int flag = 0;
    int size = sizeof(list)/sizeof(list[0]);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("Index: %d, %d\n", i, j);
            if ((list[i] + list[j]) == target) {
                printf("Success: Sum is %d\n", (list[i] + list[j]));
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            break;
        }
        
    }
    if (!flag){
        printf("Not Success");
    }
    
    return 0;
}