#include <string>
#include "View.h"
namespace Sokolova {
	class Game
	{
	private:
		Game(std::vector<std::string> playerTypes, int roundsNumber);		
		View * view_;
		std::vector<Player*> players_;
		int roundsNumber_;
		int statistic_[PLAYERS_NUMBER];
	public:		
		static Game& createGame(std::vector<std::string> playerTypes, int roundsNumber)
		{
			static Game newGame(playerTypes, roundsNumber);
			return newGame;
		}
		void start();		
		int round(int currentRoundNumber);
		ShotResult shoot(int playerIndex, Point p);	
	};	
}

