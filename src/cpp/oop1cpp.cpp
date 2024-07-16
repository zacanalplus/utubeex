#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

namespace bitmap{
    typedef unsigned int pixel;
    
    const size_t DEF_PIX_LEN = 80;
    
    class bitpic {
    public:
        bitpic(); // default constructor
        pixel getpixel(size_t x, size_t y);
        bitpic(size_t length, size_t width);
        bitpic &setpixel(size_t x, size_t y, pixel val);
        ~bitpic();
        void print();
        void alloc();
        void abort();
    private:
        pixel *base;
        size_t xlen;
        size_t ylen;
    };
    
    class pix_counter{
    private:
        pixel p;
        size_t cnt;
    public:
        pix_counter(pixel val):p(val), cnt(1) {}
        size_t count() { return cnt; }
        pixel value() { return p; }
        pix_counter &operator++();
        void print(); 
    };
    
    class setbag {
    public:
        setbag();
        bool add_count(pix_counter &pc);
        setbag &add(pix_counter &pc);
        void print_maxmin();
        void print_all();
        ~setbag();
    private:
        vector<pix_counter> list;
        size_t minidx;
        size_t maxidx;
    };
    
    bitpic::bitpic():xlen(0),ylen(0), base(NULL){}
}


int main(int argc, char *argv[]) {
    bitmap::pixel rand_pix;
    srand(time(NULL));
    bitmap::bitpic bp(bitmap::DEF_PIX_LEN, bitmap::DEF_PIX_LEN);
    bitmap::setbag sb = bitmap::setbag();
    for(size_t i =0; i< bitmap::DEF_PIX_LEN; i++){
        for(size_t j=0; j < bitmap::DEF_PIX_LEN; j++){
            rand_pix = rand() % 10;
            bp.setpixel(i, j, rand_pix);
            bitmap::pix_counter pc = bitmap::pix_counter(rand_pix);
            sb.add(pc);
        }
    }
    sb.print_maxmin();
    sb.print_all();
    bp.print();
    return 0;
}

namespace bitmap {
    pixel bitpic::getpixel(size_t x, size_t y){
        abort();
        if(x < xlen && y < ylen){
            return base[x * xlen + y];
        }
        // index is not in range
        return 0;
    }
    
    bitpic::bitpic(size_t length, size_t width):xlen(length), ylen(width), base(NULL){
        alloc();
    }
    
    void bitpic::alloc(){
        if(xlen && ylen)
            base = new pixel[xlen * ylen];
    }
    
    void bitpic::abort(){
        if(!base){
            fprintf(stderr, "Picture is not initialized and empty. \n");
            exit(-1);
        }
    }
    
    bitpic &bitpic::setpixel(size_t x, size_t y, pixel val){
        abort();
        if(x < xlen && y < ylen){
            base[x * xlen + y] = val;
        }
        return *this;
    }
    
    void bitpic::print(){
        abort();
        for(size_t i = 0; i < xlen; i++){
            for(size_t j = 0; j < ylen; j++){
                printf("%u ", getpixel(i, j));
            }
            printf("\n");
        }
    }
    
    bitpic::~bitpic(){
        if(base)
            delete[] base;
    }
    
    pix_counter &pix_counter::operator++(){
        cnt++;
        return *this;
    }
    
    void pix_counter::print(){
        printf("Pixel value %u has count %zu. \n", p, cnt);
    }
    
    setbag::setbag():minidx(0), maxidx(0) {
        list = vector<pix_counter>();
    }
    
    bool setbag::add_count(pix_counter &pc){
        for(size_t i=0; i < list.size(); i++){
            if(list[i].value() == pc.value()){
                ++list[i];
                if(list[maxidx].count() < list[i].count()){
                    maxidx = i;
                }
                return true;
            }
            if(list[minidx].count() > list[i].count()){
                minidx = i;
            }
        }
        return false;
    }
    
    setbag &setbag::add(pix_counter &pc){
        if(!add_count(pc)){
            list.push_back(pc);
        }
        return *this;
    }
    
    void setbag::print_maxmin(){
        printf("Pixel value %u has maximum count %zu. \n", list[maxidx].value(), list[maxidx].count());
        printf("Pixel value %u has minimum count %zu. \n", list[minidx].value(), list[minidx].count());
    }
    
    void setbag::print_all(){
        for(pix_counter item : list){
            item.print();
        }
    }
    
    setbag::~setbag(){
        list.clear();
    }
}