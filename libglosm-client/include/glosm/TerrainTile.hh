/*
 * Copyright (C) 2010-2011 Dmitry Marakasov
 *
 * This file is part of glosm.
 *
 * glosm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * glosm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with glosm.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TERRAINTILE_HH
#define TERRAINTILE_HH

#include <glosm/Tile.hh>
#include <glosm/NonCopyable.hh>
#include <glosm/BBox.hh>

#include <glosm/util/gl.h>

#include <memory>
#include <vector>

class SimpleVertexBuffer;
class HeightmapDatasource;

class Projection;

template<class T>
class VBO;

/**
 * A terrain tile
 *
 * This tile type is used by TerrainLayer
 */
class TerrainTile : public Tile, private NonCopyable {
protected:
	struct TerrainVertex {
		Vector3f pos;
		Vector3f norm;
	};

protected:
	typedef std::vector<TerrainVertex> VertexVector;
	typedef std::vector<GLushort> IndexVector;

protected:
	std::auto_ptr<VertexVector> vertices_;
	std::auto_ptr<IndexVector> indices_;

	std::auto_ptr<VBO<TerrainVertex> > vbo_;
	std::auto_ptr<VBO<GLushort> > ibo_;

	size_t size_;

public:
	TerrainTile(const Projection& projection, HeightmapDatasource& datasource, const Vector2i& ref, const BBoxi& bbox);

	/**
	 * Destructor
	 */
	virtual ~TerrainTile();

	/**
	 * Moves projected geometry into OpenGL vertex buffers
	 *
	 * This can't be done in constructor as it may be called
	 * from another thread, so this is done in Render()
	 *
	 * @todo doing tihs many times in a single frame may produce
	 * noticeable lag so maybe it should be limited somehow
	 */
	void BindBuffers();

	/**
	 * Render this tile
	 */
	virtual void Render();

	/**
	 * Returns tile size in bytes
	 */
	virtual size_t GetSize() const;
};

#endif
