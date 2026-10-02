#include "components/TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
    : tileWidth(tileWidth), tileHeight(tileHeight), tileCount(0) {
    if (tileWidth <= 0 || tileHeight <= 0) {
        return;
    }

    tileSet.Open(file);

    if (!tileSet.IsOpen()) {
        return;
    }

    int imgHeight = tileSet.GetHeight();
    int imgWidth = tileSet.GetWidth();

    int colunas = imgWidth / tileWidth;
    int linhas = imgHeight / tileHeight;

    tileSet.SetFrameCount(colunas, linhas);

    tileCount = colunas * linhas;
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if (index >= static_cast<unsigned>(tileCount)) {
        return;
    }

    tileSet.SetFrame(index);
    tileSet.Render(x, y, tileWidth, tileHeight);
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}