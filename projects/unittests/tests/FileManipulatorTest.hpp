#pragma once

#include "../TestCase.hpp"

WRD_TESTCASE(FileManipulatorTest, (
	//  read-write test:
	WRD_TEST(File().remove())
	
	std::string current = ".";
	std::string input_path = current + "/resources/sample.txt";

	AsciiStream as(input_path);
	WRD_TEST(as.getPath() == input_path);
	WRD_TEST( ! as.init())
	WRD_TEST(as.isInit())

	std::string reaad = as.readLine();
	WRD_TEST(reaad != "")
	WRD_TEST( ! as.release())

	std::string output_filename = "FileManipulatorTest.txt";
	std::string source = current + "/" + output_filename;
	File output(source);
	WRD_TEST(output.getPath() == source)
	WRD_TEST( ! output.remove());

	
	//  searching test:
	Folder build(current, Folder::Option(false));
	WRD_TEST( ! build.isInit())
	WRD_TEST( ! build.init())
	WRD_TEST(build.isInit())
	wbool found = false;
	while( ! build.next().isNull())
		if(build.peek().getName() == output_filename)
		{
			found = true;
			break;
		}
	WRD_TEST( ! found)
	WRD_TEST( ! build.release());


	BinaryStream bs(source);
	WRD_TEST(bs.getPath() == source)
	WRD_TEST(bs.init())
	WRD_TEST( ! bs.isInit())
	WRD_TEST( ! bs.setMode(FileStream::APPENDABLE))
	WRD_TEST( ! bs.init())
	WRD_TEST(bs.isInit())
	WRD_TEST(bs.write(reaad) > 0)
	bs -= 1;
	WRD_TEST(bs.write("?", 1) > 0)
	bs = 2;
	WRD_TEST(bs.write("I'm ") > 0)
	WRD_TEST( ! bs.setCursor(bs.getEndOfFile()))
	WRD_TEST(bs.write(std::string(" keep testing!")) > 0)
	WRD_TEST( ! bs.release())

	WRD_TEST( ! as.setPath(source))
	WRD_TEST(as.getPath() == source)
	WRD_TEST( ! as.init())
	std::string reaaad = as.readLine();   
	reaad = "HeI'm hello world? keep testing!";
	WRD_TEST(reaaad == reaad)

	wint eof_cursor = as.getEndOfFile();

	std::string whole_context = as.readWhole();

	WRD_TEST(whole_context == reaad)
	WRD_TEST(as.isEndOfFile())
	WRD_TEST(as.getCursor() == eof_cursor)

	
	//  searching test:
	found = false;
	WRD_TEST(build.next().isNull())
	WRD_TEST( ! build.init())
	WRD_TEST(build.isInit())
	while( ! build.next().isNull())
		if(build.peek().getName() == output_filename)
		{
			found = true;
			break;
		}
	WRD_TEST(found)

	return "";
))
