#include "stdio.h"
#include "math.h"
#include <stdlib.h>
typedef struct s_dvec2
{
	double					x;
	double					y;
}						t_dvec2;

int** createMap() {
    // Allocate memory for the map
    int** map;
    map = (int**)malloc(10 * sizeof(int*));
    for (int i = 0; i < 10; i++) {
        map[i] = (int*)malloc(10 * sizeof(int));
    }

    // Initialize the map with walls (0) and floors (1)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == 0 || i == 10 - 1 || j == 0 || j == 10 - 1) {
                map[i][j] = 0;  // Set walls (edges) to 0
            } else {
                map[i][j] = 1;  // Set floor (interior) to 1
            }
        }
    }

    return map;
}

void printMap(int** map) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
}

int is_wall_tile(t_dvec2 pos, int **map)
{
    double x;
    double y;
    
    x = floor(pos.x);
    y = floor(pos.y);

    if (x < 0 || x  > 9 || y < 0 || y  > 9)
        return (1);
    if (map[(int)y][(int)x]) 
        return (1);
    return (0);
}


int main() 
{
    int** map = createMap();
    t_dvec2 pos;

    pos.x = 1.5;
    pos.y = 1.5;

    if(is_wall_tile(pos, map))
        printf("Wall\n");
    else
        printf("no wall\n");

    printMap(map);
    return 0;
}