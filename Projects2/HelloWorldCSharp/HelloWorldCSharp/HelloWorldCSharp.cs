using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloWorldCSharp
{
    class Person
    {
        private string myName ="N/A";
        private int myAge = 0;

    // Declare a Name property of type string:
    public string Name
    {
        get 
        {
           return myName; 
        }
        set 
        {
           myName = value; 
        }
    }

    // Declare an Age property of type int:
    public int Age
    {
        get 
        { 
           return myAge; 
        }
        set 
        { 
           myAge = value; 
        }
    }

    public override string ToString()
    {
        return "Name = " + Name + ", Age = " + Age;
    }
    class Hello
    {
        public static void Main(string[] args)
        {
            Random rnd = new Random();
            Console.WriteLine("Hello, World!");
            Console.WriteLine("Number of command line parameters = {0}", args.Length);
            for (int i = 0; i < args.Length; i++)
            {
                Console.WriteLine("Arg[{0}] = [{1}]", i, args[i]);
            }
            Console.WriteLine("foreach example!");
            foreach (string s in args)
            {
                Console.WriteLine(s);
            }
            Console.WriteLine("arrays example!");
            // Single-dimensional array
            int[] numbers = new int[5];

            // Multidimensional array
            string[,] names = new string[5, 4];

            // Array-of-arrays (jagged array)
            byte[][] scores = new byte[5][];

            // Create the jagged array
            for (int i = 0; i < scores.Length; i++)
            {
                scores[i] = new byte[i + 3];
            }
            for (int i = 0; i < scores.Length; i++)
            {
                for (int j = 0; j < scores[i].Length; j++)
                    scores[i][j] = (byte)rnd.Next(52); 
            }
            // Print length of each row
            for (int i = 0; i < scores.Length; i++)
            {
                Console.WriteLine("Length of row {0} is {1}", i, scores[i].Length);
                for (int j=0; j < scores[i].Length;j++)
                    Console.WriteLine(scores[i][j]);
            }
            Console.WriteLine("Simple Properties");

            // Create a new Person object:
            Person person = new Person();

            // Print out the name and the age associated with the person:
            Console.WriteLine("Person details - {0}", person);

            // Set some values on the person object:
            person.Name = "Joe";
            person.Age = 99;
            Console.WriteLine("Person details - {0}", person);

            // Increment the Age property:
            person.Age += 1;
            Console.WriteLine("Person details - {0}", person);
        }
      }
    }
}
