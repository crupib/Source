using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Learning
{
    public partial class Form1 : Form
    {
        public const Learning.counter counters = new counter ();
            
        public Form1()
        {
            InitializeComponent();
 
        }

        public void Form1_Load(object sender, EventArgs e)
        {
            
            counters.Rightcounter = 0;
            counters.Wrongcounter = 0;
            label3.Text = counters.Rightcounter.ToString();
            label4.Text = counters.Rightcounter.ToString(); 

        }

        public  void button1_Click(object sender, EventArgs e)
        {
            counters.Rightcounter++;
            counters.Wrongcounter++;
            label3.Text = counters.Rightcounter.ToString();
            label4.Text = counters.Rightcounter.ToString(); 
        }
       
    }
}
