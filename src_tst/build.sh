printf "\033c"
#g++ unit_tests.cpp MockupBitmapAccessor.cpp ../src/IBitmapAccessor.cpp ../src/Segment.cpp ../src/BitmapScanner.cpp ../src/Scanline.cpp ../src/DrillScanner.cpp ../src/DrillConnector.cpp && ./a.out
g++ unit_tests.cpp MockupBitmapAccessor.cpp ../src/IBitmapAccessor.cpp ../src/Segment.cpp ../src/BitmapScanner.cpp ../src/Scanline.cpp ../src/DrillScanner.cpp ../src/DrillConnector.cpp && ./a.exe
