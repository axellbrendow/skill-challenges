#include <iostream>

using namespace std;

class asd
{
    public:
        int x;

        asd(int x) : x(x) {}
};

asd &create(asd &b)
{
    b.x = 150;

    return b;
}

int main()
{
    asd a(100);

    cout << a.x << endl;

    create(a).x = 200;

    cout << a.x << endl;

    return 0;
}
