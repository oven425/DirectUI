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
using System.Windows.Threading;
using System.ComponentModel;
using System.Threading;

namespace WpfApp1
{
    /// <summary>
    /// MainWindow.xaml 的互動邏輯
    /// </summary>
    public partial class MainWindow : Window
    {
        public static readonly DependencyProperty TestProperty;
        public static readonly RoutedEvent ConditionalClickEvent;
        public static readonly RoutedEvent ConditionalClickEvent1;
        public static readonly RoutedEvent AnimationStartedEvent = EventManager.RegisterRoutedEvent("AnimationStarted",
            RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(MainWindow));
        
        static MainWindow()
        {
            TestProperty = DependencyProperty.Register("AA", typeof(int), typeof(MainWindow), new PropertyMetadata() { PropertyChangedCallback = TestPropertyChange });
            ConditionalClickEvent = EventManager.RegisterRoutedEvent("ConditionalClick", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(MainWindow));
            ConditionalClickEvent = EventManager.RegisterRoutedEvent("ConditionalClick1", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(MainWindow));
        }
        public event RoutedEventHandler ConditionalClick
        {
            add { AddHandler(ConditionalClickEvent, value); }
            remove { RemoveHandler(ConditionalClickEvent, value); }
        }
        public event RoutedEventHandler AnimationStarted
        {
            add { AddHandler(AnimationStartedEvent, value); }
            remove { RemoveHandler(AnimationStartedEvent, value); }
        }
        
        public int AA
        {
            set { this.SetValue(TestProperty, value); }
            get {  return (int)GetValue(TestProperty); }
        }
        static void TestPropertyChange(DependencyObject obj, DependencyPropertyChangedEventArgs args)
        {
            var aa = obj as MainWindow;
            
        }
        public MainWindow()
        {
            InitializeComponent();
        }
        async Task Test(int data)
        {
            System.Diagnostics.Trace.WriteLine($"begin {data}");
            await Task.Delay(5000);
            System.Diagnostics.Trace.WriteLine($"end {data}");
        }

        public async Task Foo(int num)
        {
            Console.WriteLine("Thread {0} - Start {1}", Thread.CurrentThread.ManagedThreadId, num);
            await Task.Delay(5000);
            Console.WriteLine("Thread {0} - End {1}", Thread.CurrentThread.ManagedThreadId, num);
        }
        public List<Task> TaskList = new List<Task>();
        MinUI m_MinUI;
        DispatcherTimer m_Timer = new DispatcherTimer();
        async private void Window_Loaded(object sender, RoutedEventArgs e)
        {

            //List<Task> tasks = new List<Task>();

            //foreach(var oo in Enumerable.Range(1, 2))
            //{
            //    var task = new Task(async() => await Test(oo));
            //    //var task = Task.Run(async () => await Test(oo));

            //    tasks.Add(task);
            //}
            //tasks.ForEach(x => x.Start());
            //Task.WaitAll(tasks.ToArray());
            //System.Diagnostics.Trace.WriteLine("All end");

            //CustomEventArgs args = new CustomEventArgs(CustomClickWithCustomArgsEvent,10);
            //RaiseEvent(args);
            if (this.m_MinUI == null)
            {
                this.DataContext = this.m_MinUI = new MinUI();
            }

            this.m_Timer.Interval = TimeSpan.FromSeconds(1);
            //this.m_Timer.Start();
            this.m_Timer.Tick += M_Timer_Tick;
            this.m_Timer.Tick += M_Timer_Tick;

            //Binding binding = new Binding("IsChecked");
            //binding.Mode = BindingMode.OneWay;
            //binding.Source = this.checkbox_2;
            //this.checkbox_1.SetBinding(CheckBox.IsCheckedProperty, binding);

            //Binding binding1 = new Binding("IsChecked");
            //binding1.Mode = BindingMode.OneWay;
            //binding1.Converter = new Bool2Visibility();
            //binding1.Source = this.checkbox_2;
            //this.border_1.SetBinding(Border.VisibilityProperty, binding1);


            //this.B.AddHandler(ButtonTest.CustomClickWithCustomArgsEvent, new CustomClickWithCustomArgsEventHandler(TT));
            //this.B.AddHandler(ButtonTest.CustomClickWithCustomArgsEvent, new CustomClickWithCustomArgsEventHandler(TT1));
            //this.B.AddHandler(ButtonTest.CustomClickWithCustomArgsEvent, new CustomClickWithCustomArgsEventHandler(TT1));
            //this.B.RemoveHandler(ButtonTest.CustomClickWithCustomArgsEvent, new CustomClickWithCustomArgsEventHandler(TT1));
        }
       

        private void M_Timer_Tick(object sender, EventArgs e)
        {
            System.Diagnostics.Trace.WriteLine("M_Timer_Tick");
            this.m_MinUI.Time = DateTime.Now;
        }

        void TT (object sender, CustomEventArgs args)
        {

        }

        void TT1(object sender, CustomEventArgs args)
        {

        }

        private void A_CustomClickWithCustomArgs(object sender, CustomEventArgs e)
        {
            
        }

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            //this.border.CaptureMouse();
            //this.border.ReleaseMouseCapture();
            System.Diagnostics.Trace.WriteLine($"Window_MouseDown:{sender.GetType()}");
        }

        private void Window_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            //e.GetPosition();
            //Keyboard.IsKeyDown();
            System.Diagnostics.Trace.WriteLine($"Window_PreviewMouseDown:{sender.GetType()}");
        }
        protected override void OnRender(DrawingContext drawingContext)
        {
            drawingContext.DrawEllipse(Brushes.Red, null, new Point(this.ActualWidth / 2, this.ActualHeight / 2), this.ActualWidth / 2, this.ActualHeight / 2);

            base.OnRender(drawingContext);
        }
    }

    public interface DebugTrace<T>
    {
        void Trace(T data);
    }

    public class TraceData
    {
        public DateTime Time { set; get; }
        public string Message { set; get; }
        public int Level { set; get; }
    }

    public class Trace : DebugTrace<TraceData>
    {
        void DebugTrace<TraceData>.Trace(TraceData data)
        {
            this.m_CSVLog.Trace(data);
            this.m_DebugView.Trace($"Message:{data.Message}");
        }

        CSVTrace m_CSVLog = new CSVTrace();
        StringTrace m_DebugView = new StringTrace();
    }

    public class CSVTrace : DebugTrace<TraceData>
    {
        public void Trace(TraceData data)
        {
            throw new NotImplementedException();
        }
    }

    public class StringTrace : DebugTrace<string>
    {
        public void Trace(string data)
        {
            System.Diagnostics.Trace.WriteLine(data);
        }
    }


    public class RenderT:Control
    {
        protected override void OnRender(DrawingContext drawingContext)
        {
            drawingContext.DrawEllipse(Brushes.Red, null, new Point(this.ActualWidth / 2, this.ActualHeight / 2), this.ActualWidth/2, this.ActualHeight/2);
            base.OnRender(drawingContext);
        }
    }


    public class MinUI : INotifyPropertyChanged
    {
        DateTime m_Time;
        public DateTime Time
        {
            set
            {
                this.m_Time = value;
                this.Update("Time");
            }
            get
            {
                return this.m_Time;
            }
        }
        public event PropertyChangedEventHandler PropertyChanged;
        void Update(string name)
        {
            if(this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
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
