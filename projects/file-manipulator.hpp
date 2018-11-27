//	---------------------------------------------------------------------------------
//	DLL명	:	FileSystem.dll
//	설명	:	경로 상에 존재하는 파일을 검색함. 와일드 카드(*.exe) 사용 가능
//	관계	:	기반 패키지.	Macro
//				외부 포함.		<windows.h>
//								<tchar_t.h>
//	특성	:	파일 시스템을 다루는 부분은 WINAPI를, C String 다루는 부분은 CRT를 사용
//				한다.
//	클래스	:	NEFileSystem(with Status, TaskUnit)
//	메모	:
//	히스토리:	2011-01-07	이태훈	프로토타입 제작
//				2011-01-08	이태훈	테스트런 완료
//				2011-01-12	이태훈	추가	workDirectory라는 개념을 만듬, 접근자 함수 작성
//				2011-02-11	이태훈	추가	하위 폴더도 검색 가능하도록 수정함
//											Task와 TaskManager를 이용한 스택구조로 작업을 스위칭함.
//				2011-06-04	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "file-manipulator/file-structures.hpp"
#include "file-manipulator/file-streams.hpp"
