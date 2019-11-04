#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> a, b, c;
    a.push_back(10);
    a.push_back(5);
    b = a;
    c.assign(a.begin(), a.end());

    cout << &a << " " << &b << " " << &c << endl;
    cout << &a[1] << " " << &b[1] << " " << &c[1] << endl;

    return 0;
}