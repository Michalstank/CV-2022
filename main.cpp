#include <iostream>
#include <stdlib.h>

const int mapx = 7;
const int mapy = 5;

const int b_count = 1;

const char o_GameMap[mapy][mapx] = {
		{'#','#','#','#','#','#','#'},
		{'#',' ',' ',' ',' ',' ','#'},
		{'#',' ',' ',' ','#',' ','#'},
		{'#',' ','#',' ','#',' ','#'},
		{'#','#','#','#','#','#','#'}
};

char d_GameMap[mapy][mapx] = {
		{'#','#','#','#','#','#','#'},
		{'#',' ',' ',' ',' ',' ','#'},
		{'#',' ',' ',' ','#',' ','#'},
		{'#',' ','#',' ','#',' ','#'},
		{'#','#','#','#','#','#','#'}
};

struct Player {
	int x = 1;
	int y = 1;
	char icon = '@';
};

struct Box {
	int x;
	int y;
	char icon = 'o';
};

const Box s_boxList[b_count] = {
	{2,2,'o'}
};

Box d_boxList[b_count];

void initBoxList() {
	memcpy(d_boxList, s_boxList, sizeof(d_boxList));
}


Player player;

int xOff = 0;
int yOff = 0;

const int viewHeight = 25;
const int viewWidth = 80;

char input;

void drawMap();

void mergeMap();
void clearMap();

void inputHandler(char c);
void movePlayer(char c);
void moveMap(char c);

bool validMove(Player p, int dy,int dx);
bool checkIfBox(int y, int x);
bool checkIfPushValid(Box b, int dy, int dx);
Box getBox(int y, int x);
void moveBox(Box br, int dy, int dx);

bool isOver();

int main() {

	initBoxList();

	while (isOver()) {
		drawMap();
		std::cin >> input;
		inputHandler(input);
	}

	return 0;
}

void drawMap() {
	system("CLS");

	mergeMap();
	for (int y = yOff; y < viewHeight+yOff; y++) {
		for (int x = xOff; x < viewWidth+xOff; x++) {
			if (y < mapy&& y>-1 && x>-1 && x < mapx) {
				std::cout << d_GameMap[y][x] << " ";
			}
			else {
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}

	clearMap();
}

void mergeMap() {
	for (int b = 0; b < b_count; b++) {
		d_GameMap[d_boxList[b].y][d_boxList[b].x] = 'o';
	}

	d_GameMap[player.y][player.x] = player.icon;
}

void clearMap() {
	memcpy(d_GameMap,o_GameMap,sizeof(d_GameMap));
}

void inputHandler(char c) {
	if (c == 'a' || c == 'd' || c == 's' || c == 'w') {
		movePlayer(c);
	}
	else if (c == 'i' || c == 'j' || c == 'k' || c == 'm') {
		moveMap(c);
	}
}

void moveMap(char c) {
	switch (c) {
	case 'i':
		yOff += 1;
		break;
	case 'j':
		xOff += 1;
		break;
	case 'k':
		xOff -= 1;
		break;
	case 'm':
		yOff -= 1;
		break;
	}
}

void movePlayer(char c) {
	switch (c) {
	case 'a':
		if (validMove(player,0,-1)) {
			player.x -= 1;
		}
		break;
	case 'w':
		if (validMove(player, -1,0)) {
			player.y -= 1;
		}
		break;
	case 's':
		if (validMove(player, 1, 0)) {
			player.y += 1;
		}
		break;
	case 'd':
		if (validMove(player, 0,1)) {
			player.x += 1;
		}
		break;
	}
}

bool validMove(Player p, int dy, int dx) {
	if (o_GameMap[p.y + dy][p.x + dx] != '#') {
		if (checkIfBox(p.y + dy, p.x + dx)) {
			if (checkIfPushValid(getBox(p.y + dy, p.x + dx), dy, dx)) {
				moveBox(getBox(p.y + dy, p.x + dx), dy, dx);
			}
			else {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool checkIfBox(int y, int x) {
	for (int b = 0; b < b_count; b++) {
		if (d_boxList[b].y == y && d_boxList[b].x == x) {
			return true;
		}
	}
	return false;
}

bool checkIfPushValid(Box b, int dy, int dx) {
	mergeMap();

	if (d_GameMap[b.y + dy][b.x + dx] == ' ') {
		clearMap();
		return true;
	}
	clearMap();
	return false;
}

Box getBox(int y, int x) {
	for (int b = 0; b < b_count; b++) {
		if (d_boxList[b].y == y && d_boxList[b].x == x) {
			return d_boxList[b];
		}
	}
}

void moveBox(Box br, int dy, int dx) {
	for (int b = 0; b < b_count; b++) {
		if (d_boxList[b].y == br.y && d_boxList[b].x == br.x) {
			d_boxList[b].y = br.y + dy;
			d_boxList[b].x = br.x + dx;
		}
	}
}

bool isOver() {
	return 1;
}