using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
namespace OpenTool
{
    public partial class Form1 : Form
    {
        bool loaded = false;
        public Form1()
        {
            InitializeComponent();
        }
        private void glControl1_Load(object sender, EventArgs e)
        {
            
            loaded = true;
            GL.ClearColor(Color.SkyBlue);
            SetupViewport();
        }
        private void glControl1_Resize(object sender, EventArgs e)
        {
            if (!loaded)
                return;
        }
        private void glControl1_Paint(object sender, PaintEventArgs e)
        {
            if (!loaded) // Play nice
                return;

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
            GL.Color3(Color.Yellow);
            GL.Begin(BeginMode.Triangles);
            GL.Vertex2(10, 20);
            GL.Vertex2(100, 20);
            GL.Vertex2(100, 50);
            GL.End();
            GL.Color3(Color.Red);
            GL.Begin(BeginMode.Triangles);
            GL.Vertex2(10, 60);
            GL.Vertex2(200, 60);
            GL.Vertex2(200, 150);
            GL.End();
            GL.Color3(Color.Green);
            GL.Begin(BeginMode.Triangles);
            GL.Vertex2(10, 150);
            GL.Vertex2(200, 150);
            GL.Vertex2(200, 250);
            GL.End();
            GL.Color3(Color.Violet);
            GL.Begin(BeginMode.Triangles);
            GL.Vertex2(10, 250);
            GL.Vertex2(200, 250);
            GL.Vertex2(200, 350);
            GL.End();
            glControl1.SwapBuffers();
        }

        private void SetupViewport()
        {
            int w = glControl1.Width;
            int h = glControl1.Height;
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(0, w, 0, h, -1, 1); // Bottom-left corner pixel has coordinate (0, 0)
            GL.Viewport(0, 0, w, h); // Use all of the glControl painting area
        }
    }
   
}
