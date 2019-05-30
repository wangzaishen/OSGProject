// animation.cpp : 定义控制台应用程序的入口点。
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

#include <istream>
#include <string>
#include <vector>
#include <math.h>

class SequenceEventHandler:public osgGA::GUIEventHandler
{
public:
	SequenceEventHandler(osg::ref_ptr<osg::Sequence> seq)
	{
		_seq = seq;

	}

	virtual bool handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa)
	{
		osg::Sequence::SequenceMode mode = _seq->getMode();
		if(ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN)
		{
			switch(ea.getKey())
			{
			case 'p':
				{
					mode = osg::Sequence::PAUSE;
					_seq->setMode(mode);
				}
				break;
			case 's':
				{
					mode = osg::Sequence::START;
					_seq->setMode(mode);
				}
				break;
			case 'r':
				{
					mode = osg::Sequence::RESUME;
					_seq->setMode(mode);
				}

				break;
			case 't':
				{
					mode = osg::Sequence::STOP;
					_seq->setMode(mode);

				}
				break;
			default:
				break;
			}
		}

		return false;
	}

private:
	osg::ref_ptr<osg::Sequence> _seq;
};
osg::ref_ptr<osg::Node> createScaledNode(osg::ref_ptr<osg::Node> node, float targetScale)
{
	const osg::BoundingSphere & bsphere = node->getBound();
	float scale = targetScale /bsphere._radius;

	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	pat->setPosition(osg::Vec3(0.0f, 0.0f, 0.0f));
	pat->setScale(osg::Vec3(scale, scale, scale));
	pat->setDataVariance(osg::Object::DYNAMIC);
	pat->addChild(node.get());

	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
	stateset = pat->getOrCreateStateSet();
	stateset->setMode(GL_NORMALIZE, osg::StateAttribute::ON);

	return pat.get();
}

osg::ref_ptr<osg::Sequence> createSequence()
{
	osg::ref_ptr<osg::Sequence> seq = new osg::Sequence;
	typedef std::vector<std::string> Filenames;
	Filenames filenames;

	filenames.push_back("OSGData/cow.osg");
	filenames.push_back("OSGData/spaceship.osg");
	filenames.push_back("OSGData/dumptruck.osg");
	filenames.push_back("OSGData/cessna.osg");
	filenames.push_back("OSGData/glider.osg");

	for(Filenames::iterator itr = filenames.begin(); itr != filenames.end(); ++itr)
	{
		osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(*itr);

		if(node)
		{
			seq->addChild(createScaledNode(node, 100.0f));
			seq->setTime(seq->getNumChildren()-1, 1.0f);
		}
	}
	seq->setInterval(osg::Sequence::LOOP,0,-1);
	seq->setDuration(1.0f, -1);

	seq->setMode(osg::Sequence::START);

	return seq.get();
}





int _tmain(int argc, _TCHAR* argv[])
{
	osgViewer::Viewer* viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;

	//osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("OSGDate/cessna.osg");
	//osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("OSGData/lz.osg");

	osg::ref_ptr<osg::Sequence> sq = new osg::Sequence();
	sq = createSequence();
	root->addChild(sq.get());
	viewer->addEventHandler(new SequenceEventHandler(sq.get()));



	//root->addChild(node.get());
	osgUtil::Optimizer optimizer ;
	optimizer.optimize(root.get());


	viewer->setSceneData(root);

	//viewer->addEventHandler(new AnimationEventHandler( *viewer ));
	viewer->realize();
	viewer->run();

	return 0;
}

