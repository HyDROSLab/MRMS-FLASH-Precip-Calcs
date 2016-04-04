#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include "Grid.h"
#include "TifGrid.h"

int main(int argc, char *argv[]) {

        char buf[256];

	if (argc < 2) {
		printf("Usage is maxtif outputfile inputfiles\n");
		return 1;
	}
	
	FloatGrid *maxGrid = NULL;
	
	for (int i = 2; i < argc; i++) {
		if (!maxGrid) {
			maxGrid = ReadFloatTifGrid(argv[i]);
		} else {
			FloatGrid *newGrid = ReadFloatTifGrid(argv[i]);
			if (!newGrid) {
				continue;
			}
			for (int y = 0; y < maxGrid->numRows; y++) {
				for (int x = 0; x < maxGrid->numCols; x++) {
					if (newGrid->data[y][x] != newGrid->noData && newGrid->data[y][x] > maxGrid->data[y][x]) {
						maxGrid->data[y][x] = newGrid->data[y][x];
					}
				}
			}
			delete newGrid;
		}
	}

	if (maxGrid) {
		WriteFloatTifGrid(argv[1], maxGrid);
		return 0;
	} else {
		printf("Failed to create maximum data grid %s\n", argv[1]);
		return 2;
	}
		
}
