using System;
using System.Collections.Concurrent;
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

            var controllerName = "WpfApp1.HogeController";
            var actionName = "TakoAction";
            var type = Type.GetType(controllerName);
            var method = type.GetMethod(actionName);
            var instance = Activator.CreateInstance(type);
            //var cache = new ConcurrentDictionary<Tuple<string, string>, Delegate>();
            //var dynamicDelegate = cache.GetOrAdd(Tuple.Create(controllerName, actionName), _ =>
            //{
            //    // パラメータはMethodInfoから動的に作る
            //    var parameters = method.GetParameters().Select(x =>
            //            System.Linq.Expressions.Expression.Parameter(x.ParameterType, x.Name))
            //        .ToArray();

            //    return System.Linq.Expressions.Expression.Lambda(
            //            System.Linq.Expressions.Expression.Call(System.Linq.Expressions.Expression.New(type), method, parameters),
            //        parameters).Compile();
            //});
            //var result = dynamicDelegate.DynamicInvoke(new object[] { 10, 20 });

            //var cache = new ConcurrentDictionary<string, Func<object[], object>>();
            //var args = System.Linq.Expressions.Expression.Parameter(typeof(object[]), "args");
            //var parameters = method.GetParameters()
            //    .Select((x, index) =>
            //        System.Linq.Expressions.Expression.Convert(
            //            System.Linq.Expressions.Expression.ArrayIndex(args, System.Linq.Expressions.Expression.Constant(index)),
            //        x.ParameterType))
            //    .ToArray();

            //var lambda = System.Linq.Expressions.Expression.Lambda<Func<object[], object>>(
            //            System.Linq.Expressions.Expression.Convert(
            //                System.Linq.Expressions.Expression.Call(System.Linq.Expressions.Expression.New(type), method, parameters),
            //                typeof(object)),
            //            args).Compile();
            //var result = lambda.Invoke(new object[] { "1.1", (float)2.2 });

            //method = typeof(Func<int, int, string>).GetMethods()[0];
            //var args = System.Linq.Expressions.Expression.Parameter(typeof(object[]), "args");
            //var parameters = method.GetParameters()
            //    .Select((x, index) =>
            //        System.Linq.Expressions.Expression.Convert(
            //            System.Linq.Expressions.Expression.ArrayIndex(args, System.Linq.Expressions.Expression.Constant(index)),
            //        x.ParameterType))
            //    .ToArray();

            //var lambda = System.Linq.Expressions.Expression.Lambda<Func<object[], object>>(
            //            System.Linq.Expressions.Expression.Convert(
            //                System.Linq.Expressions.Expression.Call(System.Linq.Expressions.Expression.New(type), method, parameters),
            //                typeof(object)),
            //            args).Compile();

            EventTest tt = new EventTest();
            tt.Org += Tt_Org;
            tt.Org += Tt_Org1;
            tt.OrgInt += Tt_OrgInt;
            tt.OrgTest += Tt_OrgTest;
            tt.Fire();
        }

        private void Tt_OrgTest(object sender, TestArgs e)
        {
        }

        private void Tt_OrgInt(object sender, int e)
        {
        }

        private void Tt_Org(object sender, EventArgs e)
        {
            
        }

        private void Tt_Org1(object sender, EventArgs e)
        {

        }

        Func<int, int, string> m_Func;
        public void Test(Func<int, int, string> data)
        {
            this.m_Func = data;
        }

    }

    public class EventTest
    {
        public event EventHandler Org;
        public event EventHandler<int> OrgInt;
        public event EventHandler<TestArgs> OrgTest;
        public EventTest()
        {
            

        }

        public void Fire()
        {
            Org(this, new EventArgs());
            OrgInt(this, 10);
        }
    }

    public class TestArgs:EventArgs
    {
        public string A { set; get; }
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

    public class HogeController
    {
        public string HugaAction(int x, int y)
        {
            return (x + y).ToString();
        }

        public double TakoAction(string s, float f)
        {
            return double.Parse(s) * f;
        }
    }
}
