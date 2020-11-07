#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    freopen("E:\\algorithm_EXP\\test-1-5.txt", "w", stdout);
    int num[] = {50, 100, 40, 70, 120};
    for (auto i : num)
    {
        cout << i << endl;
        for (int a = 1; a <= i; a++)
        {
            char s = a + i;
            for (int i = 0; i < 7; i++)
            {

                s *= a;
                s = abs(s % 26);
                s += 'A';
                cout << s;
            }
            cout << endl;
        }
    }
    return 0;
}