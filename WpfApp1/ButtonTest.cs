using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace WpfApp1
{
    public class ButtonTest:Button
    {
        public static readonly DependencyProperty TestProperty;
        static ButtonTest()
        {
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

    }
}
