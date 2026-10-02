#ifndef TILESET_H
#define TILESET_H

#include <string>

#include "Sprite.h"

// Esta classe é responsável por armazenar os tiles utilizados
// na renderização do TileMap. Internamente, os tiles fazem parte de um
// grande Sprite (img/Tileset.png). Quando queremos renderizar um deles,
// recortamos usando o clip do Sprite.
class TileSet {
   public:
    TileSet(int tileWidth, int tileHeight, std::string file);

    void RenderTile(unsigned index, float x, float y);

    int GetTileWidth();
    int GetTileHeight();

   private:
    Sprite tileSet;
    int tileWidth;
    int tileHeight;
    int tileCount;
};

#endif