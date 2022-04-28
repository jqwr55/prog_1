#include <common.h>
#include <Simple_window.h>
#include <Graph.h>
#include <exception>
#include <string>

void MakeGrid(std::vector<Line*>& lines, Point topLeft, Point bottomRight, u32 xLineCount, u32 yLineCount) {

    lines.reserve(xLineCount * yLineCount);

    i32 sizeX = bottomRight.x - topLeft.x;
    i32 sizeY = bottomRight.y - topLeft.y;

    Point it = topLeft;
    i32 xStep = sizeX / xLineCount;
    for(u32 i = 0; i < xLineCount; i++) {
        lines.push_back( new Line({it.x + i * xStep, it.y}, {it.x + i * xStep, it.y + sizeY}) );
    }
    i32 yStep = sizeY / yLineCount;
    for(u32 i = 0; i < yLineCount; i++) {
        lines.push_back( new Line({it.x, it.x + i * yStep}, {it.x + sizeX, it.y + i * yStep}) );
    }
}
void WindowExit (Fl_Widget* widget, void* user) {
    
    std::cout << "Exiting\n";
    exit(0);
}

i32 main(i32 argc, const char** argv) {

    try {

        i32 xmax = 800;
		i32 ymax = 1000;
		Simple_window myWindow{Point{100,100}, xmax, ymax, "Canvas"};
        myWindow.set_label("week02");
        myWindow.callback(WindowExit);

        std::vector<Line*> lines;
        MakeGrid(lines, {0, 0}, {800, 800}, 8, 8);
        for(auto i : lines) myWindow.attach(*i);

        std::vector<Rectangle*> redSquares;
        redSquares.reserve(8);

        for(u32 i = 0; i < 8; i++) {
            redSquares.push_back(new Rectangle{ {i*100, i * 100}, 100, 100});
            redSquares[i]->set_fill_color(Color::red);
            myWindow.attach(*redSquares[i]);
        }

        std::vector<Image*> frens;
        frens.reserve(4);
        frens.push_back(new Image{{0 ,600}, "./week02/fren.jpg", Suffix::jpg});
        frens.push_back(new Image{{0 ,200}, "./week02/fren.jpg", Suffix::jpg});
        frens.push_back(new Image{{400 ,100}, "./week02/fren.jpg", Suffix::jpg});
        frens.push_back(new Image{{0 ,0}, "./week02/serious_fren.jpg", Suffix::jpg});
        auto serious_fren = frens.back();

        for(auto i : frens) myWindow.attach(*i);

        std::cout << "Press the exit to exit\n";
        std::cout.flush();
        i32 px = 0;
        i32 py = 0;

        for(;;) {

		    myWindow.wait_for_button();

            i32 dx = 100;
            i32 dy = 0;

            if(px == 700 && py == 700) {
                dx = -700;
                dy = -700;
            }
            else if(px == 700) {
                dx = -700;
                dy = 100;
            }

            px += dx;
            py += dy;
            serious_fren->move(dx, dy);
        }
    }
    catch(std::exception& e) {
        std::cout << e.what() << '\n';
	    std::cout.flush();
		return 1;
	}
	catch(...) {
        std::cout << "uknown exception caught\n";
	    std::cout.flush();
		return 2;
	}

    std::cout.flush();
    return 0;
}