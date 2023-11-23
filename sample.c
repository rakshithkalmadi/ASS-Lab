#include<stdio.h>
int main(int argc, char const *argv[])
{
    int n;
    printf("Enter the number: ");
    scanf("%d",&n);
    
    for(int j=1;j<n;j++){
        int flag =1;
        for(int i=2;i<=j/2;i++){
        if(j%i==0){
            flag = 0;
            break;
        }
    }
    if(flag && j!=1){
        printf("%d is a prime number\n",j);
    }

    }
    
    return 0;
}
