#include <cstdio>
#include <string>

class number_string{
public:
    number_string();
    number_string(int n);
    number_string(unsigned int);
    number_string(char);
    number_string(unsigned char);
    number_string(long);
    number_string(unsigned long);
    number_string(std::string);
    ~number_string();
private:
    char *str;
};


using namespace std;
int main(int argc, char *argv[]) {
    
}