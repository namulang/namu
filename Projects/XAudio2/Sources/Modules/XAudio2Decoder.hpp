#pragma once

#include "../Includes/Includes.hpp"

namespace XA2
{
	using namespace NE;

	class NE_DLL XAudio2Decoder : public NEModule
	{
	public:
		typedef XAudio2Decoder ThisClass;
		typedef NEModule SuperClass;

	public:
		XAudio2Decoder()
			: SuperClass(), _wave_format(0), _wave_data(0)
		{

		}
		XAudio2Decoder(const ThisClass& rhs)
			: SuperClass(rhs), _wave_format(0), _wave_data(0),
			arg_load_success(rhs.arg_load_success), arg_raw_pcm_size(rhs.arg_raw_pcm_size),
			arg_filepath(rhs.arg_filepath)
		{
			arg_load_success.setValue(false);
		}
		virtual ~XAudio2Decoder()
		{
			_release();
		}

	public:
		NETArgument<NETStringKey>		arg_filepath;
		NETArgument<NEUIntKey>			arg_raw_pcm_size;
		NETArgument<NEBooleanKey>		arg_load_success;

	public:
		virtual const NETString& getFileExtension() const = 0;
		virtual void release() 
		{
			_stopAllRelativePlayers();

			SuperClass::release();

			_release();
		}

	public:
		type_result open(const NETString& path)
		{
			arg_load_success.setValue(false);
			if(path.getLength() < 4) return RESULT_TYPE_ERROR | RESULT_INVALID_DATA;

			type_index last_n = path.getLengthLastIndex();
			const NETString& ext = getFileExtension();
			NETString sample_ext = path.extract(last_n - (ext.getLength()-1/*without null*/), last_n);

			if (sample_ext != ext)
				return RESULT_TYPE_WARNING;

			type_result result = _onDecode(path);
			if(NEResult::hasError(result))
				ALERT_ERROR(" : %s 파일을 Decode에 실패했습니다.", path.toCharPointer())
			else
			arg_load_success.setValue(true);

			return result;
		}
		const WAVEFORMATEX& getWaveFormatEX() const 
		{
			return *_wave_format;
		}
		const type_uchar* getWaveData() const
		{
			return _wave_data;
		}		

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader instance;
			if(NEResult::hasError(instance.isValid()))
			{
				NETStringSet& args = instance.getArgumentsComments();
				args.create(3);
				args.push("FilePath\n디코딩할 파일 경로입니다.");
				args.push("Size\n파일을 디코딩 후, 그 size를 이곳에 기록됩니다.");
				args.push("is loading success\n디코딩이 성공했는지 여부를 이곳에 기록합니다.");
			}

			return instance;
		}

	protected:
		virtual type_result _onDecode(const NETString& path) = 0;
		virtual type_result _onFetchModule()
		{
			arg_filepath.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_raw_pcm_size.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_load_success.setPurposeLimitation(NEArgumentBase::WRITTEN);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_filepath);
			tray.push(arg_raw_pcm_size);
			tray.push(arg_load_success);

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute()
		{
			if( ! arg_load_success.getValue())
				return open(arg_filepath.getValue());

			return RESULT_SUCCESS;
		}

	protected:
		void _release()
		{
			_stopAllRelativePlayers();

			if (arg_load_success.getValue())
			{
				_releaseWaveFormat();
				_releaseWaveData();
				arg_load_success.setValue(false);
			}
		}

	private:
		void _releaseWaveFormat()
		{
			if (_wave_format)
			{
				delete[] _wave_format;
				_wave_format = NULL;
			}
		}
		void _releaseWaveData()
		{
			if (_wave_data)
			{
				delete[] _wave_data;
				_wave_data = NULL;
			}
		}
		void _stopAllRelativePlayers();

	protected:
		WAVEFORMATEX*	_wave_format;
		type_uchar*		_wave_data; // 동적 배열

	public:
		static const NECodeSet& getModuleScriptCodes();
	};
}