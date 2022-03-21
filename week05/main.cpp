#include <GUI.h>
#include <exception>
#include <string>

#include <common.h>

using namespace Graph_lib;

struct My_Lines_window : Graph_lib::Window {
		My_Lines_window(Point xy, int w, int h, const string& title);
	private:
		Open_polyline lines;

		Button next_button;
		Button quit_button;
		Button color_menu_button;
		Button style_menu_button;

		In_box next_x;
		In_box next_y;
		Out_box xy_out;

		Menu color_menu;
		Menu style_menu;

		void change_color(Color c) { lines.set_color(c); }
		void change_style(Line_style c) { lines.set_style(c); }

		void hide_color_menu() { color_menu.hide(); color_menu_button.show(); }
		void hide_style_menu() { style_menu.hide(); style_menu_button.show(); }

		void red_pressed() { change_color(Color::red); hide_color_menu(); }
		void blue_pressed() { change_color(Color::blue); hide_color_menu(); }
		void black_pressed() { change_color(Color::black); hide_color_menu(); }
		
		void solid_pressed() { change_style(Line_style::solid); hide_style_menu(); }
		void dash_pressed() { change_style(Line_style::dash); hide_style_menu(); }
		void dot_pressed() { change_style(Line_style::dot); hide_style_menu(); }

		void color_menu_pressed() { color_menu_button.hide(); color_menu.show(); }
		void style_menu_pressed() { style_menu_button.hide(); style_menu.show(); }

		void next() {
			int x = next_x.get_int();
			int y = next_y.get_int();

			lines.add(Point{x,y});

			ostringstream ss;
			ss << '(' << x << ',' << y << ')';
			xy_out.put(ss.str());

			redraw();
		}
		void quit() { hide(); }
};

My_Lines_window::My_Lines_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},

	next_button{Point{x_max() - 150,0}, 70, 20, "Next point", 
        [](Address, Address pw) {reference_to<My_Lines_window>(pw).next();}},
	quit_button{Point{x_max() - 70,0}, 70, 20, "Quit", 
	[](Address, Address pw) {reference_to<My_Lines_window>(pw).quit();}},

	next_x{Point{x_max() - 310,0}, 50, 20, "next x:"},
	next_y{Point{x_max() - 210,0}, 50, 20, "next y:"},
	xy_out{Point{100,0}, 100, 20, "current (x,y):"},

	color_menu{Point{x_max() - 70,30},70,20,Menu::vertical,"color"},
	color_menu_button{Point{x_max() - 80,30}, 80, 20, "color menu", 
		[](Address, Address pw) {reference_to<My_Lines_window>(pw).color_menu_pressed();}},

	style_menu{Point{x_max() - 150,30},70,20,Menu::vertical,"style"},
	style_menu_button{Point{x_max() - 160,30}, 80, 20, "style menu", 
		[](Address, Address pw) {reference_to<My_Lines_window>(pw).style_menu_pressed();}}
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no point");

	color_menu.attach(new Button{Point{0,0},0,0,"red",
		[](Address, Address pw) {reference_to<My_Lines_window>(pw).red_pressed();}});
	color_menu.attach(new Button{Point{0,0},0,0,"blue",
		[](Address, Address pw) {reference_to<My_Lines_window>(pw).blue_pressed();}});
	color_menu.attach(new Button{Point{0,0},0,0,"black",
		[](Address, Address pw) {reference_to<My_Lines_window>(pw).black_pressed();}});

	attach(color_menu);
	color_menu.hide();
	attach(color_menu_button);

	style_menu.attach(new Button{Point{0,0},0,0,"solid",
		[](Address, Address pw) {reference_to<My_Lines_window>(pw).solid_pressed();}});
	style_menu.attach(new Button{Point{0,0},0,0,"dash",
		[](Address, Address pw) {reference_to<My_Lines_window>(pw).dash_pressed();}});
	style_menu.attach(new Button{Point{0,0},0,0,"dot",
		[](Address, Address pw) {reference_to<My_Lines_window>(pw).dot_pressed();}});
	attach(style_menu);
	style_menu.hide();
	attach(style_menu_button);

	attach(lines);
}

i32 main(i32 argc, const char** argv) {

    try {
		My_Lines_window win{Point{100, 100}, 600, 400, "lines"};
		return gui_main();
	}
	catch(std::exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some exception\n";
		return 2;
	}

	return 0;
}