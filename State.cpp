#pragma once
#include "stdafx.h"
#include "State.h"
#include "System.h"
#include "camera.h"
#include "staticmesh.h"

GameState::GameState()
{
	m_world = nullptr;
}

bool GameState::initialise()
{
	m_world = new World();
	if (!m_world)
		return false;

	if (!m_world->initialise())
		return false;

	m_mainCamera = m_world->getCamera();

	return true;
}

void GameState::shutdown()
{
	if (m_world)
	{
		m_world->shutdown();
		delete m_world;
	}
}