#include<bits/stdc++.h>
#include<string>
using namespace std;
#include<chrono>
using namespace std::chrono;

#define SHA256_H
 
class SHA256
{
protected:
    typedef unsigned char uint8;
    typedef unsigned int uint32;
    typedef unsigned long long uint64;
 
    const static uint32 sha256_k[];
    static const unsigned int SHA224_256_BLOCK_SIZE = (512/8);
public:
    void init();
    void update(const unsigned char *message, unsigned int len);
    void final(unsigned char *digest);
    static const unsigned int DIGEST_SIZE = ( 256 / 8);
 
protected:
    void transform(const unsigned char *message, unsigned int block_nb);
    unsigned int m_tot_len;
    unsigned int m_len;
    unsigned char m_block[2*SHA224_256_BLOCK_SIZE];
    uint32 m_h[8];
};
 
std::string sha256(std::string input);



int main()
{
    auto start = high_resolution_clock::now();
    string file;
    cout<<"Enter your input\n";
    cin>>file;
    cout<<"\n"<<file<<"\n"<<sha256(file);

   /* while(ch!=EOF)
    {
        file=file+getch();
    }
    auto concat_val = '0';
    concat_val+=1;
    //while(1)
    {
        cout<<file+concat_val;
    }*/
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout<<"\n"<<duration.count()<<"\n";
    return 0;
}
