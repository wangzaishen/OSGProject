// Bone.cpp : 定义控制台应用程序的入口点。
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
#include <osgAnimation/Skeleton>
#include <osgAnimation/RigGeometry>
#include <osgAnimation/BasicAnimationManager>
#include <osgAnimation/Bone>
#include <osg/Matrix>




int _tmain(int argc, _TCHAR* argv[])
{

	osgViewer::Viewer* viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;

	osg::ref_ptr<osgAnimation::Skeleton> sk = new osgAnimation::Skeleton;
	sk->setDefaultUpdateCallback();

	osg::ref_ptr<osgAnimation::Bone> bone = new osgAnimation::Bone;
	bone->setDefaultUpdateCallback();

	bone->setInvBindMatrixInSkeletonSpace(osg::Matrix::translate(-1,0,0));
	bone->setName("bone");
	sk->addChild(bone);

	osg::ref_ptr<osgAnimation::BasicAnimationManager> manager = 
		new osgAnimation::BasicAnimationManager;
	root->setUpdateCallback(manager.get());

	osgAnimation::Animation *anim = new osgAnimation::Animation;
	osgAnimation::QuatKeyframeContainer* keys = new osgAnimation::QuatKeyframeContainer;

	osg::Quat rotate1;
	rotate1.makeRotate(osg::PI_2, osg::Vec3(0,0,1));



	//root->addChild(node.get());
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root.get());


	viewer->setSceneData(root);

	//viewer->addEventHandler(new AnimationEventHandler( *viewer ));
	viewer->realize();
	viewer->run();
	return 0;
}

