#include <iostream>

using namespace std;

const size_t MAX_DIGITS {128};

class digits{
public:
    digits();
    inline size_t count() { return n; }
    explicit digits(int num);
    digits(long num);
    ~digits();
    void print();
private:
    bool alloc();
    size_t n; 
    char *digs; // digits of a specific number
};

int main(int argc, char *argv[]) {
    digits d(7634789);
    d.print();
    digits d2 = 239;
    d2.print();
    auto n = 74982012736458;
    digits d3(n);
    d3.print();
    digits d4;
    d4.print();
    digits d5 = 0;
    d5.print();
    return 0;
}

digits::digits():digs(nullptr), n(0){}

bool digits::alloc(){
    digs = new (nothrow)char[MAX_DIGITS];
    if(digs == nullptr)
        return false;
    return true;
}

digits::digits(int num):digits(){
    if(alloc()){
        if(num == 0){
            //digs[0] = '0';
            n = 1;
            return;
        }
        if(num < 0){
            num = -num;
        }
        size_t i{};
        while(num > 0){
            digs[i++] = num % 10;
            num /= 10;
            n++;
            if(n > MAX_DIGITS)
                break;
        }
    }
}

void digits::print(){
    if(n == 0)
        return;
    cout<<'[';
    for (int i=n-1; i >= 0; i--) {
        cout<<static_cast<int>(digs[i])<<',';
    }
    cout<<'\b'<<']'<<endl;
}

digits::~digits(){
    //static int cnt = 0;
    //static int in_cnt = 0;
    //cerr<<++cnt<<":normal count"<<endl;
    if(digs != nullptr){
        //cerr<<++in_cnt<<":process count"<<endl;
        delete digs;
    }
}

digits::digits(long num):digits(){
    if(alloc()){
        if(num == 0L){
            //digs[0] = '0';
            n = 1;
            return;
        }
        if(num < 0){
            num = -num;
        }
        size_t i{};
        while(num > 0L){
            digs[i++] = num % 10L;
            num /= 10L;
            n++;
            if(n > MAX_DIGITS)
                break;
        }
    }
}