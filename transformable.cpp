#include "stdafx.h"
#include "transformable.h"

void Transformable::updateMatrix()
{
	if (m_pendingMatrixUpdate)
		forceMatrixUpdate();
}

void Transformable::forceMatrixUpdate()
{
	m_matrix.reset();
	m_matrix *= math::createTranslationMatrix(m_pos);
	m_matrix *= m_rot.normalize().toMatrix();
	m_matrix *= math::createScaleMatrix(m_scale);

	m_pendingMatrixUpdate = false; //Signals that no update is needed
}
