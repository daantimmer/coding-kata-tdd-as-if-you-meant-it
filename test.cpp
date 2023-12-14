#include "gmock/gmock.h"
#include <algorithm>
#include <array>

namespace
{
    enum class Result
    {
        unknown,
        p1,
        p2,
        tie
    };

    enum class Tile
    {
        empty,
        p1,
        p2
    };

    struct TicTacToeAlgorithm
    {
        static std::size_t Count(const std::array<Tile, 9>& board, Tile tile, int x, int y, int xstep, int ystep)
        {
            std::size_t count = 0;
            for (auto i = 0; i != 3; ++i)
            {
                if (board[x + (y * 3)] == tile)
                {
                    ++count;
                }

                x += xstep;
                y += ystep;
            }
            return count;
        }

        static Result Execute(const std::array<Tile, 9>& board, Tile tile, int x, int y)
        {
            auto countrow = Count(board, tile, 0, y, 1, 0);
            auto countcol = Count(board, tile, x, 0, 0, 1);

            auto counttlbr = Count(board, tile, 0, 0, 1, 1);
            auto counttrbl = Count(board, tile, 2, 0, -1, 1);

            if (countrow == 3 || countcol == 3 || counttlbr == 3 || counttrbl == 3)
            {
                if (tile == Tile::p1)
                {
                    return Result::p1;
                }
                else
                {
                    return Result::p2;
                }
            }

            if (std::ranges::count(board, Tile::empty) == 0)
            {
                return Result::tie;
            }

            return Result::unknown;
        }
    };

    struct TicTacToe
    {
        Result Move(Tile tile, int x, int y)
        {
            board[x + y * 3] = tile;

            return TicTacToeAlgorithm::Execute(board, tile, x, y);
        }

    private:
        std::array<Tile, 9> board{};
    };

    struct TestTicTacToe: testing::Test
    {
        TicTacToe tictactoe;
    };
}

TEST_F(TestTicTacToe, Player1MoveResultsInUnkownState)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 0), Result::unknown);
}

TEST_F(TestTicTacToe, Player2MoveResultsInUnkownState)
{
    EXPECT_THAT(tictactoe.Move(Tile::p2, 0, 0), Result::unknown);
}

TEST_F(TestTicTacToe, Player1WinsRowTop)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 1, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 0), Result::p1);
}

TEST_F(TestTicTacToe, Player2WinsRowTop)
{
    EXPECT_THAT(tictactoe.Move(Tile::p2, 0, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 1, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 2, 0), Result::p2);
}

TEST_F(TestTicTacToe, Player2InterruptsPlayer1TopRow)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 1, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 0), Result::unknown);
}

TEST_F(TestTicTacToe, Player1WinsRowMiddle)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 1, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 1), Result::p1);
}

TEST_F(TestTicTacToe, Player2WinsRowMiddle)
{
    EXPECT_THAT(tictactoe.Move(Tile::p2, 0, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 1, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 2, 1), Result::p2);
}

TEST_F(TestTicTacToe, Player1WinsRowBottom)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 2), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 1, 2), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 2), Result::p1);
}

TEST_F(TestTicTacToe, Player1WinsColumnLeft)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 2), Result::p1);
}

TEST_F(TestTicTacToe, Player2WinsColumnLeft)
{
    EXPECT_THAT(tictactoe.Move(Tile::p2, 0, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 0, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 0, 2), Result::p2);
}

TEST_F(TestTicTacToe, Player1WinsColumnMiddle)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 1, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 1, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 1, 2), Result::p1);
}

TEST_F(TestTicTacToe, Player1WinsColumnRight)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 2), Result::p1);
}

TEST_F(TestTicTacToe, Player1WinsDiagonalTopLeftBottomRight)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 1, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 2), Result::p1);
}

TEST_F(TestTicTacToe, Player1WinsDiagonalTopRightBottomLeft)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 1, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 2), Result::p1);
}

TEST_F(TestTicTacToe, Player1WinsDiagonalBottomRightTopLeft)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 2), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 1, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 0), Result::p1);
}

TEST_F(TestTicTacToe, Player1WinsDiagonalBottomLeftTopRight)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 2), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 1, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 0), Result::p1);
}

TEST_F(TestTicTacToe, Player2WinsDiagonalTopRightBottomLeft)
{
    EXPECT_THAT(tictactoe.Move(Tile::p2, 2, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 1, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 0, 2), Result::p2);
}

TEST_F(TestTicTacToe, NoPlayerWins)
{
    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 1, 0), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 2, 0), Result::unknown);

    EXPECT_THAT(tictactoe.Move(Tile::p2, 0, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 1, 1), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p1, 2, 1), Result::unknown);

    EXPECT_THAT(tictactoe.Move(Tile::p1, 0, 2), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 1, 2), Result::unknown);
    EXPECT_THAT(tictactoe.Move(Tile::p2, 2, 2), Result::tie);
}
