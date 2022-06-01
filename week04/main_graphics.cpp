#include <common.h>
#include <Simple_window.h>
#include <Graph.h>
#include <exception>
#include <string>

void WindowExit(Fl_Widget* widget, void* user) {

    std::cout.flush();
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

    try {

        i32 xmax = 600;
        i32 ymax = 600;
        Point center{xmax/2, ymax/2};

        i32 rangeMin = -10;
        i32 rangeMax = 11;
        i32 n = 400;
        i32 scaleX = 20;
        i32 scaleY = 20;

        Function s0{One, rangeMin, rangeMax, center, n, scaleX, scaleY};
        Function s1{Slope, rangeMin, rangeMax, center, n, scaleX, scaleY};
        Function s2{Square, rangeMin, rangeMax, center, n, scaleX, scaleY};
        Function s3{cos, rangeMin, rangeMax, center, n, scaleX, scaleY};
        Function s4{SlopingCos, rangeMin, rangeMax, center, n, scaleX, scaleY};
        s3.set_color(Color::blue);

		Simple_window myWindow{Point{100,100}, xmax, ymax, "Function graphs"};
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

        return 0;
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
		return 1;
	}
	catch(...) {
        std::cout << "uknown exception caught" << std::endl;
		return 2;
	}

}