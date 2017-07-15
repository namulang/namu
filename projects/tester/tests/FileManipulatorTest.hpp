#pragma once

#include <file-manipulator.hpp>
#include "../TestCase.hpp"
#include "../Initiator.hpp"

namespace NE
{
    struct FileManipulatorTest : public TestCase {
        virtual const char* getName() const { return "FileManipulatorTest"; }
        virtual std::string _onTest() {
            Folder root("C:\\", Folder::Option(true));
            
            int n = 0;
            while( ! root.next().isNull())
            {
                const File& e = root.peek();
                std::cout << e.getPath() << "\n";
                if(n++ > 10)
                    break;
            }
            NE_ASSERT_OR_RETURN(n < 10)
            
            return "";
        }
    };

    INITIATE_CLASS(FileManipulatorTest)
}