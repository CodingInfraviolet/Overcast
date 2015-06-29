#pragma once

class GeometryShader;
class ShadowShader;
class Camera;
/**An interface for all drawable entities.*/
class Drawable
{
public:
	/**Override this to add drawing functionality.*/
	virtual void draw(Camera* camera) = 0;

	/**A pointer to the global geometry shader to be used.*/
	static GeometryShader* s_geometryShader;
	static ShadowShader*   s_shadowShader;
};
