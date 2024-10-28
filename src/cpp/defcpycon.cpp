#include <iostream>

using namespace std;

const size_t MAX_DIGITS {128};

class digits{
public:
    digits();
    digits(int num);
    digits(long num);
    digits(const digits &d); // Copy constructor
    void print();
    ~digits();
    inline long to_number() { return oval; }
private:
    bool alloc();
    char *dgs; // store all digits 
    size_t n;  // length of `dgs`, the total number of digits in array `dgs`
    long oval; // original value of number
};

void add_one(digits d);

int main(int argc, char *argv[]) {
    digits d1;
    d1.print();
    digits d2(76'453);
    d2.print();
    digits d3 = 912;
    d3.print();
    auto n = 7'650'091'287'432'499L;
    digits d4(n);
    add_one(d4);
    d4.print();
    return 0;
}

digits::digits():dgs(nullptr), n(0), oval(0L){
    // Empty default constructor
}

void digits::print(){
    if(n == 0)
        return;
    cout<<'[';
    for(int i=n-1; i >= 0; i--){
        cout<<static_cast<int>(dgs[i])<<',';
    }
    cout<<"\b]"<<endl;
}

digits::digits(int num):digits(){
    if(alloc()){
        oval = static_cast<long>(num);
        if(num == 0){
            dgs[0] = '\0';
            n = 1;
            return;
        }
        if(num < 0){
            num = -num;
        }
        size_t i {};
        while(num > 0){
            dgs[i++] = num % 10;
            num /= 10;
            n++;
        }
    }
}

bool digits::alloc(){
    dgs = new (nothrow) char [MAX_DIGITS];
    if(dgs == nullptr)
        return false;
    return true;
}

digits::~digits(){
    if(dgs != nullptr)
        delete[] dgs;
    n = 0;
}

digits::digits(long num):digits(){
    if(alloc()){
        oval = num;
        if(num == 0){
            dgs[0] = '\0';
            n = 1;
            return;
        }
        if(num < 0){
            num = -num;
        }
        size_t i {};
        while(num > 0){
            dgs[i++] = num % 10;
            num /= 10;
            n++;
        }
    }
}

void add_one(digits d){
    long num = d.to_number();
    num += 1;
    digits d1(num);
    d1.print();
    return;
}

digits::digits(const digits &d):digits(){
    if(alloc()){
        for(int i = 0; i < d.n; i++){
            dgs[i] = d.dgs[i];
        }
        n = d.n;
        oval = d.oval;
    }
}