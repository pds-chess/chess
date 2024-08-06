#pragma once
/**
 * @brief all possible states a chess game can have.
 *
 * @details inProgress says that the game is happening.
 * @details Draw says that the game result is a draw.
 * @details VictoryW says that the game result into White's victory.
 * @details VictoryB says that the game result into Blacks's victory
 */
enum Gamestate { inProgress, Draw, VictoryW, VictoryB };