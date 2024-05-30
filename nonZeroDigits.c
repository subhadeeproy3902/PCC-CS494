#include <stdio.h>
#include <stdlib.h>

int count(int i){
    int r, c = 0;
    while(i != 0){
        r = i % 10;
        i /= 10;
        if(r != 0){
            c++;
        }
    }
    return c;
}

int countNonZeroDigits(int n, int k){
    int i, c, x = 0, s = 0;
    for(i=1; i<=k; i++){
        s *= 10;
        s += 1;
    }
    for(i=s; i<=n; i++){
        c = count(i);
        if(c == k){
            printf("%d, ",i);
            x++;
        }
    }
    return x;
}

int main(){
    int n,k,c;
    printf("Enter n : ");
    scanf("%d",&n);
    printf("Enter k : ");
    scanf("%d",&k);

    if(k <= 0){
        printf("\nValue of 'k' should be greater than 0.\n\n");
        exit(0);
    }
    printf("\nDisplaying the integers containing %d non-zero digits between 1 to %d : \n",k,n);
    c = countNonZeroDigits(n, k);
    printf("\n\nCount = %d\n\n",c);
    return 0;
}