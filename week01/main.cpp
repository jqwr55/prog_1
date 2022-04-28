#include <common.h>
#include <Simple_window.h>
#include <Graph.h>
#include <exception>
#include <string>

void WindowExit (Fl_Widget* widget, void* user) {

    exit(0);
}

i32 main(i32 argc, const char** argv) {

    byte mem[512];

	try {
		i32 xmax = 600;
		i32 ymax = 400;
		Simple_window myWindow{Point{100,100}, xmax, ymax, "Canvas"};
		myWindow.wait_for_button();
		myWindow.callback(WindowExit);
			
		{
			Axis xAxis {Axis::x, Point{20,300}, 350, 10, "x axis"};

			myWindow.attach(xAxis);
			myWindow.set_label("Canvas #2");
			myWindow.wait_for_button();
		}

		{
			Axis xAxis {Axis::x, Point{20,250}, 300, 5, "x axis"};
			Axis yAxis {Axis::y, Point{20,250}, 300, 5, "y axis"};
			yAxis.set_color(Color::cyan);

			myWindow.attach(xAxis);
			myWindow.attach(yAxis);
			myWindow.set_label("Canvas #3");
			myWindow.wait_for_button();
		}
		
		{
			Axis xAxis {Axis::x, Point{20,300}, 280, 10, "x axis"};
			Axis yAxis {Axis::y, Point{20,300}, 280, 10, "y axis"};
			yAxis.set_color(Color::red);

			Function sineFn {sin, 0, 100,Point{25,100}, 500, 55, 60};

			myWindow.attach(sineFn);
			myWindow.attach(xAxis);
			myWindow.attach(yAxis);
			myWindow.set_label("Canvas #4");
			myWindow.wait_for_button();
		}

		{
			Axis xAxis {Axis::x, Point{20,300}, 280, 10, "x axis"};
			Axis yAxis {Axis::y, Point{20,300}, 280, 10, "y axis"};
			yAxis.set_color(Color::black);

			Function sineFn {sin, 0, 100, Point{20,150},1000,50,50};
			sineFn.set_color(Color::yellow);

			myWindow.attach(sineFn);
			myWindow.attach(xAxis);
			myWindow.attach(yAxis);

			Polygon poly;
			poly.add(Point{300, 250});
			poly.add(Point{350, 120});
			poly.add(Point{400, 220});
			poly.set_color(Color::black);
			poly.set_style(Line_style::dashdot);
			myWindow.attach(poly);

			myWindow.set_label("Canvas #5");
			myWindow.wait_for_button();
		}

		{
			Axis xAxis {Axis::x, Point{20,300}, 280, 10, "x axis"};
			Axis yAxis {Axis::y, Point{20,300}, 280, 10, "y axis"};
			yAxis.set_color(Color::black);

			Function sineFn {sin, 0, 100, Point{20,150},1000,50,50};
			sineFn.set_color(Color::red);

			myWindow.attach(sineFn);
			myWindow.attach(xAxis);
			myWindow.attach(yAxis);

			Polygon poly;
			poly.add(Point{300, 200});
			poly.add(Point{350, 100});
			poly.add(Point{400, 200});
			poly.set_color(Color::cyan);
			poly.set_style(Line_style::dash);
			myWindow.attach(poly);

			Rectangle rect {Point{200, 200}, 100, 50};
			myWindow.attach(rect);

			myWindow.set_label("Canvas #6");
			myWindow.wait_for_button();
		}

		{
			Axis xAxis {Axis::x, Point{20,300}, 280, 10, "x axis"};
			Axis yAxis {Axis::y, Point{20,300}, 280, 10, "y axis"};
			yAxis.set_color(Color::cyan);

			Function sineFn {sin, 0, 100, Point{20,150},1000,50,50};
			sineFn.set_color(Color::dark_green);


			Polygon poly;
			poly.add(Point{300, 200});
			poly.add(Point{350, 100});
			poly.add(Point{400, 200});
			poly.set_color(Color::dark_magenta);
			poly.set_style(Line_style::dash);

			Rectangle rect {Point{200, 200}, 100, 50};

			Closed_polyline polyRect;
			polyRect.add(Point{100, 50});
			polyRect.add(Point{200, 50});
			polyRect.add(Point{200, 100});
			polyRect.add(Point{100, 100});

			myWindow.attach(sineFn);
			myWindow.attach(xAxis);
			myWindow.attach(yAxis);
			myWindow.attach(polyRect);
			myWindow.attach(poly);
			myWindow.attach(rect);
			myWindow.set_label("Canvas #6.1");
			myWindow.wait_for_button();

			polyRect.add(Point{50, 75});
			myWindow.attach(sineFn);
			myWindow.attach(xAxis);
			myWindow.attach(yAxis);
			myWindow.attach(polyRect);
			myWindow.attach(poly);
			myWindow.attach(rect);

			myWindow.set_label("Canvas #6.2");
			myWindow.wait_for_button();
		}

		{
			Axis xAxis {Axis::x, Point{20,300}, 280, 10, "x axis"};
			Axis yAxis {Axis::y, Point{20,300}, 280, 10, "y axis"};
			yAxis.set_color(Color::cyan);

			Function sineFn {sin, 0, 100, Point{20,150},1000,50,50};
			sineFn.set_color(Color::blue);


			Polygon poly;
			poly.add(Point{300, 200});
			poly.add(Point{350, 100});
			poly.add(Point{400, 200});
			poly.set_color(Color::red);
			poly.set_style(Line_style(Line_style::dash,4));

			Rectangle rect {Point{200, 200}, 100, 50};
			rect.set_fill_color(Color::yellow);

			Closed_polyline polyRect;
			polyRect.add(Point{100, 50});
			polyRect.add(Point{200, 50});
			polyRect.add(Point{200, 100});
			polyRect.add(Point{100, 100});
			polyRect.add(Point{50, 75});
			polyRect.set_style(Line_style(Line_style::dash,2));
			polyRect.set_fill_color(Color::green);

			myWindow.attach(sineFn);
			myWindow.attach(xAxis);
			myWindow.attach(yAxis);
			myWindow.attach(polyRect);
			myWindow.attach(poly);
			myWindow.attach(rect);
			myWindow.set_label("Canvas #7");
			myWindow.wait_for_button();
		}

		{
			Axis xAxis {Axis::x, Point{20,300}, 280, 10, "x axis"};
			Axis yAxis {Axis::y, Point{20,300}, 280, 10, "y axis"};
			yAxis.set_color(Color::cyan);

			Function sineFn {sin, 0, 100, Point{20,150},1000,50,50};
			sineFn.set_color(Color::blue);


			Polygon poly;
			poly.add(Point{300, 200});
			poly.add(Point{350, 100});
			poly.add(Point{400, 200});
			poly.set_color(Color::red);
			poly.set_style(Line_style(Line_style::dash,4));

			Rectangle rect {Point{200, 200}, 100, 50};
			rect.set_fill_color(Color::yellow);

			Closed_polyline polyRect;
			polyRect.add(Point{100, 50});
			polyRect.add(Point{200, 50});
			polyRect.add(Point{200, 100});
			polyRect.add(Point{100, 100});
			polyRect.add(Point{50, 75});
			polyRect.set_style(Line_style(Line_style::dash,2));
			polyRect.set_fill_color(Color::green);

			Text text{Point{150, 150}, "Hello graphics world!"};
			text.set_font(Graph_lib::Font::times_bold);
			text.set_font_size(20);

			myWindow.attach(text);
			myWindow.attach(sineFn);
			myWindow.attach(xAxis);
			myWindow.attach(yAxis);
			myWindow.attach(polyRect);
			myWindow.attach(poly);
			myWindow.attach(rect);
			myWindow.set_label("Canvas #9");
			myWindow.wait_for_button();
		}

		{
			Axis xAxis {Axis::x, Point{20,300}, 280, 10, "x axis"};
			Axis yAxis {Axis::y, Point{20,300}, 280, 10, "y axis"};
			yAxis.set_color(Color::cyan);

			Function sineFn {sin, 0, 100, Point{20,150},1000,50,50};
			sineFn.set_color(Color::blue);


			Polygon poly;
			poly.add(Point{300, 200});
			poly.add(Point{350, 100});
			poly.add(Point{400, 200});
			poly.set_color(Color::red);
			poly.set_style(Line_style(Line_style::dash,4));

			Rectangle rect {Point{200, 200}, 100, 50};
			rect.set_fill_color(Color::yellow);

			Closed_polyline polyRect;
			polyRect.add(Point{100, 50});
			polyRect.add(Point{200, 50});
			polyRect.add(Point{200, 100});
			polyRect.add(Point{100, 100});
			polyRect.add(Point{50, 75});
			polyRect.set_style(Line_style(Line_style::dash,2));
			polyRect.set_fill_color(Color::green);

			Text text{Point{150, 150}, "Hello graphics world!"};
			text.set_font(Graph_lib::Font::times_bold);
			text.set_font_size(20);

			Image img {Point{100, 50}, "./week01/badge.jpg", Suffix::jpg};

			myWindow.attach(img);
			myWindow.attach(text);
			myWindow.attach(sineFn);
			myWindow.attach(xAxis);
			myWindow.attach(yAxis);
			myWindow.attach(polyRect);
			myWindow.attach(poly);
			myWindow.attach(rect);
			myWindow.set_label("Canvas #10");
			myWindow.wait_for_button();

			img.move(100, 200);
			myWindow.attach(img);
			myWindow.attach(text);
			myWindow.attach(sineFn);
			myWindow.attach(xAxis);
			myWindow.attach(yAxis);
			myWindow.attach(polyRect);
			myWindow.attach(poly);
			myWindow.attach(rect);
			myWindow.set_label("Canvas #11");
			myWindow.wait_for_button();
		}

		{
			Axis xAxis {Axis::x, Point{20,300}, 280, 10, "x axis"};
			Axis yAxis {Axis::y, Point{20,300}, 280, 10, "y axis"};
			yAxis.set_color(Color::cyan);

			Function sineFn {sin, 0, 100, Point{20,150},1000,50,50};
			sineFn.set_color(Color::blue);


			Polygon poly;
			poly.add(Point{300, 200});
			poly.add(Point{350, 100});
			poly.add(Point{400, 200});
			poly.set_color(Color::red);
			poly.set_style(Line_style(Line_style::dash,4));

			Rectangle rect {Point{200, 200}, 100, 50};
			rect.set_fill_color(Color::yellow);

			Closed_polyline polyRect;
			polyRect.add(Point{100, 50});
			polyRect.add(Point{200, 50});
			polyRect.add(Point{200, 100});
			polyRect.add(Point{100, 100});
			polyRect.add(Point{50, 75});
			polyRect.set_style(Line_style(Line_style::dash,2));
			polyRect.set_fill_color(Color::green);

			Text text{Point{150, 150}, "Hello graphics world!"};
			text.set_font(Graph_lib::Font::times_bold);
			text.set_font_size(20);

			Image img {Point{100, 50}, "./week01/badge.jpg", Suffix::jpg};
			img.move(100, 200);
			img.set_mask(Point{40,40},200,150);

			Circle circle {Point{100, 200}, 50};
			Ellipse ellipse {Point{100, 200}, 75, 25};
			ellipse.set_color(Color::dark_red);
			Mark mark {Point{100, 200}, 'x'};

			*local_print(mem, 512, "sicisici", "screen size: ", x_max(), '*', y_max(), "; window size: ", myWindow.x_max(), '*', myWindow.y_max()) = 0;
			std::string str((const char*)mem);
			Text sizes {Point{100, 20}, str};

			myWindow.attach(circle);
			myWindow.attach(mark);
			myWindow.attach(ellipse);
			myWindow.attach(sizes);
			myWindow.attach(img);
			myWindow.attach(text);
			myWindow.attach(sineFn);
			myWindow.attach(xAxis);
			myWindow.attach(yAxis);
			myWindow.attach(polyRect);
			myWindow.attach(poly);
			myWindow.attach(rect);
			myWindow.set_label("Canvas #12");
			myWindow.wait_for_button();

		}

	}
	catch(std::exception& e) {
		return 1;
	}
	catch(...) {
		return 2;
	}

    return 0;
}