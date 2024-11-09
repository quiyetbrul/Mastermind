#include "scoreboard.h"

namespace data_management {
Scoreboard::Scoreboard()
    : db_(MASTERMIND_DATA, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
}
} // namespace data_management
