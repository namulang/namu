#include <iostream>
#include "../file-manipulator/Headers.hpp"
using namespace std;

int main()
{
    using namespace NE;

    cout << "test1\n";

    Folder root("C:\\", Folder::Option(true));
    while( ! root.next().isNull())
    {
        const File& e = root.peek();
        cout << e.getPath() << "\n";
    }

    system("pause");
}