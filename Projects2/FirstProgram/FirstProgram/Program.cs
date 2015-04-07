using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstProgram
{
   

    class Counter
    {
        int value;
        int scaleFactor;
        public Counter(int scaleFactor)
        {
            this.scaleFactor = scaleFactor;
        }
        public void Inc()
        {
            value += scaleFactor;
        }
        public int Count
        {
            get { return value; }
        }
    }
    class PointR
    {
        public int x, y;
    }
    struct PointV
    {
        public int x, y;
    }
    class Program
    {
        int Compare(int a, int b)
        {
            if (a > b)
                return 1;
            else if (a < b)
                return -1;
            return 0;
        }
        void Award(int x)
        {
            switch(x)
            {
                case 1:
                    Console.WriteLine("Winner");
                    break;
                case 2:
                    Console.WriteLine("Runner-up");
                    break;
                case 3:
                case 4:
                    Console.WriteLine("Highly commended");
                    break;
                default:
                    Console.WriteLine("Don't quit your day job!");
                    break;
            }
                
        }
        static void Main(string[] args)
        {
            Program Comp;
            Comp = new Program();
            Console.WriteLine("Welcome to C#!");
            Counter c = new Counter(5);
            c.Inc();
            c.Inc();
            Console.WriteLine(c.Count);
            Counter d = new Counter(7);
            d.Inc();
            Console.WriteLine(d.Count);
            PointR a;
            PointV b;
            a = new PointR();
            b = new PointV();
            a.x = 7;
            b.x = 7;
            a.y = 8;
            b.y = 9;
            Console.WriteLine("x = "+ a.x);
            Console.WriteLine("y = "+ a.y);
            Console.WriteLine("x = "+ b.x);
            Console.WriteLine("y = "+ b.y);        
            PointV[]  pvarr = new PointV[1000];
            PointR[] prarr = new PointR[1000];

            for (int i=0; i < prarr.Length; i++)
                prarr[i] = new PointR();

            if (Comp.Compare(a.x,b.x)==1)
               Console.WriteLine("a.x > b.x");
            else if (Comp.Compare(a.x, b.x) == -1)
                Console.WriteLine("a.x < b.x");
            else Console.WriteLine("a.x = b.x");

            if (Comp.Compare(a.y, b.y) == 1)
                Console.WriteLine("a.y > b.y");
            else if (Comp.Compare(a.y, b.y) == -1)
                Console.WriteLine("a.y < b.y");
            else Console.WriteLine("a.y = b.y");
            Comp.Award(3);
            Comp.Award(1);
            Comp.Award(2);
            Comp.Award(4);
            Comp.Award(5);


        }
    }
}
    

