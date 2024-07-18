#include "main.h"

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

void disabled() {}
void competition_initialize() {}
void autonomous() {}

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor m_leftMotor{1};
	pros::Motor m_rightMotor{2};
	pros::ADIEncoder m_encoder{1, 2, true};

	double const kLeftGearRatio = 84.0/36.0;
	double const kEncoderResolution = 360.0;

	while (true) {
		int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		double num_rot = m_encoder.get_value() / kEncoderResolution / kLeftGearRatio;
		pros::lcd::print(1, "Num. Rotations: %.2f", num_rot);
		m_leftMotor.move(left);
		m_rightMotor.move(right);
		pros::delay(20);	// Run for 20 ms then update
	}
}