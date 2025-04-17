namespace Ex1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            String checkBoxText = "";
            if(checkBox1.Checked)
            {
                checkBoxText = checkBox1.Text;
            }
            if (checkBox2.Checked)
            {
                checkBoxText = checkBox2.Text;
            }
                MessageBox.Show(textBox1.Text + '\n' +
                                textBox2.Text + '\n' +
                                "Studia " + comboBox1.Text + '\n' +
                                checkBoxText
                                );
        }

        private void button2_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.Application.Exit();
        }
    }
}
