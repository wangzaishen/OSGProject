#include "StdAfx.h"
#include "Person.h"


Person::Person(void)
{

	root_tr = new osg::MatrixTransform;
	head_tr = new osg::MatrixTransform;
	body_tr = new osg::MatrixTransform;
	left_arm_tr = new osg::MatrixTransform;
	right_arm_tr = new osg::MatrixTransform;
	left_leg_tr = new osg::MatrixTransform;
	right_leg_tr = new osg::MatrixTransform;
}


Person::~Person(void)
{
}

osg::ref_ptr<osg::Group> Person::createPerson()
{
	//osg::ref_ptr<osg::Node> node = new osg::Node;
	osg::ref_ptr<osg::Group> group = new osg::Group;
	group->addChild(root_tr.get());

	osg::ref_ptr<osg::Geode> head = new osg::Geode;
	head_tr->addChild(head.get());

	osg::ref_ptr<osg::Geode> body = new osg::Geode;
	body_tr->addChild(body.get());

	osg::ref_ptr<osg::Geode> left_arm = new osg::Geode;
	left_arm_tr->addChild(left_arm.get());

	osg::ref_ptr<osg::Geode> right_arm = new osg::Geode;
	right_arm_tr->addChild(right_arm.get());

	osg::ref_ptr<osg::Geode> left_leg = new osg::Geode;
	left_leg_tr->addChild(left_leg.get());

	osg::ref_ptr<osg::Geode> right_leg = new osg::Geode;
	right_leg_tr->addChild(right_leg.get());

	root_tr->addChild(head_tr);
	root_tr->addChild(body_tr);
	root_tr->addChild(left_arm_tr);
	root_tr->addChild(right_arm_tr);
	root_tr->addChild(left_leg_tr);
	root_tr->addChild(right_leg_tr);


	osg::ref_ptr<osg::Sphere> head_sp = new osg::Sphere(osg::Vec3(0,0.0,20), 2);
	osg::ref_ptr<osg::ShapeDrawable> head_shape_drawable = new osg::ShapeDrawable(head_sp);
	head_shape_drawable->setColor(osg::Vec4(1,0,0,1));
	head->addDrawable(head_shape_drawable.get());


	osg::ref_ptr<osg::Sphere> eye1_sp = new osg::Sphere(osg::Vec3(-0.7,-1.7,21), 0.5);
	osg::ref_ptr<osg::ShapeDrawable> eye1_ShapeDrawable = new osg::ShapeDrawable(eye1_sp.get());
	eye1_ShapeDrawable->setColor(osg::Vec4(0,0,1,1));
	head->addDrawable(eye1_ShapeDrawable.get());
	osg::ref_ptr<osg::Sphere> eye2_sp = new osg::Sphere(osg::Vec3(0.7,-1.7,21), 0.5);
	osg::ref_ptr<osg::ShapeDrawable> eye2_ShapeDrawable = new osg::ShapeDrawable(eye2_sp.get());
	eye2_ShapeDrawable->setColor(osg::Vec4(0,0,1,1));
	head->addDrawable(eye2_ShapeDrawable.get());
	osg::ref_ptr<osg::Sphere> mouth_sp = new osg::Sphere(osg::Vec3(0,-1.7,20), 0.5);
	osg::ref_ptr<osg::ShapeDrawable> mouth_ShapeDrawable = new osg::ShapeDrawable(mouth_sp.get());
	mouth_ShapeDrawable->setColor(osg::Vec4(0,0,1,1));
	head->addDrawable(mouth_ShapeDrawable.get());
	//osg::ref_ptr<osg::Sphere> ear2_sp = new osg::Sphere(osg::Vec3(0,-1.7,20), 0.5);
	//osg::ref_ptr<osg::ShapeDrawable> ear2_ShapeDrawable = new osg::ShapeDrawable(ear2_sp.get());
	//ear2_ShapeDrawable->setColor(osg::Vec4(0,0,1,1));
	//head->addDrawable(ear2_ShapeDrawable.get());
	osg::ref_ptr<osg::Cylinder> head_cylinder = new osg::Cylinder(osg::Vec3(0,0,18),1,2);
	osg::ref_ptr<osg::ShapeDrawable> cylinderDrawable = new osg::ShapeDrawable(head_cylinder.get());
	cylinderDrawable->setColor(osg::Vec4(1,0,0,1));
	head->addDrawable(cylinderDrawable);

	osg::ref_ptr<osg::ShapeDrawable> body_shape = 
		new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f, 0.0f, 13.0f), 6.0f, 3.0f, 8.0f));
	body_shape->setColor(osg::Vec4(1,0,0,1));
	body->addDrawable(body_shape.get());

	osg::ref_ptr<osg::Cylinder> left_arm_shape = new osg::Cylinder(osg::Vec3(-4,0,14),1,6);
	osg::ref_ptr<osg::ShapeDrawable> left_arm_drawable = new osg::ShapeDrawable(left_arm_shape.get());
	left_arm_drawable->setColor(osg::Vec4(1,0,0,1));
	left_arm->addDrawable(left_arm_drawable);

	osg::ref_ptr<osg::Cylinder> right_arm_shape = new osg::Cylinder(osg::Vec3(4,0,14),1,6);
	osg::ref_ptr<osg::ShapeDrawable> right_arm_drawable = new osg::ShapeDrawable(right_arm_shape.get());
	right_arm_drawable->setColor(osg::Vec4(1,0,0,1));
	right_arm->addDrawable(right_arm_drawable);

	osg::ref_ptr<osg::Cylinder> left_leg_shape = new osg::Cylinder(osg::Vec3(-1.5,0,6),1,8);
	osg::ref_ptr<osg::ShapeDrawable> left_leg_drawable = new osg::ShapeDrawable(left_leg_shape.get());
	left_leg_drawable->setColor(osg::Vec4(1,0,0,1));
	left_leg->addDrawable(left_leg_drawable);

	osg::ref_ptr<osg::Cylinder> right_leg_shape = new osg::Cylinder(osg::Vec3(1.5,0,6),1,8);
	osg::ref_ptr<osg::ShapeDrawable> right_leg_drawable = new osg::ShapeDrawable(right_leg_shape.get());
	right_leg_drawable->setColor(osg::Vec4(1,0,0,1));
	right_leg->addDrawable(right_leg_drawable);

	root_tr->setMatrix(osg::Matrix::rotate(osg::PI_2,osg::Vec3(0,0,1)));
	return group.get();
}