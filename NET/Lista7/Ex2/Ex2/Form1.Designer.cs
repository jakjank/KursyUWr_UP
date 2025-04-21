namespace Ex2
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            smoothProgressBar1 = new SmoothProgressBar(components);
            bindingSource1 = new BindingSource(components);
            smoothProgressBar2 = new SmoothProgressBar(components);
            timer1 = new System.Windows.Forms.Timer(components);
            ((System.ComponentModel.ISupportInitialize)bindingSource1).BeginInit();
            SuspendLayout();
            // 
            // smoothProgressBar1
            // 
            smoothProgressBar1.Location = new Point(0, 0);
            smoothProgressBar1.max = 100;
            smoothProgressBar1.min = 0;
            smoothProgressBar1.Name = "smoothProgressBar1";
            smoothProgressBar1.Size = new Size(0, 0);
            smoothProgressBar1.TabIndex = 0;
            smoothProgressBar1.value = 0;
            // 
            // smoothProgressBar2
            // 
            smoothProgressBar2.Location = new Point(196, 140);
            smoothProgressBar2.max = 100;
            smoothProgressBar2.min = 0;
            smoothProgressBar2.Name = "smoothProgressBar2";
            smoothProgressBar2.Size = new Size(392, 29);
            smoothProgressBar2.TabIndex = 0;
            smoothProgressBar2.Text = "smoothProgressBar2";
            smoothProgressBar2.value = 0;
            // 
            // timer1
            // 
            timer1.Enabled = true;
            timer1.Tick += timer1_Tick;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(smoothProgressBar2);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)bindingSource1).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private SmoothProgressBar smoothProgressBar1;
        private BindingSource bindingSource1;
        private SmoothProgressBar smoothProgressBar2;
        private System.Windows.Forms.Timer timer1;
    }
}
