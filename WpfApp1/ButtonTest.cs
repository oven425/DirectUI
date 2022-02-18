using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace WpfApp1
{
    public delegate void CustomClickWithCustomArgsEventHandler(object sender, CustomEventArgs e);
    public class ButtonTest:Button
    {
        public static readonly DependencyProperty TestProperty;
        public static readonly RoutedEvent ConditionalClickEvent;
        public static readonly RoutedEvent CustomClickWithCustomArgsEvent =
    EventManager.RegisterRoutedEvent(
    "CustomClickWithCustomArgs", RoutingStrategy.Bubble,
    typeof(CustomClickWithCustomArgsEventHandler),
    typeof(ButtonTest));
        static ButtonTest()
        {
            //ConditionalClickEvent = EventManager.RegisterRoutedEvent("ConditionalClick", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(ButtonTest));
            TestProperty = DependencyProperty.Register("Test", typeof(int), typeof(ButtonTest), new PropertyMetadata()
            {
                PropertyChangedCallback = TestPropertyChange
            });
        }
        static void TestPropertyChange(DependencyObject obj, DependencyPropertyChangedEventArgs args)
        {
            var aa = obj as ButtonTest;
            System.Diagnostics.Trace.WriteLine($"Name:{aa.Name} Test:{aa.Test}");
        }
        public event CustomClickWithCustomArgsEventHandler CustomClickWithCustomArgs
        {
            add { AddHandler(CustomClickWithCustomArgsEvent, value); }
            remove { RemoveHandler(CustomClickWithCustomArgsEvent, value); }
        }
        public int Test
        {
            set
            {
                this.SetValue(TestProperty, value);
            }
            get
            {
                return (int)this.GetValue(TestProperty);
            }
        }

        public ButtonTest()
        {

        }

        protected override void OnClick()
        {
            CustomEventArgs args = new CustomEventArgs(CustomClickWithCustomArgsEvent, 10);
            //RoutedEventArgs args = new RoutedEventArgs(CustomClickWithCustomArgsEvent);

            RaiseEvent(args);
            base.OnClick();
        }

    }

    
    public class CustomEventArgs : RoutedEventArgs
    {
        public int SomeNumber { get; private set; }

        public CustomEventArgs(RoutedEvent routedEvent,
            int someNumber)
            : base(routedEvent)
        {
            this.SomeNumber = someNumber;
        }
    }
}
