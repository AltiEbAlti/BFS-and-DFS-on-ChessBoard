#include "SFML/Graphics.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#define N 10
#include <array>
#include <vector>

int  idx21(int y, int x) {
	return x + y * N;
}

void _longestpath_check(int y, int x, std::vector<int> currentpath, std::array<bool, N* N> checked, std::vector<int>& result, char* arr) {
	//std::cout << "x-> "<< x;
	//std::cout << " y->"<< y << '\n';
	currentpath.push_back(idx21(y, x));
	checked[idx21(y, x)] = true;
	if (result.size() < currentpath.size()) { //
		result = currentpath;
	}

	if (x + 1 < N && arr[0] == arr[idx21(y, x + 1)] && !(checked[idx21(y, x + 1)])) {
		_longestpath_check(y, x + 1, currentpath, checked, result, arr);
	}
	if (y + 1 < N && arr[0] == arr[idx21(y + 1, x)] && !(checked[idx21(y + 1, x)])) { //  **
		_longestpath_check(y + 1, x, currentpath, checked, result, arr);// *
	}
	if (x - 1 >= 0 && arr[0] == arr[idx21(y, x - 1)] && !(checked[idx21(y, x - 1)])) {
		_longestpath_check(y, x - 1, currentpath, checked, result, arr);
	}
	if (y - 1 >= 0 && arr[0] == arr[idx21(y - 1, x)] && !(checked[idx21(y - 1, x)])) {
		_longestpath_check(y - 1, x, currentpath, checked, result, arr);
	}
}

std::vector<int> longestpath(char* arr) { // works with DFS
	std::vector<int> result;
	std::array <bool, N* N> checked = {};
	std::vector<int> currentpath;
	_longestpath_check(0, 0, currentpath, checked, result, arr); // coordinates, coordinates, currentpath, checked squares, the longest way,
	return result;
}

std::vector<int> find_island(char* arr) { // BFS
	std::vector<int> result;
	std::array<bool, N* N> checked = {};
	std::vector <sf::Vector2i> queue {sf::Vector2i(N-1, N-1)};
	while (!queue.empty()) {
		sf::Vector2i node = queue.back();
		int x = node.x;
		int y = node.y;
		result.push_back(idx21(y, x));
		checked[idx21(node.y, node.x)] = true;
		queue.pop_back();
		if (x - 1 >= 0 && arr[N * N - 1] == arr[idx21(y, x - 1)] && !(checked[idx21(y, x - 1)])) {
			queue.insert(queue.begin(), sf::Vector2i(x - 1, y));
		}
		if (y - 1 >= 0 && arr[N * N - 1] == arr[idx21(y - 1, x)] && !(checked[idx21(y - 1, x)])) {
			queue.insert(queue.begin(), sf::Vector2i(x, y - 1));
		}
		if (x + 1 < N && arr[N * N - 1] == arr[idx21(y, x + 1)] && !(checked[idx21(y, x + 1)])) {
			queue.insert(queue.begin(), sf::Vector2i(x + 1, y));
		}
		if (y + 1 < N && arr[N * N - 1] == arr[idx21(y + 1, x)] && !(checked[idx21(y + 1, x)])) {
			queue.insert(queue.begin(), sf::Vector2i(x, y + 1));
		}
	}


	return result;
}



int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(50 * N, 50 * N), "Test");
	//rectangle.move(50, 0);

	sf::Texture image1;
	image1.loadFromFile("./images/light.png");
	sf::Texture image2;
	image2.loadFromFile("./images/dark.png");
	sf::Texture image4;
	image4.loadFromFile("./images/darkpurple.png");
	sf::Texture image3;
	image3.loadFromFile("./images/lightpurple.png"); //("D:\\eclipse_works\\chessBoard\\src\\");
	sf::Texture image5;
	image5.loadFromFile("./images/green.png");
	sf::Texture image6;
	image6.loadFromFile("./images/greenpurple.png");
	sf::Sprite rectangle(image2);
	// image1, image2 - light and dark, two cells which generates our board, according to the choice of coordinates light or dark will be replaced with 
	// the algorithm color 
	// image5 - bfs(green), image3 - dfs(purple), others are combinations of colors in format color1+color2.png
	sf::Texture Colors[] = { image1, image2, image5, image3, image4, image6 };
	// bfs(green), dfs(purple), greenpurpleя

	char arr[N * N] = {};
	for (int i = 0; i <= N * N; i++)
		arr[i] = rand() % 2;

	std::vector<int> path = longestpath(arr);
	std::vector<int> island = find_island(arr);
	for (int i = 0; i < island.size(); i++)
		arr[island[i]] = 2; // bfs - green 
	for (int i = 0; i < path.size(); i++)
		arr[path[i]] += 3;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}//
			window.clear();
			;

			for (int i = 0; i <= N * N; i++) {
				if (i % N == 0) {
					rectangle.setTexture(Colors[arr[i]]);

					rectangle.setPosition(0, i / N * 50);
				}
				else {

					rectangle.setPosition(50 * (i % N), rectangle.getPosition().y);
					rectangle.setTexture(Colors[arr[i]]); //

				}

				window.draw(rectangle);
			}

			rectangle.setPosition(0, 0);
			window.display();

		}
	}


	return 0;
}
// creating +50 +50 +50 +50  if (coordinate >=100) a b = start pos  -50 +50 y
//