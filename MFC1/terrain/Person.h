#pragma once

#include <osgViewer/Viewer>
#include <osg/LineSegment>
#include <osg/PositionAttitudeTransform>
#include <osgUtil/IntersectionVisitor>
#include <osgGA/DriveManipulator>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osgUtil/Optimizer>
#include <osg/ShapeDrawable>
//#include <osg/Cl>

class Person
{
public:
	Person(void);
	~Person(void);
	osg::ref_ptr<osg::Group> createPerson();


public:
	osg::ref_ptr<osg::MatrixTransform> root_tr;
	osg::ref_ptr<osg::MatrixTransform> head_tr;
	osg::ref_ptr<osg::MatrixTransform> body_tr;
	osg::ref_ptr<osg::MatrixTransform> left_arm_tr;
	osg::ref_ptr<osg::MatrixTransform> right_arm_tr;
	osg::ref_ptr<osg::MatrixTransform> left_leg_tr;
	osg::ref_ptr<osg::MatrixTransform> right_leg_tr;

};

