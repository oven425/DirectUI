using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace WpfApp1
{
    public class DiagnolPanel : Panel
    {
        protected override Size MeasureOverride(Size availableSize)
        {
            var mySize = new Size();

            foreach (UIElement child in this.InternalChildren)
            {
                child.Measure(availableSize);
                mySize.Width += child.DesiredSize.Width;
                mySize.Height += child.DesiredSize.Height;
            }

            return mySize;
        }

        protected override Size ArrangeOverride(Size finalSize)
        {
            var location = new Point();

            int childNumber = 0;
            int middleChild = GetTheMiddleChild(this.InternalChildren.Count);

            foreach (UIElement child in this.InternalChildren)
            {

                if (childNumber < middleChild)
                {
                    child.Arrange(new Rect(location, child.DesiredSize));
                    location.X += child.DesiredSize.Width;
                    location.Y += child.DesiredSize.Height;
                }
                else
                {
                    //The x location will always keep increasing, there is no need to take care of it
                    location.X = GetXLocationAfterMiddleChild(childNumber);

                    //If the UIElements are odd in number
                    if (this.InternalChildren.Count % 2 != 0)
                    {
                        //We need to get the Y location of the child before middle location, 
                        //to have the same Y location for the child after middle child                      
                        int relativeChildBeforeMiddle = middleChild - (childNumber - middleChild);
                        location.Y = GetYLocationAfterMiddleChild(relativeChildBeforeMiddle);
                    }
                    else
                    {
                        ///TODO: Do the design for the even number of children
                    }

                    child.Arrange(new Rect(location, child.DesiredSize));
                }

                childNumber++;
            }

            return finalSize;
        }

        private double GetXLocationAfterMiddleChild(int childNUmber)
        {
            double xLocation = 0;
            for (int i = 0; i < childNUmber; i++)
            {
                xLocation += this.InternalChildren[i].DesiredSize.Width;
            }

            return xLocation;
        }

        private double GetYLocationAfterMiddleChild(int relativeChildNumber)
        {
            UIElement correspondingChild = this.InternalChildren[relativeChildNumber - 2];
            Point pointCoordinates =
            correspondingChild.TransformToAncestor((Visual)this.Parent).Transform(new Point(0, 0));

            return pointCoordinates.Y;
        }

        private int GetTheMiddleChild(int count)
        {
            int middleChild;
            if (count % 2 == 0)
            {
                middleChild = count / 2;
            }
            else
            {
                middleChild = (count / 2) + 1;
            }

            return middleChild;
        }
    }
}
