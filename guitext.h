#pragma once
#include<ft2build.h>
#include "sprite.h"
#include "ShaderProgram.h"

#include FT_FREETYPE_H

extern GuiText* guitextptr;

class GuiText
{
public:


	GuiText();
	~GuiText();

	void draw();

	bool initialise();
	bool initialiseCharmap();
	void shutdown();

	//Did here temporarily
	bool initialiseShaders();

private:
	friend class GuiTextBox;
	friend class GuiCharacter;

	FT_Library library;
	FT_Face mainFont;
	SpriteShader shader;
	std::vector<GuiCharacter> charmap;
};


class GuiCharacter : public Sprite
{

	char character = 0;
	math::vec2 charScaleOffset{ 1, 1 };

public:
	friend class GuiCharacterInstance;

	GuiCharacter()
	{

	}

	GuiCharacter(char c)
	{
		constructFromChar(c);
	}

	float getWidthMultiplier()
	{
		return charScaleOffset.x;
	}

	bool constructFromChar(char c)
	{
		character = c;

		FT_UInt index = FT_Get_Char_Index(guitextptr->mainFont, wchar_t(charToWchar((unsigned char)c)));
		if (!index)
			return false;
		FT_Error error = FT_Load_Glyph(guitextptr->mainFont, index, FT_LOAD_DEFAULT);
		if (error)
			return false;
		if (guitextptr->mainFont->glyph->format != FT_GLYPH_FORMAT_BITMAP)
			FT_Render_Glyph(guitextptr->mainFont->glyph, FT_RENDER_MODE_NORMAL);
		FT_Bitmap gBit = guitextptr->mainFont->glyph->bitmap;

		if (gBit.buffer == nullptr)
			return false;

		unsigned char* convertedBuffer = Texture::convert1ByteTo4Byte(gBit.buffer, gBit.rows*gBit.width);

		auto gHeight = guitextptr->mainFont->glyph->metrics.height;
		auto gWidth = guitextptr->mainFont->glyph->metrics.width;

		charScaleOffset.x = (float)gWidth / gHeight;

		loadFromBuffer(gBit.width, gBit.rows, convertedBuffer, true, Enum::RGBA, { { GL_TEXTURE_MAG_FILTER, GL_NEAREST }, { GL_TEXTURE_MIN_FILTER, GL_NEAREST } }, Enum::UNSIGNED_BYTE);

		return true;
	}

};


class GuiCharacterInstance : public Movable
	{
	private:
		GuiCharacter* mParent = nullptr;

	public:
		GuiCharacterInstance(){}
		GuiCharacterInstance(GuiCharacter& parent)
		{
			mParent = &parent;
		}

		void draw(SpriteShader& shader)
		{
			shader.set();GLERROR
				mParent->setForRendering(); GLERROR
				if (pendingUpdate())GLERROR
					update(shader); GLERROR
					glDrawArrays(GL_TRIANGLES, 0, 6); GLERROR
		}

		void update(SpriteShader& shader)
		{
			shader.setPosScale(math::vec4( m_pos.x, m_pos.y,
							mParent->charScaleOffset.x*m_scale, mParent->charScaleOffset.y*m_scale));
			m_pendingMatrixUpdate = false;
		}
	};

class GuiTextBox
{
public:
	math::vec2 mTopLeft;
	math::vec2 mBottomRight;
	std::string mText;
	bool mPreparePending = true;

	GuiTextBox();
	GuiTextBox(const math::vec2& topLeft, const math::vec2& bottomRight);
	GuiTextBox(const std::string& text);
	GuiTextBox(const std::string& text, const math::vec2& topLeft, const math::vec2& bottomRight);

	void setText(const std::string& text);
	void setTopLeft(const math::vec2& topLeft);
	void setBottomRight(const math::vec2& BottomRight);

	void prepare();

	void draw(GuiText* engine);
};