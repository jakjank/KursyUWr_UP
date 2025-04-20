using System.Configuration;
using System.Runtime.CompilerServices;
using System.Windows.Forms;

namespace Ex5
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
            HelloMsg = new Label();
            timer1 = new System.Windows.Forms.Timer(components);
            SuspendLayout();
            // 
            // HelloMsg
            // 
            HelloMsg.AutoSize = true;
            HelloMsg.Location = new Point(108, 44);
            HelloMsg.Name = "HelloMsg";
            HelloMsg.Size = new Size(74, 20);
            HelloMsg.TabIndex = 0;
            HelloMsg.Text = "some text";
            HelloMsg.Text = ConfigurationManager.AppSettings["WelcomeMessage"];
            // 
            // timer1
            // 
            timer1.Enabled = true;
            timer1.Tick += TimerCloses;
            timer1.Interval = int.Parse(ConfigurationManager.AppSettings["TimeToClose"]);
            timer1.Start();
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(303, 110);
            Controls.Add(HelloMsg);
            Name = "Form1";
            Text = "label1";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        public Label HelloMsg;
        public System.Windows.Forms.Timer timer1;

        
        private void TimerCloses(object? sender, EventArgs e)
        {
            this.Close();
        }
    }
}
