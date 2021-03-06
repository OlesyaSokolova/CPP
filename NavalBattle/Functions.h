#include "BasePlayer.h"
#include "UserPlayer.h"
#include "RandomPlayer.h"
#include "OptimalPlayer.h"
#include <time.h>
#include <tuple>
namespace Sokolova{

	typedef int(*calcFunc)(std::vector<Point> points);

	inline int indexToArrayIndex(int & i)
	{
		return i - INDEX_SHIFT;
	}

	Player * createPlayer(std::string playerType);

	inline int nextPlayer(int playerIndex, ShotResult result)
	{
		bool res = (result == missed ? MISSED : NOT_MISSED);
		int next = (playerIndex + (int)!res) % PLAYERS_NUMBER;
		return next;
	}
	inline int choosePlayer()
	{
		srand(time(NULL));
		return rand() % PLAYERS_NUMBER;
	}

	bool isAccessible(const Point& point);

	inline char symbol(int j)
	{
		char c = (char)j + ADDENDUM_FOR_LETTER_LOWERCASE;
		return c;
	}

	int calcDif(int x, int y);

	Point randomPointOnLine(int line);

	void shufflePoints(std::vector<Point>& vec);

	int firstDirection_calcLastPoint(std::vector<Point> points);

	int secondDirection_calcLastPoint(std::vector<Point> points);

	int thirdDirection_calcLastPoint(std::vector<Point> points);

	int fourthDirection_calcLastPoint(std::vector<Point> points);

	std::unordered_map<int, calcFunc> initLastPointsMap();

	bool isAccessibleForTurn(const Point& point);

	inline std::string indexToString(int i)
	{
		if (i == FIRST)
		{
			return "first player";
		}
		else
		{
			return "second player";
		}
	}
	std::vector<std::string> parsingString(std::string line, std::string delim);

	std::tuple <std::string, int, std::vector<std::string>> parsingString(const int argumentsNumber, const char ** argv);

	void printHelp();
	void printRoundNumber(int currentRound, int roundsNumber);
}
