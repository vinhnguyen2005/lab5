#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>




int main() {
    int a[3][3], det;
	printf("Enter element: \n");
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			//nhap matrix
			scanf("%d",&a[i][j]);
		}
	}
	//Tính det(làm kiểu nông dân tại cx ko nghĩ ra:(( 
	det = a[0][0] * ((a[1][1]*a[2][2]) - (a[2][1]*a[1][2])) -a[0][1] * (a[1][0]
   * a[2][2] - a[2][0] * a[1][2]) + a[0][2] * (a[1][0] * a[2][1] - a[2][0] * a[1][1]);
   printf("\nThe determinant of the given Matrix is %d\n",det);
    
    return 0;
}		