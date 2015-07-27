using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SQLServer_connect
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void mycustBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            this.Validate();
            this.mycustBindingSource.EndEdit();
            this.tableAdapterManager.UpdateAll(this.crupidbDataSet);
            

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'crupidbDataSet.mycust' table. You can move, or remove it, as needed.
            this.mycustTableAdapter.Fill(this.crupidbDataSet.mycust);

        }
    }
}
