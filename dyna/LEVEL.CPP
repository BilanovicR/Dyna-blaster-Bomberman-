#include "Level.h"

Level::Level(string path, SDL_Renderer *renderer)
{
    int tileId;
    levelPath = path;
    ifstream input;
    input.open(levelPath.c_str());
    input >> width;
    input >> height;

    for(size_t i = 0; i < width; i++)
    {
        levelMatrix.push_back(vector<int>());
        for(size_t j = 0; j < height; j++)
        {
            input >> tileId;
            levelMatrix[i].push_back(tileId);
        };
    };

    levelTiles.push_back(new Tile(renderer, "resources/tiles/block.png", 0, false, false));
    levelTiles.push_back(new Tile(renderer, "resources/tiles/grass.png", 1, true, false));
    levelTiles.push_back(new Tile(renderer, "resources/tiles/wall.png", 2, false, true));
    levelTiles.push_back(new Tile(renderer, "resources/tiles/door.png", 3, true, true));
}

void Level::draw(SDL_Renderer *renderer){

    for(size_t i = 0; i < levelMatrix.size(); i++)
    {
        for(size_t j = 0; j < levelMatrix[i].size(); j++)
        {
            levelTiles[levelMatrix[i][j]]->drawTile(renderer, levelMatrix[i][j], j, i);
        }
    }
}

Level::~Level()
{
    levelTiles.clear();
}

int getIdFromMatrix(Level *levelWithTiles, int iMatrix, int jMatrix){
    int foundTile = NULL;
for(size_t i = 0; i < levelWithTiles->levelMatrix.size(); i++)
    {
        for(size_t j = 0; j < levelWithTiles->levelMatrix[i].size(); j++)
        {
            if (i==iMatrix && j==jMatrix){
                foundTile = levelWithTiles->levelMatrix[i][j];
                }
        }
    }
return foundTile;
}

