#pragma once

#include "../Includes/Includes.hpp"
#pragma warning(push)
#pragma warning(disable: 4244)	// float 형변환시 데이터 손실 가능성 경고
/*
	cosmic.mearie.org/2005/03/bmsguide 참고
	롱노트 미지원,
	#STP 키워드 미지원
	#IF, #ENDIF 등 미지원

note type:
01	배경음			02	마디 길이 압축		03	BPM		04	BGA		06	PoorBGA		07	Layer	08	확장BPM
11	Z				12	S					13	X		14	D		15	C			16	Scratch
17	Freezone		18	F					19	V
*/

namespace BMSFormatter_kniz
{
	using namespace std;
	using namespace NE;

	class BMSParser : public NEModule
	{
	public:
		//	기본값	포맷명		설명
		NETArgument<NETStringKey>		arg_path;
		NETArgument<NEIntKey>			arg_player_count;		//						3은 더플플레이
		NETArgument<NETStringKey>		arg_genre;
		NETArgument<NETStringKey>		arg_title;
		NETArgument<NETStringKey>		arg_artist;
		NETArgument<NEIntKey>			arg_bpm;				//	130
		NETArgument<NEIntKey>			arg_playlevel;
		NETArgument<NEIntKey>			arg_judgement_level;	//			RANK
		NETArgument<NEIntKey>			arg_total_in_manual;	//			TOTAL		수동으로 입력한 노트의 갯수. 실제 오브젝트보다 많을 수록 에너지 감소가 강해짐
		NETArgument<NEIntKey>			arg_volume;				//	100		VOLWAV
		NETArgument<NETStringKey>		arg_stage_bga;			//			STAGEFILE
		NETArgument<NETStringKey>		arg_videofile;			//			VIDEOFILE	BGA대신에 재생된다. 즉, 모든 BGA 명령은 무시된다.
		NETArgument<NEModuleCodeSetKey>	arg_on_found_headers;
		NETArgument<NETStringKey>		arg_type;				//	BMP or WAV
		NETArgument<NEFloatKey>			arg_value;
		NETArgument<NETStringKey>		arg_resource_path;
		NETArgument<NEModuleCodeSetKey>	arg_on_load_resource;	//	on_load_resource(resource_type, resource_path, value)
		NETArgument<NEIntKey>			arg_pos;
		NETArgument<NEModuleCodeSetKey>	arg_on_found_note;		//	on_found_note(type, pos, value)

	protected:
		virtual type_result _onFetchModule()
		{
			arg_path.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_player_count.setValue(1);
			arg_player_count.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_genre.setValue("Unknown");
			arg_genre.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_title.setValue("Untitled");
			arg_title.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_artist.setValue("Unknown");
			arg_artist.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_bpm.setValue(130);
			arg_bpm.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_playlevel.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_judgement_level.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_total_in_manual.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_volume.setValue(100);
			arg_volume.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_stage_bga.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_videofile.setPurposeLimitation(NEArgumentBase::WRITTEN);			

			arg_type.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_value.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_resource_path.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_on_load_resource.setEnable(true);

			arg_pos.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_on_found_note.setEnable(true);

			return RESULT_SUCCESS;
		}

		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_path);
			tray.push(arg_player_count);
			tray.push(arg_genre);
			tray.push(arg_title);
			tray.push(arg_artist);
			tray.push(arg_bpm);
			tray.push(arg_playlevel);
			tray.push(arg_judgement_level);
			tray.push(arg_total_in_manual);
			tray.push(arg_volume);
			tray.push(arg_stage_bga);
			tray.push(arg_videofile);
			tray.push(arg_on_found_headers);
			tray.push(arg_type);
			tray.push(arg_value);
			tray.push(arg_resource_path);
			tray.push(arg_on_load_resource);
			tray.push(arg_pos);
			tray.push(arg_on_found_note);

