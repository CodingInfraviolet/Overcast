#include "stdafx.h"
#include "Texture.h"
#include "graphicsinterface.h"
#include "SOIL.h"
Texture::Texture(Enum::Type type)
{
	m_id = 0;
	m_type = type;
	m_format = Enum::RGBA;
	m_inCPU = false;
	m_inGPU = false;
	m_height = m_width = m_components = 0;
	m_data = nullptr;
}

Texture::~Texture()
{
	clear();
}

bool Texture::loadFromBuffer(int width, int height, unsigned char* buffer, bool uploadToGPU,
	Enum::ImageFormat format,const std::vector<std::pair<int, int> >& flags, Enum::Type type,
	Enum::InternalImageFormat internalFormat)
{
	clear();
	m_inGPU = uploadToGPU;
	m_inCPU = true;

	m_width = width;
	m_height = height;

	m_type = type;
	m_format = format;

	m_components = determineComponentsFromType(m_format);

	if (uploadToGPU)
	{
		m_id = GraphicsInterface::createTexture2D(width, height, flags, m_format, m_type, buffer, internalFormat);
	}

	m_data = buffer;
	if (m_data == nullptr)
		return false;

	return true;
}

bool Texture::create(int width, int height, int loadLocationEnum,
	Enum::ImageFormat format, const std::vector<std::pair<int, int> >& flags, Enum::Type type,
	Enum::InternalImageFormat internalFormat)
{
	clear();

	m_inCPU = (loadLocationEnum & Enum::CPU) == Enum::CPU;
	m_inGPU = (loadLocationEnum & Enum::GPU) == Enum::GPU;

	m_width = width;
	m_height = height;

	m_type = type;
	m_format = format;

	m_components = determineComponentsFromType(m_format);

	if (m_inGPU)
	{
		m_id = GraphicsInterface::createTexture2D(width, height, flags, m_format, m_type, nullptr, internalFormat);
	}
	if (m_inCPU)
	{
		m_data = (unsigned char*)malloc(m_width*m_height*m_components);
		if (m_data == nullptr)
			return false;
		memset(m_data, 0, m_width*m_height*m_components);
	}
	return true;
}

bool Texture::load(const char location[], int loadLocationEnum)
{
	clear();

	m_inCPU = (loadLocationEnum & Enum::CPU) == Enum::CPU;
	m_inGPU = (loadLocationEnum & Enum::GPU) == Enum::GPU;
	m_type = Enum::Type::UNSIGNED_BYTE;

	Inform(std::string("Loading image: \"") + location + "\"...");

	m_data = SOIL_load_image(location, &m_width, &m_height, &m_components, SOIL_LOAD_RGBA);
	if (m_data == NULL)
	{
		Warning("SOIL Failed to load image!");
		return false;
	}

	m_format = determineFormatFromComponents(m_components);

	if (m_inGPU)
	{
		m_id = GraphicsInterface::createTexture2D(m_width, m_height,
		{
			{ GL_TEXTURE_WRAP_S, GL_REPEAT },
			{ GL_TEXTURE_WRAP_T, GL_REPEAT },
			{ GL_TEXTURE_MAG_FILTER, GL_LINEAR },
			{ GL_TEXTURE_MIN_FILTER, GL_LINEAR }
		}, m_format, m_type, m_data);
	}

	if (!m_inCPU)
		SOIL_free_image_data(m_data);

	return true;
}

void Texture::clear()
{
	clearGPU();
	clearCPU();
}

void Texture::clearCPU()
{
	if (m_inCPU)
	{
		free(m_data);
		m_data = nullptr;
		m_inCPU = false;
	}
}

void Texture::clearGPU()
{
	if (m_inGPU)
	{
		GraphicsInterface::destroyTexture2D(m_id);
		m_id = 0;
		m_inGPU = false;
	}
}

int Texture::determineComponentsFromType(Enum::ImageFormat format)
{
	switch (format)
	{
	case Enum::ImageFormat::RGB:
		return 3;
	case Enum::ImageFormat::RGBA:
		return 4;
	default:
		assert(0);
		return 0;
	}
}

Enum::ImageFormat Texture::determineFormatFromComponents(int components)
{
	switch (components)
	{
	case 3:
		return Enum::ImageFormat::RGB;
	case 4:
		return Enum::ImageFormat::RGBA;
	default:
		assert(0);
		return Enum::ImageFormat::RGBA; //to avoid warning
	}
}

void Texture::bindForGPU() const
{
	GraphicsInterface::bindTextureID(m_id);
}

/**Saves the image file to disk as BMP*/
bool Texture::save(const char* path, ImageType::ImageSaveType type)
{
	if (!m_inCPU)
		return false;
	if (!SOIL_save_image(path, type, m_width, m_height, m_components, m_data))
		return false;
	return true;
}

unsigned char* Texture::getPixel(unsigned x, unsigned y)
{
	return m_data + (x + m_width*y)*m_components;
}

void Texture::setPixel(unsigned x, unsigned y, const unsigned char* const px)
{
	int index = (x + m_width*y)*m_components;
	for (int i = 0; i < m_components; ++i)
		m_data[index + i] = px[i];
}

unsigned char* Texture::convert1ByteTo4Byte(unsigned char* buffer, size_t size)
{
	unsigned char* out = new unsigned char[size * 4];
	for (size_t i = 0; i < size; ++i)
	{
		out[i * 4] = buffer[i];
		out[i * 4 + 1] = buffer[i];
		out[i * 4 + 2] = buffer[i];
		out[i * 4 + 3] = buffer[i];
	}
	return out;
}

bool Texture::isInGPU()
{
	return m_inGPU;
}

bool Texture::isInCPU()
{
	return m_inCPU;
}