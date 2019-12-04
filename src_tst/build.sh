printf "\033c"
g++ unit_tests.cpp MockupBitmapAccessor.cpp ../src/IBitmapAccessor.cpp ../src/Segment.cpp && ./a.out
