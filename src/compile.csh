#!/bin/csh

g++ -g -O3 -ltiff -lgeotiff -lz -I/usr/include/libgeotiff  Main.cpp TifGrid.cpp MRMSGrid.cpp -o precip_rp
g++ -O3 -ltiff -lgeotiff -lz -I/usr/include/libgeotiff  AccumMRMS.cpp TifGrid.cpp MRMSGrid.cpp TimeVar.cpp TimeUnit.cpp DatedName.cpp -o accummrms
g++ -O3 -ltiff -lgeotiff -lz -I/usr/include/libgeotiff  AccumTIF.cpp TifGrid.cpp TimeVar.cpp TimeUnit.cpp DatedName.cpp -o accumtif
g++ -O3 -ltiff -lgeotiff -lz -I/usr/include/libgeotiff  MaxTIF.cpp TifGrid.cpp -o maxtif
