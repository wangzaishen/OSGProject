// anima.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
//#include <osgCal/>
#include <osgUtil/Optimizer>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/Sequence>
#include <osg/ArgumentParser>
#include <osgSim/OverlayNode>
#include <istream>
#include <string>
#include <vector>
#include <math.h>


osg::Node* createBase(const osg::Vec3& center, float radius)
{

	osg::Geode* geode = new osg::Geode;
	return geode;
}

osg::Node* createMovingModel(const osg::Vec3& center, float radius)
{
	osg::Group* model = new osg::Group;


	return model;
}

osg::Node* createModel(bool overlay, osgSim::OverlayNode::OverlayTechnique technique)
{
	osg::Vec3 center(0.0f, 0.0f, 0.0f);
	float radius = 100.0f;
	osg::Group* root = new osg::Group;

	float baseHeight = center.z() - radius*0.5;
	osg::Node* baseModel = createBase(osg::Vec3(center.x(), center.y(), baseHeight), radius);
	osg::Node* movingModel = createMovingModel(center, radius* 0.8f);


	if(overlay)
	{
		osgSim::OverlayNode* overlayNode = new osgSim::OverlayNode(technique);
		overlayNode->setContinuousUpdate(true);
		overlayNode->setOverlaySubgraph(movingModel);
		overlayNode->setOverlayBaseHeight(baseHeight - 0.01);
		overlayNode->addChild(baseModel);
		root->addChild(overlayNode);
	}
	else
	{
		root->addChild(baseModel);
	}
	root->addChild(movingModel);

	return root;
}


int _tmain(int argc, char* argv[])
{

	osgViewer::Viewer* viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;

	bool overlay = false;
	osg::ArgumentParser arguments(&argc, argv);
	while(arguments.read("--overlay"))
	{
		overlay = true;
	}
	osgSim::OverlayNode::OverlayTechnique technique = osgSim::OverlayNode::OBJECT_DEPENDENT_WITH_ORTHOGRAPHIC_OVERLAY;
	while(arguments.read("--object"))
	{
		technique = osgSim::OverlayNode::OBJECT_DEPENDENT_WITH_ORTHOGRAPHIC_OVERLAY;
		overlay = true;
	}
	while(arguments.read("ortho") || arguments.read("--orthographic"))
	{
		technique = osgSim::OverlayNode::VIEW_DEPENDENT_WITH_ORTHOGRAPHIC_OVERLAY;
		overlay = true;


	}
	while(arguments.read("--persp") || arguments.read("--perspective"))
	{
		technique = osgSim::OverlayNode::VIEW_DEPENDENT_WITH_PERSPECTIVE_OVERLAY;
		overlay = true;
	}

	osg::Node* model = createModel(overlay, technique);
	if(!model)
	{
		return 1;
	}






	//root->addChild(node.get());
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root.get());


	viewer->setSceneData(root);

	//viewer->addEventHandler(new AnimationEventHandler( *viewer ));
	viewer->realize();
	viewer->run();

	return 0;
}

