#include "Lines_window.h"

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    :Window{xy,w,h,title},
    next_button{Point{x_max()-300,0}, 150, 40, "Next point",
        [](Address, Address pw) {reference_to<Lines_window>(pw).next();}},

    quit_button{Point{x_max()-150,0}, 150, 40, "Quit",
        [](Address, Address pw) {reference_to<Lines_window>(pw).quit();}},

    next_x{Point{300,0}, 50, 40, "next x:"},
    next_y{Point{450,0}, 50, 40, "next y:"},
    xy_out{Point{100,0}, 100, 40, "current (x,y):"},
    color_menu{Point{x_max() - 70,40},  70, 20, Menu::vertical,"color", },
    menu_button{Point{x_max() - 80,30}, 80, 20, "color menu", cb_menu}
{
    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    xy_out.put("no point");
    color_menu.attach(new Button{Point{x_max()-70, 60}, 70, 20, "red",cb_red});
    color_menu.attach(new Button{Point{x_max()-70, 80}, 70, 20, "blue",cb_blue});
    color_menu.attach(new Button{Point{x_max()-70, 100}, 70, 20, "black",cb_black});
    
    attach(color_menu);
    color_menu.hide();

    attach(menu_button);
}

void Lines_window::quit() {
    hide();
}

void Lines_window::next()
{
    int x = next_x.get_int();
    int y = next_y.get_int();

    lines.add(Point{x,y});

    ostringstream ss;
    ss << '(' << x << ',' << y << ')';
    xy_out.put(ss.str());

    redraw();
}

void Lines_window::red_pressed() {
    change(Color::red);
}
void Lines_window::blue_pressed() {
    change(Color::blue);
}
void Lines_window::black_pressed() {
    change(Color::black);
}
void Lines_window::menu_pressed() {
    menu_button.hide();
    color_menu.show();
}
void Lines_window::change(Color c) {
    lines.set_color(c);
}
void Lines_window::hide_menu() {
    color_menu.hide();
    menu_button.show();
}