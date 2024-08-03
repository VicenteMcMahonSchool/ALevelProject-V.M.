#!/usr/bin/python3
WIDTH_OF_TILE_MAP = 512
HEIGHT_OF_TILE_MAP = 16
NUMBER_OF_TILES = WIDTH_OF_TILE_MAP * HEIGHT_OF_TILE_MAP

tileTypes = {
    "TILE_NONE": b"\x00",
    "TILE_AIR": b"\x01",
    "TILE_BOARDER": b"\x02",
    "TILE_PLATFORM": b"\x03",
    "TILE_WIN": b"\x04",
    "TILE_LOSE": b"\x05",
    "TILE_ROTATION": b"\x06",
    "ENEMY_SPAWNER": b"\x07",
    "TILE_SPAWN": b"\x08",
}

if __name__ == "__main__":
    with open("./map", "wb") as file:
        buffer = b""
        for i in range(WIDTH_OF_TILE_MAP * HEIGHT_OF_TILE_MAP):
            if i == WIDTH_OF_TILE_MAP + 1:
                buffer += tileTypes["TILE_SPAWN"]
            elif i < WIDTH_OF_TILE_MAP:
                buffer += tileTypes["TILE_BOARDER"]
            elif i % WIDTH_OF_TILE_MAP == 0 or i % WIDTH_OF_TILE_MAP == WIDTH_OF_TILE_MAP-1:
                buffer += tileTypes["TILE_BOARDER"]
            elif i > NUMBER_OF_TILES - WIDTH_OF_TILE_MAP:
                buffer += tileTypes["TILE_LOSE"]
            else:
                buffer += tileTypes["TILE_AIR"]
        file.write(buffer)