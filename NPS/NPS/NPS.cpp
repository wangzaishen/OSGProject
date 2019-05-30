// NPS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <osg/Geode>

#include <osgDB/WriteFile>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osg/ShadeModel>
#include <osg/CullFace>
#include <osg/PolygonMode>
#include <osg/LineWidth>
#include <osg/Image>
#include <osg/Material>
#include <osgText/Font>
#include <osgText/Text>
#include <osg/NodeCallback>
#include <osgGA/TrackballManipulator>
#include <osg/Camera>
#include <osg/Group>
#include <vector>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/ref_ptr>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Texture2D>
#include <iostream>
#include <iostream>
#include <osg/Geometry>
#include <osg/BlendFunc>
#include <osg/Fog>
#include <osgGA/TrackballManipulator>


using std::endl;

osg::Geode* createPyramid()
{

	osg::Geode* pyramidGeode = new osg::Geode();
	osg::Geometry* pyramidGeometry = new osg::Geometry();

	pyramidGeode->addDrawable( pyramidGeometry);


	osg::Vec3Array* pyramidVertices = new osg::Vec3Array;
	pyramidVertices->push_back( osg::Vec3(0, 0, 0));
	pyramidVertices->push_back( osg::Vec3(10, 0, 0));
	pyramidVertices->push_back( osg::Vec3(10, 10, 0));
	pyramidVertices->push_back( osg::Vec3(0, 10, 0));
	pyramidVertices->push_back( osg::Vec3(1, 1, 10));

	pyramidGeometry->setVertexArray( pyramidVertices);

	osg::DrawElementsUInt* pyramidBase = 
		new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS, 0);
	pyramidBase->push_back(3);
	pyramidBase->push_back(2);
	pyramidBase->push_back(1);
	pyramidBase->push_back(0);

	pyramidGeometry->addPrimitiveSet( pyramidBase);

		osg::DrawElementsUInt* pyramidBase1 = 
		new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLES, 0);
	pyramidBase1->push_back(0);
	pyramidBase1->push_back(1);
	pyramidBase1->push_back(4);


	pyramidGeometry->addPrimitiveSet( pyramidBase1);

	osg::DrawElementsUInt* pyramidBase2 = 
		new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLES, 0);
	pyramidBase2->push_back(1);
	pyramidBase2->push_back(2);
	pyramidBase2->push_back(4);


	pyramidGeometry->addPrimitiveSet( pyramidBase2);




	osg::DrawElementsUInt* pyramidBase3 = 
		new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLES, 0);
	pyramidBase3->push_back(2);
	pyramidBase3->push_back(3);
	pyramidBase3->push_back(4);


	pyramidGeometry->addPrimitiveSet( pyramidBase3);


	osg::DrawElementsUInt* pyramidBase4 = 
		new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLES, 0);
	pyramidBase4->push_back(3);
	pyramidBase4->push_back(0);
	pyramidBase4->push_back(4);


	pyramidGeometry->addPrimitiveSet( pyramidBase4);

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

	osg::TemplateIndexArray 
		<unsigned int, osg::Array::UIntArrayType,5,5> *colorIndexArray;
	colorIndexArray = 
		new osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 5, 5>;
	colorIndexArray->push_back( 0 );
	colorIndexArray->push_back( 1 );
	colorIndexArray->push_back( 2 );
	colorIndexArray->push_back( 3 );
	colorIndexArray->push_back( 0 );

	pyramidGeometry->setColorArray( colors );
	//pyramidGeometry->setColorIndices( colorIndexArray);
	pyramidGeometry->setColorBinding( osg::Geometry::BIND_PER_VERTEX);

	osg::Vec2Array* texcoords = new osg::Vec2Array( 5);
	(*texcoords)[0].set( 0.00f, 0.0f);
	(*texcoords)[1].set( 0.25f, 0.0f);
	(*texcoords)[2].set( 0.50f, 0.0f);
	(*texcoords)[3].set( 0.75f, 0.0f);
	(*texcoords)[0].set( 0.50f, 0.0f);
	pyramidGeometry->setTexCoordArray( 0, texcoords);

	//osg::PositionAttitudeTransform* pyramidTwoXForm =
	//	new osg::PositionAttitudeTransform();

	//root->addChild(pyramidTwoXForm);
	//pyramidTwoXForm->addChild( pyramidGeode);


	//osg::Vec3 pyramidTwoPosition(15, 0, 0);
	//pyramidTwoXForm->setPosition(pyramidTwoPosition );


	return pyramidGeode;
}
void textureTest()
{
/*	osg::Geode* pyramidGeode = createPyramid();
	//root->addChild( pyramidGeode);

	osg::Texture2D* KLN89FaceTexture = new osg::Texture2D;
	KLN89FaceTexture->setDataVariance( osg::Object::DYNAMIC);


	osg::StateSet* stateOne = new osg::StateSet();
	stateOne->setTextureAttributeAndModes( 
		0,tex, osg::StateAttribute::ON);
	pyramidGeode->setStateSet( stateOne );








	osg::PositionAttitudeTransform* pyramidTwoXForm =
		new osg::PositionAttitudeTransform();


	//pyramidTwoXForm->addChild( pyramidGeode);
	osg::Vec3 basicShapesPosition(15, 0, 0);
	pyramidTwoXForm->setPosition(basicShapesPosition );


	//root->addChild(pyramidTwoXForm);
	//osg::Vec3 pyramidTwoPosition(15, 0, 0);


	//pyramidTwoXForm->addChild(basicShapesGeode);



	osg::StateSet* blendStateSet = new osg::StateSet();

	osg::TexEnv* blendTexEnv = new osg::TexEnv;
	blendTexEnv->setMode( osg::TexEnv::BLEND);
	blendStateSet->setTextureAttributeAndModes(0, KLN89FaceTexture, osg::StateAttribute::ON);

	blendStateSet->setTextureAttribute(0,blendTexEnv);
	//osg::StateSet* decalStateSet = new osg::StateSet();
	//root->setStateSet(blendStateSet);
	//unitSphereGeode->setStateSet();

	//blendTexEnv->setMode( osg::TexEnv::BLEND);
	//stateRootBlend->setAttribute(0, blendTexEnv, osg::StateAttribute::ON);
	//stateRootBlend->setAttributeAndModes(0, ocotilloTexture, osg::StateAttribute::ON);

	//stateFiveDustTexture->setTextureAttributeAndModes(0, dustTexture, osg::StateAttribute::ON);
//	std::string fileName("sun.png");
//	osg::ref_ptr<osg::Image> image = osgDB::readImageFile( fileName );
//	if(!image.valid())
//	{
//		osg::notify( osg::FATAL ) << "Unable to load data file Exiting." << std::endl;
//		return  NULL;
//	}

*/
}
/*
osg::ref_ptr<osg::Node> createPlane()
{
	//osg::ref_ptr<osg::Node> node = createGeodes();

}
*/
void wenli()
{
	osg::Box* unitCube = new osg::Box(osg::Vec3(0, 0, 0),1.0f);
	osg::ShapeDrawable* unitCubeDrawable = new osg::ShapeDrawable(unitCube);
	osg::Geode* basicShapesGeode = new osg::Geode();
	basicShapesGeode->addDrawable( unitCubeDrawable);
	//root->addChild(basicShapesGeode);

	//osg::StateSet* state = basicShapesGeode->getOrCreateStateSet();
	//state->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
	//state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN);

	osg::Image* image = osgDB::readImageFile("dog_left_eye.jpg");
	if(!image)
	{
	
		std::cout<< "Image File Fialed" << std::endl;
		//return -1;
	}
	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
	tex->setImage( image );

	osg::StateSet* state = new osg::StateSet();
	

	//tex->setUnRefImageDataAfterApply(true);
	state->setTextureAttributeAndModes(0, tex.get(),osg::StateAttribute::ON);
	basicShapesGeode->setStateSet( state );
	//osg::BlendFunc* fa

/*
	osg::StateSet *pState = new osg::StateSet;
	osg::Fog *fog = new osg::Fog;
	fog->setMode( osg::Fog::LINEAR);
	fog->setDensity( 0.01f);
	fog->setStart( 10.0f );
	fog->setEnd(30.0f);
	fog->setColor(osg::Vec4(1.f, 0.5f, 0.f, 0.5f));
	pState->setAttributeAndModes(fog, osg::StateAttribute::ON);
	root->setStateSet( pState);

	*/


	osg::Sphere* unitSphere = new osg::Sphere(osg::Vec3(0, 0,0), 1.0);
	osg::ShapeDrawable* unitSphereDrawable = new osg::ShapeDrawable(unitSphere);
	osg::PositionAttitudeTransform* sphereXForm =
		new osg::PositionAttitudeTransform();
	sphereXForm->setPosition( osg::Vec3(2.5, 0, 0));
	osg::Geode* unitSphereGeode = new osg::Geode();
	//root->addChild( sphereXForm );

	sphereXForm->addChild(unitSphereGeode);
	unitSphereGeode->addDrawable(unitSphereDrawable);
	osg::StateSet* blendStateSet = new osg::StateSet();

	osg::TexEnv* blendTexEnv = new osg::TexEnv;
	blendTexEnv->setMode( osg::TexEnv::BLEND);
	blendStateSet->setTextureAttributeAndModes(0, tex, osg::StateAttribute::ON);

	blendStateSet->setTextureAttribute(0,blendTexEnv);
	
	osg::StateSet* decalStateSet = new osg::StateSet();
	osg::TexEnv* decalTexEnv = new osg::TexEnv();
	decalTexEnv->setMode(osg::TexEnv::DECAL);
	decalStateSet->setTextureAttributeAndModes(
		0,tex, osg::StateAttribute::ON);
	decalStateSet->setTextureAttribute(0, decalTexEnv);


	//root->setStateSet(blendStateSet);
	unitSphereGeode->setStateSet( decalStateSet);

	//blendTexEnv->setMode( osg::TexEnv::BLEND);
	//stateRootBlend->setAttribute(0, blendTexEnv, osg::StateAttribute::ON);
	//stateRootBlend->setAttributeAndModes(0, ocotilloTexture, osg::StateAttribute::ON);
	




}




