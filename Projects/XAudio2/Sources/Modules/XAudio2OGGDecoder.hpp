#pragma once

#include "XAudio2Decoder.hpp"

namespace XA2
{
	class NE_DLL XAudio2OGGDecoder : public XAudio2Decoder
	{
	public:
		typedef XAudio2OGGDecoder ThisClass;
		typedef XAudio2Decoder SuperClass;

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader instance;

			if (NEResult::hasError(instance.isValid()))
			{
				instance.getName() = "XAudio2OGGDecoder";
				instance.getDeveloper() = "kniz";
				instance.setRevision(1);
				instance.getVersion() = "0.0.1a";
				instance.getReleaseDate() = "2015-05-07";
				instance.getComment() =
					".ogg 파일을 읽는 Module 입니다.\n"
					"XAudio2Player에 사용됩니다.";
				instance.getArgumentsComments() = SuperClass::getHeader().getArgumentsComments();
			}

			return instance;
		}
		virtual const NETString& getFileExtension() const
		{
			static NETString ext(".ogg");

			return ext;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	protected:
		virtual type_result _onDecode(const NETString& path)
		{
			_release();

			if(NEResult::hasError((_open(path))))
				return ALERT_ERROR(" : 로드 실패");

			arg_load_success.setValue(true);
			return RESULT_SUCCESS;
		}

	private:
		type_result _open(const NETString& strFileName);
	};
}