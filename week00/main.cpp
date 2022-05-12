#include <common.h>
#include <Simple_window.h>
#include <Graph.h>

using namespace Graph_lib;

double one(double) {
    return 1;
}
double square(double x) {
    return x*x;
}

void WindowExit (Fl_Widget* widget, void* user) {
	widget->hide();
	exit(0);
}

i32 main() {

	try {

		i32 xmax = 1280;
		i32 ymax = 720;

		i32 x_orig = xmax/2;
		i32 y_orig = ymax/2;

		i32 rmin = -11;
		i32 rmax = 11;
		
		i32 n_points = 400;

		Simple_window win {Point{100,100}, xmax, ymax, "Canvas"};
		win.callback(WindowExit);
		Point origo {x_orig, y_orig};

		i32 xlength = xmax - 40;
		i32 ylength = ymax - 40;

		i32 xscale = 30, yscale = 30;

		Function s (one, rmin, rmax, origo, n_points, xscale, yscale);
		Function sq (square, rmin, rmax, origo, n_points, xscale, yscale);
		Function cos_func ( [] (double x) { return cos(x); },
							rmin, rmax, origo, n_points, xscale, yscale);

		Axis x {Axis::x, Point{20, y_orig}, xlength, xlength/xscale, "x"};
		Axis y {Axis::y, Point{x_orig, ylength + 20}, ylength, ylength/yscale, "y"};

		Rectangle r {Point{200,200}, 100, 50};

		r.set_fill_color(Graph_lib::Color::yellow);
		r.set_style( Line_style( Line_style::dash, 4));

		Text t {Point{200,400}, "Hello graphics!"};
		t.set_font( Graph_lib::Font::times_bold);
		t.set_font_size(20);

		Image ii {Point{100,100}, "./week01/badge.jpg", Suffix::jpg};

		Circle c {Point{700,700}, 100};

		Ellipse e {Point{500,500}, 100, 50};
		e.set_fill_color(Color::red);

		win.attach(e);
		win.attach(ii);
		win.attach(c);
		win.attach(t);
		win.attach(r);
		win.attach(s);
		win.attach(sq);
		win.attach(cos_func);
		win.attach(x);
		win.attach(y);

		win.wait_for_button();
		return 0;
	}
	catch(std::exception& e) {
		std::cerr << "exception caught " << e.what() << std::endl;
		return 1;
	}
	catch(...) {
		std::cerr << "Uknown exception" << std::endl;
		return 2;
	}
}