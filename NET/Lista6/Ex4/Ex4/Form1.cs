using System.Windows.Forms;

namespace Ex4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string pathFrom = openFileDialog1.FileName;
                string fileName = Path.GetFileName(pathFrom);
                string extension = Path.GetExtension(pathFrom);

                if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
                {
                    string selectedFolder = folderBrowserDialog1.SelectedPath;

                    saveFileDialog1.InitialDirectory = selectedFolder;
                    saveFileDialog1.FileName = fileName;
                    saveFileDialog1.Filter = $"{extension.ToUpper()} files (*{extension})|*{extension}|All files (*.*)|*.*";

                    if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                    {
                        string pathTo = saveFileDialog1.FileName;
                        File.Copy(pathFrom, pathTo, overwrite: true);
                    }
                }
            }

            this.Close();
        }
    }
}
