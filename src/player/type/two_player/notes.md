# Two-Player Mode Notes

- if no log in
  - both players are anonymous and play on the same screen
  - real time

- if log in
  - can play online
    - need to learn networking for this. enet is a good library for this
    - if no networking, online playgame can happen but not in real time
      - player 1 plays and then player 2 plays
      - changes happen in the database. will need associated game_id for this
      - can be expensive to implement both db storage and overall CRUD operations
  - can have user profile
    - stats
      - started games vs completed games
      - win/loss ratio
      - average time to complete a game
      - average guesses per game
