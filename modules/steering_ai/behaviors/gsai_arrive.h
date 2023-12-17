#ifndef GSAI_ARRIVE_H
#define GSAI_ARRIVE_H

/*************************************************************************/
/*  gsai_arrive.h                                                        */
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

#include "core/object/reference.h"

#include "../gsai_steering_behavior.h"

class GSAIAgentLocation;

class GSAIArrive : public GSAISteeringBehavior {
	GDCLASS(GSAIArrive, GSAISteeringBehavior);

public:
	Ref<GSAIAgentLocation> get_target();
	void set_target(const Ref<GSAIAgentLocation> &val);

	float get_arrival_tolerance() const;
	void set_arrival_tolerance(const float val);

	float get_deceleration_radius() const;
	void set_deceleration_radius(const float val);

	float get_time_to_reach() const;
	void set_time_to_reach(const float val);

	void arrive(const Ref<GSAITargetAcceleration> &acceleration, const Vector3 &target_position);
	virtual void _arrive(Ref<GSAITargetAcceleration> acceleration, Vector3 target_position);

	void _calculate_steering(Ref<GSAITargetAcceleration> acceleration);

	GSAIArrive();
	~GSAIArrive();

protected:
	static void _bind_methods();

	Ref<GSAIAgentLocation> target;
	float arrival_tolerance;
	float deceleration_radius;
	float time_to_reach;
};

#endif
