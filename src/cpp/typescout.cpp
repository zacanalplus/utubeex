#include <iostream>
#include <iomanip>

extern "C"{
    int add(int x, int y);
}
using namespace std;
int main(int argc, char *argv[]) {
    auto ticks {15'000'000};
    cout<<ticks<<endl;
    ticks = 0b0010'0110'0011'0011;
    //////////   2    6    3    3
    
    
    cout<<ticks<<' '<<setbase(16)<<"0x"<<ticks<<endl;
    cout<<sizeof(ticks)<<endl;
    
    auto ip = new int(47);
    cout<<setbase(10)<<*ip<<endl;
    
    const auto pi = 3.14159270;
    
    cout<<setprecision(8)<<pi<<endl;
    
    cout<<numeric_limits<unsigned long long>::max()<<endl;
    wchar_t me { L'ဇ' };
    wcout<<'-'<< me <<'-'<<endl;
    
    return 0;
}

