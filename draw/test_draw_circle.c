#include <stdio.h>

#include <math.h>

int main ()

{
	int i,j,k,r=10,x=10,y=10,d,a,l;

	for(i=0;i<24;i++){
		for(j=0;j<25;j++){
			a=((i-x)*(i-x))+((j-y)*(j-y));
			d=sqrt(a);
			if(r>=d){
				printf("*");
			}
		}
	printf("\n");
	}
	return 0;
}

int	in_circle(float x, float y, float x1, float y1)
{
	float	distance;

	distance = sqrtf(powf(x - x1, 2.0f) + powf(y - y1, 2.0f));
	if (distance <= 100)
		return (1);
	return (0);
}

void	draw_shape(t_zone *zone, char *drawing, t_shape *shape)
{
	int	y;
	int	x;
	int	is_it;

	y = 0;
	while (y < MINIMAPHEIGHT)
	{
		x = 0;
		while (x < MINIMAPWIDTH)
		{
			is_it = in_circle((float)x, (float)y, MOVEX, MOVEY);
			if ( is_it == 2)||  is_it))
				my_m
			x++;
		}
		y++;
	}
}

//square ramk
// if (i <= MM_BOARD_SIZE || i >= MINIMAPHEIGHT - MM_BOARD_SIZE)
// 	my_mlx_pixel_put(data, i , j , MM_BOARD_COL);
// else if (j <= MM_BOARD_SIZE || j >= MINIMAPWIDTH - MM_BOARD_SIZE)
// 	my_mlx_pixel_put(data, i , j , MM_BOARD_COL);