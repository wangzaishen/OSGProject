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

//using std::endl;
//typedef Float float;
//const Float M_PI = 3.14f;
/*
osg::ref_ptr<osg::Node> createSceneGraph()
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray(v.get());
	v->resize(0.1);
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
*/


/*

int _tmain(int argc, _TCHAR* argv[])
{
	osg::ref_ptr<osg::Group> group = new osg::Group;
	osg::ref_ptr<osg::Geode> geode0 = new osg::Geode;
	group->addChild( geode0.get() );
	osg::ref_ptr<osg::Geode> geode1 = new osg::Geode;
	group->addChild( geode1.get() );

	/*osg::Matrix T;
	T.makeTranslate(1.0f,0.f,0.f);
	osg::Matrix R;
	R.makeRotate( angle, axis);
	Vec3 vPrime = v*R*T;

	*/
/*	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
	osg::Matrix m;
	//m.setTranslate(x,y,z);
	m.set(1.0f,0.f,0.f,0.f
		0.0f,1.f,0.f,0.f
		0.0f,0.f,1.f,0.f
		10.0f,0.f,0.f,1.f	);
	mt->setMatrix(m);
*/
/*	osg::ref_ptr<osg::Node> root = createSceneGraph();
	if( !root.valid() )
	{
		osg::notify(osg::FATAL)<< "Failed create" << endl;
	}


	bool result = osgDB::writeNodeFile( *(root.get()), "Simple.osg");
	if(!result)
	{
		osg::notify(osg::FATAL) << "Failed write" << endl;
	}

	Float theta(M_PI * .5f);
	osg::Vec3 axis(.707f, .707f, 0.f);
	osg::Quat q0(theta, axis);

	osg::Vec3 yawAxis(0.f,0.f,1.f);
	osg::Vec3 pitchAxis(1.f,0.f,0.f);
	osg::Vec3 rollAxis(0.f,1.f,0.f);
	//osg::Quat q1(yawRad, yawAxis, pitchRad, pitchAxis, rollRad, rollAxis);

	//q0 *= q1;
	osg::ref_ptr<osg::Geode> geode;
	osg::ref_ptr<osg::LOD> lod = new osg::LOD;
	lod->addChild( geode.get(), 0.f, 1000.f);


	osg::ref_ptr<osg::Geode> geode0, geode1;
	osg::ref_ptr<osg::LOD> lod = new osg::LOD;
	lod->addChild(geode0.get(), 0.f, 1050.f);
	lod->addChild(geode1.get(), 950.f, 2000.f);

	osg::ref_ptr<osg::LOD> lod = new osg::LOD;
	lod->setCenterMode(osg::LOD::USER_DEFINED_CENTER);
	lod->setCenter( osg::Vec3(10.f, 100.f, 0.f));


	osg::ref_ptr<osg::Group> group0, group1;
	osg::ref_ptr<osg::Switch> switch0 = new osg::Switch;
	switch0->addChild( group1.get(), true);
	switch0->addChild( group1.get(), false);
	switch0->setNewChildDefaultValue( false );
	switch0->setChildValue( group0.get(), false);

	//osg::StateSet* state = obj->getOrCreateStateSet();
	//osg::StateSet *state = geom->getOrCreateStateSet();
	//osg::CullFace *cf = new osg::CullFace( osg::CullFace::BACK);
	//state->setAttribute( cf);

	//osg::StateSet* state = geom->getOrCreateStateSet();
	//state->setMode(GL_FOG, osg::StateAttribute::ON);

	//osg::BlendFunc* df = new osg::BlendFunc();
	//state->setAttributeAndModes(bf);
	//osg::StateSet* state = root->getOrCreateStateSet();
	//osg::PolygonMode *pm = new osg::PolgoneMode( osg::PolgonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	//state->setAttributeAndModes( pm, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);


	osgViewer::Viewer viewer;
	viewer.setSceneData( osgDB::readNodeFile("Simple.osg"));
	viewer.setUpViewInWindow(300, 100, 800, 600);


	return viewer.run();
}
*/
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