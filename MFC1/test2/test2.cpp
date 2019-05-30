// test2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
//#include <osgCal/>
#include <osgUtil/Optimizer>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
//#include <osg/GUI>

#include <istream>
#include <string>
#include <vector>
#include <math.h>

class AnimationEventHandler: public osgGA::GUIEventHandler
{
public:
	AnimationEventHandler(osgViewer::Viewer &vr):viewer(vr)
	{

	}

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
	{ 
		osg::ref_ptr<osg::AnimationPathCallback> animationPathCallback =
			new osg::AnimationPathCallback();

		osg::ref_ptr<osg::Group> group = dynamic_cast<osg::Group*>(viewer.getSceneData());
		animationPathCallback = dynamic_cast<osg::AnimationPathCallback*>(group->getChild(0)->getUpdateCallback());
		switch(ea.getEventType())
		{
		case osgGA::GUIEventAdapter::KEYDOWN:
			{
				if(ea.getKey() == 'p')
				{
					animationPathCallback->setPause(true);
					return true;
				}
				if(ea.getKey() == 's')
				{
					animationPathCallback->setPause(false);
					return true;
				}
				if(ea.getKey() == 'r')
				{
					animationPathCallback->reset();
					return true;
				}

			}
			break;

		default:
			break;
		}

		return false; 
	}


private:
	osgViewer::Viewer &viewer;

};



osg::ref_ptr<osg::AnimationPath> createAnimationPath(osg::Vec3 & center, float radius, float looptime)
{
	osg::ref_ptr<osg::AnimationPath> animationPath = new osg::AnimationPath();
	animationPath->setLoopMode( osg::AnimationPath::LOOP);

	int numPoint = 60;
	float yaw = 0.0f;
	float yaw_delta = 2.0f* osg::PI/((float)(numPoint -1.0f));
	float roll = osg::inDegrees(45.0f);
	float time = 0.0f;
	float time_delta = looptime/((float)numPoint);

	for(int i=0; i< numPoint; i++)
	{
		osg::Vec3 position(center + osg::Vec3(sinf(yaw)*radius, cosf(yaw)* radius, 0.0f));
		osg::Quat rotation(osg::Quat(roll, osg::Vec3(0.0,1.0,0.0)) * 
			osg::Quat(-(yaw + osg::inDegrees(90.0f)),osg::Vec3(0.0,0.0,1.0)));
		animationPath->insert(time, osg::AnimationPath::ControlPoint(position,rotation));
		yaw += yaw_delta;
		time += time_delta;


	}


	return animationPath.get();
}


int _tmain(int argc, _TCHAR* argv[])
{
	osgViewer::Viewer* viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	//osg::ref_ptr<osg::Node> robot =  osgDB::readNodeFile("OSGData/robot.osg");
	//root->addChild(robot);

	//std::vector<std::string> animationnames;
	//std::string fn("cal3d.cfg");
	//int animNum = -1;

	//osgCal::
	osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("OSGDate/cessna.osg");
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("OSGData/lz.osg");

	const osg::BoundingSphere& bs = cessna->getBound();
	osg::Vec3 position = bs.center() + osg::Vec3(0.0f, 0.0f, 200.0f);
	float size = 100.0f/bs.radius()*0.3f;


	osg::ref_ptr<osg::AnimationPath> animationPath = new osg::AnimationPath;
	animationPath = createAnimationPath(position, 200.0f, 10.0f);

	std::string fileName("animation.path");
	std::ofstream out(fileName.c_str());
	animationPath->write(out);



	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	mt->setDataVariance( osg::Object::STATIC);
	mt->setMatrix(osg::Matrix::translate(-bs.center())*
		osg::Matrix::scale(size,size,size)*
		osg::Matrix::rotate(osg::inDegrees(-180.0f),0.0f,0.0f,1.0f));
	mt->addChild(cessna.get());

	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	pat->setUpdateCallback(new osg::AnimationPathCallback(animationPath.get(), 0.0f, 1.0f));
	pat->addChild(mt.get());

	root->addChild(pat.get());


	root->addChild(node.get());
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root.get());


	viewer->setSceneData(root);

	viewer->addEventHandler(new AnimationEventHandler( *viewer ));
	viewer->realize();
	viewer->run();

	return 0;
}

