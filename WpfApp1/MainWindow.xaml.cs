﻿using System;
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

        private void Border_MouseDown(object sender, MouseButtonEventArgs e)
        {

        }
    }
}
