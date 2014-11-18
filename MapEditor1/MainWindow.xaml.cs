using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Drawing;
using System.Diagnostics;
using System.Collections.ObjectModel;


namespace MapEditor1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        ObservableCollection<Object> listObject = new ObservableCollection<Object>();
        int id_;
        UIElement selectedElement;
        System.Windows.Shapes.Rectangle rect;
        private String _currentBGPath = string.Empty;
        const int tileSize = 16;

        System.Windows.Size imageZise;

        System.Windows.Point startPos;

        System.Windows.Point ipCurrent;
        System.Windows.Point ipStart;

        System.Windows.Point currentPos;    // current mouse position
        bool drawing;        // busy drawing
        List<System.Drawing.Rectangle> rectangles = new List<System.Drawing.Rectangle>();

        public MainWindow()
        {
            InitializeComponent();
            System.Windows.Controls.Image img = new System.Windows.Controls.Image();
            BitmapImage bitmapImage = new BitmapImage();
            bitmapImage.UriSource = new Uri("1BG.png", UriKind.Relative);
            img.Source = bitmapImage;
            mapCanvas.Width = 2000;
            mapCanvas.Children.Add(img);
           
           
        }

        private void Open_btn_Click(object sender, RoutedEventArgs e)
        {
             var openFile = new OpenFileDialog() { Title = "Open Background", Multiselect = false, Filter = "Image file (.png) |*.png|All files (*.*)|*.*" };
            var _Result = openFile.ShowDialog();

            if (_Result == true)
            {
                if (openFile.CheckFileExists)
                {
                    _currentBGPath = openFile.FileName;
                    var img = new ImageBrush() { ImageSource = new BitmapImage(new Uri(_currentBGPath, UriKind.RelativeOrAbsolute)), Stretch = Stretch.UniformToFill };
                    System.Drawing.Image imgSize = System.Drawing.Image.FromFile(_currentBGPath);
                    mapCanvas.Background = img;
                    mapCanvas.Height = imgSize.Height;
                    mapCanvas.Width = imgSize.Width;

                    imageZise = new System.Windows.Size(imgSize.Width, imgSize.Height);

                    int column = imgSize.Width / tileSize;
                    int row = imgSize.Height / tileSize;

                    for (int i = 0; i < column; i++)
                    {
                        Line myLine = new Line();
                        myLine.Stroke = System.Windows.Media.Brushes.White;

                        myLine.X1 = tileSize * i;
                        myLine.Y1 = 0;
                        myLine.X2 = tileSize * i;
                        myLine.Y2 = imgSize.Height;

                        myLine.StrokeThickness = 1f;

                        mapCanvas.Children.Add(myLine);
                    }

                    for (int i = 1; i <= row; i++)
                    {
                        Line myLine = new Line();
                        myLine.Stroke = System.Windows.Media.Brushes.White;

                        myLine.X1 = 0;
                        myLine.Y1 = tileSize * i;
                        myLine.X2 = imgSize.Width;
                        myLine.Y2 = tileSize * i;

                        myLine.StrokeThickness = 1;

                        mapCanvas.Children.Add(myLine);
                    }
                }
            }
        
        }

     

        private void mapCanvas_MouseDown(object sender, MouseButtonEventArgs e)
        {
            rect = new System.Windows.Shapes.Rectangle();
            currentPos = startPos = e.GetPosition(mapCanvas);
            drawing = true;
            posX.Text = ((int)currentPos.X).ToString();
            posY.Text = ((int)currentPos.Y).ToString();

            System.Windows.Point ip = new System.Windows.Point(currentPos.X, currentPos.Y);
            ip.X = (int)(ip.X / tileSize) * tileSize;
            ip.Y = (int)(ip.Y / tileSize) * tileSize;
            Canvas.SetLeft(rect, ip.X);
            Canvas.SetTop(rect, ip.Y);
          
           
        }

        private void mapCanvas_MouseMove(object sender, MouseEventArgs e)
        {
            
            if (drawing)
            {
                currentPos = e.GetPosition(mapCanvas);
                mapCanvas.InvalidateArrange();

               
            }

        }

        private void mapCanvas_MouseUp(object sender, MouseButtonEventArgs e)
        {
            currentPos = e.GetPosition(mapCanvas);
            if (drawing)
            {
                drawing = false;

                posX.Text = ((int)currentPos.X).ToString();
                posY.Text = ((int)currentPos.Y).ToString();

                // rect = new System.Windows.Shapes.Rectangle();
                rect.Stroke = new SolidColorBrush(Colors.Yellow);
                rect.Fill = new SolidColorBrush(Colors.Red);
                rect.Opacity = 0.5f;

                //var x_ = currentPos.X - startPos.X;
                //var y_ = currentPos.Y - startPos.Y;

                ipCurrent = new System.Windows.Point(currentPos.X, currentPos.Y);
                ipCurrent.X = (int)((ipCurrent.X + tileSize) / tileSize) * tileSize;
                ipCurrent.Y = (int)((ipCurrent.Y + tileSize) / tileSize) * tileSize;

                ipStart = new System.Windows.Point(startPos.X, startPos.Y);
                ipStart.X = (int)((ipStart.X) / tileSize) * tileSize;
                ipStart.Y = (int)((ipStart.Y) / tileSize) * tileSize;


                //ipStart.Y = imageZise.Height / tileSize - ipStart.Y;
                //if (ipStart.Y < 0)
                //    ipStart.Y = -ipStart.Y;
               

                var x_ = ipCurrent.X - ipStart.X;
                var y_ = ipCurrent.Y - ipStart.Y;

                if (x_ < 0)
                {
                    x_ = -x_;

                    Canvas.SetTop(rect, ipCurrent.Y);
                    Canvas.SetLeft(rect, ipCurrent.X);
                }
                if (y_ < 0)
                {
                    y_ = -y_;

                    Canvas.SetTop(rect, ipCurrent.Y);
                    Canvas.SetLeft(rect, ipCurrent.X);
                }

                rect.Width = x_;
                rect.Height = y_;
              

               

                listObject.Add(new Object(2000 +id_, 0, rect, 0,ipStart));
                id_++;


               

                

               mapCanvas.Children.Add(rect);

               // Update();
            }
           
        }

        private void Update()
        {
            try
            {
                
                foreach (Object o in listObject)
                {
                    mapCanvas.Children.Add(o.rect);
                }
            }
            catch
            {
                MessageBox.Show("LOI");
            }
        }

        private void mapCanvas_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {

            

            foreach (UIElement element in mapCanvas.Children)
            {
                if (element is System.Windows.Shapes.Rectangle)
                {
                    ((System.Windows.Shapes.Rectangle)element).Fill = System.Windows.Media.Brushes.Blue;
                }
                Canvas.SetZIndex(element, 0);
            }
           
          
        }

        private void Save_btn_Click(object sender, RoutedEventArgs e)
        {
            if (listObject == null)
                return;
            else
            {
                Save();
                MessageBox.Show("DOne");
            }
        }


        void Save()
        {
            using (System.IO.StreamWriter file = new System.IO.StreamWriter(@"C:\F\hideObject.txt"))
            {
                int i = 0;
                foreach (Object data in listObject)
                {
                    i++;
                    data.position.Y = imageZise.Height - data.position.Y - tileSize / 2;
                    data.position.X += data.rect.Width / 2;
                    if (data.position.Y < 0)
                        data.position.Y = -data.position.Y;
                    file.Write(data.ID.ToString() + " " + ((int)data.IDIMAGE).ToString() + " " + (data.position.X).ToString() + " " + (data.position.Y).ToString() + " " + data.rect.Width.ToString() + " " + data.rect.Height.ToString());
                    //if (i == (int)(pic.Width / tileSize))
                    //{
                        file.Write(Environment.NewLine);
                    //    i = 0;
                    //}
                }

            }
        }
       
    }
}
