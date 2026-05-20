#include <iostream>
using namespace std;
void a(){
    cout<<8<<endl;
    b()
}
void b(){
    cout<<9<<endl;
    c();
}
void c(){
    cout<<10<<endl;
}
int main(){
    // calling b()
    b();
    return 0;
}