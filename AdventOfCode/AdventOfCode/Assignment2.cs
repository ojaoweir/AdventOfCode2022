using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Schema;

namespace AdventOfCode
{
    public class Assignment2
    {
        public static void Run()
        {
            string[] moves = FileReader.ReadFile("ass2");
            int totalScore = 0;
            int totalScore2 = 0;
            foreach (string move in moves)
            {
                var m = new Move(move);
                totalScore +=  m.CalculateScore();
                totalScore2 += m.CalculateScore2();
            }
            Console.WriteLine(totalScore);
            Console.WriteLine(totalScore2);
        }
    }

    public class Move
    {
        MoveEnum theirMove;
        char myMove;
        enum MoveEnum
        {
            Rock,
            Paper,
            Scissors
        }
        public Move(string move)
        {
            theirMove = GetEnum(move.First());
            myMove = move.Last();
        }

        private MoveEnum GetWinner(MoveEnum move)
        {
            switch (move)
            {
                case MoveEnum.Rock:
                    return MoveEnum.Paper;
                    break;
                case MoveEnum.Paper:
                    return MoveEnum.Scissors;
                    break;
                case MoveEnum.Scissors:
                    return MoveEnum.Rock;
                    break;
            }
            return MoveEnum.Rock;
        }
        private MoveEnum GetGetLoser(MoveEnum move)
        {
            switch (move)
            {
                case MoveEnum.Rock:
                    return MoveEnum.Scissors;
                    break;
                case MoveEnum.Paper:
                    return MoveEnum.Rock;
                    break;
                case MoveEnum.Scissors:
                    return MoveEnum.Paper;
                    break;
            }
            return MoveEnum.Rock;
        }

        private MoveEnum GetEnum(char move)
        {
            switch(move)
            {
                case 'A':
                    return MoveEnum.Rock;
                    break;
                case 'B':
                    return MoveEnum.Paper;
                    break;
                case 'C':
                    return MoveEnum.Scissors;
                    break;
                case 'X':
                    return MoveEnum.Rock;
                    break;
                case 'Y':
                    return MoveEnum.Paper;
                    break;
                case 'Z':
                    return MoveEnum.Scissors;
                    break;
            }
            Console.WriteLine("wrong move: " + move);
            return MoveEnum.Rock;
        }

        public int CalculateScore()
        {
            var myMove = GetEnum(this.myMove);
            int winScore = 0;
            if (theirMove == myMove)
            {
                winScore = 3;
            } else
            {
                if (myMove == GetWinner(theirMove)) winScore = 6;
            }
            return winScore + ScoreOfMove(myMove);
        }

        public int CalculateScore2()
        {
            MoveEnum myMove;
            switch(this.myMove)
            {
                case 'X':
                    myMove = GetGetLoser(theirMove);
                    break;
                case 'Y':
                    myMove = theirMove;
                    break;
                case 'Z':
                    myMove = GetWinner(theirMove);
                    break;
                default:
                    myMove= MoveEnum.Rock;
                    break;
            }
            int winScore = 0;
            if (theirMove == myMove)
            {
                winScore = 3;
            } else
            {
                if (myMove == GetWinner(theirMove)) winScore = 6;
            }
            return winScore + ScoreOfMove(myMove);
        }

        private int ScoreOfMove(MoveEnum move)
        {
            switch (move)
            {
                case MoveEnum.Rock:
                    return 1;
                case MoveEnum.Paper:
                    return 2;
                case MoveEnum.Scissors:
                    return 3;
                default: 
                    return -100000;
            }
        }
    }
}
