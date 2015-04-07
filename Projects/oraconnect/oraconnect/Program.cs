using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Oracle.DataAccess.Client; 

namespace oraconnect
{
    class Program
    {
        static void Main(string[] args)
        {
            DBconnector testdb = new DBconnector();
            testdb.ConnectAndQuery();
        }
    }
    class DBconnector
    {
        public void ConnectAndQuery()
        {
            using (OracleConnection conn = new OracleConnection("Data Source=(DESCRIPTION=(ADDRESS_LIST=(ADDRESS=(PROTOCOL=TCP)(HOST=torasysa)(PORT=1526)))(CONNECT_DATA=(SERVER=DEDICATED)(SERVICE_NAME=orastest.tcs.timeinc.com)));User Id=scott;Password=tiger;"))
            {              
                conn.Open();
                Console.WriteLine("State: " + conn.State);
                Console.WriteLine("Connction String: " + conn.ConnectionString);

                OracleCommand command = conn.CreateCommand();
                string sql = "SELECT * FROM emp";
                command.CommandText = sql;

                OracleDataReader reader = command.ExecuteReader();
                while (reader.Read())
                {
                    string myField = (string)reader["Ename"];
                    Console.WriteLine(myField);
                }
            }

        }

    }
}


