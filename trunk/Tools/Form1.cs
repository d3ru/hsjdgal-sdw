using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TileMap
{
    public partial class Form1 : Form
    {
        Bitmap pic;
        List<Bitmap> listStoreBimap;
        List<ObjectBitMap> listDataBitMap;
        List<Map> mapTile;
        List<int> listIndex;
        int id;
        int equaIndex;
        int idEqua;
      
        public Form1()
        {
           
            InitializeComponent();
            pictureBox1.BackColor = colorDialog1.Color;
            button1.Enabled = false;
            clearButton.Enabled = false;

        }

        private void showButton_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {              
                pic = new Bitmap(openFileDialog1.FileName);
                pictureBox1.Image = pic.Clone(new Rectangle(0, 0, pic.Width, pic.Height), System.Drawing.Imaging.PixelFormat.DontCare);                            
            }
            if (pictureBox1.Image != null)
            {
                id = -1;
                equaIndex = 0;
                button1.Enabled = true;
                clearButton.Enabled = true;
                Strect();
            }

           
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            DialogResult dialogResult = MessageBox.Show("Are You Sure ?", "Delete Image", MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                pictureBox1.Image = null;
                button1.Enabled = false;
                clearButton.Enabled = false;
                
            }
            
        }

        private void closeButton_Click(object sender, EventArgs e)
        {
            DialogResult dialogResult = MessageBox.Show("Are You Sure ?", "Exit", MessageBoxButtons.YesNo);

            if (dialogResult == DialogResult.Yes)
            {
                this.Close();

            } 
            
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            Strect();
        }

        private void Strect()
        {
            if (checkBox1.Checked)
            {
                pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            }
            else
            {
                pictureBox1.SizeMode = PictureBoxSizeMode.Normal;
            }
        }

        private void pictureBox1_Move(object sender, EventArgs e)
        {
           
        }

       

        private void is_Click(object sender, EventArgs e)
        {
            int x = pictureBox1.Location.X;
            int y = pictureBox1.Location.Y;

            pictureBox1.Location = new Point(x + 25, y);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            int tileSize = Convert.ToInt32(textBox1.Text);
            if ((int)pic.Width % tileSize != 0 && (int)pic.Height % tileSize != 0)
                MessageBox.Show("Stop", "Error");
            else
            {
                CropImage(pic, tileSize);
  
            }
        }

        private void CropImage(Bitmap imageToCrop, int tileSize)
        {
            listIndex = new List<int>();
           
            listStoreBimap = new List<Bitmap>();
            listDataBitMap = new List<ObjectBitMap>();
            mapTile = new List<Map>();

            for (int startY = 0; startY < (int)imageToCrop.Height; startY += tileSize)
            {
                for(int startX = 0; startX < (int)imageToCrop.Width; startX += tileSize)
                {
                    Map map = new Map();
                    
                    if (!CheckBitMap(listDataBitMap, imageToCrop, startX, startY))
                    {
                        ObjectBitMap objectBitMap = new ObjectBitMap();
                        id += 1;
                        
                        objectBitMap.bitmapImage = imageToCrop.Clone(new Rectangle(startX, startY, tileSize, tileSize), System.Drawing.Imaging.PixelFormat.DontCare);
                        objectBitMap.idObject = id;
                        map.ID = id;

                        listDataBitMap.Add(objectBitMap);
                  
                        
                    }
                    else
                    {
                        map.ID = idEqua;
                    }
                    equaIndex = 0;
                   
       
                    mapTile.Add(map);
                    
                }
            }
         
            
            SaveImage(listDataBitMap, tileSize);
            SaveMap(mapTile,listDataBitMap ,tileSize);
            
            id = -1;
            MessageBox.Show("Done !");

            OpenFolder("C:\\F\\");
            
        }

        private void OpenFolder(string filePath)
        {
            System.Diagnostics.Process prc = new System.Diagnostics.Process();
            prc.StartInfo.FileName = filePath;
            prc.Start();
        }

        private bool CheckBitMap(List<ObjectBitMap> listCurrent, Bitmap image, int startX, int startY)
        {
            bool result = false;

            if (listCurrent.Count == null)
                result = false;
            
            foreach (ObjectBitMap bitMapStored in listCurrent)
            {
               
                if (IsEqua(bitMapStored.bitmapImage, image, startX, startY))
                {
                    int num = 0;
                    result = true;
                    equaIndex = listDataBitMap.IndexOf(bitMapStored);
                    idEqua = bitMapStored.idObject;
                    listIndex.Add(equaIndex);
                    break;
                }
            }

            return result;
        }

        private bool IsEqua(Bitmap image1, Bitmap image2, int startX, int startY)
        {
            bool result = true;
            bool flag = false;

            {

                for (int x = 0; x < image1.Width; ++x)
                {
                    for (int y = 0; y < image1.Height; ++y)
                    {
                        if (image1.GetPixel(x, y) != image2.GetPixel(startX + x, startY + y))
                        {
                            result = false;
                            flag = true;
                            break;
                        }
                    }
                    if (flag)
                        break;
                }
            }
            return result;
        }

       

        private void SaveImage(List<ObjectBitMap> imageCropped, int tileSize)
        {
            int count = 0;

            Bitmap resultBitMap = new Bitmap(tileSize * imageCropped.Count, tileSize);

            using (Graphics g = Graphics.FromImage(resultBitMap))
            {
                //set background color
                g.Clear(Color.Black);

                int offset = 0;

                foreach (ObjectBitMap _image in imageCropped)
                {

                    g.DrawImage(_image.bitmapImage, new Rectangle(offset, 0, tileSize, tileSize));
                    offset += tileSize;
                   
                }


            }

            resultBitMap.Save("C:\\F\\TileSet.png", System.Drawing.Imaging.ImageFormat.Png);
             
        }

       
        private void SaveMap(List<Map> listMap, List<ObjectBitMap> listObject,int tileSize)
        {
            using (System.IO.StreamWriter file = new System.IO.StreamWriter(@"C:\F\tileMap.txt"))
            {
                int i = 0;
                foreach (Map data in listMap)
                {
                    i++;
                    file.Write(data.ID.ToString() + " ");
                    if (i == (int)(pic.Width / tileSize))
                    {
                        file.Write(Environment.NewLine);
                        i = 0;
                    }
                }

            }

            using (System.IO.StreamWriter file = new System.IO.StreamWriter(@"C:\F\infoMap.txt"))
            {
               
                foreach (ObjectBitMap data in listObject)
                {
                   
                    file.Write(data.idObject + "  " + listObject.IndexOf(data));
                   
                    file.Write(Environment.NewLine);
                        
                   
                }

            }
        }

       
    }
}
