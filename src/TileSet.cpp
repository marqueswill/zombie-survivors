#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
    : tileWidth(tileWidth), tileHeight(tileHeight) {
    tileSet.Open(file);

    if (!tileSet.IsOpen()) {
        return;
    }

    // Altura e largura da imagem
    int imgHeight = tileSet.GetHeight();
    int imgWidth = tileSet.GetWidth();

    // Número de colunas e linhas que a imagem ocupa, com base no tamanho do tile
    int colunas = imgWidth / tileWidth;
    int linhas = imgHeight / tileHeight;

    tileSet.SetFrameCount(colunas, linhas);

    // Número de tiles que a imagem ocupa
    tileCount = colunas * linhas;
}

void TileSet::RenderTile(unsigned index, float x, float y) {}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}