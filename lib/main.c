#include <stdio.h>
#include "inc/my_math.h"
#include "inc/hello.h"
#include "inc/goodbye.h"
#include "inc/sub.h"

int main(){
    hello();
    printf("4 + 5 = %d \n",sum(4,5));
    printf("%d - 5 = %d \n",sum(4,5),sub(sum(4,5),5));
    goodbye();
    return 0;
}