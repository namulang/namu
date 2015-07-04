#pragma once

#include "../../Includes/Includes.hpp"

class ScriptFilePopUpMenu : public LG::ListWindow
{
public:
	class LoadScript : public LG::ListWindow
	{
	public:
		NEStringSet real_paths;

		LoadScript() : LG::ListWindow("읽어들일 파일을 선택하세요", 40, 10, 20, 12, BLACK, WHITE, WHITE, LIGHTMAGENTA)
		{
			updateFileList();
		}
		virtual NEObject& clone() const { return *(new LoadScript(*this)); }

		void updateFileList()
		{
			NEStringList bucket, path_bucket;

			const NETString& work_directory = Kernal::getInstance().getSettings().getScriptDirectory(),
				&extractor = Kernal::getInstance().getSettings().getScriptExtractor();
			NETString path = work_directory + "*" + extractor;

			NEFileSystem fs(path.toCharPointer(), true);
			const NEFileSystem::TaskUnit* task = 0;
			fs.findFile();
			while (task = &fs.getLastElement())
			{
				bucket.push(task->getFileName());
				path_bucket.push(task->getFilePath());

				fs.findFile();
			}

			//	Bucket에서 실제 데이터로 이동:
			_synchronizeListToArray(bucket, list.items);
			_synchronizeListToArray(path_bucket, real_paths);
		}

		void _synchronizeListToArray(const NEStringList& source, NEStringSet& to)
		{
			to.create(source.getLength());

			for (const NEStringList::Iterator* itr = source.getIterator(0); itr; itr = itr->getNext())
				to.push(itr->getValue());
		}

		virtual void onItemChoosed(type_index chosen, const NEString& content);
	};

	class SaveScript : public LG::InputWindow
	{
	public:
		SaveScript(const NEString& hint) : LG::InputWindow("저장할 파일이름을 입력하세요.", BLACK, WHITE, hint) { input.text = hint; }
		virtual NEObject& clone() const { return *(new SaveScript(*this)); }

		virtual void onInputed();
	};

	ScriptFilePopUpMenu();
	FUNC_CLONE(ScriptFilePopUpMenu)

	virtual void onUpdateData();
	virtual void onItemChoosed(type_index index, const NEString& chosen_content);
};