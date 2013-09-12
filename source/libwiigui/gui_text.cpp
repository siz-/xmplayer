/****************************************************************************
 * libwiigui
 *
 * Tantric 2009
 *
 * gui_text.cpp
 *
 * GUI class definitions
 ***************************************************************************/
#include <wchar.h>
#include "gui.h"
#include "../gettext.h"
//#include "../gui_wchar.h"
#include "../gui_debug.h"

extern "C" wchar_t * wcsdup(const wchar_t *str);

static XeColor presetColor = (XeColor){255, 255, 255, 255};
static int currentSize = 0;
static int presetSize = 0;
static int presetMaxWidth = 0;
static int presetAlignmentHor = 0;
static int presetAlignmentVert = 0;
static u16 presetStyle = 0;

#define TEXT_SCROLL_DELAY			8
#define	TEXT_SCROLL_INITIAL_DELAY	6

std::wstring strToWideStr(std::string str) {
	std::wstring wstr(str.begin(), str.end());
	return wstr;
}
/**
 * Constructor for the GuiText class.
 */
GuiText::GuiText(std::string t, int s, XeColor c) {
	text = L"";
	origText = "";
	size = s;
	color = c;
	alpha = c.a;
	style = FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE;
	maxWidth = 0;
	wrap = false;
	textDynNum = 0;
	textScroll = SCROLL_NONE;
	textScrollPos = 0;
	textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;
	textScrollDelay = TEXT_SCROLL_DELAY;

	alignmentHor = ALIGN_CENTRE;
	alignmentVert = ALIGN_MIDDLE;

	if (!t.empty()) {
		origText = t;
		text = strToWideStr(t);
	}

	for (int i = 0; i < 20; i++)
		textDyn[i] = L"";
}

GuiText::GuiText(std::string t, int s, uint32_t u32c) {
	text = L"";
	origText = "";
	XeColor c;
	c.lcol = u32c;
	size = s;
	color = c;
	alpha = c.a;
	style = FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE;
	maxWidth = 0;
	wrap = false;
	textDynNum = 0;
	textScroll = SCROLL_NONE;
	textScrollPos = 0;
	textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;
	textScrollDelay = TEXT_SCROLL_DELAY;

	alignmentHor = ALIGN_CENTRE;
	alignmentVert = ALIGN_MIDDLE;

	if (!t.empty()) {
		origText = t;
		text = strToWideStr(t);
	}

	for (int i = 0; i < 20; i++)
		textDyn[i] = L"";

}

/* GuiText::GuiText(const char * t, int s, XeColor c) {
	origText = NULL;
	text = NULL;
	size = s;
	color = c;
	alpha = c.a;
	style = FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE;
	maxWidth = 0;
	wrap = false;
	textDynNum = 0;
	textScroll = SCROLL_NONE;
	textScrollPos = 0;
	textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;
	textScrollDelay = TEXT_SCROLL_DELAY;

	alignmentHor = ALIGN_CENTRE;
	alignmentVert = ALIGN_MIDDLE;

	if (t) {
		origText = strdup(t);
		text = charToWideChar(gettext(t));
	}

	for (int i = 0; i < 20; i++)
		textDyn[i] = NULL;
}

GuiText::GuiText(const char * t, int s, uint32_t u32c) {
	XeColor c;
	c.lcol = u32c;
	origText = NULL;
	text = NULL;
	size = s;
	color = c;
	alpha = c.a;
	style = FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE;
	maxWidth = 0;
	wrap = false;
	textDynNum = 0;
	textScroll = SCROLL_NONE;
	textScrollPos = 0;
	textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;
	textScrollDelay = TEXT_SCROLL_DELAY;

	alignmentHor = ALIGN_CENTRE;
	alignmentVert = ALIGN_MIDDLE;

	if (t) {
		origText = strdup(t);
		text = charToWideChar(gettext(t));
	}

	for (int i = 0; i < 20; i++)
		textDyn[i] = NULL;

} */

/**
 * Constructor for the GuiText class, uses presets
 */
GuiText::GuiText(std::string t) {
	text = L"";
	origText = "";
	size = presetSize;
	color = presetColor;
	alpha = presetColor.a;
	style = presetStyle;
	maxWidth = presetMaxWidth;
	wrap = false;
	textDynNum = 0;
	textScroll = SCROLL_NONE;
	textScrollPos = 0;
	textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;
	textScrollDelay = TEXT_SCROLL_DELAY;

	alignmentHor = presetAlignmentHor;
	alignmentVert = presetAlignmentVert;

	if (!t.empty()) {
		origText = t;
		text = strToWideStr(t);
	}

	for (int i = 0; i < 20; i++)
		textDyn[i] = L"";
}

