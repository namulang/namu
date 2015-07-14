#include "ListGliph.hpp"
#include "../Core/Core.hpp"
#include "../FloatingGliph/FloatingGliph.hpp"

namespace LG
{
	ListGliph::ListGliph(	Window* new_owner, type_ushort new_x, type_ushort new_y, type_ushort new_width, 
		type_ushort new_height, type_ushort new_fore, type_ushort new_back, 
		type_ushort new_choosed_fore, type_ushort new_choosed_back, bool new_use_matching, bool new_use_sound)
		: Gliph(new_owner, new_x, new_y, new_width, new_height, new_fore, new_back), use_matching(new_use_matching),
		choosed_back(new_choosed_back), choosed_fore(new_choosed_fore), choosed(0), use_sound(new_use_sound)
	{

	}
	ListGliph::ListGliph(const ListGliph& rhs)
		: Gliph(rhs), items(rhs.items), choosed(rhs.choosed), choosed_back(rhs.choosed_back), 
		choosed_fore(rhs.choosed_fore), use_matching(rhs.use_matching), use_sound(rhs.use_sound)
	{

	}

	void ListGliph::onDraw() {
		Gliph::onDraw();

		COORD backup_pos = Core::getCursorPosition();
		WORD backup_color = Core::getColor();
		BackBuffer& buf = Core::back_buffer;

		int half_height = (height / 2),
			list_head_index = choosed - half_height,
			bottom_limit_index = items.getLength()-height;	//	무조건 이거보단 list_head가 커야 한다.
		if(bottom_limit_index < 0)
			bottom_limit_index = 0;
		if(list_head_index < 0)
			list_head_index = 0;
		if(list_head_index > bottom_limit_index)
			list_head_index = bottom_limit_index;

		int last_index = list_head_index + height-1;
		for(int y1=list_head_index; y1 <= last_index ;y1++) {
			if(y1 > items.getLengthLastIndex())	continue;

			int y_coordinate = y1 - list_head_index;
			buf.setBufferPointer(x, y + y_coordinate);
			if(y1 == choosed)
				buf.setColor(choosed_fore, choosed_back);
			else
				buf.setColor(fore, back);

			bool	is_there_more_contents_after	= items.getLengthLastIndex() > last_index,
				is_there_more_contents_before	= list_head_index != 0;

			NEString s = 
				(	(is_there_more_contents_after && y1 == last_index)			||
				(is_there_more_contents_before && y1 == list_head_index)	)	? 
				" . . . " 
				: 
			items[y1];
			s.resize(width + 1);
			s.pop();
			if(s.getLength() < width)
				for(int n=s.getLength(); n < width ;n++) 
					s.push(' ');				
			s.push('\0');

			buf << s.toCharPointer();
		}

		if (matchingword.getLength() > 0 &&
			use_matching)
		{
			FloatingGliph for_matchingword(x + width + 1, y + height / 2, matchingword.getLength() + 2, 1, CYAN, LIGHTGRAY, matchingword);
			for_matchingword.onDraw();
		}

		Core::setColor(backup_color);
		Core::setCursorTo(backup_pos);
	}


	void ListGliph::onKeyPressed(int inputed) 
	{
		switch(inputed) 
		{
		case UP: 
			choosed--;
			if(choosed < 0) 
				choosed = items.getLengthLastIndex();
			matchingword.release();
			if(use_sound)
				Core::play(Core::SND_TICK);
			break;

		case DOWN: 
			choosed++;
			if(choosed > items.getLengthLastIndex())
				choosed = 0;
			matchingword.release();
			if(use_sound)
				Core::play(Core::SND_TICK);
			break;

		case LEFT:	case RIGHT:	case CLOSE:	case MAP: case ADD: case REMOVE: case COPY:
		case PASTE: case CUT: case HELP: case COMMAND: case CONFIRM: case CANCEL:
			matchingword.release();
			if(use_sound)
				Core::play(Core::SND_CONFIRM);
			break;

		default:
			match(matchingword + (char)inputed);
		}        
	}

	void ListGliph::match(const NEString& new_matching_word)
	{
		if( ! use_matching) return;
		if( ! &new_matching_word && new_matching_word.getLength() <= 0) return;
		NEString test_forward = new_matching_word.toLowerCase();
		type_index last_idx = test_forward.getLengthLastIndex() - 1; // without null character.
		if(last_idx < 0) return;

		for(int n = 0; n < items.getLength(); n++)
		{			
			if(items[n].extract(0, last_idx).toLowerCase().isEqualElement(test_forward))
			{
				choosed = n;
				matchingword = test_forward;
				return;
			}
		}

		matchingword.release();
	}

	void ListGliph::onUpdateData()
	{
		Gliph::onUpdateData();

		if(choosed < 0)
			choosed = 0;
		else if(choosed > items.getLengthLastIndex())
			choosed = items.getLengthLastIndex();	
	}
}