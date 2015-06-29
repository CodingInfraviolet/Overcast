#include "stdafx.h"
#include "guitext.h"

GuiText* guitextptr;

GuiText::GuiText()
{
	guitextptr = this;
}

GuiText::~GuiText()
{
	guitextptr = nullptr;
}

void GuiText::draw()
{
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(systemptr->graphics->screenQuad.VAO);

	static GuiTextBox box("Text! More text. Loooots of text. Copious amounts of text. Hope this works!", math::vec2(-0.9, 0.2), math::vec2(0.8, 0.8)); 

	box.draw(this);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

bool GuiText::initialise()
{
	if (!initialiseShaders())
		return false;


	std::string mainFontPath = "Engine/Fonts/ElegantLux-Mager.otf";
	FT_Error error = FT_Init_FreeType(&library);
	if (error)
		return false;

	error = FT_New_Face(library, mainFontPath.c_str(), 0, &mainFont);
	if (error == FT_Err_Unknown_File_Format)
	{
		Error(std::string("Unrecognised font face: ") + mainFontPath);
		return false;
	}
	else if (error)
	{
		Error("Could not load font face: " + mainFontPath);
		return false;
	}

	FT_Set_Pixel_Sizes(mainFont, 256, 0);

	if (!initialiseCharmap())
		return false;
	return true;
}

bool GuiText::initialiseCharmap()
{
	charmap.resize(128);
	for (size_t i = 0; i < charmap.size(); ++i)
	{
		charmap[i].constructFromChar((char)i);
	}

	return true;
}

void GuiText::shutdown()
{
	FT_Done_Face(mainFont);
	FT_Done_FreeType(library);
}

//Did here temporarily
bool GuiText::initialiseShaders()
{
	if (!shader.load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
		return false;
	shader.set();
	shader.setAspectScale((float)systemptr->displaySet.screenHeight / systemptr->displaySet.screenWidth);
	return true;
}



GuiTextBox::GuiTextBox()
{

}

GuiTextBox::GuiTextBox(const math::vec2& topLeft, const math::vec2& bottomRight)
{
	setTopLeft(topLeft);
	setBottomRight(bottomRight);
}

GuiTextBox::GuiTextBox(const std::string& text)
{
	setText(text);
}

GuiTextBox::GuiTextBox(const std::string& text, const math::vec2& topLeft, const math::vec2& bottomRight)
	: GuiTextBox(topLeft, bottomRight)
{
	setText(text);
}

void GuiTextBox::setText(const std::string& text)
{
	mText = text;
}

void GuiTextBox::setTopLeft(const math::vec2& topLeft)
{
	mTopLeft = topLeft;
}

void GuiTextBox::setBottomRight(const math::vec2& BottomRight)
{
	mBottomRight = BottomRight;
}

void GuiTextBox::prepare()
{
	mPreparePending = false;
}

void GuiTextBox::draw(GuiText* engine)
{
	if (mPreparePending)
		prepare();

	float textSize = 0.07;
	float xPos = mTopLeft.x;
	float yPos = mTopLeft.y;

	for (size_t i = 0; i < mText.size(); ++i)
	{
		GuiCharacter& character = engine->charmap[mText[i]];

		if (!character.isInGPU())
			continue;
		GuiCharacterInstance c(character);
	
			c.setScale(textSize);
			c.setPos(math::vec3(xPos,yPos,0));
			xPos += (character.getWidthMultiplier())*textSize*2;
			c.draw(engine->shader);

			if (xPos > mBottomRight.x)
			{
				xPos = mTopLeft.x;
				yPos -= textSize * 2.8;
			}
	}
}
