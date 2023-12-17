#ifndef GSAI_KINEMATIC_BODY_2D_AGENT_H
#define GSAI_KINEMATIC_BODY_2D_AGENT_H

/*************************************************************************/
/*  gsai_kinematic_body_2d_agent.h                                       */
/*************************************************************************/
/*                         This file is part of:                         */
/*                          PANDEMONIUM ENGINE                           */
/*             https://github.com/Relintai/pandemonium_engine            */
/*************************************************************************/
/* Copyright (c) 2022-present Péter Magyar.                              */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "gsai_specialized_agent.h"

class KinematicBody2D;
class GSAITargetAcceleration;

class GSAIKinematicBody2DAgent : public GSAISpecializedAgent {
	GDCLASS(GSAIKinematicBody2DAgent, GSAISpecializedAgent);

public:
	KinematicBody2D *get_body();
	void set_body(KinematicBody2D *p_body);
	void set_body_bind(Node *p_body);

	int get_movement_type() const;
	void set_movement_type(const int val);

	enum MovementType {
		SLIDE,
		COLLIDE,
		POSITION
	};

	void _physics_process_connect();
	void _physics_process_disconnect();

	void _apply_steering(Ref<GSAITargetAcceleration> acceleration, float delta);

	void _apply_sliding_steering(KinematicBody2D *body, const Vector3 &accel, const float delta);
	void _apply_collide_steering(KinematicBody2D *body, const Vector3 &accel, const float delta);
	void _apply_position_steering(KinematicBody2D *body, const Vector3 &accel, const float delta);
	void _apply_orientation_steering(KinematicBody2D *body, const float angular_acceleration, const float delta);

	void _on_SceneTree_physics_frame();

	GSAIKinematicBody2DAgent();
	~GSAIKinematicBody2DAgent();

protected:
	static void _bind_methods();

	int movement_type;
	Vector2 _last_position;
	ObjectID _body_ref;
};

VARIANT_ENUM_CAST(GSAIKinematicBody2DAgent::MovementType);

#endif
