#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include "Grid.h"
#include "TifGrid.h"
#include "TimeVar.h"
#include "DatedName.h"

int main(int argc, char *argv[]) {

        char buf[256];

	if (argc != 4) {
		printf("Usage is accummrms path_to_precip_rate_files end_datetime increment\n");
		return 1;
	}

	TimeUnit thirtyMin = TimeUnit();
	thirtyMin.ParseUnit(argv[3]);	
	TimeUnit twoMin = TimeUnit();
	twoMin.ParseUnit((char*)"2u");

	TimeVar endTime = TimeVar();
	endTime.LoadTime(argv[2]);

	TimeVar startTime = TimeVar();
	startTime = endTime;
	startTime.Decrement(&thirtyMin);

	DatedName currentTimeText = DatedName();
	currentTimeText.SetNameStr("preciprate.YYYYMMDD.HHUU.tif");
	currentTimeText.ProcessNameLoose(NULL);
	TimeVar currentTime = TimeVar();
	currentTime = startTime;
	
	FloatGrid *accumGrid = NULL;
	
	for (currentTime.Increment(&twoMin); currentTime <= endTime; currentTime.Increment(&twoMin)) {
		currentTimeText.UpdateName(currentTime.GetTM());
		sprintf(buf, "%s/%s", argv[1], currentTimeText.GetName());
		if (!accumGrid) {
			accumGrid = ReadFloatTifGrid(buf);
		} else {
			FloatGrid *newGrid = ReadFloatTifGrid(buf);
			if (!newGrid) {
				continue;
			}
			for (int y = 0; y < accumGrid->numRows; y++) {
				for (int x = 0; x < accumGrid->numCols; x++) {
					if (accumGrid->data[y][x] != accumGrid->noData && newGrid->data[y][x] != newGrid->noData) {
						accumGrid->data[y][x] += newGrid->data[y][x];
					}
				}
			}
			delete newGrid;
		}
	}

	if (accumGrid) {
		currentTimeText.SetNameStr(".ACC.YYYYMMDD.HHUUSS.tif");
		currentTimeText.ProcessNameLoose(NULL);
                currentTimeText.UpdateName(endTime.GetTM());
		sprintf(buf, "%s%s", argv[3], currentTimeText.GetName());
		for (int y = 0; y < accumGrid->numRows; y++) {
			for (int x = 0; x < accumGrid->numCols; x++) {
				if (accumGrid->data[y][x] != accumGrid->noData) {
                                                accumGrid->data[y][x] = (accumGrid->data[y][x] / 30.0);
				}
			}
		}	
		WriteFloatTifGrid(buf, accumGrid);
		return 0;
	} else {
		printf("Failed to accumulate data for time %s\n", argv[2]);
		return 2;
	}
		
}
