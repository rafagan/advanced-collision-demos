/******************************************************************************
*
* COPYRIGHT Ráfagan S. de Abreu. ALL RIGHTS RESERVED.
*
* This software can be copied, stored and distributed without
* author's prior authorization. Just let him know and leave this header in this source code.
*
* This file was made available on https://github.com/rafagan/basic-2D-collision-demos/ and it is free
* to be restributed or used under Apache 2.0 license:
* http://www.apache.org/licenses/
*
******************************************************************************/

#include "collisions.h"

using namespace math;

bool math::pointBoxCollisionCheck(const Point *point, const BoundingBox *box) {
	auto left = point->x >= box->xy[0];
	auto right = point->x <= (box->xy[0] + box->wh[0]);
	auto bottom = point->y >= box->xy[1];
	auto top = point->y <= (box->xy[1] + box->wh[1]);

	return (left && right && top && bottom);
}

bool math::AABBCollisionCheck(const BoundingBox *box, const BoundingBox *other){
	if(box->left() > other->right())
		return false;
	if(box->right() < other->left())
		return false;
	if(box->bottom() > other->top())
		return false;
	if (box->top() < other->bottom())
		return false;

	return true; 
}

bool math::AABBInnerCollisionCheck(const BoundingBox *box, const BoundingBox *other){
	if(box->right() > other->left() && box->left() < other->right())
		if(box->top() > other->bottom() && box->bottom() < other->top())
			return true;
	return false;
}

bool math::circleCollisionCheck(const BoundingCircle *circle, const BoundingCircle *other) {
	return distanceSqr(circle->position, other->position) < pow(circle->radius + other->radius, 2);
}

bool math::circleBoxCollisionCheck(const BoundingBox *box, const BoundingCircle *circle) {
	Point result;

	if(circle->xy[0] < box->left())
		result.x = box->left();
	else if(circle->xy[0] > box->right())
		result.x = box->right();
	else
		result.x = circle->xy[0];

	if(circle->xy[1] > box->top())
		result.y = box->top();
	else if(circle->xy[1] < box->bottom())
		result.y = box->bottom();
	else
		result.y = circle->xy[1];

	return distanceSqr(result, circle->position) < pow(circle->radius, 2);
}

bool math::AABBOffsetCollisionCheck(const BoundingBox *box, const BoundingBox *other) {
	auto offset = other->position - box->position;

	if(offset.x >= 0) {
		if(offset.x > box->wh[0])
			return false;
	} else if(-offset.x > other->wh[0])
		return false;

	if(offset.y >= 0) {
		if(offset.y > box->wh[1])
			return false;
	} else if(-offset.y > other->wh[1])
		return false;

	return true;
}