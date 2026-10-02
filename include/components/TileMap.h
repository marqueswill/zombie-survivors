#ifndef TILEMAP_H
#define TILEMAP_H

#include <memory>
#include <string>
#include <vector>

#include "components/Component.h"

class GameObject;
class TileSet;

class TileMap : public Component {
   public:
    TileMap(GameObject& associated, std::string file, TileSet* tileSet);

    void Load(std::string file);
    void SetTileSet(TileSet* tileSet);

    // X e Y são as posições no plano, Z é a camada ("profundidade")
    int& At(int x, int y, int z = 0);

    void Update(float dt);
    void Render();
    void RenderLayer(int layer);

    int GetWidth();
    int GetHeight();
    int GetDepth();

   private:
    std::vector<int> tileMatrix;
    std::unique_ptr<TileSet> tileSet;

    int mapWidth;
    int mapHeight;
    int mapDepth;
};

#endif