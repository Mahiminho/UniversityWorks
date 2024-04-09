using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Security.Cryptography;
using System.IO;



namespace ZIKS_lab8
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private const byte lenIV = 16;
        private static void AesCtrTransform(byte[] key, byte[] salt, Stream inputStream, Stream outputStream)
        {
            SymmetricAlgorithm aes = new AesManaged { Mode = CipherMode.ECB, Padding = PaddingMode.None };

            int blockSize = aes.BlockSize / 8;

            if (salt.Length != blockSize)
            {
                throw new ArgumentException(
                    string.Format(
                        "Salt size must be same as block size (actual: {0}, expected: {1})",
                        salt.Length, blockSize));
            }

            byte[] counter = (byte[])salt.Clone();

            Queue<byte> xorMask = new Queue<byte>();

            var zeroIv = new byte[blockSize];
            ICryptoTransform counterEncryptor = aes.CreateEncryptor(key, zeroIv);

            int b;
            while ((b = inputStream.ReadByte()) != -1)
            {
                if (xorMask.Count == 0)
                {
                    var counterModeBlock = new byte[blockSize];

                    counterEncryptor.TransformBlock(counter, 0, counter.Length, counterModeBlock, 0);

                    for (var i2 = counter.Length - 1; i2 >= 0; i2--)
                    {
                        if (++counter[i2] != 0)
                        {
                            break;
                        }
                    }

                    foreach (var b2 in counterModeBlock)
                    {
                        xorMask.Enqueue(b2);
                    }
                }

                var mask = xorMask.Dequeue();
                outputStream.WriteByte((byte)(((byte)b) ^ mask));
            }
        }

        private void DoCipher()
        {
            try
            {
                if (string.IsNullOrEmpty(textBox4.Text.Trim()))
                {
                    MessageBox.Show("Enter key!!");
                    return;
                }
                if (string.IsNullOrEmpty(textBox3.Text.Trim()))
                {
                    MessageBox.Show("Enter initialization vector!");
                    return;
                }

                byte[] keyBytes = Encoding.UTF8.GetBytes(textBox4.Text);

                int len = keyBytes.Length;
                if (len != 24)
                {
                    MessageBox.Show("Length of key must be 24 letters(192-bit) (" + len + ")");
                    return;
                }

                string salt = textBox3.Text.Substring(0, Math.Min(textBox3.Text.Length, lenIV));
                salt = salt.PadRight(16, salt[salt.Length - 1]);

                textBox3.Enabled = false;
                textBox3.Text = salt;
                textBox3.Enabled = true;

                byte[] saltBytes = Encoding.UTF8.GetBytes(salt);

                using (OpenFileDialog dOpenFile = new OpenFileDialog())
                using (SaveFileDialog dSaveFile = new SaveFileDialog())
                {
                    if (dOpenFile.ShowDialog() == DialogResult.OK)
                    {
                        using (FileStream fs = File.OpenRead(dOpenFile.FileName))
                        {
                            if (dSaveFile.ShowDialog() == DialogResult.OK)
                            {
                                using (FileStream fs2 = File.OpenWrite(dSaveFile.FileName))
                                {
                                    AesCtrTransform(keyBytes, saltBytes, fs, fs2);
                                }
                            }
                        }
                        MessageBox.Show("Success!");
                    }
                }
            }
            catch
            {
                MessageBox.Show("Error!");
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            DoCipher();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            DoCipher();
        }
        private void textBox3_TextChanged(object sender, EventArgs e)
        {
        }
        private void textBox4_TextChanged(object sender, EventArgs e)
        {
        }
    }
}