using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExercisesProject.Exercises
{
    class BeaufortCipher
    {
        //static void Main(string[] args)
        public static void Run()
        {
            Console.WriteLine("BeaufortCipher");
            Console.WriteLine();

            string clearText = "texttocipher";

            Console.WriteLine("Original Text: " + clearText);

            List<char> alphabet =
                Enumerable.Range('a', 'z' - 'a' + 1)
                .Select(x => (char)x).ToList();

            char[][] tabulaRecta = new char['z' - 'a' + 1][];
            for (int i = 0; i < tabulaRecta.Length; i++)
            {
                tabulaRecta[i] = alphabet.ToArray();
                var first = alphabet.First();
                alphabet.Remove(first);
                alphabet.Insert(alphabet.Count, first);
            }
            string keyword = "alltech";
            Console.WriteLine("Keyword: " + keyword);

            Console.WriteLine();

            string cipherText = Cipher(clearText, tabulaRecta, keyword);
            Console.WriteLine("Ciphered Text: {0}", cipherText);

            string decipherText = Decipher(cipherText, tabulaRecta, keyword);
            Console.WriteLine("Deciphered Text: {0}", decipherText);

            Console.ReadKey();
        }

        private static string GrowToTextSize(int length, string keyword)
        {
            string result = keyword;

            int idx = 0;
            while (result.Length < length)
            {
                result += keyword[idx++];

                if (idx >= keyword.Length)
                {
                    idx = 0;
                }
            }

            return result;
        }

        private static int IndexOf(char[] array, char toFind)
        {
            int result = -1;

            for (int i = 0; i < array.Length; i++)
            {
                if (array[i] == toFind)
                {
                    result = i;
                    break;
                }
            }

            return result;
        }

        private static string Cipher(string clearText, char[][] tabulaRecta, string keyword)
        {
            string result = string.Empty;

            keyword = GrowToTextSize(clearText.Length, keyword);

            for (int i = 0; i < clearText.Length; i++)
            {
                int row = keyword[i] - 'a';
                char charToCipher = clearText[i];

                int idx = IndexOf(tabulaRecta[row], charToCipher);

                if (idx == 0)
                {
                    idx = tabulaRecta[row].Length;
                }

                idx = tabulaRecta[row].Length - idx;

                result += tabulaRecta[0][idx];
            }

            return result;
        }

        private static string Decipher(string cipherText, char[][] tabulaRecta, string keyword)
        {
            string result = string.Empty;

            result = Cipher(cipherText, tabulaRecta, keyword);

            return result;
        }
    }
}