			return RESULT_SUCCESS;
		}

		virtual type_result _onExecute()
		{
			NEFloatSet bpms;
			NEIntSet stops;
			bpms.create(toIndex("ZZ") + 1);
			stops.create(toIndex("ZZ") + 1);
			bool is_header_handler_triggered = false;

			NESequencialFileLoader loader(arg_path.getValue().toCharPointer());
			loader.open();
			if (!loader.isFileOpenSuccess())
				return ALERT_WARNING("주어진 %s 파일이 없습니다.", arg_path.getValue().toCharPointer());

			while (!loader.isEndOfFile())
			{
				TCHAR buffer[512] = { 0, };
				loader.readByLine(buffer, 512);
				NETString line = buffer;
				NETStringSet split;
				line.split(" ", split);
				NETString rhs;
				for (int n = 1; n < split.getLength(); n++)
					rhs += split[n] + " ";

				if (line[0] != '#') continue;

				arg_type.setValue(line.extract(1, 1 + 2));
				if(	arg_type.getValue() == "WAV"		||
					arg_type.getValue() == "BMP"		&&
					arg_on_load_resource.isEnable()		)
				{
					int n = toIndex(line.extract(4, 4 + 1));
					arg_value.setValue(n);
					if (split.getLength() <= 1)
						continue;

					arg_resource_path.setValue(split[1]);
					arg_on_load_resource.getValue().execute();					
				}
				else if (split[0] == "#PLAYER")
					arg_player_count.setValue(split[1].toInt());
				else if (split[0] == "#GENRE")
					arg_genre.setValue(rhs);
				else if (split[0] == "#TITLE")
					arg_title.setValue(rhs);
				else if (split[0] == "#ARTIST")
					arg_artist.setValue(rhs);
				else if (split[0] == "#BPM")
					arg_bpm.setValue(split[1].toInt());
				else if (split[0] == "#PLAYLEVEL")
					arg_playlevel.setValue(split[1].toInt());
				else if (split[0] == "#RANK")
					arg_judgement_level.setValue(split[1].toInt());
				else if (split[0] == "#TOTAL")
					arg_total_in_manual.setValue(split[1].toInt());
				else if (split[0] == "#STAGEFILE")
					arg_stage_bga.setValue(rhs);
				else if (split[0] == "#VIDEOFILE")
					arg_stage_bga.setValue(rhs);
				else if (split[0] == "#VOLWAV")
					arg_stage_bga.setValue(split[1].toInt());
				else if (split[0] == "#BPM")
				{
					type_index n = toIndex(split[0].extract(4, 4 + 1).toInt());
					if (n < 0 || n > toIndex("ZZ"))
						ALERT_ERROR("인덱스 초과")
					else
						bpms[n] = split[1].toDouble();
				}
				else if (split[0] == "#STOP")
				{
					type_index n = toIndex(split[0].extract(5, 5 + 1).toInt());
					if (n < 0 || n > toIndex("ZZ"))
						ALERT_ERROR("인덱스 초과")
					else
						stops[n] = split[1].toInt();
				}
				else if (split[0][1] >= '0'	&&
						split[0][1] <= '9')
				{
					if (!is_header_handler_triggered)
					{
						is_header_handler_triggered = true;

						if (arg_on_found_headers.isEnable())
							arg_on_found_headers.getValue().execute();
					}

					arg_type.setValue(split[0].extract(4, 5));
					type_int base_position = split[0].extract(1, 1 + 2).toInt() * 192;

					line.split(":", split);
					_parseLineForNotes(split[1], base_position, bpms, stops);
				}
			}
			loader.close();

			return RESULT_SUCCESS;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (NEResult::hasError(_header.isValid()))
			{
				_header.getName() = "BMSParser";
				_header.getDeveloper() = "kniz";
				_header.setRevision(1);
				_header.getComment() =
					"리듬게임에 사용되는 .BMS 포맷의 파일을 읽어서 유효한 정보로 파싱합니다.\n";
					"크게 3파트로 분류되며, 각 파트별 파싱작업이 끝나면 적합한 ModulecodeSet을 execute 합니다.\n"
					"파트1	:헤더 파싱\n"
					"	PlayerCount 부터 VideoFile 값들이 Argument에 저장된 후 onFoundHeaders가 실행됩니다.\n"
					"파트2	:리소스 파싱	onFoundResource(Type, ResourcePath, Value)\n"
					"	리소스 하나를 파싱할때마다 Type과 ResourcePath, Value Argument들에 값이 저장된 후 onFoundResource가 실행됩니다.\n"
					"파트3	:노트 파싱		onFoundNote(Type, Position, Value)\n"
					"	노트를 하나 파싱할때마다 Type과 위치(한마디를 192로 표현했을때의 위치값), 노트가 참조하는 값이 저장된 후 onFoundNote가 실행됩니다.\n";
				_header.getVersion() = "2015-02-13";				
				NETStringSet& args = _header.getArgumentsComments();
				args.create(19);
				args.push("BMS의 경로 입니다.");
				args.push("PlayerCount\nonFoundHeader가 실행될때 이 값에 몇 명 Player용 BMS 인지 기록됩니다.\n1: 1인 플레이\t2:2인 플레이(각각 채보가 다름)\t3:1인 더블플레이\n4:2인 플레이(단, 채보는 같다)");
				args.push("Genre");
				args.push("Title");
				args.push("Artist");
				args.push("BPM\n기본값은 130이며, 도중 BPM노트로 인해서 변경 될 수 있습니다.");
				args.push("PlayLevel\n제작자가 정한 BMS의 난이도.");
				args.push("Judgement Level\n판정이 얼마나 엄격해야 하는지 제작자가 요청하는 판정레벨입니다.\n0: 매우 엄격하게\t1: 엄격하게\n\t2:보통\t3:느슨하게");
				args.push("Total\n제작자가 수동으로 입력한 노트의 갯수");
				args.push("Volume\n사운드 파일의 볼륨입니다. 100이 기준입니다.");
				args.push("StageBga Path\n로딩 중, 그림을 출력할 그림파일의 경로입니다.");
				args.push("VideoFile\nBGA 대신에 재생할 동영상 파일입니다. 이 값이 BMS 파일에 있을경우 기타 BGA와 관련된 명령은 모두 취소되어야 합니다.");
				args.push("onFoundHeaders\n위의 값들을 모두 파싱하였을때 실행됩니다.");
				
				args.push(
					"Type\n노트나 리소스의 타입을 의미합니다.\n"
					"BMP: 그림 리소스입니다.\tWAV: 사운드 파일입니다.\n"
					"다음은 노트의 타입들입니다.\n"
					"01: 배경음\t02: 마디 길이를 압축함\t03: BPM변환 노트\n"
					"04: BGA노트\t06: 판정실패시 뜰 PoorBGA노트\t07: BGA위에 그려질 Layer\n"
					"11:1번째 흰색건반\t12:1번째 검은건반\t13:2번째 흰색건반\n"
					"14:2번째 검은건반\n15:3번째 흰색건반\t16:스크래치\n"
					"17:FreeZone\t18:3번째 검은건반(7키)\t19:4번째 흰색건반(7키)"
				);
				args.push("Value\n노트의 값입니다.");
				args.push("ResourcePath\n리소스의 경로가 담겨집니다.");
				args.push("onLoadResource(Type, ResourcePath, Value)\n각각 리소스 정보를 파싱하여, 로드를 해야하는 순간, 실행됩니다.\nValue에는 Resource의 인덱스가 들어갑니다.");
				args.push("Position\n노트의 위치입니다.\n1마디를 192로 표현했을때의 양의 정수입니다.\n예를들어 288은 192 + 96으로, 1번 index 마디의 중간을 뜻하게 됩니다.");
				args.push("onFoundNote(Type, Position, Value)\n각각 노트 정보를 파싱했을때, Type, Position, Value에 파싱한 값을 담고 이 ModuleCodeSet이 실행됩니다.\nValue는 앞서 로드한 Resource의 인덱스와 일치하는 값입니다.");
			}

			return _header;
		}

		virtual NEObject& clone() const
		{
			return *(new BMSParser(*this));
		}

	public:
		type_int toDecimal(TCHAR _36hex) const
		{
			if (_36hex >= _T('0') &&
				_36hex <= _T('9'))
				return _36hex - _T('0');
			else if (_36hex >= _T('A') &&
				_36hex <= _T('Z'))
				return _36hex - _T('A') + 10;
			else if (_36hex >= _T('a') &&
				_36hex <= _T('z'))
				return _36hex - _T('a') + 10;

			return 0;
		}

		type_index toIndex(const NETString& _36hex_token) const 
		{
			type_index to_return = 0;

			if (_36hex_token.getLength() >= 2)
				to_return = toDecimal(_36hex_token[0]) * 36;

			return to_return += toDecimal(_36hex_token[1]);
		}

	private:
		void _parseLineForNotes(const NETString& line, type_int base_position, const NEFloatSet& bpms, const NEIntSet& stops)
		{
			if (line == "00") return;
			if (arg_type.getValue().toInt() == 2)
			{
				arg_value.setValue(line.toDouble());
				arg_pos.setValue(base_position);
				if(arg_on_found_note.isEnable())
					arg_on_found_note.getValue().execute();
			}
			else
			{
				type_index length = (line.getLength() - 1) / 2;
				type_float pos_per_note = 192 / length;

				for (int n = 0; n < length; n++)
				{
					arg_pos.setValue(base_position + n * pos_per_note);
					NEString vv = line.extract(n * 2, n * 2 + 1);
					type_int value = toIndex(vv);
					if (!value) continue;
					cout << vv.toCharPointer();
					arg_value.setValue(value);

					type_int t = arg_type.getValue().toInt();
					switch (t)
					{
					case 8:
						arg_type.setValue("03");
						arg_value.setValue(bpms[arg_value.getValue()]);
						break;

					case 9:
						arg_value.setValue(stops[arg_value.getValue()]);
					}

					if(arg_on_found_note.isEnable())
						arg_on_found_note.getValue().execute();

				}
			}
		}
	};
}
#pragma warning(pop)