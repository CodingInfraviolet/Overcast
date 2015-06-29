#pragma once
#include "mesh.h"
#include "transformable.h"
#include "texture.h"

/**
A class designed to implement basic static mesh functionality, adding placability and drawing methods to the
basic Mesh class.
*/
class StaticMesh : public Mesh
{
	std::vector <Transformable> m_instanceTransforms;
	std::vector <Texture>      m_appliedTextures;

public:
	/**Overrides the virtual draw() method to implement static mesh drawing functionality.*/
	void draw(Camera* camera) override;

	/**
	Creates an instance of the object in the world, stored as a privately contained information.
	@param position An instance of Transformable indication the transformation of the object.
	@param texture The texture to be applied to the object.
	*/
	void createInstance(const Transformable& position = Transformable(), const Texture& texture = Texture());

	/**Returns the number if instances of the given mesh.*/
	unsigned size()
	{
		return m_instanceTransforms.size();
	}

	Transformable& operator [] (unsigned index)
	{
		return m_instanceTransforms[index];
	}
};