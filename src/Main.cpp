#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Grid.h"
#include "TifGrid.h"

int main(int argc, char *argv[]) {

	char buf[256];

	if (argc != 6) {
		printf("Command is ./precip_rp ari_ref_grids precip_grid ffg_grid ari_output ffg_output\n");
		return 1;
	}
	
	sprintf(buf, "%s/1_nmq.tif", argv[1]);
	FloatGrid *yr1 = ReadFloatTifGrid(buf);
	if (yr1 == NULL) {
		printf("Unable to open %s\n", buf);
		return 1;
	}
	sprintf(buf, "%s/2_nmq.tif", argv[1]);
        FloatGrid *yr2 = ReadFloatTifGrid(buf);
	if (yr2 == NULL) {
                printf("Unable to open %s\n", buf);
                return 1;
        }
	sprintf(buf, "%s/5_nmq.tif", argv[1]);
        FloatGrid *yr5 = ReadFloatTifGrid(buf);
	if (yr5 == NULL) {
                printf("Unable to open %s\n", buf);
                return 1;
        }
	sprintf(buf, "%s/10_nmq.tif", argv[1]);
        FloatGrid *yr10 = ReadFloatTifGrid(buf);
	if (yr10 == NULL) {
                printf("Unable to open %s\n", buf);
                return 1;
        }
	sprintf(buf, "%s/25_nmq.tif", argv[1]);
        FloatGrid *yr25 = ReadFloatTifGrid(buf);
	if (yr25 == NULL) {
                printf("Unable to open %s\n", buf);
                return 1;
        }
	sprintf(buf, "%s/50_nmq.tif", argv[1]);
        FloatGrid *yr50 = ReadFloatTifGrid(buf);
	if (yr50 == NULL) {
                printf("Unable to open %s\n", buf);
                return 1;
        }
	sprintf(buf, "%s/100_nmq.tif", argv[1]);
        FloatGrid *yr100 = ReadFloatTifGrid(buf);
	if (yr100 == NULL) {
                printf("Unable to open %s\n", buf);
                return 1;
        }
	sprintf(buf, "%s/200_nmq.tif", argv[1]);
        FloatGrid *yr200 = ReadFloatTifGrid(buf);
	if (yr200 == NULL) {
                printf("Unable to open %s\n", buf);
                return 1;
        }

	FloatGrid *ffg = ReadFloatTifGrid(argv[3]);
        if (ffg == NULL) {
                printf("Unable to open %s\n", argv[3]);
                return 1;
        }

	FloatGrid *precip = ReadFloatTifGrid(argv[2]);
	if (precip == NULL) {
		printf("Unable to open %s\n", argv[2]);
		return 1;
	}
	ffg->noData = precip->noData;
	for (int y = 0; y < precip->numRows; y++) {
		for (int x = 0; x < precip->numCols; x++) {
			
			if (precip->data[y][x] == precip->noData || ffg->data[y][x] == -999) {
                                ffg->data[y][x] = ffg->noData;
                        } else {
				float val = precip->data[y][x] * 100.0 / ffg->data[y][x];
				val = floorf(val / 5.0 + 0.5f) * 5.0f;
                                ffg->data[y][x] = val;
                        }

			if (precip->data[y][x] == precip->noData || yr200->data[y][x] == yr200->noData || yr200->data[y][x] <= 0.0) {
				precip->data[y][x] = precip->noData;
			} else if (precip->data[y][x] > (yr200->data[y][x] * 0.0254)) {
				precip->data[y][x] = 200.0;
			} else if (precip->data[y][x] > (yr100->data[y][x] * 0.0254)) {
				float diffY = 200.0 - 100.0;
				float diffX = (yr200->data[y][x] - yr100->data[y][x]) * 0.0254;
				float slope = diffY/diffX;
				float diffP = precip->data[y][x] - (yr100->data[y][x] * 0.0254);
                                precip->data[y][x] = 100.0 + diffP*slope;
                        } else if (precip->data[y][x] > (yr50->data[y][x] * 0.0254)) {
				float diffY = 100.0 - 50.0;
                                float diffX = (yr100->data[y][x] - yr50->data[y][x]) * 0.0254;
                                float slope = diffY/diffX;
                                float diffP = precip->data[y][x] - (yr50->data[y][x] * 0.0254);
                                precip->data[y][x] = 50.0 + diffP*slope;
                        } else if (precip->data[y][x] > (yr25->data[y][x] * 0.0254)) {
				float diffY = 50.0 - 25.0;
                                float diffX = (yr50->data[y][x] - yr25->data[y][x]) * 0.0254;
                                float slope = diffY/diffX;
                                float diffP = precip->data[y][x] - (yr25->data[y][x] * 0.0254);
                                precip->data[y][x] = 25.0 + diffP*slope;
                        } else if (precip->data[y][x] > (yr10->data[y][x] * 0.0254)) {
				float diffY = 25.0 - 10.0;
                                float diffX = (yr25->data[y][x] - yr10->data[y][x]) * 0.0254;
                                float slope = diffY/diffX;
                                float diffP = precip->data[y][x] - (yr10->data[y][x] * 0.0254);
                                precip->data[y][x] = 10.0 + diffP*slope;
                        } else if (precip->data[y][x] > (yr5->data[y][x] * 0.0254)) {
				float diffY = 10.0 - 5.0;
                                float diffX = (yr10->data[y][x] - yr5->data[y][x]) * 0.0254;
                                float slope = diffY/diffX;
                                float diffP = precip->data[y][x] - (yr5->data[y][x] * 0.0254);
                                precip->data[y][x] = 5.0 + diffP*slope;
                        } else if (precip->data[y][x] > (yr2->data[y][x] * 0.0254)) {
				float diffY = 5.0 - 2.0;
                                float diffX = (yr5->data[y][x] - yr2->data[y][x]) * 0.0254;
                                float slope = diffY/diffX;
                                float diffP = precip->data[y][x] - (yr2->data[y][x] * 0.0254);
                                precip->data[y][x] = 2.0 + diffP*slope;
                        } else if (precip->data[y][x] > (yr1->data[y][x] * 0.0254)) {
				float diffY = 2.0 - 1.0;
                                float diffX = (yr2->data[y][x] - yr1->data[y][x]) * 0.0254;
                                float slope = diffY/diffX;
                                float diffP = precip->data[y][x] - (yr1->data[y][x] * 0.0254);
                                precip->data[y][x] = 1.0 + diffP*slope;
                        } else {
				precip->data[y][x] = 0.0;
			}

		}
	}

	WriteFloatTifGrid(argv[4], precip);
	WriteFloatTifGrid(argv[5], ffg);

	return 0;
}
