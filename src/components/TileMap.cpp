#include "components/TileMap.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "Game.h"
#include "components/TileSet.h"

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet, bool drawBorder)
    : Component(associated),
      mapWidth(0),
      mapHeight(0),
      mapDepth(0),
      drawBorder(drawBorder) {
    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load(std::string file) {
    std::ifstream inputFile(file);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file: " << file << std::endl;
        return;
    }

    // Primeiro padroniza o input
    std::string content(
        (std::istreambuf_iterator<char>(inputFile)),
        std::istreambuf_iterator<char>());
    for (char& c : content) {
        if (c == ',' || c == '\n' || c == '\r') {
            c = ' ';
        }
    }

    // Depois itera apenas nos números
    std::stringstream stream(content);

    // Os três primeriso são as dimensões
    int width;
    int height;
    int depth;
    if (!(stream >> width >> height >> depth) || width <= 0 || height <= 0 || depth <= 0) {
        std::cerr << "Error: Invalid map dimensions in: " << file << std::endl;
        return;
    }

    // Os demais são os tiles para a matriz

    std::vector<int> loadedTiles;
    int tile;
    while (stream >> tile) {
        loadedTiles.push_back(tile);
    }

    const auto expectedTileCount = static_cast<std::size_t>(width) * height * depth;
    if (loadedTiles.size() != expectedTileCount) {
        std::cerr << "Error: Expected " << expectedTileCount << " tiles in " << file
                  << ", but found " << loadedTiles.size() << std::endl;
        return;
    }

    mapWidth = width;
    mapHeight = height;
    mapDepth = depth;
    tileMatrix = std::move(loadedTiles);
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    int index =
        x +
        (y * mapWidth) +
        (z * mapWidth * mapHeight);

    return tileMatrix.at(index);
}

// Renderiza uma camada do mapa, tile a tile.
#include "Game.h"

void TileMap::RenderLayer(int layer) {
    if (!tileSet) {
        return;
    }

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int tileIndex = At(x, y, layer);

            if (tileIndex >= 0) {
                int tileX =
                    static_cast<int>(associated.box.x) +
                    x * tileSet->GetTileWidth();

                int tileY =
                    static_cast<int>(associated.box.y) +
                    y * tileSet->GetTileHeight();

                tileSet->RenderTile(tileIndex, tileX, tileY);

                if (drawBorder) {
                    SDL_Rect border = {
                        tileX,
                        tileY,
                        tileSet->GetTileWidth(),
                        tileSet->GetTileHeight()};

                    // RGBA: preto e totalmente opaco
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawRect(renderer, &border);
                }
            }
        }
    }
}

void TileMap::Render() {
    for (int layer = 0; layer < mapDepth; layer++) {
        RenderLayer(layer);
    }
}

int TileMap::GetWidth() {
    return mapWidth;
};
int TileMap::GetHeight() {
    return mapHeight;
};
int TileMap::GetDepth() {
    return mapDepth;
};

void TileMap::Update(float dt) {}
