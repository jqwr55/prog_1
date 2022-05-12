#include "GUI.h"

using namespace Graph_lib;


struct Lines_window : Graph_lib::Window {
	Lines_window(Point xy, int w, int h, const string& title );
	bool wait_for_button();
private:
	Open_polyline lines;
	Menu color_menu;

	Button next_button;
	Button quit_button;
	Button menu_button;

	In_box next_x;
	In_box next_y;

	Out_box xy_out;

	void hide_menu();
	void next();
	void quit();
	void change(Color c);
	void red_pressed();
	void blue_pressed();
	void black_pressed();
	void menu_pressed();

	static void cb_red(Address, Address) {}
	static void cb_blue(Address, Address) {}
	static void cb_black(Address, Address) {}
	static void cb_menu(Address, Address) {}
	static void cb_next(Address, Address) {}
	static void cb_quit(Address, Address) {}
};