#pragma once
#include "include/chunk.hpp"


#include "chunk.hpp"
#include <iostream> // only if needed

Chunk::Chunk(int xPos, int yPos, int zPos) 
    : position(xPos, yPos, zPos) {}

Chunk::Chunk(glm::vec3 pos)
    : position(pos) {}

int Chunk::getIndex(int x, int y, int z) const {
    return x + CHUNK_SIZE * z + CHUNK_SIZE * CHUNK_SIZE * y;
}

glm::vec3 Chunk::getLocalBlockPos(int index) const {

    int x = index % CHUNK_SIZE;

    int z = (index / CHUNK_SIZE) % CHUNK_SIZE;

    int y = index / (CHUNK_SIZE * CHUNK_SIZE);

    return {x, y, z};
}

glm::vec3 Chunk::getPosition() const {
    return position;
}

uint8_t Chunk::getBlock(int x, int y, int z) const {
    return blocks[getIndex(x, y, z)];
}

void Chunk::setBlock(int x, int y, int z, uint8_t type) {
    blocks[getIndex(x, y, z)] = type;
}

void Chunk::generateChunk() {
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                if (y < 32)
                    setBlock(x, y, z, 1); // dirt
                else
                    setBlock(x, y, z, 0); // air
            }
        }
    }
}

void Chunk::renderChunk() {
    // divide the render to each side and check if the face needs to be drawn (start with only working on this chunk and ignore the bordering chunks)

    // top

    // bottom

    // left

    // right

    // front

    // back
}
