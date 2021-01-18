#include <iostream>
#include "renderer.h"
#include "controller.h"
#include "game.h"

int main(){
	constexpr std::size_t kScreenWidth{640};
	constexpr std::size_t kScreenHeight{480};

	Renderer renderer(kScreenWidth, kScreenHeight);
	Controller controller;
	Game game(kScreenWidth, kScreenHeight);
	game.Run(controller, renderer); 
	std::cout << "Exiting Pong! " << "\n";
	Score score = game.GetScore();
	std::cout << "Score: " << score.playerLeft << " : " << score.playerRight  << "\n";
	return 0;
}