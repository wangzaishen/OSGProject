// Mytest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/ref_ptr>
#include <osgDB/Registry>
#include <osgDB/WriteFile>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

using std::endl;

osg::ref_ptr<osg::Node> createSceneGraph()
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray(v.get());
	v->push_back(osg::Vec3(-1.f,0.f,-1.f));
	v->push_back(osg::Vec3(1.f,0.f,-1.f));
	v->push_back(osg::Vec3(-1.f,0.f,1.f));
	v->push_back(osg::Vec3(-1.f,0.f,1.f));


	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray( c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c->push_back(osg::Vec4(1.f,0.f,0.f,1.f));
	c->push_back(osg::Vec4(0.f,1.f,0.f,1.f));
	c->push_back(osg::Vec4(0.f,0.f,1.f,1.f));
	c->push_back(osg::Vec4(1.f,1.f,1.f,1.f));

	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back( osg::Vec3(0.f,-1.f,0.f));

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));


	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable( geom.get());


	return geode.get();
}

int _tmain(int argc, _TCHAR* argv[])
{
	osg::ref_ptr<osg::Node> root = createSceneGraph();
	if( !root.valid() )
	{
		osg::notify(osg::FATAL)<< "Failed create" << endl;
	}


	bool result = osgDB::writeNodeFile( *(root.get()), "Simple.osg");
	if(!result)
	{
		osg::notify(osg::FATAL) << "Failed write" << endl;
	}


	osgViewer::Viewer viewer;
	viewer.setSceneData( osgDB::readNodeFile("Simple.osg"));
	viewer.setUpViewInWindow(300, 100, 800, 600);


	return viewer.run();
}

/*
	#include <osgViewer/Viewer>
	#include <osgDB/ReadFile>
 
	int _tmain(int argc, char **argv)
	{
  		osg::ref_ptr<osg::LightSource> ls= new osg::LightSource(); 
   		osg::ref_ptr< osg::Light> lt = new osg::Light;  
    		lt->setLightNum(0);  
    		lt->setPosition(osg::Vec4(1.0, -1.0, -1.0, 0));  
    		lt->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));  
    		lt->setDiffuse(osg::Vec4(1.0, 1.0, 1.0, 1.0));  
    		osgViewer::Viewer viewer;
    		viewer.getCamera()->setClearColor(osg::Vec4(0,1,1,1));
    		viewer.setSceneData(osgDB::readNodeFile("glider.osg"));
    		viewer.setUpViewInWindow(300,100,800,600);
   		viewer.setLight(lt);
    		return	viewer.run();

	}
	*/