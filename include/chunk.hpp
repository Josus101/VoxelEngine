#ifndef CHUNK_HPP
#define CHUNK_HPP
#pragma once

#include <glm/glm.hpp>
#include <cstdint>

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 255

class Chunk {
private:
    glm::vec3 position;
    uint8_t blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT];

    int getIndex(int x, int y, int z) const;
    glm::vec3 getLocalBlockPos(int index) const;

public:
    Chunk(int xPos, int yPos, int zPos);
    Chunk(glm::vec3 pos);

    glm::vec3 getPosition() const;

    void generateChunk();
    void renderChunk();

    uint8_t getBlock(int x, int y, int z) const;
    void setBlock(int x, int y, int z, uint8_t type);
};

#endif
