#include "../TestManager.hpp"

WRD_TEST_START(FileManipulatorTest)
	//  read-write test:
	T(File().remove())
	
	std::string current = ".";
	std::string input_path = current + "/../res/unittest/sample.txt";

	AsciiStream as(input_path);
	T(as.getPath() == input_path);
	T( ! as.init())
	T(as.isInit())

	std::string reaad = as.readLine();
	T(reaad != "")
	T( ! as.release())

	std::string output_filename = "FileManipulatorTest.txt";
	std::string source = current + "/" + output_filename;
	File output(source);
	T(output.getPath() == source)
	T(output.remove());

	
	//  searching test:
	Folder build(current, Folder::Option(false));
	T( ! build.isInit())
	T( ! build.init())
	T(build.isInit())
	wbool found = false;
	while( ! build.next().isNull())
		if(build.peek().getName() == output_filename)
		{
			found = true;
			break;
		}
	T( ! found)
	T( ! build.release());


	BinaryStream bs(source);
	T(bs.getPath() == source)
	T(bs.init())
	T( ! bs.isInit())
	T( ! bs.setMode(FileStream::APPENDABLE))
	T( ! bs.init())
	T(bs.isInit())
	T(bs.write(reaad) > 0)
	bs -= 1;
	T(bs.write("?", 1) > 0)
	bs = 2;
	T(bs.write("I'm ") > 0)
	T( ! bs.setCursor(bs.getEndOfFile()))
	T(bs.write(std::string(" keep testing!")) > 0)
	T( ! bs.release())

	T( ! as.setPath(source))
	T(as.getPath() == source)
	T( ! as.init())
	std::string reaaad = as.readLine();   
	reaad = "HeI'm hello world? keep testing!";
	T(reaaad == reaad)

	wint eof_cursor = as.getEndOfFile();

	std::string whole_context = as.readWhole();

	T(whole_context == reaad)
	T(as.isEndOfFile())
	T(as.getCursor() == eof_cursor)

	
	//  searching test:
	found = false;
	T(build.next().isNull())
	T( ! build.init())
	T(build.isInit())
	while( ! build.next().isNull())
		if(build.peek().getName() == output_filename)
		{
			found = true;

			break;
		}
	T(found)
	T( ! as.release());
	T( ! File("./" + output_filename).remove());

	return "";
WRD_TEST_END(FileManipulatorTest)
