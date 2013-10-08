
#include "Config_State.h"

#include "Cheats.h"

using namespace Zeni;
using namespace std;

Config_State::Config_State(const std::pair<Point2f, Point2f> &virtual_window_, const bool &fix_aspect_ratio_, const int minRooms_, const float minDistance_) 
	: Widget_Gamestate(virtual_window_, fix_aspect_ratio_), minRooms(minRooms_), minDistance(minDistance_), maxRooms(50), maxDistance(20.f), currentRooms(minRooms_), currentDistance(minDistance_),
	create_button(Config_State::Create_Button(&currentRooms, &currentDistance)),
	room_size_slider(Config_State::Room_Size_Slider(Point2f(100, 200), Point2f(700, 200), &minRooms, &currentRooms, &maxRooms)),
	min_distance_slider(Config_State::Min_Distance_Slider(Point2f(100, 400), Point2f(700, 400), &minDistance, &currentDistance, &maxDistance)),
	vision_check_box(Boolean_Check_Box(Point2f(100, 550), Point2f(150, 600), &see_all)),
	life_check_box(Boolean_Check_Box(Point2f(375, 550), Point2f(425, 600), &no_die)),
	logic_check_box(Boolean_Check_Box(Point2f(650, 550), Point2f(700, 600), &always_use_enemy_logic))
{
	m_widgets.lend_Widget(back_button);
	m_widgets.lend_Widget(create_button);
	m_widgets.lend_Widget(room_size_slider);
	m_widgets.lend_Widget(min_distance_slider);
	m_widgets.lend_Widget(vision_check_box);
	m_widgets.lend_Widget(life_check_box);
	m_widgets.lend_Widget(logic_check_box);
}

void Config_State::render()
{
	Widget_Gamestate::render();

	Zeni::Font &headerfont = get_Fonts()["title"];
	Zeni::Font &detailfont = get_Fonts()["system_36_800x600"];

	//Header
	headerfont.render_text(
		"Dungeon Configuration",
		Point2f(400.0f, 0),
		get_Colors()["title_text"],
		ZENI_CENTER);

	//minRoom slider
	detailfont.render_text("Minimum Number of Rooms: " + minRooms, 
							Point2f(400, 200-detailfont.get_text_height()), 
							get_Colors()["title_text"], 
							ZENI_CENTER);

	//minDistance slider
	detailfont.render_text("Minimum Distance of End from Start: " + (int)minDistance, 
		Point2f(400,400 - detailfont.get_text_height()), 
		get_Colors()["title_text"], 
		ZENI_CENTER);

	//Cheats header
	headerfont.render_text(
		"Cheats",
		Point2f(400, 500 - headerfont.get_text_height()),
		get_Colors()["title_text"],
		ZENI_CENTER
		);

	//Vision box label
	detailfont.render_text("Full Vision", 
		Point2f(125, 550 - detailfont.get_text_height()), 
		get_Colors()["title_text"], 
		ZENI_CENTER);

	//Life box label
	detailfont.render_text("No Death", 
		Point2f(400, 550 - detailfont.get_text_height()), 
		get_Colors()["title_text"], 
		ZENI_CENTER);

	//Logic box label
	detailfont.render_text("Smart Enemies", 
		Point2f(675, 550 - detailfont.get_text_height()), 
		get_Colors()["title_text"], 
		ZENI_CENTER);
}

//Create Button

Config_State::Create_Button::Create_Button(int* minRooms_, float* minDistance_) : Text_Button(Point2f(300., 650.f), Point2f(500, 750.f), "system_36_800x600", "Create Map"), minRooms(minRooms_), minDistance(minDistance_)
{
}

void Config_State::Create_Button::on_accept() {
	get_Game().pop_state();
	get_Game().push_state(Zeni::Gamestate(new Play_State(*minRooms, *minDistance)));
}

//Room_Size_Slider
Config_State::Room_Size_Slider::Room_Size_Slider(const Point2f &end_point_a_, const Point2f &end_point_b_, int* minRooms_, int* currentRooms_, int* maxRooms_) : Slider(end_point_a_, end_point_b_, 5, 0), minRooms(minRooms_), currentRooms(currentRooms_), maxRooms(maxRooms_)
{

}

void Config_State::Room_Size_Slider::on_mouse_button(const Point2i &pos, const bool &down)
{
	Slider::on_mouse_button(pos, down, 1);
	*currentRooms = (int)((*maxRooms - *minRooms) * get_slider_position()) + *minRooms;
}

void Config_State::Room_Size_Slider::on_mouse_motion(const Point2i &pos)
{
	Slider::on_mouse_motion(pos);
	*currentRooms = (int)((*maxRooms - *minRooms) * get_slider_position()) + *minRooms;
}

//Min_Distance_Slider
Config_State::Min_Distance_Slider::Min_Distance_Slider(const Point2f &end_point_a_, const Point2f &end_point_b_, float* minDistance_, float* currentDistance_, float* maxDistance_) : Slider(end_point_a_, end_point_b_, 5,0), minDistance(minDistance_), currentDistance(currentDistance_), maxDistance(maxDistance_)
{

}

void Config_State::Min_Distance_Slider::on_mouse_button(const Point2i &pos, const bool &down)
{
	Slider::on_mouse_button(pos, down, 1);
	*currentDistance = ((*maxDistance - *minDistance) * get_slider_position()) + *minDistance;
}

void Config_State::Min_Distance_Slider::on_mouse_motion(const Point2i &pos)
{
	Slider::on_mouse_motion(pos);
	*currentDistance = ((*maxDistance - *minDistance) * get_slider_position()) + *minDistance;
}
