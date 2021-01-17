#include "board.h"
#include "controller.h"
#include "humanPlayer.h"
#include "minMaxPlayer.h"
using namespace std;

int main() {
	Board board{};
	Controller controller(&board, make_unique<HumanPlayer>(), make_unique<MinMaxPlayer>(false, 6));
	controller.playGame();
}
