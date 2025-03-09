#include <iostream>

class chunk {
    private:
        int32_t xPos, yPos, zPos;

    chunk(int32_t xPos, int32_t yPos, int32_t zPos);

    void renderChunk();

};