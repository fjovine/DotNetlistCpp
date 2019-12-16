#include <string>
#include <malloc.h>
#include <iostream>

using namespace std;

void
log_memory_usage(const string &label = string())
{
	struct mallinfo m = mallinfo();
	cout << "mallinfo:" << label << endl;
	cout << "  non-mmapped space allocated from system ="<<m.arena<<endl;
	/*
	cout << "  number of free chunks ="<<m.ordblks<<endl;
	cout << "  number of fastbin blocks ="<<m.smblks<<endl;
	cout << "  number of mmapped regions ="<<m.hblks<<endl;
	cout << "  space in mmapped regions ="<<m.hblkhd<<endl;
	cout << "  maximum total allocated space ="<<m.usmblks<<endl;
	cout << "  space available in freed fastbin blocks ="<<m.fsmblks<<endl;
	cout << "  total allocated space ="<<m.uordblks<<endl;
	cout << "  total free space ="<<m.fordblks<<endl;
	*/
}