/**
 * Destructor for the GuiText class.
 */
GuiText::~GuiText() {
	if (!origText.empty())
		origText = "";
	if (!text.empty())
		text = L"";

	if (textDynNum > 0) {
		for (int i = 0; i < textDynNum; i++)
			if (!textDyn[i].empty())
				textDyn[i] = L"";
	}
}

void GuiText::SetText(std::string t) {
	if (!origText.empty())
		origText = "";
	if (!text.empty())
		text = L"";

	if (textDynNum > 0) {
		for (int i = 0; i < textDynNum; i++)
			if (!textDyn[i].empty())
				textDyn[i] = L"";
	}

	text = L"";
	origText = "";
	textDynNum = 0;
	textScrollPos = 0;
	textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;

	if (!t.empty()) {
		origText = t;
		text = strToWideStr(t);
	}
}

/*void GuiText::SetText(const char * t) {
	if (origText)
		free(origText);
	if (text)
		delete[] text;

	if (textDynNum > 0) {
		for (int i = 0; i < textDynNum; i++)
			if (textDyn[i])
				delete[] textDyn[i];
	}

	origText = NULL;
	text = NULL;
	textDynNum = 0;
	textScrollPos = 0;
	textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;

	if (t) {
		origText = strdup(t);
		text = charToWideChar(gettext(t));
	}
}*/

void GuiText::SetWText(std::wstring t) {
	if (!origText.empty())
		origText = "";
	if (!text.empty())
		text = L"";

	if (textDynNum > 0) {
		for (int i = 0; i < textDynNum; i++)
			if (!textDyn[i].empty())
				textDyn[i] = L"";
	}

	origText = "";
	text = L"";
	textDynNum = 0;
	textScrollPos = 0;
	textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;

	if (!t.empty())
		text = t;
}

int GuiText::GetLength() {
	if (text.empty())
		return 0;

	return text.size();
}

void GuiText::SetPresets(int sz, XeColor c, int w, u16 s, int h, int v) {
	presetSize = sz;
	presetColor = c;
	presetStyle = s;
	presetMaxWidth = w;
	presetAlignmentHor = h;
	presetAlignmentVert = v;
}

void GuiText::SetFontSize(int s) {
	size = s;
}

void GuiText::SetMaxWidth(int width) {
	maxWidth = width;

	for (int i = 0; i < textDynNum; i++) {
		if (!textDyn[i].empty())
			textDyn[i] = L"";
	}

	textDynNum = 0;
}

int GuiText::GetTextWidth() {
	if (text.empty())
		return 0;

	if (currentSize != size) {
		ChangeFontSize(size);

		if (!fontSystem[size])
			fontSystem[size] = new FreeTypeGX(size);

		currentSize = size;
	}
	return fontSystem[size]->getWidth(text.c_str());
}

void GuiText::SetWrap(bool w, int width) {
	wrap = w;
	maxWidth = width;

	for (int i = 0; i < textDynNum; i++) {
		if (!textDyn[i].empty())
			textDyn[i] = L"";
	}

	textDynNum = 0;
}

void GuiText::SetScroll(int s) {
	if (textScroll == s)
		return;

	for (int i = 0; i < textDynNum; i++) {
		if (!textDyn[i].empty())
			textDyn[i] = L"";
	}

	textDynNum = 0;

	textScroll = s;
	textScrollPos = 0;
	textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;
	textScrollDelay = TEXT_SCROLL_DELAY;
}

void GuiText::SetColor(XeColor c) {
	color = c;
	alpha = c.a;
}

void GuiText::SetStyle(u16 s) {
	style = s;
}

void GuiText::SetAlignment(int hor, int vert) {
	style = 0;

	switch (hor) {
		case ALIGN_LEFT:
			style |= FTGX_JUSTIFY_LEFT;
			break;
		case ALIGN_RIGHT:
			style |= FTGX_JUSTIFY_RIGHT;
			break;
		default:
			style |= FTGX_JUSTIFY_CENTER;
			break;
	}
	switch (vert) {
		case ALIGN_TOP:
			style |= FTGX_ALIGN_TOP;
			break;
		case ALIGN_BOTTOM:
			style |= FTGX_ALIGN_BOTTOM;
			break;
		default:
			style |= FTGX_ALIGN_MIDDLE;
			break;
	}

	alignmentHor = hor;
	alignmentVert = vert;
}

void GuiText::ResetText() {
	if (origText.empty())
		return;
	if (!text.empty())
		text = L"";

	text = strToWideStr(origText);

	for (int i = 0; i < textDynNum; i++) {
		if (!textDyn[i].empty())
			textDyn[i] = L"";
	}

	textDynNum = 0;
	currentSize = 0;
}

