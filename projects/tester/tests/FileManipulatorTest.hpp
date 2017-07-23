#pragma once

#include <file-manipulator.hpp>
#include "../TestCase.hpp"
#include "../Initiator.hpp"

namespace NE
{
    struct FileManipulatorTest : public TestCase {
        virtual const char* getName() const { return "FileManipulatorTest"; }
        virtual std::string _onTest() {
            //  read-write test:
            NE_ASSERT_THEN_RETURN( ! File().remove())
            
            std::string current = ".";
            std::string input_path = current + "/sample.txt";

            AsciiStream as(input_path);
            NE_ASSERT_THEN_RETURN(as.getPath() != input_path);
            NE_ASSERT_THEN_RETURN(as.initialize())
            NE_ASSERT_THEN_RETURN( ! as.isInitialized())

            std::string reaad = as.readLine();
            NE_ASSERT_THEN_RETURN(reaad == "")
            NE_ASSERT_THEN_RETURN(as.release())

            std::string output_filename = "FileManipulatorTest.txt";
            std::string source = current + "/" + output_filename;
            File output(source);
            NE_ASSERT_THEN_RETURN(output.getPath() != source)
            output.remove();

            
            //  searching test:
            Folder build(current, Folder::Option(false));
            NE_ASSERT_THEN_RETURN(build.isInitialized())
            NE_ASSERT_THEN_RETURN(build.initialize())
            NE_ASSERT_THEN_RETURN( ! build.isInitialized())
            type_bool found = false;
            while( ! build.next().isNull())
                if(build.peek().getName() == output_filename)
                {
                    found = true;
                    break;
                }
            NE_ASSERT_THEN_RETURN(found)
            NE_ASSERT_THEN_RETURN(build.release());


            BinaryStream bs(source);
            NE_ASSERT_THEN_RETURN(bs.getPath() != source)
            NE_ASSERT_THEN_RETURN(! bs.initialize())
            NE_ASSERT_THEN_RETURN(bs.isInitialized())
            NE_ASSERT_THEN_RETURN(bs.setMode(FileStream::OVERWRITE_ONLY))
            NE_ASSERT_THEN_RETURN(! bs.initialize())
            NE_ASSERT_THEN_RETURN(bs.isInitialized())
            NE_ASSERT_THEN_RETURN(bs.setMode(FileStream::WRITABLE))
            NE_ASSERT_THEN_RETURN(bs.initialize())
            NE_ASSERT_THEN_RETURN( ! bs.isInitialized())
            NE_ASSERT_THEN_RETURN(bs.write(reaad) <= 0)
            NE_ASSERT_THEN_RETURN(bs -= 1)
            NE_ASSERT_THEN_RETURN(bs.write("?", 1) <= 0)
            NE_ASSERT_THEN_RETURN(bs = 2)
            NE_ASSERT_THEN_RETURN(bs.write("I'm ") <= 0)
            NE_ASSERT_THEN_RETURN(bs.setCursor(bs.getEndOfFile()))
            NE_ASSERT_THEN_RETURN(bs.write(std::string(" keep testing!")) <= 0)
            NE_ASSERT_THEN_RETURN(bs.release())

            NE_ASSERT_THEN_RETURN(as.setPath(source))
            NE_ASSERT_THEN_RETURN(as.getPath() != source)
            NE_ASSERT_THEN_RETURN(as.initialize())
            std::string reaaad = as.readLine();   
            reaad = "HeI'm hello world? keep testing!";
            NE_ASSERT_THEN_RETURN(reaaad != reaad)

            
            //  searching test:
            found = false;
            NE_ASSERT_THEN_RETURN( ! build.next().isNull())
            NE_ASSERT_THEN_RETURN(build.initialize())
            NE_ASSERT_THEN_RETURN( ! build.isInitialized())
            while( ! build.next().isNull())
                if(build.peek().getName() == output_filename)
                {
                    found = true;
                    break;
                }
            NE_ASSERT_THEN_RETURN( ! found)

            
            return "";
        }
    };

    INITIATE_CLASS(FileManipulatorTest)
}