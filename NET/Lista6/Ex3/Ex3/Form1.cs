namespace Ex3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            toolTip1.SetToolTip(pictureBox1, "fajna strza³ka");
        }

        private void obróæWPrawoToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Image img = pictureBox1.Image;
                img.RotateFlip(RotateFlipType.Rotate90FlipNone);

                pictureBox1.Image = img;
                pictureBox1.Refresh();
            }
        }

        private void obróæWLewoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Image img = pictureBox1.Image;
                img.RotateFlip(RotateFlipType.Rotate270FlipNone);

                pictureBox1.Image = img;
                pictureBox1.Refresh();
            }
        }

        private void witajToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Witaj!");
        }

        private void zegnajToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("¯egnaj!");
        }

        private void jakSieMaszToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Jak siê masz?");
        }

        private void zapiszToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Mo¿e kiedyœ...");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var splitContForm = new splitContainerForm();
            splitContForm.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            var panel = new FlowLayoutForm();
            panel.Show();
        }
    }
}
