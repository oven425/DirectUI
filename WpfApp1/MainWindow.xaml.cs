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

namespace WpfApp1
{
    /// <summary>
    /// MainWindow.xaml 的互動邏輯
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //System.Diagnostics.Trace.WriteLine($"w:{this.uniformgrid.ActualWidth} h:{this.uniformgrid.ActualHeight}");
            //System.Diagnostics.Trace.WriteLine($"DesiredSize:{this.uniformgrid.DesiredSize}");
        }

        private void Img_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            FrameworkElement control = sender as FrameworkElement;
            System.Diagnostics.Trace.WriteLine($"w:{control.ActualWidth} h:{control.ActualHeight}");
            System.Diagnostics.Trace.WriteLine($"DesiredSize:{control.DesiredSize}");
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);
        }

        private void Border_MouseDown(object sender, MouseButtonEventArgs e)
        {

        }

        (string first, string middle, string last) LookupName(long id) // tuple return type
        {
    //... // retrieve first, middle and last from data storage
    return ("first", "middle", "last"); // tuple literal
        }

        private void Button_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {

        }

        private void Button_PreviewMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {

        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {

        }

        private void Button_IsEnabledChanged(object sender, DependencyPropertyChangedEventArgs e)
        {

        }

        private void Thumb_DragStarted(object sender, System.Windows.Controls.Primitives.DragStartedEventArgs e)
        {
            System.Diagnostics.Trace.WriteLine($"Started HorizontalOffset: {e.HorizontalOffset} VerticalOffset:{e.VerticalOffset}");
        }

        private void Thumb_DragDelta(object sender, System.Windows.Controls.Primitives.DragDeltaEventArgs e)
        {
            System.Diagnostics.Trace.WriteLine($"Delta HorizontalChange: {e.HorizontalChange} VerticalChange:{e.VerticalChange}");
        }

        private void Thumb_DragCompleted(object sender, System.Windows.Controls.Primitives.DragCompletedEventArgs e)
        {
            System.Diagnostics.Trace.WriteLine($"Delta HorizontalChange: {e.HorizontalChange} VerticalChange:{e.VerticalChange}");
        }
    }

    public class DpiDecorator : Decorator
    {
        public DpiDecorator()
        {
            this.Loaded += (s, e) =>
            {
                Matrix m = PresentationSource.FromVisual(this).CompositionTarget.TransformToDevice;
                ScaleTransform dpiTransform = new ScaleTransform(1 / m.M11, 1 / m.M22);
                if (dpiTransform.CanFreeze)
                    dpiTransform.Freeze();
                this.LayoutTransform = dpiTransform;
            };
        }
    }
}
