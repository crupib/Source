using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Learning
{
    class counter
    {
        int wrongcounter=0;

        public int Wrongcounter
        {
            get { return wrongcounter; }
            set { wrongcounter = value; }
        }
        int rightcounter=0;

        public int Rightcounter
        {
            get { return rightcounter; }
            set { rightcounter = value; }
        }
    }
}
