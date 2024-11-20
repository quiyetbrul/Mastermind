/**
 * @file game.h
 * @brief Declaration of all Game functions.
 */

#ifndef DATA_MANAGEMENT_SAVED_GAMES_GAME_H_
#define DATA_MANAGEMENT_SAVED_GAMES_GAME_H_

#include "data_management/saved_games/saved_games.h"
#include "player/player.h"

#include <ncurses.h>

namespace data_management {
/**
 * @class Game
 * @brief Represents the saved games in the game.
 *
 * The Game class manages the saved games.
 */
class Game : public SavedGames {
public:
  /**
   * @brief Default constructor.
   */
  Game();

  /**
   * @brief Saves the player's game to the database.
   *
   * @param player The player whose game needs to be saved.
   */
  void Save(player::Player &player);

  /**
   * @brief Deletes the player's game from the saved games.
   *
   * @param player The player whose game needs to be deleted.
   */
  void Delete(const int &game_id);

  /**
   * @brief Load the selected game.
   *
   * @param y The y-coordinate of the window.
   * @return int 0 if a game was selected, -1 if the user wants to go back.
   */
  int SelectGame(const std::string &menu_title);

  void SetWindow(WINDOW *window);

protected:
  WINDOW *window_;

  int GetGameId();

  void SetGameId(const int &game_id);

private:
  int limit_;
  int game_id_;
};
} // namespace data_management

#endif // DATA_MANAGEMENT_SAVED_GAMES_GAME_H_
