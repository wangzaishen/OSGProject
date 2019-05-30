// terrain.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <osgViewer/Viewer>
#include <osg/LineSegment>
#include <osg/PositionAttitudeTransform>
#include <osgUtil/IntersectionVisitor>
#include <osgGA/DriveManipulator>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osgUtil/Optimizer>
#include "Person.h"

#include <osgGA/TrackballManipulator>
#include "TravelManipulator.h"
#include "Robot.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Person* person = new Person;
	//Robot* person = new Robot;
	osgViewer::Viewer viewer;// = new osgViewer::Viewer();
	osg::ref_ptr<osg::Group> root = new osg::Group;

	TravelManipulator* tra = new TravelManipulator;
	tra->setPerson( person );
	//tra->setRobot( person );
	tra->setViewer(viewer);
	viewer.setCameraManipulator(tra);

	////osg::ref_ptr<osg::Node> test_1004 = osgDB::readNodeFile("VerData/car/jiaoc002.ive");
	osg::ref_ptr<osg::Node> lz = osgDB::readNodeFile("OSGData/lz.osg");
	root->addChild(lz);

	osg::ref_ptr<osg::Group> B25 = new osg::Group;
	//B25->addChild(osgDB::readNodeFile("OSGData/robot.osg"));
	B25->addChild(person->createPerson());
	osg::ref_ptr<osg::MatrixTransform> scale = new osg::MatrixTransform;
	scale->setMatrix(osg::Matrix::scale(0.1, 0.1, 0.1) * osg::Matrix::translate(-10.0f, -250.0f, 99.0f));
	//scale->setMatrix(osg::Matrix::scale(0.1, 0.1, 0.1) * osg::Matrix::translate(0.0f, 0.0f, 10.0f));
	scale->addChild(B25.get());

	
	root->addChild(scale);
	//root->addChild(B25.get());
	////osg::ref_ptr<osg::Node> car = osgDB::readNodeFile("VerData/car/jiaoc30.ive");
	////osg::ref_ptr<osg::PositionAttitudeTransform> carPosition = new osg::PositionAttitudeTransform;
	////carPosition->addChild(car);
	////double carXPosition = -5;
	////double carYPosition = -5;

	////root->addChild(car);

	//osgUtil::Optimizer optimizer;
	//optimizer.optimize(root.get());
	//viewer.setCameraManipulator(new osgGA::TrackballManipulator);


	viewer.setSceneData(root);
	viewer.realize();
	viewer.run();


	return 0;
}

