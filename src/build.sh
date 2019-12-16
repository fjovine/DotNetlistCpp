printf "\033c"
#g++ -o bin/netlist main.cpp BitmapScanner.cpp Segment.cpp Scanline.cpp DrillConnector.cpp MonochromeBitmapAccessor.cpp RealBitmapGenerator.cpp DrillScanner.cpp ../lodepng/lodepng.cpp meminfo.cpp
g++ -o bin/netlist.exe main.cpp BitmapScanner.cpp Segment.cpp Scanline.cpp DrillConnector.cpp MonochromeBitmapAccessor.cpp RealBitmapGenerator.cpp DrillScanner.cpp ../lodepng/lodepng.cpp
