using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ConnectCsharpToMysql
{
    public partial class Form1 : Form
    {
        DBConnect testdb = new DBConnect();
        public Form1()
        {
            InitializeComponent();
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int count = 0;
         //   testdb.OpenConnection();
            count = testdb.Count();
            MessageBox.Show(count.ToString()+" rows");
            //testdb.Delete();
            //testdb.Insert();
           // testdb.CloseConnection();
            //testdb.Update();
        }
    }
}
