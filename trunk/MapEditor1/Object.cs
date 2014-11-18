using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Shapes;

namespace MapEditor1
{
    public class Object
    {
        public int ID;

        public int IDIMAGE;

        public Rectangle rect;

        public int type;

        public Point position;

        public Object(int id, int idImage,Rectangle rect, int type, Point pos)
        {
            this.ID = id;
            this.rect = rect;
            this.type = type;
            this.position = pos;
        }

        public double getWidth()
        {
            return rect.Width;

        }
        public double getHeight()
        {
            return rect.Height;
        }

    }
}
