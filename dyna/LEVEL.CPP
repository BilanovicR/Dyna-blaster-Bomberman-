#include "Level.h"

Level::Level(string path, SDL_Renderer *renderer) {
    int tileId;
    levelPath = path;
    ifstream input;
    input.open(levelPath.c_str());
    input >> width;
    input >> height;

    //popunjavanje matrice na osnovu ucitanog id-a Tile-a
    for(size_t i = 0; i < width; i++) {
        levelMatrix.push_back(vector<int>());
        for(size_t j = 0; j < height; j++) {
            input >> tileId;
            levelMatrix[i].push_back(tileId);
        };
    };

    //konstruisanje 4 osnova tipa Tile-a i dodavanje u listu tipova
    levelTiles.push_back(new Tile(renderer, "resources/tiles/block.png", 0, false, false));
    levelTiles.push_back(new Tile(renderer, "resources/tiles/grass.png", 1, true, true));
    levelTiles.push_back(new Tile(renderer, "resources/tiles/wall.png", 2, false, true));
    levelTiles.push_back(new Tile(renderer, "resources/tiles/door.png", 3, true, true));
}

void Level::draw(SDL_Renderer *renderer) {

    for(size_t i = 0; i < levelMatrix.size(); i++) {
        for(size_t j = 0; j < levelMatrix[i].size(); j++) {
            //na osnovu id-a u matrici iscrtava se odredjeni tip Tile-a
            //i to na koordinatama na osnovu reda i kolone u matrici
            levelTiles[levelMatrix[i][j]]->drawTile(renderer, levelMatrix[i][j], j, i);
        }
    }
}

Level::~Level() {
    levelTiles.clear();
}

bool Level::checkWalkableTile(int iMatrix, int jMatrix) {
    int foundTile = this->levelMatrix[iMatrix][jMatrix];
    if (this->levelTiles[foundTile]->walkable == true) {
        return true;
    } else return false;

}

bool Level::checkDestroyableTile(int iMatrix, int jMatrix) {
    int foundTile = this->levelMatrix[iMatrix][jMatrix];
    if (this->levelTiles[foundTile]->destroyable == true) {
        return true;
    } else return false;

}

bool Level::checkExitTile(SDL_Rect other){
    //provera da li je rect(tj dyna) dodirnula izlaz na osnovu njenih koordinata
    //koje su preracunate u red i kolonu u matrici
    int otherI = other.y/32;
    int otherJ = other.x/32;
if (otherI < levelMatrix.size() && otherJ < levelMatrix.size() && otherI>=0 && otherJ >=0){
        //izlaz ima id=3
    if (levelMatrix[otherI][otherJ] == 3) return true;
    };
    return false;
}



