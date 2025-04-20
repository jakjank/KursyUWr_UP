using System.DirectoryServices.ActiveDirectory;
using System.Drawing.Text;

namespace Ex1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint | ControlStyles.OptimizedDoubleBuffer, true);
        }
        
        private void drawDial(Graphics g, int unit)
        {
            double radius = 0.9 * (double)unit;
            Font font = new Font("Arial", (int)(0.05* (double)unit));
            Brush brush = Brushes.Black;
            
            for (int hour = 1; hour <= 12; hour++)
            {
                double angle = Math.PI / 6 * (hour - 3);
                float x = (float)(radius * Math.Cos(angle));
                float y = (float)(radius * Math.Sin(angle));

                string hourText = hour.ToString();

                var size = g.MeasureString(hourText, font);
                g.DrawString(hourText, font, brush, x - size.Width / 2, y - size.Height / 2);
            }
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            var g = e.Graphics;
            g.TranslateTransform(this.ClientSize.Width / 2, this.ClientSize.Height / 2);
            var time = DateTime.Now;
            var unit = Math.Min(this.ClientSize.Width/2, this.ClientSize.Height/2);

            drawDial(g,unit);

            //sekundnik
            var gState = g.Save();
            g.RotateTransform(180+6 * time.Second);
            g.FillRectangle(Brushes.Red, 0, 0, 3, (float)0.9*unit);
            g.Restore(gState);

            //minutnik
            gState = g.Save();
            g.RotateTransform(180+6 * time.Minute + time.Second*0.1f);
            g.FillRectangle(Brushes.Black, 0, 0, 5, (float)0.8 * unit);
            g.Restore(gState);

            //godzinowa
            e.Graphics.RotateTransform(180+30 * time.Hour);
            e.Graphics.FillRectangle(Brushes.Black, 0, 0, 5, (float)0.6 * unit);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.Invalidate();
        }
    }
}
