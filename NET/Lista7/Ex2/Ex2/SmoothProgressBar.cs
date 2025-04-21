using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex2
{
    public partial class SmoothProgressBar : Control
    {
        private int _min = 0;
        private int _max = 100;
        private int _value = 0;

        public int min
        {
            get => _min;
            set
            {
                _min = value;
                Invalidate();
            }
        }

        public int max
        {
            get => _max;
            set
            {
                _max = value;
                Invalidate();
            }
        }

        public int value
        {
            get => _value;
            set
            {
                _value = value;
                Invalidate();
            }
        }

        // ???
        public SmoothProgressBar()
        {
            InitializeComponent();
        }

        public SmoothProgressBar(IContainer container)
        {
            container.Add(this);
            SetStyle(ControlStyles.ResizeRedraw | ControlStyles.UserPaint | ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer, true);
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            var g = e.Graphics;
            g.Clear(this.BackColor);

            if (_max == _min) return;

            float progressRatio = (float)(_value - _min) / (_max - _min);
            int progressWidth = (int)(this.Width * progressRatio);

            using (Brush brush = new SolidBrush(Color.Chartreuse))
            {
                g.FillRectangle(brush, 0, 0, progressWidth, this.Height);
            }

            using (Pen border = new Pen(Color.Black, 1))
            {
                g.DrawRectangle(border, 0, 0, this.Width - 1, this.Height - 1);
            }
        }
    }
}
