using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
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

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            //Binding binding = new Binding("IsChecked");
            //binding.Mode = BindingMode.OneWay;
            //binding.Source = this.checkbox_2;
            //this.checkbox_1.SetBinding(CheckBox.IsCheckedProperty, binding);

            //Binding binding1 = new Binding("IsChecked");
            //binding1.Mode = BindingMode.OneWay;
            //binding1.Converter = new Bool2Visibility();
            //binding1.Source = this.checkbox_2;
            //this.border_1.SetBinding(Border.VisibilityProperty, binding1);
        }
    }

    public class Bool2Visibility : IValueConverter
    {
        public Visibility True { set; get; } = Visibility.Visible;
        public Visibility False { set; get; } = Visibility.Collapsed;
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            bool bb = (bool)value;
            return bb == true ? this.True : this.False;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
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
