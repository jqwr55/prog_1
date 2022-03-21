#include <common.h>
#include <Simple_window.h>
#include <Graph.h>
#include <exception>
#include <string>

void WindowExit (Fl_Widget* widget, void* user) {

    global_io_flush();
    exit(0);
}

f64 One(f64 x) { 
    return 1;
}
f64 Slope(f64 x) {
    return x/2;
}
f64 Square(f64 x) {
    return x*x;
}
f64 SlopingCos(f64 x) {
    return Slope(x) + cos(x);
}


i32 main(i32 argc, const char** argv) {

    byte mem[512];
    init_global_print(make_linear_allocator(mem, 512));

    try {

        i32 xmax = 600;
        i32 ymax = 600;
        Point center{xmax/2, ymax/2};

        int rangeMin = -10;
        int rangeMax = 11;
        int n = 400;
        int scaleX = 20;
        int scaleY = 20;

        Function s0{One, rangeMin, rangeMax, center, n, scaleX, scaleY};
        Function s1{Slope, rangeMin, rangeMax, center, n, scaleX, scaleY};
        Function s2{Square, rangeMin, rangeMax, center, n, scaleX, scaleY};
        Function s3{cos, rangeMin, rangeMax, center, n, scaleX, scaleY};
        Function s4{SlopingCos, rangeMin, rangeMax, center, n, scaleX, scaleY};
        s3.set_color(Color::blue);

		Simple_window myWindow{Point{100,100}, xmax, ymax, "Canvas"};
        myWindow.set_label("Function graphs");
        myWindow.callback(WindowExit);

        Axis xAxis{Axis::x, center - Point{200, 0}, 400, 20, "1 == 20 pixels"};
        Axis yAxis{Axis::y, center + Point{0, 200}, 400, 20, "1 == 20 pixels"};
        yAxis.set_color(Color::red);
        xAxis.set_color(Color::red);

        Text text{Point{100,380}, "x/2"};

        myWindow.attach(text);
        myWindow.attach(s0);
        myWindow.attach(s1);
        myWindow.attach(s2);
        myWindow.attach(s3);
        myWindow.attach(s4);
        myWindow.attach(xAxis);
        myWindow.attach(yAxis);

        myWindow.wait_for_button();

    }
    catch(std::exception& e) {
        global_print("s", e.what());
	    global_io_flush();
		return 1;
	}
	catch(...) {
        global_print("s", "uknown exception caught");
	    global_io_flush();
		return 2;
	}

    global_io_flush();
    return 0;
}