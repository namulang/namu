#pragma once

#include "../TestCase.hpp"
#include "../Initiator.hpp"

namespace NE
{
    struct FileManipulatorTest : public TestCase {
        virtual const char* getName() const { return "FileManipulatorTest"; }
        virtual type_bool _onTest() {
            Folder root("C:\\", Folder::Option(true));
            
            int n = 0;
            while( ! root.next().isNull())
            {
                const File& e = root.peek();
                cout << e.getPath() << "\n";
                if(n++ > 10)
                    break;
            }

            return true;
        }
    };

    INITIATE_CLASS(FileManipulatorTest)
}