#pragma once

#include "../../Includes/Includes.hpp"

class GuideEncyclo : public LG::Window
{
public:
	class Guide : public NEObject
	{
	public:
		Guide(){}
		Guide(const NEString& new_title, const NEString& new_content)
			: title(new_title), content(new_content) {}

		bool operator==(const Guide& rhs) const
		{
			return	title == rhs.title		&&
					content == rhs.content	;
		}

		virtual void release() 
		{ 
			title.release();
			content.release();
		}
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			return saver << title << content;
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			return loader >> title >> content;
		}
		virtual type_result isValid() const
		{
			return RESULT_SUCCESS;
		}
		virtual NEObject& clone() const 
		{
			return *(new Guide(*this));
		}


		NEString title;
		NEString content;
	};

	class Status : public LG::Gliph {
	public:
		Status() : LG::Gliph(0, 1, 1, 78, 1, LG::BLACK, LG::RED) {
			text = " > Guide Enyclopedia!";
		}
		Status(const Status& rhs) : LG::Gliph(rhs) {}
		FUNC_CLONE(Status)
	};

	class GuidePanel : public LG::Gliph 
	{
	public:
		GuidePanel() : LG::Gliph(0, 22, 2, 57, 5, WHITE, LIGHTRED) {}
		GuidePanel(const GuidePanel& rhs) : Gliph(rhs) {}
		FUNC_TO_OWNER(GuideEncyclo)
		FUNC_CLONE(GuidePanel)	
	};
	class ContentPanel : public LG::Gliph
	{
	public:
		ContentPanel() : LG::Gliph(0, 22, 7, 57, 17, BLACK, WHITE) {}
		ContentPanel(const ContentPanel& rhs) : LG::Gliph(rhs) {}
		FUNC_CLONE(ContentPanel)
	};
	class GuideList : public LG::ListGliph
	{
	public:
		GuideList() 
			: LG::ListGliph(0, 1, 2, 20, 22, BLACK, WHITE, WHITE, LIGHTRED)	{ use_sound = true; }	
		GuideList(const GuideList& rhs) : LG::ListGliph(rhs){ }
		FUNC_TO_OWNER(GuideEncyclo)
		FUNC_CLONE(GuideList)

		virtual void onUpdateData();
		void setPanelsTextByChoosed();
		virtual void onKeyPressed(int inputed);		
	};

public:
	GuideEncyclo() 
		: LG::Window(1, 1, 78, 23, BLACK, DARKGRAY)
	{ 
		regist(4, &status, &panel, &list, &content);
	}
	GuideEncyclo(CONST GuideEncyclo & rhs) 
		: Window(rhs), list(rhs.list), content(rhs.content), panel(rhs.panel)
	{ 
		regist(4, &status, &panel, &list, &content); 
	}
	NEObject& clone() const { return *(new GuideEncyclo(*this)); }

	virtual void onUpdateData()
	{
		LG::Window::onUpdateData();

		guides.create(2);
		guides.push(	Guide(	"처음오면 이거부터 읽어요.", 
								"안녕하세요. 가이드1의 내용임"));
		guides.push(	Guide(	"가이드2", 
								"가이드2의 내용임"));
	}

	Status status;
	GuidePanel panel;
	GuideList list;
	ContentPanel content;
	NEArrayTemplate<Guide> guides;
};