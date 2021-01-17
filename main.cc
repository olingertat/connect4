#include "board.h"
#include "controller.h"
#include "humanPlayer.h"
using namespace std;

int main() {
	Board board{};
	Controller controller(&board, make_unique<HumanPlayer>(), make_unique<HumanPlayer>());
	controller.playGame();
}