int _tmain(int argc, _TCHAR* argv[])
{

	osg::Group* root = new osg::Group();
	osg::Node* cessnaNode = osgDB::readNodeFile( "cessna.osg");
	
	osg::PositionAttitudeTransform* cowXform = 
		new osg::PositionAttitudeTransform();
	root->addChild( cowXform);

	osg::Node* cowNode = osgDB::readNodeFile("cow.osg");
	cowXform->addChild(cowNode);
	
	


	root->addChild( cessnaNode );
	root->addChild( cowXform );


	osg::Vec3 cowPosit(15, 0, 0);
	cowXform->setPosition(cowPosit);

	osg::Geode* HUDGeode = new osg::Geode();
	osgText::Text* textOne = new osgText::Text();

	osgText::Text* cowLable = new osgText::Text();
	osg::Projection* HUDProjectionmarix = new osg::Projection;

	//osgDB::FilePathList pathList = osgDB::getDateFilePathList();

	HUDProjectionmarix->setMatrix(osg::Matrix::ortho2D(0, 1034, 0, 768));
	osg::MatrixTransform* HUDModelViewMatrix = new osg::MatrixTransform;
	HUDModelViewMatrix->setMatrix(osg::Matrix::identity());

	HUDModelViewMatrix->setReferenceFrame( osg::Transform::ABSOLUTE_RF);

	root->addChild(HUDProjectionmarix);
	HUDProjectionmarix->addChild(HUDModelViewMatrix);

	HUDModelViewMatrix->addChild(HUDGeode);


	osg::Geometry* HUDBackgroundGeometry = new osg::Geometry;
	osg::Vec3Array* HUDbackgroundVertices = new osg::Vec3Array;
	HUDbackgroundVertices->push_back(osg::Vec3(0, 0, -1));
	HUDbackgroundVertices->push_back(osg::Vec3(1024, 0, -1));
	HUDbackgroundVertices->push_back(osg::Vec3(1024, 200, -1));
	HUDbackgroundVertices->push_back(osg::Vec3(0, 200, -1));


	HUDGeode->addDrawable(HUDBackgroundGeometry);

	osgViewer::Viewer viewer;
	viewer.setSceneData( root );
	//viewer.addCameraManipulator(new osgGA::TrackballManipulator);
	//viewer.realize();


	//while( !viewer.done() )
	//{
	//	viewer.frame();
	//}





	viewer.run();


	return 0;
}

