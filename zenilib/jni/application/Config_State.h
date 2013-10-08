//
//  Config_State.h
//  game
//
//  Created by Christopher Harris on 10/2/13.
//
//

#ifndef __game__Config_State__
#define __game__Config_State__

#include <iostream>
#include <zenilib.h>

#include "Play_State.h"

class Config_State : public Zeni::Widget_Gamestate
{
public:
	Config_State(const std::pair<Zeni::Point2f, Zeni::Point2f> &virtual_window_ = std::make_pair(Zeni::Point2f(0.f, 0.f), Zeni::Point2f(800., 800.f)), const bool &fix_aspect_ratio_ = true, const int minRooms_ = 9, const float minDistance_ = 4.f);

	void render();

private:
	int maxRooms;
	float maxDistance;

	int minRooms;
	float minDistance;

	int currentRooms;
	float currentDistance;

	friend class Create_Button;

	class Create_Button : public Zeni::Text_Button {
	public:
		Create_Button(int* minRooms_, float* minDistance_);
		void on_accept();
	private:
		int* minRooms;
		float* minDistance;

	};

	class Back_Button : public Zeni::Text_Button {
	public:
		Back_Button() : Zeni::Text_Button(Zeni::Point2f(25, 725), Zeni::Point2f(75,775), "system_36_800x600", "Back") 
		{
		}

		void on_accept() {
			Zeni::get_Game().pop_state();
		}

	} back_button;

	class Room_Size_Slider : public Zeni::Slider {
	public:
		Room_Size_Slider(const Zeni::Point2f &end_point_a_, const Zeni::Point2f &end_point_b_, int* minRooms_, int* currentRooms_, int* maxRooms_);

		void on_mouse_button(const Zeni::Point2i &pos, const bool &down);
		void on_mouse_motion(const Zeni::Point2i &pos);
	private:
		int* minRooms;
		int* currentRooms;
		int* maxRooms;
	};

	class Min_Distance_Slider : public Zeni::Slider {
	public:
		Min_Distance_Slider(const Zeni::Point2f &end_point_a_, const Zeni::Point2f &end_point_b_, float* minDistance_, float* currentRooms_, float* maxDistance_);

		void on_mouse_button(const Zeni::Point2i &pos, const bool &down);
		void on_mouse_motion(const Zeni::Point2i &pos);
	private:
		float* minDistance;
		float* currentDistance;
		float* maxDistance;
	};

	class Boolean_Check_Box : public Zeni::Check_Box {
	public:
		Boolean_Check_Box(const Zeni::Point2f &upper_left_, const Zeni::Point2f &lower_right_, bool* bool_) : Zeni::Check_Box(upper_left_, lower_right_, *bool_, true), boolean(bool_)
		{};

		void on_accept()
		{
			*boolean = !(*boolean);
			set_checked(*boolean);
		}
	private:
		bool* boolean;
	};

	Create_Button create_button;
	Room_Size_Slider room_size_slider;
	Min_Distance_Slider min_distance_slider;
	Boolean_Check_Box vision_check_box;
	Boolean_Check_Box life_check_box;
	Boolean_Check_Box logic_check_box;
};

#endif /* defined(__game__Door__) */