int GuiText::GetLeft() {
	int x = GuiElement::GetLeft();
	if ((style & FTGX_JUSTIFY_RIGHT) && (maxWidth > 0)) {
		x = (x + maxWidth) - GetTextWidth();
	}
	return x;
}

/**
 * Draw the text on screen
 */
void GuiText::Draw() {
	if (text.empty())
		return;

	if (!this->IsVisible())
		return;

	XeColor c = color;
	c.a = this->GetAlpha();

	int newSize = size * this->GetScale();

	if (newSize > MAX_FONT_SIZE)
		newSize = MAX_FONT_SIZE;

	if (newSize != currentSize) {
		ChangeFontSize(newSize);
		if (!fontSystem[newSize])
			fontSystem[newSize] = new FreeTypeGX(newSize);
		currentSize = newSize;
	}

	if (maxWidth == 0) {
		fontSystem[currentSize]->drawText(this->GetLeft(), this->GetTop(), text.c_str(), c, style);
		this->UpdateEffects();
		return;
	}

	u32 textlen = text.size();

	if (wrap) {
		if (textDynNum == 0) {
			u32 n = 0, ch = 0;
			int linenum = 0;
			int lastSpace = -1;
			int lastSpaceIndex = -1;

			while (ch < textlen && linenum < 20) {
				if (n == 0)
					textDyn[linenum] = new wchar_t[textlen + 1];

				textDyn[linenum][n] = text[ch];
				textDyn[linenum][n + 1] = 0;

				if (text[ch] == ' ' || ch == textlen - 1) {
					if (fontSystem[currentSize]->getWidth(textDyn[linenum].c_str()) > maxWidth) {
						if (lastSpace >= 0) {
							textDyn[linenum][lastSpaceIndex] = 0; // discard space, and everything after
							ch = lastSpace; // go backwards to the last space
							lastSpace = -1; // we have used this space
							lastSpaceIndex = -1;
						}
						++linenum;
						n = -1;
					} else if (ch == textlen - 1) {
						++linenum;
					}
				}
				if (text[ch] == ' ' && n >= 0) {
					lastSpace = ch;
					lastSpaceIndex = n;
				}
				++ch;
				++n;
			}
			textDynNum = linenum;
		}

		int lineheight = newSize + 6;
		int voffset = 0;

		if (alignmentVert == ALIGN_MIDDLE)
			voffset = (lineheight >> 1) * (1 - textDynNum);

		int left = this->GetLeft();
		int top = this->GetTop() + voffset;

		for (int i = 0; i < textDynNum; ++i)
			fontSystem[currentSize]->drawText(left, top + i * lineheight, textDyn[i].c_str(), c, style);
	} else {
		if (textDynNum == 0) {
			textDynNum = 1;
			textDyn[0] = text;
			int len = textDyn[0].size();

			while (fontSystem[currentSize]->getWidth(textDyn[0].c_str()) > maxWidth)
				textDyn[0][--len] = 0;
		}

		if (textScroll == SCROLL_HORIZONTAL) {
			if (fontSystem[currentSize]->getWidth(text.c_str()) > maxWidth && (FrameTimer % textScrollDelay == 0)) {
				if (textScrollInitialDelay) {
					--textScrollInitialDelay;
				} else {
					++textScrollPos;
					if ((u32) textScrollPos > textlen - 1) {
						textScrollPos = 0;
						textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;
					}

					textDyn[0] = text[textScrollPos];
					u32 dynlen = textDyn[0].size();

					if (dynlen + 2 < textlen) {
						textDyn[0][dynlen] = ' ';
						textDyn[0][dynlen + 1] = ' ';
						textDyn[0][dynlen + 2] = 0;
						dynlen += 2;
					}

					if (fontSystem[currentSize]->getWidth(textDyn[0].c_str()) > maxWidth) {
						while (fontSystem[currentSize]->getWidth(textDyn[0].c_str()) > maxWidth)
							textDyn[0][--dynlen] = 0;
					} else {
						int i = 0;

						while (fontSystem[currentSize]->getWidth(textDyn[0].c_str()) < maxWidth && dynlen + 1 < textlen) {
							textDyn[0][dynlen] = text[i++];
							textDyn[0][++dynlen] = 0;
						}

						if (fontSystem[currentSize]->getWidth(textDyn[0].c_str()) > maxWidth)
							textDyn[0][dynlen - 2] = 0;
						else
							textDyn[0][dynlen - 1] = 0;
					}
				}
			}
		}
		fontSystem[currentSize]->drawText(this->GetLeft(), this->GetTop(), textDyn[0].c_str(), c, style);
	}
	this->UpdateEffects();
}
