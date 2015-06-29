#pragma once
#include "enums.h"

enum class SoilForward { SOIL_SAVE_TYPE_BMP = 1, SOIL_SAVE_TYPE_DDS = 2, SOIL_SAVE_TYPE_TGA =0};

/**Adds the ability to load, create and manage textures in the CPU and GPU.*/
class Texture
{
protected:
	int m_height, m_width, m_components;
	unsigned m_id;
	unsigned char* m_data;
	Enum::ImageFormat m_format;
	Enum::Type m_type;
	bool m_inCPU, m_inGPU;

public:

	struct ImageType
	{
		enum ImageSaveType { BMP = SoilForward::SOIL_SAVE_TYPE_BMP, DDS = SoilForward::SOIL_SAVE_TYPE_DDS,
							TGA = SoilForward::SOIL_SAVE_TYPE_TGA };
	};


	/**The constructor does basic initialisation.*/
	Texture(Enum::Type = Enum::UNSIGNED_BYTE);

	/**Cleans up the resources, if any.*/
	~Texture();

	/**Returns the ID of the texture.*/
	GLuint id() const { return m_id; }

	/**Loads the texture from a file.
	@param location The path to the texture file. e.g. "texture.dds".
	@param loadLocationEnum The location to load the texture to. A combination of Enum::CPU and Enum::GPU.
	*/
	bool load(const char location[], int loadLocationEnum = Enum::GPU);

	bool loadFromBuffer(int width, int height, unsigned char* buffer, bool uploadToGPU, Enum::ImageFormat format = Enum::RGBA,
		const std::vector<std::pair<int, int> >& flags =
	{ { GL_TEXTURE_MAG_FILTER, GL_NEAREST }, { GL_TEXTURE_MIN_FILTER, GL_NEAREST } }, Enum::Type type = Enum::UNSIGNED_BYTE,
		Enum::InternalImageFormat = Enum::_IIFUndefined);

	/**
	Creates a texture in the CPU or GPU given the parameters. Some parameters are ignored for CPU only.
	@param width The width of the texture.
	@param height The height of the texture.
	@param loadLocationEnum The location to load the texture to. A combination of Enum::CPU and Enum::GPU.
	@param format The component format of the image. See Enum::ImageFormat. e.g., RGBA.
	@param flags The flags to be passed to the texture using the format std::pair<flag,value>. See OpenGL documentation.
		Ignored in CPU only.
	@param type Sets the type of the components of the image. See Enum::Type. e.g., UNSIGNED_BYTE. Ignored in CPU only.
	@param internalFormat The internal format under which the image is stored. See Enum::InternalImageFormat. If
		_IIFUndefined, then the format field will be used. Ignored in CPU only.
	@return Returns the id of the texture.
	*/
	bool create(int width, int height, int loadLocationEnum, Enum::ImageFormat format = Enum::RGBA,
		const std::vector<std::pair<int, int> >& flags = {}, Enum::Type type = Enum::UNSIGNED_BYTE,
		Enum::InternalImageFormat = Enum::_IIFUndefined);

	/**Saves the image file to disk as BMP*/
	bool save(const char* path, ImageType::ImageSaveType type = ImageType::DDS);

	/**Clears the entire texture.*/
	void clear();

	/**Clears the texture from the CPU.*/
	void clearCPU();

	/**Clears the texture from the GPU.*/
	void clearGPU();

	/**Sets the texture in the graphics context.*/
	void bindForGPU() const;

	/**Determines the number of components for a given ImageFormat.*/
	static int determineComponentsFromType(Enum::ImageFormat format);

	/**Determines the corresponding format to a component count.*/
	static Enum::ImageFormat determineFormatFromComponents(int components);

	/**Returns a pointer to the specified pixel in the image. Pixels are stored linearly in memory.*/
	unsigned char* getPixel(unsigned x, unsigned y);

	/**Sets the corresponding pixel to the value pointed to by px.*/
	void setPixel(unsigned x, unsigned y, const unsigned char* const px);

	static unsigned char* convert1ByteTo4Byte(unsigned char* buffer, size_t size);

	bool isInGPU();
	bool isInCPU();
};